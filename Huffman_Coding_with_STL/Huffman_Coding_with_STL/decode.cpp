#include "functions.h"

void getFrequenciesForDecoding(std::array<size_t, SIZE_ARRAY_SYMBOL>& frequencies, std::istream& in); // ��������� ������ ��������
bool getFileNamesForDecoding(std::ifstream& in, std::ofstream& out); // ��������� ��� ������

void decode()
{
	// �������� �������� � ��������� ������
	std::ifstream fin;
	std::ofstream fout;
	if (!(getFileNamesForDecoding(fin, fout)))
	{
		return;
	}

	std::cout << "������� �������������...\n";
	auto startTime = std::chrono::steady_clock::now();

	// ���������� ������ �������� � �������� ������� � ����
	std::array<size_t, SIZE_ARRAY_SYMBOL> frequencies = { 0 };
	getFrequenciesForDecoding(frequencies, fin);

	// ���������� ������ ��������
	HuffmanTree decodingTree;
	decodingTree.assembleTree(frequencies);

	// ����� ��������������� ������ � ����
	decodingTree.outputDecodingData(fin, fout);

	// �������� �������� � ��������� ������
	fout.close();
	fin.close();

	auto endTime = std::chrono::steady_clock::now();

	StreamGuard guard(std::cout);
	std::cout << "������������� ������� ���������\n";
	std::cout << "��������������� ������ �������� � ����\n";
	std::cout << "����� �������������: " << std::fixed << std::setprecision(3)
		<< ((std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()) / 1000.0) << std::endl;
}

// ��������� ������ ��������
void getFrequenciesForDecoding(std::array<size_t, SIZE_ARRAY_SYMBOL>& frequencies, std::istream& in)
{
	size_t nSymbol = 0;
	unsigned char symbol = '\0';
	size_t frequence = 0;
	size_t sizeSymbol = sizeof(char);
	size_t sizeFrequence = sizeof(size_t);
	in.read(reinterpret_cast<char*>(&nSymbol), sizeFrequence);
	for (size_t i = 0; i < nSymbol; i++)
	{
		in.read(reinterpret_cast<char*>(&symbol), sizeSymbol);
		in.read(reinterpret_cast<char*>(&frequence), sizeFrequence);
		frequencies[symbol] = frequence;
	}
}

// ��������� ��� ������
bool getFileNamesForDecoding(std::ifstream& fin, std::ofstream& fout)
{
	// �������� �������� �����
	bool isFileOpen = false;
	std::string inOutFileName;
	char tempID[21] = "\0";

	std::cout << "\n��� ������ ������ �������� ������� ������� BACK";
	while (!isFileOpen)
	{
		std::cout << "\n������� �������� ����� � ��������������� �������: ";
		std::getline(std::cin, inOutFileName, '\n'); // encoded_data.txt
		if (inOutFileName == "BACK")
		{
			return false;
		}
		std::cout << "\n�������� ������� ����...";
		fin.open(inOutFileName, std::ifstream::binary);
		while (!fin.is_open())
		{
			std::cout << "\nERROR: �� ������� ������� ������ ����. ���������� �����\n";
			std::cout << "\n������� �������� ����� � ��������������� �������: ";
			std::getline(std::cin, inOutFileName, '\n');
			if (inOutFileName == "BACK")
			{
				return false;
			}
			fin.open(inOutFileName, std::ifstream::binary);
		}
		fin.read(tempID, strlen(ID));
		if (strcmp(tempID, ID) != 0)
		{
			std::cout << "\nERROR: ������ ���� �� �������� ��������������. ���������� �����\n";
			fin.close();
		}
		else
		{
			isFileOpen = true;
		}
	}

	std::cout << "\n������� ���� " << inOutFileName << " ������� ������\n";

	// �������� ��������� �����
	std::cout << "\n������� �������� ����� ��� ��������������� ������: ";
	std::getline(std::cin, inOutFileName, '\n'); // output_data.txt
	if (inOutFileName == "BACK")
	{
		return false;
	}
	std::cout << "\n�������� �������� ����...";
	fout.open(inOutFileName);
	std::cout << "\n�������� ���� " << inOutFileName << " ������� ������\n";

	return true;
}