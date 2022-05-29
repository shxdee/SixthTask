#include "TreeDictionary.h"


BTElem::BTElem(std::string word, unsigned int frequency, int bal, BTElem * right, BTElem * left)
{
	this->word = word;
	this->bal = bal;
	this->frequency = frequency;
	this->right = right;
	this->left = left;
}

void TreeDictionary::RRotation(BTElem *& pA, BTElem *& pB)
{
	if (!pB->right || pA->right) {
		pB->bal = pA->bal = 0;
	}
	else {
		pB->bal = 1;
		pA->bal = -1;
	}
	pA->left = pB->right;
	pB->right = pA;
	pA = pB;
}

void TreeDictionary::LRRotation(BTElem *& pA, BTElem *& pB)
{
	BTElem* pC = pB->right;
	if (pC->bal > 0) {
		pA->bal = pC->bal = 0;
		pB->bal = -1;
	}
	else {
		if (pC->bal == 0) {
			pA->bal = pC->bal = pB->bal = 0;
		}
		else {
			pA->bal = 1;
			pB->bal = pC->bal = 0;
		}
	}
	pA->left = pC->right;
	pB->right = pC->left;
	pC->left = pB;
	pC->right = pA;
	pA = pC;
}

void TreeDictionary::LRotation(BTElem *& pA, BTElem *& pB)
{
	if (!pB->left || pA->left) {
		pB->bal = pA->bal = 0;
	}
	else {
		pA->bal = 1;
		pB->bal = -1;
	}
	pA->right = pB->left;
	pB->left = pA;
	pA = pB;
}

void TreeDictionary::RLRotation(BTElem *& pA, BTElem *& pB)
{
	BTElem* pC = pB->left;
	if (pC->bal > 0) {
		pB->bal = pC->bal = 0;
		pA->bal = -1;
	}
	else {
		if (pC->bal == 0) {
			pA->bal = pC->bal = pB->bal = 0;
		}
		else {
			pB->bal = 1;
			pA->bal = pC->bal = 0;
		}
	}
	pA->right = pC->left;
	pB->left = pC->right;
	pC->left = pA;
	pC->right = pB;
	pA = pC;
}

bool TreeDictionary::balanceAddLeft(BTElem *& pA)
{
	switch (pA->bal)
	{
	case 1:
		pA->bal = 0;
		return false;
	case 0:
		pA->bal = -1;
		return true;
	case -1:
		BTElem *pB = pA->left;
		if (pB->bal < 0) {
			RRotation(pA, pB);
			return false;
		}
		else {
			LRRotation(pA, pB);
			return false;
		}
	}
}

bool TreeDictionary::balanceAddRight(BTElem *& pA)
{
	switch (pA->bal)
	{
	case 0:
		pA->bal = 1;
		return true;
	case -1:
		pA->bal = 0;
		return false;
	case 1:
		BTElem *pB = pA->right;
		if (pB->bal < 0) {
			RLRotation(pA, pB);
			return false;
		}
		else {
			LRotation(pA, pB);
			return false;
		}
	}
}

bool TreeDictionary::balanceDelLeft(BTElem *& pA)
{
	switch (pA->bal)
	{
	case 0:
		pA->bal = 1;
		return false;
	case -1:
		pA->bal = 0;
		return true;
	case 1:
		BTElem *pB = pA->right;
		if (pB->bal < 0) {
			RLRotation(pA, pB);
			return true;
		}
		else {
			LRotation(pA, pB);
			if (pA->left->right) {
				return false;
			}
			return true;
		}
	}
}

bool TreeDictionary::balanceDelRight(BTElem *& pA)
{
	switch (pA->bal)
	{
	case 0:
		pA->bal = -1;
		return false;
	case 1:
		pA->bal = 0;
		return true;
	case -1:
		BTElem *pB = pA->left;
		if (pB->bal <= 0) {
			RRotation(pA, pB);
			if (pA->right->left) {
				return false;
			}
			return true;
		}
		else {
			LRRotation(pA, pB);
			return true;
		}
	}
}

bool TreeDictionary::deleteHelper(BTElem *& rootLeft, BTElem *& toDel)
{
	if (rootLeft->right) {
		if (deleteHelper(rootLeft->right, toDel)) {
			return balanceDelRight(rootLeft);
			
		}
		return false;
	}
	toDel->word = rootLeft->word;
	toDel = rootLeft;
	rootLeft = rootLeft->left;
	return true;
}

