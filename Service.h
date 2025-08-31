#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
class abstr_emp;

void printArray(const std::vector<std::unique_ptr<abstr_emp>>& arr, std::ostream& os);		// вывести массив на экран
void saveToFile(abstr_emp& ae, std::fstream& fout);		// вывести данные в файл
void loadFromFileToArray(std::vector<std::unique_ptr<abstr_emp>>& arr, std::fstream& fin);		// выгрузить из файла в массив
std::unique_ptr<abstr_emp> createEmployeeFromInput(int n);		// создать работника на основе ввода выбора
