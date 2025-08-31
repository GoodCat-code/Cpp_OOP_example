#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
class abstr_emp;

void printArray(const std::vector<std::unique_ptr<abstr_emp>>& arr, std::ostream& os);		// ������� ������ �� �����
void saveToFile(abstr_emp& ae, std::fstream& fout);		// ������� ������ � ����
void loadFromFileToArray(std::vector<std::unique_ptr<abstr_emp>>& arr, std::fstream& fin);		// ��������� �� ����� � ������
std::unique_ptr<abstr_emp> createEmployeeFromInput(int n);		// ������� ��������� �� ������ ����� ������
