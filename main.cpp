#include <iostream>
#include "AbstrEmp.h"
#include "Service.h"
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main()
{
	fstream fiout("output.txt", ios::in | ios::out | ios::ate);		// и чтение, и запись
	vector<unique_ptr<abstr_emp>> allArr;		// массив указателей на виртуальный базовый класс

	if (fiout.tellg() == 0)		// только первое открытие
	{
		fiout.seekg(0);
		employee em("Trip", "Harris", "Thumper");
		allArr.push_back(make_unique<employee>(em));
		manager ma("Amorphia", "Spindragon", "Nuancer", 5);
		allArr.push_back(make_unique<manager>(ma));
		fink fi("Matt", "Oggs", "Oiler", "Juno Barr");
		allArr.push_back(make_unique<fink>(fi));
		highfink hf(ma, "Curly Kew");
		allArr.push_back(make_unique<highfink>(hf));

		printArray(allArr, cout);		// вывести массив на экран

		for (auto &ar : allArr)		// вывести данные в файл
			saveToFile(*ar, fiout);

		fiout.close();
		return 1;
	}

	// если файл не пустой
	loadFromFileToArray(allArr, fiout);		// выгрузить из файла в массив 
	printArray(allArr, cout);		// вывести массив на экран

	cout << "0 for employee\n1 for manager\n2 for fink\n3 for highfink\nq for quit\nEnter worker: ";
	int n;

	// выбор типа и ввод данных работника с занесением в файл и массив
	while (cin >> n)
	{
		cin.get();
		unique_ptr<abstr_emp> ptr;
		ptr = createEmployeeFromInput(n);
		saveToFile(*ptr, fiout);
		allArr.push_back(std::move(ptr));
		cout << "0 for employee\n1 for manager\n2 for fink\n3 for highfink\nq for quit\nEnter worker: ";
	}

	printArray(allArr, cout);
	cout << "End!\n";

	fiout.close();
}
