#include "employees.h"

using mapTEmployees = std::unordered_map<size_t, TEmployee>;
using vectorPairsIDSalary = std::vector<std::pair<size_t, double>>;
// using mapStringDepData = std::unordered_map<std::string, DepData>;
using StringToPairDoubleMap = std::unordered_map<std::string, std::pair<double, double>>;

size_t TEmployee::idCounter = 0; // уникальный айдишник

static const std::string error_name = "Error_TEmployee_Name";
static const std::string error_surname = "Error_TEmployee_Surname";
static const std::string error_position = "Error_TEmployee_Position";
static const std::string error_department = "Error_TEmployee_Department";
static const double INVALID_SALARY = -1;
static const bool theSmallestSalary = false;


// Часть I. Функционал по работе с данными.

// 1. Функция считывания данных из файла.

TEmployee::TEmployee():
            Name(error_name), Surname(error_surname),
            Position(error_position), Department(error_department),
            Salary(INVALID_SALARY) {}

// ID теперь гененрируется автоматически
TEmployee::TEmployee(const std::string& name, const std::string& surname, const std::string& position,
            const std::string& department, const double& salary):
            Name(name), Surname(surname), Position(position), Department(department), Salary(salary)
{
    ++TEmployee::idCounter; // изменяю айдишник
    Id = TEmployee::idCounter;
}

size_t TEmployee::GetId() const {
    return Id;
}

void Split(const std::string& line,
           char delimiter,
           std::vector<std::string>* columns)
{
    size_t begin = 0;
    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] == delimiter) {
            std::string word = line.substr(begin, i - begin);
            columns->push_back(word);
            ++i;
            begin = i;
        }
    }
    std::string word = line.substr(begin);
    columns->push_back(word);
}

mapTEmployees ReadEmployees(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    std::string line;
    mapTEmployees employees;

    std::getline(inputFile, line);

    while (std::getline(inputFile, line)) {
        //разделюя строку запятыми
        std::vector<std::string> columns;
        Split(line, ',', &columns);
        //убираю знак доллара
        columns[3] = columns[3].substr(1, columns[3].size() - 1);
        //отделяю имя от фамилии
        std::vector<std::string> subColumns;
        Split(columns[0], ';', &subColumns);
        //изменяю имя и фамилию
        subColumns[1].pop_back();
        subColumns[0] = subColumns[0].substr(1, subColumns[0].size() - 1);
        //создаю объект
        TEmployee emp(subColumns[1], subColumns[0], columns[1], columns[2], std::stod(columns[3]));
        employees[emp.GetId()] = emp;
    }
    return employees;
}

// 2. Функции добавления/удаления сотрудников.

void DeleteEmployeeById(mapTEmployees* empMap, size_t idToDel) {
    if (empMap->find(idToDel) != empMap->end()) {
        empMap->erase(idToDel);
    }
}

void AddEmployee(mapTEmployees* empMap, const TEmployee& empToAdd) {
    if (empMap->find(empToAdd.GetId()) == empMap->end()) {
        empMap->insert(std::make_pair(empToAdd.GetId(), empToAdd));
    }
}

// 3. Функция, генерирующая случайного сотрудника.

double GetMaxOrMinSalary(const mapTEmployees& empMap, const bool maxSalary) {
    double output = empMap.begin()->second.Salary;
    if (maxSalary) {
        for(const std::pair<size_t, TEmployee>& x : empMap) {
            output = std::max(output, x.second.Salary);
        }
    } else {
        for(const std::pair<size_t, TEmployee>& x : empMap) {
            output = std::min(output, x.second.Salary);
        }
    }
    return output;
}

TEmployeeGenerator::TEmployeeGenerator(const mapTEmployees& baseData) {
    for (const auto& x : baseData) {
        setOfNames.insert(x.second.Name);
        setOfSurnames.insert(x.second.Surname);
        setOfPositions.insert(x.second.Position);
        setOfDepartments.insert(x.second.Department);
    }
    salaryRange = GetMaxOrMinSalary(baseData) - GetMaxOrMinSalary(baseData, theSmallestSalary);
    salaryMin = GetMaxOrMinSalary(baseData, theSmallestSalary);
}

// если имена не уникальны то получиться, что-то вроде стратифицированной выборки

