#include "HuffmanTree.h"

// Построение дерева
void HuffmanTree::assembleTree(const size_t* frequencies, const unsigned int& size)
{
	std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, HuffmanComparator> queue;

	// Создание узлов
	for (unsigned int numberSymbol = 0; numberSymbol < size; numberSymbol++)
	{
		if (frequencies[numberSymbol] != 0)
		{
			std::shared_ptr<Node> node = std::make_shared<Node>(frequencies[numberSymbol], numberSymbol);
			queue.push(node);
		}
	}

	nSymbol_ = queue.size();

	// Построение дерева
	while (queue.size() != 1)
	{
		std::shared_ptr<Node> node = std::make_shared<Node>();

		node->left_ = queue.top();
		queue.pop();
		node->right_ = queue.top();
		queue.pop();

		node->frequence_ = node->left_->frequence_ + node->right_->frequence_;

		queue.push(node);
	}

	root_ = queue.top();
	queue.pop();
}

// Получение массива кодов символов
void HuffmanTree::getCodes(CodeVector* codes) const
{
	CodeVector code;

	getCodes(codes, code, root_);
}

// Получение массива кодов символов
void HuffmanTree::getCodes(CodeVector* codes, CodeVector& code, const std::shared_ptr<Node>& current) const
{
	if (current->left_ != nullptr)
	{
		code.push(0);
		getCodes(codes, code, current->left_);
	}
	if (current->right_ != nullptr)
	{
		code.push(1);
		getCodes(codes, code, current->right_);
	}
	if (current->symbol_)
	{
		codes[current->symbol_] = code;
	}
	if (!code.isEmpty())
	{
		code.pop();
	}
	else
	{
		return;
	}
}

// Вывод раскодированной строки
void HuffmanTree::outputDecodingData(std::istream& in, std::ostream& out) const
{
	std::shared_ptr<Node> currentNode = root_;
	unsigned char byte = 0;
	bool bit = 0;
	size_t countBit = 0;
	size_t nCurrentSymbol = 0;
	size_t nSymbolInText_ = root_->frequence_;

	byte = in.get();
	while (nCurrentSymbol < nSymbolInText_)
	{
		bit = byte & 1 << (7 - countBit);
		if (bit)
		{
			currentNode = currentNode->right_;
		}
		else
		{
			currentNode = currentNode->left_;
		}
		if (currentNode->symbol_)
		{
			out << currentNode->symbol_;
			nCurrentSymbol++;
			currentNode = root_;
		}
		countBit++;
		if (countBit == 8)
		{
			countBit = 0;
			byte = in.get();
		}
	}
}