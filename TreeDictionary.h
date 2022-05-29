#pragma once

#include "iostream"
#include "string"

struct BTElem {
	std::string word;
	unsigned int frequency;
	int bal;
	BTElem *right, *left;
	BTElem(std::string word, unsigned int frequency = 1U, int bal = 0, BTElem *right = nullptr, BTElem *left = nullptr);
};

class TreeDictionary
{
private:
	BTElem* root;
	int size;
	void RRotation(BTElem *& pA, BTElem *& pB);
	void LRRotation(BTElem *& pA, BTElem *& pB);
	void LRotation(BTElem *& pA, BTElem *& pB);
	void RLRotation(BTElem *& pA, BTElem *& pB);
	bool balanceAddLeft(BTElem*& pA);
	bool balanceAddRight(BTElem*& pA);
	bool balanceDelLeft(BTElem *& pA);
	bool balanceDelRight(BTElem *& pA);
	bool deleteHelper(BTElem *& rootLeft, BTElem *& toDel);
	void copyTree(BTElem *root, BTElem *copy);
	void deleteTree(BTElem *root);
	unsigned int findWord(BTElem *root, std::string word);
	bool addWord(BTElem *& root, std::string& word);
	bool deleteWord(BTElem *& root, std::string& word);
	void printAsTable(std::ostream& os, BTElem* root);
	void printAsTree(std::ostream& os, BTElem* root, int i);
public:
	TreeDictionary();
	TreeDictionary(const TreeDictionary &copy);
	TreeDictionary(TreeDictionary &&move);
	~TreeDictionary();
	TreeDictionary& operator=(const TreeDictionary &copy);
	TreeDictionary& operator=(TreeDictionary &&move);
	unsigned int findWord(std::string word);
	void addWord(std::string word);
	void deleteWord(std::string word);
	unsigned int countWords();
	friend std::ostream& operator<< (std::ostream& os, TreeDictionary& obj);
};

