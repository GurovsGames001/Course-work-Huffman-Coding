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
	std::cout << "\n������� ��������� ������\n";

	bool isEqual = true;

	isEqual = std::equal(std::istream_iterator<char>(fin1), std::istream_iterator<char>(), 
							std::istream_iterator<char>(fin2), std::istream_iterator<char>());

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