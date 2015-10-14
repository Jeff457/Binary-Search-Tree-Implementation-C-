#pragma warning (disable: 4290)

#include "soundtrack.h"
#include "BinaryNodeTree.h"
#include <fstream>
using namespace std;

template<class ItemType>
bool readInput(ifstream& inputFile,  const string& filename, BinaryNodeTree<ItemType>& BNT);

void display(soundtrack& cds);

int main()
{
	ifstream inputFile;
	string fileName = "Topic A Soundtrack.txt";
	soundtrack test;
	BinaryNodeTree<soundtrack> BNT;
	BinaryNodeTree<int> numberTree;
	numberTree.add(1);
	numberTree.add(2);
	numberTree.clear();

	try {
		cout << boolalpha << numberTree.contains(2) << endl;
	}
	catch (exception e) { cout << e.what() << endl; }

	readInput<soundtrack>(inputFile, fileName, BNT);

	BNT.inorderTraverse(display);

	return 0;

} // end Main

template<class ItemType>
bool readInput(ifstream& inputFile, const string& filename, BinaryNodeTree<ItemType>& BNT)
{
	inputFile.open(filename);
	if (inputFile.fail())
	{
		cout << "\nInput file" << filename << " cannot be found" << endl;
		return false;
	}
	else
	{
		while (!inputFile.eof())
		{
			soundtrack* cd = new soundtrack;
			inputFile >> *cd;
			BNT.add(*cd);
			delete cd;
			cd = nullptr;
		}
		return true;
	}
} // end readInput


void display(soundtrack& cds)
{
	cout << cds << endl;
}