mapTEmployees TEmployeeGenerator::GenerateRandomEmployees(size_t randomEmployeesNumber) {
    mapTEmployees randomTEmployeesMap;
    std::random_device rd;

    for (size_t i = 0; i < randomEmployeesNumber; ++i) {
        std::string randomName = *std::next(setOfNames.begin(), rd() % setOfNames.size());
        std::string randomSurame = *std::next(setOfSurnames.begin(), rd() % setOfSurnames.size());
        std::string randomPosition = *std::next(setOfPositions.begin(), rd() % setOfPositions.size());
        std::string randomDepartment = *std::next(setOfDepartments.begin(), rd() % setOfDepartments.size());
        double randomSalary = rd() % salaryRange + salaryMin;

        TEmployee tempTEmployee (randomName, randomSurame, randomPosition, randomDepartment, randomSalary);
        AddEmployee(&randomTEmployeesMap, tempTEmployee);
    }
    return randomTEmployeesMap;
}

// 4. Функция поиска сотрудников по должности и департаменту.

std::unordered_set<size_t> GetIdByDepartmentAndPosition(const mapTEmployees& empMap,
            const std::string& firstParameter, const std::string& secondParameter) {
    std::unordered_set<size_t> output;
    if ("" == secondParameter) {
        for (const auto& x : empMap) {
            if (x.second.Position == firstParameter ||
                    x.second.Department == firstParameter) {
                output.insert(x.first);
            }
        }
    } else {
        for (const auto& x : empMap) {
            if ((x.second.Department == firstParameter && x.second.Position == secondParameter) ||
                    (x.second.Position == firstParameter && x.second.Department == secondParameter)) {
                output.insert(x.first);
            }
        }
    }
    return output;
}

// 5. Функция поиска по имени.

std::unordered_set<size_t> GetIdByNameAndSurname(const mapTEmployees& empMap,
            const std::string& nameToFind, const std::string& SurnameToFind) {
    std::unordered_set<size_t>  output;
    if ("" == SurnameToFind) {
        std::string tempName;
        std::string tempSurname;

        for (const auto& x : empMap) {
            tempName = x.second.Name.substr(0, nameToFind.size());
            tempSurname = x.second.Surname.substr(0, nameToFind.size());
            if (tempName == nameToFind || tempSurname == nameToFind) {
                output.insert(x.first);
            }
        }
    } else {
        for (const auto& x : empMap) {
            if (x.second.Name == nameToFind && x.second.Surname == SurnameToFind) {
                output.insert(x.first);
            }
        }
    }
    return output;
}

// 6. Фильтр по зарплате.

std::unordered_set<size_t>  GetIdBySalary(const mapTEmployees& empMap, const double& max, const double& min) {
    std::unordered_set<size_t>  output;
        for (const auto& x : empMap) {
            if (x.second.Salary <= max && x.second.Salary >= min) {
                output.insert(x.first);
            }
        }
    return output;
}

// 7. Сортировка множества сотрудников по зарплате.

bool ComparePairBySalaryGreater(const std::pair<size_t, double>& lhv,
            const std::pair<size_t, double>& rhv) {
    return (lhv.second > rhv.second);
}

vectorPairsIDSalary GetIdBySalarySortedVector(const mapTEmployees& empMap) {
    vectorPairsIDSalary VSalary;
    VSalary.reserve(empMap.size());
    std::pair<size_t, double> tempPair;

    for (const auto& x : empMap) {
        tempPair = std::make_pair(x.first, x.second.Salary);
        VSalary.push_back(tempPair);
    }
    std::sort(VSalary.begin(), VSalary.end(), ComparePairBySalaryGreater);
    return VSalary;
}

// 8. operator << д ля  TEmployee. 

std::ostream& operator<<(std::ostream& os, const TEmployee& empl) {
    os << empl.Name << " " << empl.Surname << ", "
       << empl.Department << ": " << empl.Position << " $" << empl.Salary << "; ID: " << empl.GetId();
   return os;
}

// Часть II. Другие полезные функции.

// 1. Объединение/пересечение/разность двух множеств.

bool operator==(const TEmployee& lhv, const TEmployee& rhv) {
    return (lhv.Name == rhv.Name) &&
            (lhv.Surname == rhv.Surname) &&
            (lhv.Position == rhv.Position) &&
            (lhv.Department == rhv.Department) && (lhv.Salary == rhv.Salary);
}

