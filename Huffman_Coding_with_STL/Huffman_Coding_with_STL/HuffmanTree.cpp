#include "HuffmanTree.h"

// Построение дерева
void HuffmanTree::assembleTree(const std::array<size_t, 256>& frequencies)
{
	std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, HuffmanComparator> queue;

	// Создание узлов
	size_t numberSymbol = 0;
	std::for_each(frequencies.begin(), frequencies.end(), 
		[&queue, &numberSymbol](const int& frequence)
		{
			if (frequence != 0)
			{
				std::shared_ptr<Node> node = std::make_shared<Node>(frequence, numberSymbol);
				queue.push(node);
			}
			numberSymbol++;
		});

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
		node->left_->p_ = node;
		node->right_->p_ = node;

		queue.push(node);
	}

	root_ = queue.top();
	queue.pop();
}

// Получение массива кодов символов
void HuffmanTree::getCodes(std::array<std::vector<bool>, 256>& codes) const
{
	std::vector<bool> code;
	std::stack<std::shared_ptr<Node>> parentStack;
	std::shared_ptr<Node> current = root_;

	getCodes(codes, code, current);
}

// Получение массива кодов символов
void HuffmanTree::getCodes(std::array<std::vector<bool>, 256>& codes, std::vector<bool>& code, const std::shared_ptr<Node>& current) const
{
	if (current->left_ != nullptr)
	{
		code.push_back(0);
		getCodes(codes, code, current->left_);
	}
	if (current->right_ != nullptr)
	{
		code.push_back(1);
		getCodes(codes, code, current->right_);
	}
	if (current->symbol_)
	{
		codes[current->symbol_] = code;
	}
	if (!code.empty())
	{
		code.pop_back();
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