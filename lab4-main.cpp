#include "employees.h"

int main(int argc, char const *argv[])
{
    std::unordered_map<size_t, TEmployee> employees = ReadEmployees("employees1.csv");
/*    // 2. Функции добавления/удаления сотрудников
    std::cout << "Add\n";
    TEmployee employeeToAdd("New", "New", "New", "New", 100);
    AddEmployee(&employees, employeeToAdd);
    for (const auto& x : employees) {
        std::cout << x << "\n";
    }
    
    std::cout << "\nDelete\n";
    DeleteEmployeeById(&employees, 13);
    for (const auto& x : employees) {
        std::cout << x << "\n";
    }
*/
    // 3. Функция, генерирующая случайного сотрудника.
    TEmployeeGenerator random(employees);
    std::unordered_map<size_t, TEmployee> newTEmployees = random.GenerateRandomEmployees(20);
    std::cout << "\nrandom\n";
    for (const auto& x : newTEmployees) {
        std::cout << x << "\n";
    }
    std::cout << "\n";

/*   // 4. Функция поиска сотрудников по должности и департаменту.
    std::unordered_set<size_t> employeesInDepartment = GetIdByDepartmentAndPosition(newTEmployees, "AVIATION");
    for (const auto& x : employeesInDepartment) {
        std::cout << x << "\n";
    }

    // 5. Функция поиска по имени.
    std::unordered_set<size_t>  employeesByName = GetIdByNameAndSurname(newTEmployees, "R");
    for (const auto& x : employeesByName) {
        std::cout << x << "\n";
    }
*/
 /*   // 6. Фильтр по зарплате.
    std::unordered_set<size_t> empBySalary = GetIdBySalary(newTEmployees, 200000);

    for (const auto& x : empBySalary) {
        std::cout << x << "\n";
    }
*/
    // 7. Сортировка множества сотрудников по зарплате.
/*
    std::vector<std::pair<size_t, double>> salaryVector = GetIdBySalarySortedVector(newTEmployees);

    for (std::vector<std::pair<size_t, double>>::iterator i = salaryVector.begin(); i != salaryVector.end(); ++i) {
        std::cout << *i << "\n";
    }
*/
    // Часть III. Аналитика данных.
    // 1. Для каждого департамента посчитать минимальную и максимальную зарплату.
/*    std::unordered_map<std::string, std::pair<double, double>> depMap= getDepartmentMinMaxSalary(newTEmployees);

    for (const auto& x : depMap) {
        std::cout << x << "\n";
    }
*/

    // 2. Для каждого департамента посчитать среднюю зарплату.
/*    std::vector<std::pair<std::string, double>> depMapAvrSal = getDepartmentAverageSalary(newTEmployees);

    for (const auto& x : depMapAvrSal) {
        std::cout << x << "\n";
    }
*/
    // 3. Для каждого департамента посчитать общие годовые траты.
/*    std::priority_queue<std::pair<std::string, double>> budgetQueue = getDepartentYearlyBudget(newTEmployees);
    while (!budgetQueue.empty()) {
        std::cout << budgetQueue.top() << "\n";
        budgetQueue.pop();
    }
*/
    // 4. Посчитать на каких должностях наибольшее число сотрудников.
/*    std::vector<std::pair<std::string, size_t>> positionFrV = getMostFrequentPositions(newTEmployees, 5);
    for (std::vector<std::pair<std::string, size_t>>::iterator i = positionFrV.begin(); i != positionFrV.end(); ++i) {
        std::cout << *i << "\n";
    }
*/
    // 5. Вернуть м ножество фамилий самых высокооплачиваемых сотрудников указанного департамента.
    std::unordered_map<std::string, double> higlyPaidEmp = getSurnamesMostHighlyPaidInDepartment(newTEmployees, "AVIATION", 5);
    for (const auto& x : higlyPaidEmp) {
        std::cout << x << "\n";
    }


    return 0;
}