std::unordered_set<size_t> GetIDIntersection(const std::unordered_set<size_t>& lhv,
                                                const std::unordered_set<size_t>& rhv) {
    std::unordered_set<size_t> output;
    for (const auto& x : lhv) {
        if (rhv.find(x) != rhv.end()) {
            output.insert(x);
        }
    }
    return output;
}

std::unordered_set<size_t> GetIDUnity(std::unordered_set<size_t> lhv, //  не по ссылке, поэтому и не конст
                                                const std::unordered_set<size_t>& rhv) {
    for (const auto& x : rhv) {
        lhv.insert(x);
    }
    return lhv;
}

std::unordered_set<size_t> GetIDDifference(const std::unordered_set<size_t>& lhv,
                                                const std::unordered_set<size_t>& rhv) {
    std::unordered_set<size_t> intersection = GetIDIntersection(rhv, lhv);
    std::unordered_set<size_t> output = GetIDUnity(rhv, lhv);
    for (const auto& x : intersection) {
        output.erase(x);
    }
    return output;
}

// 2. operator << для произвольных векторов ( std :: vector) и пар ( std :: pair) .

// Часть III. Аналитика данных.

// 1. Для каждого департамента посчитать минимальную и максимальную зарплату.

StringToPairDoubleMap getDepartmentMinMaxSalary(const mapTEmployees& empMap) {
    StringToPairDoubleMap output;
    // сначала оба элемента пары инициализирую максимальным числом, ведь по умолчанию значение ноль
    // и если сравнивать его с минимальной зарплатой то ничего не выйдет
    for (const auto& x : empMap) {
        if (output[x.second.Department].second < x.second.Salary) {
            output[x.second.Department].first = output[x.second.Department].second = x.second.Salary;
        }
    }
    for (const auto& x : empMap) {
        if (output[x.second.Department].first > x.second.Salary) {
            output[x.second.Department].first = x.second.Salary;
        }
    }
    return output;
}

// 2. Для каждого департамента посчитать среднюю зарплату.

bool operator<(const std::pair<std::string, double>& lhv, const std::pair<std::string, double>& rhv) {
    return lhv.second < rhv.second;
}

std::vector<std::pair<std::string, double>> getDepartmentAverageSalary(const mapTEmployees& empMap) {
    std::unordered_map<std::string, std::pair<size_t, double>> departments;
    for (auto const& x : empMap) {
        ++departments[x.second.Department].first;
        departments[x.second.Department].second += x.second.Salary; 
    }
    std::vector<std::pair<std::string, double>> output;
    for (auto const& x : departments) {
        output.push_back(std::make_pair(x.first, x.second.second / x.second.first));
    }
    std::sort(output.begin(), output.end());
    return output;
}

// 3. Для каждого департамента посчитать общие годовые траты.

std::priority_queue<std::pair<std::string, double>> getDepartentYearlyBudget(const mapTEmployees& empMap) {
    std::unordered_map<std::string, double> departments;
    for (auto const& x : empMap) {
        departments[x.second.Department] += x.second.Salary;
    }
    std::priority_queue<std::pair<std::string, double>> output;
    for(const auto& x : departments) {
        output.push(x);
    }
    return output;
}

// 4. Посчитать на каких должностях наибольшее число сотрудников.

bool ComparePairDepartmentStaffByStaffLess(const std::pair<std::string, size_t>& lhv, const std::pair<std::string, size_t>& rhv) {
    return lhv.second < rhv.second;
}

bool ComparePairDepartmentStaffByStaffGreater(const std::pair<std::string, size_t>& lhv, const std::pair<std::string, size_t>& rhv) {
    return lhv.second > rhv.second;
}

std::vector<std::pair<std::string, size_t>> getMostFrequentPositions(const mapTEmployees& empMap, size_t numberOfEmployeesToReturn) {
    std::unordered_map<std::string, size_t> departments;
    for (auto const& x : empMap) {
        ++departments[x.second.Position];
    }
    
    std::vector<std::pair<std::string, size_t>> output;
    output.reserve(departments.size());
    for (const auto& x : departments) {
        output.emplace_back(x);
    }
    std::sort(output.begin(), output.end(), ComparePairDepartmentStaffByStaffGreater);
    if (numberOfEmployeesToReturn < output.size()) {
        output.resize(numberOfEmployeesToReturn);
    }
    return output;
}


// 5. Вернуть м ножество фамилий самых высокооплачиваемых сотрудников указанного департамента.