void TreeDictionary::copyTree(BTElem * root, BTElem * copy)
{
	if (!copy) {
		return;
	}
	root = new BTElem(copy->word, copy->bal, copy->frequency);
	copyTree(root->left, copy->left);
	copyTree(root->right, copy->right);
}

void TreeDictionary::deleteTree(BTElem * root)
{
	if (!root) {
		return;
	}
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}

unsigned int TreeDictionary::findWord(BTElem * root, std::string word)
{
	if (!root) { return 0; }
	if (root->word.compare(word) == 0) {
		return root->frequency;
	}
	if (root->word.compare(word) > 0) {
		return findWord(root->left, word);
	}
	if (root->word.compare(word) < 0) {
		return findWord(root->right, word);
	}
}

bool TreeDictionary::addWord(BTElem *& root, std::string &word)
{
	if (!root) {
		root = new BTElem(word);
		return true;
	}
	if (root->word.compare(word) == 0) {
		root->frequency++;
		return false;
	}
	if (root->word.compare(word) > 0) {
		if (addWord(root->left, word)) {
			return balanceAddLeft(root);
		}
		return false;
	}
	if (root->word.compare(word) < 0) {
		if (addWord(root->right, word)) {
			return balanceAddRight(root);
		}
		return false;
	}
	return false;
}

bool TreeDictionary::deleteWord(BTElem *& root, std::string& word)
{
	if (!root) {
		return false;
	}
	if (root->word.compare(word) > 0) {
		if (deleteWord(root->left, word)) {
			return balanceDelLeft(root);
		}
		return false;
	}
	if (root->word.compare(word) < 0) {
		if (deleteWord(root->right, word)) {
			return balanceDelRight(root);
		}
		return false;
	}
	BTElem* pDel = root;
	if (root->frequency > 1) {
		root->frequency--;
	}
	else {
		if (!root->right) {
			root = root->left;
			delete pDel;
			return true;
		}
		if (!root->left) {
			root = root->right;
			delete pDel;
			return true;
		}
		if (deleteHelper(root->left, pDel)) {
			delete pDel;
			return balanceDelLeft(root);
		}
		return false;
	}
}

void TreeDictionary::printAsTable(std::ostream & os, BTElem * root)
{
	if (!root) { return; }
	printAsTable(os, root->left);
	os << root->word << " - " << root->frequency << std::endl;
	printAsTable(os, root->right);
}

void TreeDictionary::printAsTree(std::ostream & os, BTElem * root, int ic)
{
	if (!root) {
		return;
	}
	for (int i = 0; i < ic; i++) {
		os << "\t";
	}
	os << root->word << " " << root->frequency << std::endl;
	printAsTree(os, root->left, ic + 1);
	printAsTree(os, root->right, ic + 1);
}

TreeDictionary::TreeDictionary()
{
	root = nullptr;
	size = 0;
}

TreeDictionary::TreeDictionary(const TreeDictionary & copy)
{
	copyTree(root, copy.root);
	size = copy.size;
}

TreeDictionary::TreeDictionary(TreeDictionary && move)
{
	size = move.size;
	std::swap(root, move.root);
}


TreeDictionary::~TreeDictionary()
{
	size = 0;
	deleteTree(root);
}

TreeDictionary & TreeDictionary::operator=(const TreeDictionary & copy)
{
	if (this == &copy) {
		return *this;
	}
	deleteTree(root);
	root = nullptr;
	size = copy.size;
	copyTree(root, copy.root);
}

TreeDictionary & TreeDictionary::operator=(TreeDictionary && move)
{
	size = move.size;
	std::swap(root, move.root);
	move.deleteTree(move.root);
	return *this;
}

unsigned int TreeDictionary::findWord(std::string word)
{
	return findWord(root, word);
}

void TreeDictionary::addWord(std::string word)
{
	size++;
	addWord(root, word);
}

void TreeDictionary::deleteWord(std::string word)
{
	size--;
	deleteWord(root, word);
}

unsigned int TreeDictionary::countWords()
{
	return size;
}

std::ostream& operator<< (std::ostream& os, TreeDictionary& obj)
{
	obj.printAsTable(os, obj.root);

	//obj.printAsTree(os, obj.root, 0);

	os << "\n";

	return os;
}
