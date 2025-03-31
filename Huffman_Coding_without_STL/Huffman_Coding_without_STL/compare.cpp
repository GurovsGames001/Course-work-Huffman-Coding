#include "functions.h"

bool getFileNamesForCompare(std::ifstream& fin1, std::ifstream& fin2); // ��������� ��� ������

void compare()
{
	// �������� ������
	std::ifstream fin1;
	std::ifstream fin2;

	if (!getFileNamesForCompare(fin1, fin2))
	{
		return;
	}

	// ��������� ������
	std::cout << "\n������� ��������� ������...\n";

	bool isEqual = true;
	char c1 = 0;
	char c2 = 0;
	while (!fin1.eof() && !fin2.eof() && isEqual)
	{
		c1 = fin1.get();
		c2 = fin2.get();
		if (c1 != c2)
		{
			isEqual = false;
		}
	}
	if (!fin1.eof() || !fin2.eof())
	{
		isEqual = false;
	}

	std::cout << "��������� ���������\n";
	if (isEqual)
	{
		std::cout << "����� ����� ���������� ������ ������\n";
	}
	else
	{
		std::cout << "����� ����� ������ ������ ������\n";
	}
}

// ��������� ��� ������
bool getFileNamesForCompare(std::ifstream& fin1, std::ifstream& fin2)
{
	// �������� ������� �����
	std::cout << "\n��� ������ ������ �������� ������� ������� BACK";
	std::cout << "\n������� �������� ������� �����: ";

	std::string fileName;
	std::getline(std::cin, fileName, '\n');
	if (fileName == "BACK")
	{
		return false;
	}
	fin1.open(fileName);

	while (!fin1.is_open())
	{
		std::cout << "\nERROR: �� ������� ������� ������ ����. ���������� �����";
		std::cout << "\n������� �������� ������� �����: ";
		std::getline(std::cin, fileName, '\n');
		if (fileName == "BACK")
		{
			return false;
		}
		fin1.open(fileName);
	}

	// �������� ������� �����
	std::cout << "\n������� �������� ������� �����: ";
	std::getline(std::cin, fileName, '\n');
	if (fileName == "BACK")
	{
		return false;
	}
	fin2.open(fileName);

	while (!fin2.is_open())
	{
		std::cout << "\nERROR: �� ������� ������� ������ ����. ���������� �����";
		std::cout << "\n������� �������� ������� �����: ";
		std::getline(std::cin, fileName, '\n');
		if (fileName == "BACK")
		{
			return false;
		}
		fin2.open(fileName);
	}

	return true;
}