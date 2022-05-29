#include "TreeDictionary.h"
using namespace std;

void main()
{
	TreeDictionary* tree = new TreeDictionary();
	tree->addWord("Hello");
	tree->addWord("KKKK");
	tree->addWord("AAAA");
	tree->addWord("AAAA");
	tree->addWord("JJJJ");
	tree->addWord("EEEE");
	tree->addWord("CCCC");
	tree->addWord("DDDD");
	tree->addWord("BBBB");
	tree->addWord("AAAA");
	tree->addWord("FFFF");
	tree->addWord("GGGG");
	tree->addWord("JJJJ");
	tree->addWord("CCCC");
	tree->addWord("JJJJ");
	tree->addWord("EEEE");
	tree->addWord("CCCC");
	tree->addWord("Idea");
	tree->addWord("AAAA");
	tree->addWord("AAAA");
	cout << *tree << endl;
	cout << endl;

	cout << "Amount of words:" << tree->countWords() << endl;
	cout << "Amount of AAAA :" << tree->findWord("AAAA") << endl;
	cout << "Amount of GGGG :" << tree->findWord("GGGG") << endl;
	cout << "Amount of World :" << tree->findWord("World") << endl;
	cout << endl;

	tree->deleteWord("CCCC");
	tree->deleteWord("BBBB");
	tree->deleteWord("AAAA");
	tree->deleteWord("GGGG");
	cout << *tree << endl;
	cout << endl;

	cout << "Amount of words: " << tree->countWords() << endl;
	cout << "Amount of AAAA :" << tree->findWord("AAAA") << endl;
	cout << "Amount of GGGG :" << tree->findWord("GGGG") << endl;
	cout << "Amount of World :" << tree->findWord("World") << endl;
	delete tree;
}

