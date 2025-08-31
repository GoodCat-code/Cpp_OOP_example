#pragma once
#include <string>
#include <iostream>
#include <fstream>

class abstr_emp
{
private:
	std::string fname;			// ��� abstr_emp
	std::string lname;			// ������� abstr_emp
	std::string job;				// ������ abstr_emp
public:
	abstr_emp() {};
	abstr_emp(const std::string& fn, const std::string& ln, const std::string& j) : fname(fn), lname(ln), job(j) {};
	virtual void SetAll();				// ����������� �������� � ������������
	virtual void ShowAll(std::ostream& os) const;		// ������� ��� ������ � �������
	virtual void WriteAll(std::fstream& os) const;		// ������� ��� ������ � ����
	friend std::ostream& operator<< (std::ostream& os, const abstr_emp& �);			// ������� ������ ��� � �������
	virtual ~abstr_emp() = 0;		// �����������
};

class employee : public abstr_emp
{
public:
	employee() {};
	employee(const std::string& fn, const std::string& ln, const std::string& j) : abstr_emp(fn, ln, j) {};
};

class manager : virtual public abstr_emp
{
private:
	int inchargeof;			// ���������� ����������� abstr_emp
protected:
	int InChargeOf() const { return inchargeof; };			// �����
	int& InChargeOf() { return inchargeof; };					// �����
public:
	manager() : abstr_emp(), inchargeof(0) {};
	manager(const std::string& fn, const std::string& ln, const std::string& j, int ico = 0) : abstr_emp(fn, ln, j), inchargeof(ico) {};
	manager(const abstr_emp& e, int ico) : abstr_emp(e), inchargeof(ico) {};
	manager(const manager& m) : abstr_emp(m), inchargeof(m.inchargeof) {};
	void SetAll() override;
	void ShowAll(std::ostream& os) const override;
	void WriteAll(std::fstream& os) const override;
};

class fink : virtual public abstr_emp
{
private:
	std::string reportsto;		// ���� �������� ������
protected:
	const std::string ReportsTo() const { return reportsto; };
	std::string& ReportsTo() { return reportsto; }
public:
	fink() : abstr_emp() {};
	fink(const std::string& fn, const std::string& ln, const std::string& j, const std::string& rpo) 
		: abstr_emp(fn, ln, j), reportsto(rpo) {};
	fink(const abstr_emp& e, const std::string& rpo) : abstr_emp(e), reportsto(rpo) {};
	fink(const fink& e) : abstr_emp(e), reportsto(e.reportsto) {};
	void SetAll() override;
	void ShowAll(std::ostream& os) const override;
	void WriteAll(std::fstream& os) const override;
};

class highfink : public manager, public fink		// ������ �� ������������
{
public:
	highfink() : abstr_emp(), manager(), fink() {};
	highfink(const std::string& fn, const std::string& ln,
		const std::string& j, const std::string& rpo, int ico) : 
		abstr_emp(fn, ln, j), manager(fn, ln, j, ico), fink(fn, ln, j, rpo) {};
	highfink(const abstr_emp& e, const std::string& rpo, int ico) : abstr_emp(e), manager(e, ico), fink(e, rpo) {};
	highfink(const fink& f, int ico) : abstr_emp(f), manager(f, ico), fink(f) {};
	highfink(const manager& m, const std::string& rpo) : abstr_emp(m), manager(m), fink(m, rpo) {};
	highfink(const highfink& h) : abstr_emp(h), manager(h), fink(h){};
	void SetAll() override;
	void ShowAll(std::ostream& os) const override;
	void WriteAll(std::fstream& os) const override;
};

