#ifndef _HUFFMAN_TREE_H
#define _HUFFMAN_TREE_H
#include <iostream>
#include <queue>
#include <memory>
#include "CodeVector.h"

class HuffmanTree
{
public:
	HuffmanTree() : root_(nullptr), nSymbol_(0) {};
	HuffmanTree(const HuffmanTree& tree) = delete;
	HuffmanTree(HuffmanTree&& tree) = delete;
	~HuffmanTree() { root_ = nullptr; };

	HuffmanTree& operator=(const HuffmanTree& tree) = delete;
	HuffmanTree& operator=(HuffmanTree&& tree) = delete;

	void assembleTree(const size_t* frequencies, const unsigned int& size); // ���������� ������
	void getCodes(CodeVector* codes) const; // ��������� ������� ����� ��������
	void outputDecodingData(std::istream& in, std::ostream& out) const; // ����� ��������������� ������
	size_t getNumberSymbol() const { return nSymbol_; }; // �������� ���������� �������� � ��������

private:
	struct Node
	{
		size_t frequence_; // �������
		unsigned char symbol_; // ������
		std::shared_ptr<Node> left_;
		std::shared_ptr<Node> right_;

		// ������������ ����
		Node() : frequence_(0), symbol_(0), left_(nullptr), right_(nullptr) {};
		Node(size_t frequence, unsigned char symbol) :
			frequence_(frequence), symbol_(symbol), left_(nullptr), right_(nullptr) {};
	};

	struct HuffmanComparator
	{
		bool operator()(const std::shared_ptr<Node> node1, const std::shared_ptr<Node> node2) const
		{
			return node1->frequence_ > node2->frequence_;
		}
	};

	std::shared_ptr<Node> root_;
	unsigned int nSymbol_; // ���������� �������� � ��������

	void getCodes(CodeVector* codes, CodeVector& code, const std::shared_ptr<Node>& current) const; // ��������� ������� ����� ��������
};

#endif