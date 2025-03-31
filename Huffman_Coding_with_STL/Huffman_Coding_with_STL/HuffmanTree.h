#ifndef _HUFFMAN_TREE_H
#define _HUFFMAN_TREE_H
#include <array>
#include <vector>
#include <memory>
#include <iostream>
#include <stack>
#include <queue>

class HuffmanTree
{
public:
	HuffmanTree() : root_(nullptr), nSymbol_(0) {};
	HuffmanTree(HuffmanTree& tree) = delete;
	~HuffmanTree() { root_ = nullptr; };

	void assembleTree(const std::array<size_t, 256>& frequencies); // ���������� ������
	void getCodes(std::array<std::vector<bool>, 256>& codes) const; // ��������� ������� ����� ��������
	void outputDecodingData(std::istream& in, std::ostream& out) const; // ����� ��������������� ������
	size_t getNumberSymbol() const { return nSymbol_; }; // �������� ���������� �������� � ��������

private:
	struct Node
	{
		using ptrNode = std::shared_ptr<Node>;
		using ptrParentNode = std::weak_ptr<Node>;

		size_t frequence_; // �������
		unsigned char symbol_; // ������
		ptrNode left_;
		ptrNode right_;
		ptrParentNode p_;

		// ������������ ����
		Node() : frequence_(0), symbol_(0), left_(nullptr), right_(nullptr), p_() {};
		Node(int frequence, char symbol) :
			frequence_(frequence), symbol_(symbol), left_(nullptr), right_(nullptr), p_() {};
	};

	struct HuffmanComparator
	{
		bool operator()(const std::shared_ptr<Node>& node1, const std::shared_ptr<Node>& node2) const
		{
			return node1->frequence_ > node2->frequence_;
		}
	};

	std::shared_ptr<Node> root_;
	size_t nSymbol_; // ���������� �������� � ��������

	void getCodes(std::array<std::vector<bool>, 256>& codes, std::vector<bool>& code, const std::shared_ptr<Node>& current) const; // ��������� ������� ����� ��������
};

#endif