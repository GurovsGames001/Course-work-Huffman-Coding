#include "functions.h"

void getFrequenciesForCoding(size_t* frequencies, std::istream& in); // ��������� ������ ��������
void outputEncodedData(const CodeVector* codes, std::istream& in, std::ostream& out); // ����� �������������� ������
bool getFileNamesForCoding(std::ifstream& in, std::ofstream& out); // ��������� ��� ������

void encode()
{
	// �������� �������� � ��������� ������
	std::ifstream fin;
	std::ofstream fout;
	if (!(getFileNamesForCoding(fin, fout)))
	{
		return;
	}

	std::cout << "������� �����������...\n";
	auto startTime = std::chrono::steady_clock::now();

	// ��������� ������ ��������
	size_t frequencies[SIZE_ARRAY_SYMBOL] = { 0 };
	getFrequenciesForCoding(frequencies, fin);

	// ���������� ������ ��������
	HuffmanTree codingTree;
	codingTree.assembleTree(frequencies, SIZE_ARRAY_SYMBOL);

	// ��������� ������� � ������ ��������
	CodeVector codes[SIZE_ARRAY_SYMBOL];
	codingTree.getCodes(codes);

	// ����� ������ ��� �������� �����
	fin.clear();
	fin.seekg(0, fin.beg);

	// ������ �������� � �� ������ � ����
	unsigned int nSymbol = codingTree.getNumberSymbol();
	unsigned int numberSymbol = 0;
	size_t sizeSymbol = sizeof(char);
	size_t sizeFrequence = sizeof(size_t); // ���������
	fout.write(ID, strlen(ID));
	fout.write(reinterpret_cast<char*>(&nSymbol), sizeof(unsigned int));
	for (size_t& frequence : frequencies)
	{
		if (frequence != 0)
		{
			fout.write(reinterpret_cast<char*>(&numberSymbol), sizeSymbol);
			fout.write(reinterpret_cast<char*>(&frequence), sizeFrequence);
		}
		numberSymbol++;
	}

	// ����� �������������� ������ � ����
	outputEncodedData(codes, fin, fout);

	// �������� �������� � ��������� ������
	fout.close();
	fin.close();

	auto endTime = std::chrono::steady_clock::now();

	StreamGuard guard(std::cout);
	std::cout << "����������� ������� ���������\n";
	std::cout << "�������������� ������ �������� � ����\n";
	std::cout << "����� �����������: " << std::fixed << std::setprecision(3)
		<< ((std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()) / 1000.0) << " c" << std::endl;
}

// ��������� ������ ��������
void getFrequenciesForCoding(size_t* frequencies, std::istream& in)
{
	unsigned char symbol = 0;
	while (!in.eof())
	{
		symbol = in.get();
		frequencies[symbol]++;
	}
	frequencies[symbol]--;
}

// ����� �������������� ������
void outputEncodedData(const CodeVector* codes, std::istream& in, std::ostream& out)
{
	unsigned int countBit = 0;
	unsigned char byte = 0;
	unsigned char symbol = 0;
	while (!in.eof())
	{
		symbol = in.get();
		CodeVector code = codes[symbol];
		for (unsigned int i = 0; i < code.size(); i++)
		{
			byte = byte | code[i] << (7 - countBit);
			countBit++;
			if (countBit == 8)
			{
				countBit = 0;
				out << byte;
				byte = 0;
			}
		}
	}
	if (countBit > 0)
	{
		out << byte;
	}
}

// ��������� ��� ������
bool getFileNamesForCoding(std::ifstream& fin, std::ofstream& fout)
{
	// �������� �������� �����
	std::cout << "\n��� ������ ������ �������� ������� ������� BACK";
	std::cout << "\n������� �������� ����� � ��������� �������: ";

	std::string inOutFileName;
	std::getline(std::cin, inOutFileName, '\n');
	if (inOutFileName == "BACK")
	{
		return false;
	}
	std::cout << "\n�������� ������� ����...";
	fin.open(inOutFileName);

	while (!fin.is_open())
	{
		std::cout << "\nERROR: �� ������� ������� ������ ����. ���������� �����";
		std::cout << "\n������� �������� ����� � ��������� �������: ";
		std::getline(std::cin, inOutFileName, '\n');
		if (inOutFileName == "BACK")
		{
			return false;
		}
		fin.open(inOutFileName);
	}
	std::cout << "\n������� ���� " << inOutFileName << " ������� ������\n";

	// �������� ��������� �����
	std::cout << "\n������� �������� ����� ��� �������������� ������: ";
	std::getline(std::cin, inOutFileName, '\n');
	if (inOutFileName == "BACK")
	{
		return false;
	}
	std::cout << "\n�������� �������� ����...";
	fout.open(inOutFileName, std::ofstream::binary);
	std::cout << "\n�������� ���� " << inOutFileName << " ������� ������\n";

	return true;
}