bool myGreater(const std::pair<std::string, double>& lhv, const std::pair<std::string, double>& rhv) {
    return lhv.second > rhv.second;
}

std::unordered_map<std::string, double> getSurnamesMostHighlyPaidInDepartment(const mapTEmployees& empMap,
                                                const std::string& departmentName, const size_t numberOfEmployeesToReturn) {
    std::vector<std::pair<std::string, double>> temp;
    for (const auto& x : empMap) {
        if (x.second.Department == departmentName) {
            temp.emplace_back(std::make_pair(x.second.Surname, x.second.Salary));
        }
    }
    std::sort(temp.begin(), temp.end(), myGreater);
    if (numberOfEmployeesToReturn < temp.size()) {
        temp.resize(numberOfEmployeesToReturn);
    }
    std::unordered_map<std::string, double> output;
    for(const auto& x : temp) {
        output.insert(x);
    }
    return output;
}


/*
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CompareBySalary(const TEmployee& lhv, const TEmployee& rhv) {
    return (lhv.Salary < rhv.Salary);
}

bool ComparePairBySalaryLess(const std::pair<size_t, double>& lhv,
            const std::pair<size_t, double>& rhv) {
    return (lhv.second < rhv.second);
}

mapTEmployees CreateMapByDepartmentAndPosition(const mapTEmployees& empMap,
            const std::string& depToFind, const std::string& positionToFind) {
    mapTEmployees output;
    if ("" == positionToFind) {
        for (const auto& x : empMap) {
            if (x.second.Department == depToFind) {
                output.insert(x);
            }
        }
    } else {
        for (const auto& x : empMap) {
            if (x.second.Department == depToFind && x.second.Position == positionToFind) {
                output.insert(x);
            }
        }
    }
    return output;
}

// департамент описывается штатом и бюджетом зп
mapStringDepData GetDepDateMap(const mapTEmployees& empMap) {
    mapStringDepData output;
    for (const auto& x : empMap) {
        ++output[x.second.Department].employeesNumber; // штат
        output[x.second.Department].salaryTotal += x.second.Salary; // бюджет
    }
    return output;
}

std::unordered_map<std::string, double> AvgByDep(const mapStringDepData& departments) {
    std::unordered_map<std::string, double> output;
    for (const auto& x : departments) {
        output[x.first] = x.second.salaryTotal/x.second.employeesNumber;
    }
    return output;
}

std::unordered_map<std::string, double> DepartmentAndSalary(const mapTEmployees& empMap) {
    std::unordered_map<std::string, double> output;
    for(const auto& x : empMap) {
        output[x.second.Department] += x.second.Salary;
    }
    return output;
}

std::unordered_map<std::string, double> DepartmentAndStaffNum(const mapTEmployees& empMap) {
    std::unordered_map<std::string, double> output;
    for(const auto& x : empMap) {
        ++output[x.second.Department];
    }
    return output;
}

std::unordered_map<std::string, double> DepartmentAndAvgSalary(const mapTEmployees& empMap) {
    std::unordered_map<std::string, double> output;
    std::unordered_map<std::string, double> depAndSal = DepartmentAndSalary(empMap);
    std::unordered_map<std::string, double> depAndStaff = DepartmentAndStaffNum(empMap);
    for(const auto& x : empMap) {
        output[x.second.Department] = depAndSal[x.second.Department] / depAndStaff[x.second.Department];
    }
    return output;
}

mapTEmployees ByNameAndSurnameMap(const mapTEmployees& empMap,
            const std::string& nameToFind, const std::string& SurnameToFind) {
    mapTEmployees output;
    if ("" == SurnameToFind) {
        std::string tempName;
        std::string tempSurname;

        for (const auto& x : empMap) {
            tempName = x.second.Name.substr(0, nameToFind.size());
            tempSurname = x.second.Surname.substr(0, nameToFind.size());
            if (tempName == nameToFind || tempSurname == nameToFind) {
                output.insert(x);
            }
        }
    } else {
        for (const auto& x : empMap) {
            if (x.second.Name == nameToFind && x.second.Surname == SurnameToFind) {
                output.insert(x);
            }
        }
    }
    return output;
}

mapTEmployees BySalaryMap(const mapTEmployees& empMap, const double& max, const double& min) {
    mapTEmployees output;
        for (const auto& x : empMap) {
            if (x.second.Salary <= max && x.second.Salary >= min) {
                output.insert(x);
            }
        }
    return output;
}
*/


