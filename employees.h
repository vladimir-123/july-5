#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <string>
#include <random>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <queue>

// Часть I. Функционал по работе с данными.

// 1. Функция считывания данных из файла.
class TEmployee {
    size_t Id;
public:
    std::string Name;
    std::string Surname;
    std::string Position;
    std::string Department;
    double Salary;
    TEmployee();
    TEmployee(const std::string& name, const std::string& surname, const std::string& position, const std::string& department, const double& salary);
    size_t GetId() const;
    static size_t idCounter;
};

void Split(const std::string& line, char delimiter, std::vector<std::string>* columns);
std::unordered_map<size_t, TEmployee> ReadEmployees(const std::string& fileName);

// 2. Функции добавления/удаления сотрудников.
void DeleteEmployeeById(std::unordered_map<size_t, TEmployee>* EmpMap, size_t idToDel);
void AddEmployee(std::unordered_map<size_t, TEmployee>* EmpMap, const TEmployee& empToAdd);

// 3. Функция, генерирующая случайного сотрудника.
double GetMaxOrMinSalary(const std::unordered_map<size_t, TEmployee>& empMap, const bool maxSalary = true);

class TEmployeeGenerator {
    std::unordered_set<std::string> setOfNames;
    std::unordered_set<std::string> setOfSurnames;
    std::unordered_set<std::string> setOfPositions;
    std::unordered_set<std::string> setOfDepartments;
    size_t salaryRange;
    size_t salaryMin;
public:
    TEmployeeGenerator(const std::unordered_map<size_t, TEmployee>&);
    std::unordered_map<size_t, TEmployee> GenerateRandomEmployees(size_t);
};

// 4. Функция поиска сотрудников по должности и департаменту.
std::unordered_set<size_t> GetIdByDepartmentAndPosition(const std::unordered_map<size_t, TEmployee>& empMap,
            const std::string& firstParameter, const std::string& secondParameter = "");

// 5. Функция поиска по имени.
std::unordered_set<size_t> GetIdByNameAndSurname(const std::unordered_map<size_t, TEmployee>& empMap,
            const std::string& nameToFind, const std::string& SurnameToFind = "");

// 6. Фильтр по зарплате.
std::unordered_set<size_t>  GetIdBySalary(const std::unordered_map<size_t, TEmployee>& empMap, const double& max, const double& min = 0);

// 7. Сортировка множества сотрудников по зарплате.
bool ComparePairIDSalaryBySalaryGreater(const std::pair<size_t, double>& lhv, const std::pair<size_t, double>& rhv);

std::vector<std::pair<size_t, double>> GetIdBySalarySortedVector(const std::unordered_map<size_t, TEmployee>& empMap);

// 8. operator << д ля  TEmployee. 
std::ostream& operator<<(std::ostream& os, const TEmployee& empl);

// Часть II. Другие полезные функции.
// 1. Объединение/пересечение/разность двух множеств.
bool operator==(const TEmployee& lhv, const TEmployee& rhv);

std::unordered_set<size_t> GetIDIntersection(const std::unordered_set<size_t>& lhv,
                                                const std::unordered_set<size_t>& rhv);
std::unordered_set<size_t> GetIDUnity(std::unordered_set<size_t> lhv, // не по ссылке, поэтому и не конст
                                                const std::unordered_set<size_t>& rhv);
std::unordered_set<size_t> GetIDDifference(const std::unordered_set<size_t>& lhv,
                                                const std::unordered_set<size_t>& rhv);

// 2. operator << для произвольных векторов ( std :: vector) и пар ( std :: pair) .
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& pair) {
    os << pair.first << " : " << pair.second;
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& myVector) {
    for (typename std::vector<T>::iterator i = myVector.begin(); i != myVector.end(); ++i)
    {
        os << *i << " ";
    }  
    return os;
}

// Часть III. Аналитика данных.
// 1. Для каждого департамента посчитать минимальную и максимальную зарплату.
std::unordered_map<std::string, std::pair<double, double>> 
                        getDepartmentMinMaxSalary(const std::unordered_map<size_t, TEmployee>& empMap);

// 2. Для каждого департамента посчитать среднюю зарплату.
bool operator<(const std::pair<std::string, double>& lhv, const std::pair<std::string, double>& rhv);

std::vector<std::pair<std::string, double>> getDepartmentAverageSalary(const std::unordered_map<size_t, TEmployee>& empMap);

// 3. Для каждого департамента посчитать общие годовые траты.
std::priority_queue<std::pair<std::string, double>> getDepartentYearlyBudget(const std::unordered_map<size_t, TEmployee>& empMap);

// 4. Посчитать на каких должностях наибольшее число сотрудников.
bool ComparePairDepartmentStaffByStaffGreater(const std::pair<std::string, size_t>& lhv, const std::pair<std::string, size_t>& rhv);

bool ComparePairDepartmentStaffByStaffLess(const std::pair<std::string, size_t>& lhv, const std::pair<std::string, size_t>& rhv);

std::vector<std::pair<std::string, size_t>> getMostFrequentPositions(const std::unordered_map<size_t, TEmployee>& empMap, size_t numberOfEmployeesToReturn);

// 5. Вернуть м ножество фамилий самых высокооплачиваемых сотрудников указанного департамента.
bool myGreater(const std::pair<std::string, double>& lhv, const std::pair<std::string, double>& rhv);

std::unordered_map<std::string, double> getSurnamesMostHighlyPaidInDepartment(const std::unordered_map<size_t, TEmployee>& empMap,
                                                const std::string& departmentName, const size_t numberOfEmployeesToReturn);


























/* все работает
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// структура описывающая департамент
struct DepData {
    size_t employeesNumber;
    double salaryTotal;
};

// поиск
std::unordered_map<size_t, TEmployee> CreateMapByDepartmentAndPosition(const std::unordered_map<size_t, TEmployee>& empMap,
            const std::string& depToFind, const std::string& positionToFind = "");
std::unordered_map<size_t, TEmployee> ByNameAndSurnameMap(const std::unordered_map<size_t, TEmployee>& EmpMap,
            const std::string& nameToFind, const std::string& SurnameToFind = "");
std::unordered_map<size_t, TEmployee> BySalaryMap(const std::unordered_map<size_t, TEmployee>& EmpMap,
            const double max, const double min = 0);
std::unordered_set<size_t> getIdByDepartmentAndPosition(const std::unordered_map<size_t, TEmployee>& empMap,
            const std::string& firstParameter, const std::string& secondParameter = "");



// сортировать по з/п
bool CompareBySalary(const TEmployee& lhv, const TEmployee& rhv);

bool ComparePairBySalaryLess(const std::pair<size_t, double>& lhv,
            const std::pair<size_t, double>& rhv);


std::vector<std::pair<size_t, double>> SortBySalary(const std::unordered_map<size_t, TEmployee>& EmpMap);

// получить контейнер из структур описывающих департаменты
std::unordered_map<std::string, DepData> GetDepDateMap(const std::unordered_map<size_t, TEmployee>& EmpMap);
std::unordered_map<std::string, double> AvgByDep(const std::unordered_map<std::string, DepData>& departments);

// использование контернеров для каждой характеристики отдельно
std::unordered_map<std::string, double> DepartmentAndSalary(const std::unordered_map<size_t, TEmployee>& empMap);
std::unordered_map<std::string, double> DepartmentAndStaffNum(const std::unordered_map<size_t, TEmployee>& empMap);
std::unordered_map<std::string, double> DepartmentAndAvgSalary(const std::unordered_map<size_t, TEmployee>& empMap);
*/



