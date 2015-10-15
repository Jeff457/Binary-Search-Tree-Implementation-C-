#pragma warning (disable: 4290)

#include "soundtrack.h"
#include "BinarySearchTree.h"
#include <fstream>
#include <vector>>
using namespace std;

// Open the file & read the input
template<class ItemType>
bool readInput(ifstream& inputFile,  const string& filename, vector<soundtrack>& cdVector, BinarySearchTree<ItemType>& BST);

// Displays items in a tree
template<class ItemType>
void display(ItemType& entries);

// Below functions pass display to appropriate
// traversal methods
template<class ItemType>
void preOrder(BinarySearchTree<ItemType>& BST);

template<class ItemType>
void inOrder(BinarySearchTree<ItemType>& BST);

template<class ItemType>
void postOrder(BinarySearchTree<ItemType>& BST);

int main()
{
	ifstream inputFile;
	string fileName = "Topic A Soundtrack.txt";
	vector<soundtrack> cdVector;
	bool ableToOpen;

	// Create int BST and call display
	cout << "Create default int tree bst1\n";
	BinarySearchTree<int> bst1;
	cout << "Display bst1\n";
	preOrder(bst1);
	inOrder(bst1);
	postOrder(bst1);

	// Read values from file and put release year into BST
	cout << "\n\n\nRead values from input file\n";
	cout << "Put release year values into bst1\n\n\n";
	do {
		ableToOpen = readInput(inputFile, fileName, cdVector, bst1);
	} while (!ableToOpen);
	
	// Add additional values into BST
	cout << "Next, insert following values into bst1 in this order: 1 2 -10 15 -20 0 10\n";
	bst1.add(1);
	bst1.add(2);
	bst1.add(-10);
	bst1.add(15);
	bst1.add(-20);
	bst1.add(0);
	bst1.add(10);
	cout << "Display bst1\n";
	preOrder(bst1);
	inOrder(bst1);
	postOrder(bst1);

	// Display height, # of nodes, use getEntry, and contains methods
	cout << "\nHeight of bst1 is " << bst1.getHeight() << endl;
	cout << "\nNumber of nodes in bst1 is " << bst1.getNumberOfNodes() << endl;
	cout << "\nRetrieve value using getEntry -10 from the tree:\n\n";
	try {
		bst1.getEntry(-10);
		cout << "Found -10 in tree bst1";
	}
	catch (exception e) {
		cout << "-10 NOT found in bst1";
	}
	cout << "\n\nUse contains to see if value 11 is in the tree:\n\n";
	try {
		bst1.getEntry(11);
		cout << "Found 11 in tree bst1";
	}
	catch (exception e) {
		cout << "11 NOT found in bst1";
	}

	// Create a new BST from bst1 and display it
	cout << "\n\nCreate bst2, a pointer to BinarySearchTree, from bst1\n";
	BinarySearchTree<int>* bst2 = new BinarySearchTree<int>(bst1);
	cout << "Display bst2";
	preOrder(*bst2);
	inOrder(*bst2);
	postOrder(*bst2);

	// Test bst2 member functions
	cout << "\nHeight of bst2 is " << bst2->getHeight();
	cout << "\n\nNumber of nodes in bst2 is " << bst2->getNumberOfNodes();
	cout << "\n\nDelete 2014 from bst2\n";
	int tryToDelete = 2014;
	bool success = bst2->remove(tryToDelete);
	if (success)
		cout << tryToDelete << " deleted from bst2\n\n";
	else
		cout << tryToDelete << " NOT deleted from bst2\n";
	cout << "Delete 2014 from bst2\n";
	success = bst2->remove(tryToDelete);
	if (success)
		cout << tryToDelete << " deleted from bst2\n\n";
	else
		cout << tryToDelete << " NOT deleted from bst2\n";

	// Display bst2
	cout << "Display bst2";
	preOrder(*bst2);
	inOrder(*bst2);
	postOrder(*bst2);

	// Display height and # of nodes in bst2
	cout << "\nHeight of bst2 is " << bst2->getHeight();
	cout << "\n\nNumber of nodes in bst2 is " << bst2->getNumberOfNodes();

	// Create bst3; use assignment operator to copy values from bst2
	cout << "\n\nCreate bst3 then assign bst2 to bst3\n";
	BinarySearchTree<int> bst3;
	bst3 = *bst2;

	// Display bst3
	cout << "Display bst3";
	preOrder(bst3);
	inOrder(bst3);
	postOrder(bst3);
	cout << "\nHeight of bst3 is " << bst3.getHeight() << endl;
	cout << "\nNumber of nodes in bst3 is " << bst3.getNumberOfNodes() << endl;

	cout << endl << endl;
	cout << "***************************************************************" << endl;
	cout << "Press Enter to continue --> ";
	cin.ignore();

	// Create BST w/ soundtrack objects
	BinarySearchTree<soundtrack> bstST1;

	// Read input file
	cout << "\n\n\nPut soundtrack records into bstST1\n\n";
	for (int i = 0; i < cdVector.size(); i++)
		bstST1.add(cdVector[i]);

	cout << "Display bstST1";
	preOrder(bstST1);
	inOrder(bstST1);
	postOrder(bstST1);

	// TO-DO  change soundtrack comparison operator to compare by title

	return 0;

} // end Main

template<class ItemType>
bool readInput(ifstream& inputFile, const string& filename, vector<soundtrack>& cdVector, BinarySearchTree<ItemType>& BST)
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
			cdVector.push_back(*cd);
			BST.add(cd->getDateReleased());
			delete cd;
			cd = nullptr;
		}
		inputFile.close();
	}
		return true;
} // end readInput

template<class ItemType>
void display(ItemType& entries)
{
	cout << entries << endl;
}  // end display

template<class ItemType>
void preOrder(BinarySearchTree<ItemType>& BST)
{
	cout << "\nPreorder:\n";
	BST.preorderTraverse(display);
}  // end preOrder

template<class ItemType>
void inOrder(BinarySearchTree<ItemType>& BST)
{
	cout << "\nInorder:\n";
	BST.inorderTraverse(display);
}  // end inOrder

template<class ItemType>
void postOrder(BinarySearchTree<ItemType>& BST)
{
	cout << "\nPostorder:\n";
	BST.postorderTraverse(display);
}  // end postOrder