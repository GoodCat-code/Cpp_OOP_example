#include "Service.h"
#include "AbstrEmp.h"

void printArray(const std::vector<std::unique_ptr<abstr_emp>>& arr, std::ostream& os)
{
	for (const auto& ar : arr)
	{
		ar->ShowAll(os);
		std::cout << '\n';
	}
}

void saveToFile(abstr_emp& ae, std::fstream& fout)
{
	fout.clear();		// очистка флага конца файла
	fout.seekp(0, std::ios::end);		// установка чтения до конца файла
	enum classID { Employee, Manager, Fink, Highfink };
	int id = 0;
	if (employee* em = dynamic_cast<employee*>(&ae))
		id = Employee;
	else if (highfink* hf = dynamic_cast<highfink*>(&ae))
		id = Highfink;
	else if (manager* mn = dynamic_cast<manager*>(&ae))
		id = Manager;
	else if (fink* fn = dynamic_cast<fink*>(&ae))
		id = Fink;
	else std::cerr << "Badcast!";

	fout << id << '\t'; 
	ae.WriteAll(fout);
	fout << std::endl;
}

// TODO: заменить на getline() и vector, добавить enum для замены магических
void loadFromFileToArray(std::vector<std::unique_ptr<abstr_emp>>& arr, std::fstream& fin)
{
	fin.seekg(0);
	std::string str, fname, lname, job, reportsto;
	char ch, classtype;
	int inchargeof, counter = 0;
	while (fin.get(ch))		// чтение до конца файла по словам
	{
		if (counter == 0)		// считать тип работника
		{
			classtype = ch;
			counter++;
			fin.get(ch);		// удалить пустой символ
			continue;
		}

		if (ch != '\t' && ch != '\n')		// считать слово
			str += ch;
		else
		{		// запись полей типа из файла
			counter++;
			switch (counter)
			{
			case 2: fname = str; break;
			case 3: lname = str; break;
			case 4: job = str; break;
			case 5:
			{
				if (classtype == '1' || classtype == '3')
				{
					inchargeof = str[0] - '0';
					break;
				}
				if (classtype == '2')
				{
					while (ch != '\n')
						str += ch;
					reportsto = str;
				}
				break;
			}
			case 6:
			{
				while (ch != '\n')
					str += ch;
				reportsto = str;
			}
			break;
			default: break;
			}
			str = "";
		}
		if (ch == '\n' || fin.peek() == EOF)		// вывести данные в массив на основе типа
		{														// TODO (?): вынести в отдельную функцию
			switch (classtype)
			{
			case '0': arr.push_back(std::make_unique<employee>(fname, lname, job)); break;
			case '1': arr.push_back(std::make_unique<manager>(fname, lname, job, inchargeof)); break;
			case '2': arr.push_back(std::make_unique<fink>(fname, lname, job, reportsto)); break;
			case '3': arr.push_back(std::make_unique<highfink>(fname, lname, job, reportsto, inchargeof)); break;
			default: break;
			}
			counter = 0;
		}
	}
}

std::unique_ptr<abstr_emp> createEmployeeFromInput(int n)
{
	std::unique_ptr<abstr_emp> ptr;

	switch (n)
	{
	case 0: ptr = std::make_unique<employee>(); break;
	case 1: ptr = std::make_unique<manager>(); break;
	case 2: ptr = std::make_unique<fink>(); break;
	case 3: ptr = std::make_unique<highfink>(); break; 
	default: break;
	}
	ptr->SetAll();
	return ptr;
}