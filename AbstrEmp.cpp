#include "AbstrEmp.h"

void abstr_emp::ShowAll(std::ostream& os) const
{
	using std::endl;
	os << "Name: " << fname << "\nLast name: " << lname << "\nJob: " << job << endl;
}

void abstr_emp::WriteAll(std::fstream& os) const
{
	os << fname << "\t" << lname << "\t" << job;
}

void abstr_emp::SetAll()
{
	using std::cout;
	using std::cin;
	cout << "Enter name: ";
	getline(cin, fname);
	cout << "Enter last name: ";
	getline(cin, lname);
	cout << "Enter job: ";
	getline(cin, job);
}

abstr_emp::~abstr_emp() {}

std::ostream& operator<<(std::ostream& os, const abstr_emp& e)
{
	os << e.fname << "\t" << e.lname;
	return os;
}

void manager::ShowAll(std::ostream& os) const
{
	abstr_emp::ShowAll(os);
	os << "Charges number: " << inchargeof << std::endl;
}

void manager::WriteAll(std::fstream& os) const
{
	abstr_emp::WriteAll(os);
	os << '\t' << inchargeof;
}

void manager::SetAll()
{
	using std::cin;
	abstr_emp::SetAll();
	std::cout << "Enter charges number: ";
	cin >> inchargeof;
	cin.get();
}

void fink::ShowAll(std::ostream& os) const
{
	abstr_emp::ShowAll(os);
	os << "Report to: " << ReportsTo() << std::endl;
}

void fink::WriteAll(std::fstream& os) const
{
	abstr_emp::WriteAll(os);
	os << '\t' << reportsto;
}

void fink::SetAll()
{
	using std::cin;
	abstr_emp::SetAll();
	std::cout << "Enter name of reporter: ";
	getline(cin, reportsto);
}

void highfink::ShowAll(std::ostream& os) const
{
	manager::ShowAll(os);
	os << "Report to: " << highfink::ReportsTo() << std::endl;
}

void highfink::WriteAll(std::fstream& os) const
{
	manager::WriteAll(os);
	os << '\t' << highfink::ReportsTo();
}

void highfink::SetAll()
{
	using std::cin;
	manager::SetAll();
	std::cout << "Enter name of reporter: ";
	getline(std::cin, fink::ReportsTo());
}
