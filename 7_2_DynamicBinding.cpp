#include<iostream>
#include<string>

class Employee
{
protected:
	std::string name;
	int age;
	std::string position;
	int rank;
public:
	Employee() {}
	Employee(std::string _name, int _age, std::string _pos, int _rank) : name(_name), age(_age), position(_pos), rank(_rank) {}
	Employee(const Employee& origin) : name(origin.name), age(origin.age), position(origin.position), rank(origin.rank) {}

	virtual int calculate_salary()
	{
		return 200 + rank * 50;
	}
	virtual void print_info()
	{
		std::cout << "(" << name << ", " << age << ") 직급 : " << position << " 월급 : "
			<< calculate_salary() << "만원" << std::endl;
	}
};
class Manager : public Employee
{
	int year_of_service;
public:
	Manager() {}
	Manager(std::string _name, int _age, std::string _pos, int _rank, int _year) : Employee(_name, _age, _pos, _rank),
		year_of_service(_year) {}
	Manager(const Manager& mgr) : Employee(mgr.name, mgr.age, mgr.position, mgr.rank), year_of_service(mgr.year_of_service) {}
	int calculate_salary() override
	{
		return 200 + 50 * rank + 5 * year_of_service;
	}
	void print_info() override
	{
		std::cout << name << " (" << position << ", " << age << ", " << year_of_service << "년차) 월급 : "
			<< calculate_salary() << "만원" << std::endl;
	}
};
class EmployeeList
{
	int alloc_num;
	int cur_empolyee_num;
	Employee** list;
public:
	EmployeeList(int _alloc) :alloc_num(_alloc)
	{
		list = new Employee * [alloc_num];
		cur_empolyee_num = 0;
	}
	~EmployeeList()
	{
		for (int i = 0; i < cur_empolyee_num; ++i)
		{
			delete list[i];
		}
		delete[] list;
	}
	void add_employee(Employee* employee)
	{
		if (cur_empolyee_num + 1 > alloc_num)
		{
			resize_list(alloc_num * 2);
		}
		list[cur_empolyee_num] = employee;
		++cur_empolyee_num;
	}
	void resize_list(int _alloc)
	{
		if (_alloc < cur_empolyee_num)
		{
			return;
		}
		alloc_num = _alloc;
		Employee** temp = list;
		list = new Employee * [alloc_num];
		for (int i = 0; i < cur_empolyee_num; ++i)
		{
			list[i] = temp[i];
		}
		delete[] temp;
	}
	int current_employee_num() const { return cur_empolyee_num; }

	void print_employee_info() const
	{
		int total_pay = 0;
		for (int i = 0; i < cur_empolyee_num; ++i)
		{
			list[i]->print_info();
			total_pay += list[i]->calculate_salary();
		}
		std::cout << "Total Pay: " << total_pay << "만원" << std::endl;
	}
};
int main(void)
{
	EmployeeList emp_list(10);
	emp_list.add_employee(new Employee("노홍철", 34, "평사원", 1));
	emp_list.add_employee(new Employee("하하", 34, "평사원", 1));

	emp_list.add_employee(new Manager("유재석", 41, "부장", 7, 12));
	emp_list.add_employee(new Manager("정준하", 43, "과장", 4, 15));
	emp_list.add_employee(new Manager("박명수", 43, "차장", 5, 13));

	emp_list.add_employee(new Employee("정형돈", 36, "대리", 2));
	emp_list.add_employee(new Employee("길", 36, "인턴", -2));
	emp_list.print_employee_info();
}