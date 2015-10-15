/************************************************
*			Jeff Stanton						*
*			CS M20   							*
*			Topic D Project						*
*												*
*			TopicD.cpp      			 		*
*			Status: Working              		*
************************************************/

#pragma warning (disable: 4290)

#include "soundtrack.h"
#include "BinarySearchTree.h"
#include <fstream>
#include <vector>
using namespace std;

// Open the file & read the input
template<class ItemType>
bool readInput(ifstream& inputFile,  const string& filename, vector<soundtrack>& cdVector, BinarySearchTree<ItemType>& BST);

// Displays items in a tree
template<class ItemType>
void display(ItemType& entries);

// Function passes display to appropriate
// traversal methods: 1 preorder | 2 inorder | 3 postorder | 4 all
template<class ItemType>
void traverse(const BinarySearchTree<ItemType>& BST, const int& version);

// Displays the height and number of nodes in a tree
template<class ItemType>
void heightAndNodes(const BinarySearchTree<ItemType>& BST, const string& treeName);

// Removes entry from tree
template<class ItemType>
void remove(BinarySearchTree<ItemType>& BST, const string& treeName, const string& title);

// Break in output
void programBreak();

// Program over
void endProgram();


int main()
{
	ifstream inputFile;  // To open file
	string fileName = "Topic A Soundtrack.txt"; // File to open
	vector<soundtrack> cdVector;  // Holds soundtrack objects created from file input
	bool ableToOpen;  // Test success of opening file
	bool success;  // Test remove method

	// Create int BST and call display
	cout << "Create default int tree bst1\n";
	BinarySearchTree<int> bst1;
	cout << "Display bst1\n";
	traverse(bst1, 4);

	// Read values from file and put release year into BST
	cout << "\n\n\nRead values from input file\n";
	cout << "Put release year values into bst1\n\n\n";
	do {
		ableToOpen = readInput(inputFile, fileName, cdVector, bst1);
		if (!ableToOpen)  // Couldn't open the file, try another one
		{
			cout << fileName << " cannot be opened. Enter another file name -->  ";
			getline(cin, fileName);  // To read whitespaces in file name
		}
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
	traverse(bst1, 4);

	// Display height, # of nodes, use getEntry, and contains methods
	heightAndNodes(bst1, "bst1");  // Should be: Height: 8 | Nodes: 38
	cout << "\n\nRetrieve value using getEntry -10 from the tree:\n\n";
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
	traverse(*bst2, 4);

	// Test bst2 member functions
	heightAndNodes(*bst2, "bst2");  // Should be: Height: 8 | Nodes: 38
	cout << "\n\nDelete 2014 from bst2\n";
	int tryToDelete = 2014;
	success = bst2->remove(tryToDelete);
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
	traverse(*bst2, 4);

	// Display height and # of nodes in bst2
	heightAndNodes(*bst2, "bst2");  // Should be: Height: 8 | Nodes: 37

	// Create bst3; use assignment operator to copy values from bst2
	cout << "\n\nCreate bst3 then assign bst2 to bst3\n";
	BinarySearchTree<int> bst3;
	bst3 = *bst2;

	// Display bst3
	cout << "Display bst3";
	traverse(bst3, 4);
	heightAndNodes(bst3, "bst3");  // Should be: Height: 8 | Nodes: 37

	programBreak();

	// Create BST w/ soundtrack objects
	BinarySearchTree<soundtrack> bstST1;

	// Read input file
	cout << "\n\n\nPut soundtrack records into bstST1\n\n";
	for (unsigned int i = 0; i < cdVector.size(); i++)
		bstST1.add(cdVector[i]);

	cout << "Display bstST1";
	traverse(bstST1, 4);
	heightAndNodes(bstST1, "bstST1");  // Should be: Height: 11 | Nodes: 31

	// Create copy of bstST1
	cout << "\n\nCreate bstST2 from bstST1\n\n\n";
	BinarySearchTree<soundtrack> bstST2(bstST1);
	cout << "Display bstST2";
	traverse(bstST2, 4);
	heightAndNodes(bstST2, "bstST2");  // Should be: Height: 11 | Nodes: 31

	programBreak();

	// Search, remove, and display entries from bstST2
	cout << "\n\nSearch bstST2 using getEntry for the object that has Godzilla as a title\n\n";
	soundtrack godzilla;
	godzilla.setTitle("Godzilla");
	try {
		bstST2.getEntry(godzilla);
		cout << "Found.  The object consists of " << bstST2.getEntry(godzilla);
	}
	catch (exception e) {
		cout << e.what() << endl;
	}

	cout << "\n\nSearch bstST2 using getEntry for the object that has godzilla as a title\n\n";
	godzilla.setTitle("godzilla");
	try {
		bstST2.getEntry(godzilla);
		cout << "Found.  The object consists of " << bstST2.getEntry(godzilla);
	}
	catch (exception e) {
		cout << e.what() << endl;
	}

	cout << "\n\nSearch bstST2 using getEntry for the object that has Elmer Bernstein as the composer\n\n";
	soundtrack elmer;
	elmer.setComposer("Elmer Bernstein");
	try {
		bstST2.getEntry(elmer);
		cout << "Found.  The object consists of " << bstST2.getEntry(elmer);
	}
	catch (exception e) {
		cout << e.what() << endl;
	}

	cout << "\n\n\nDelete the object from bstST2 with the title Much Ado About Nothing, a leaf\n\n\n";
	remove(bstST2, "bstST2", "Much Ado About Nothing");

	// Display bstST2
	cout << "\n\nDisplay bstST2";
	traverse(bstST2, 1);
	heightAndNodes(bstST2, "bstST2");  // Should be: Height: 10 | Nodes: 30

	// Delete and display
	cout << "\n\nDelete the object from bstST2 with the title Moonfleet, a tree with only a right subtree\n\n\n";
	remove(bstST2, "bstST2", "Moonfleet");
	
	cout << "\nDisplay bstST2";
	traverse(bstST2, 1);
	heightAndNodes(bstST2, "bstST2");

	cout << "\n\n\nDelete the object from bstST2 with title Godzilla, a tree with two subtrees whose right child is the inorder successor\n\n\n";
	remove(bstST2, "bstST2", "Godzilla");
	cout << "\nDisplay bstST2";
	traverse(bstST2, 1);
	heightAndNodes(bstST2, "bstST2");  // Should be: Height: 9 | Nodes: 28

	cout << "\n\n\nDelete from bstST2 with the title King of Hearts, a tree successor with two children whose right child is NOT the inorder successor\n\n\n";
	remove(bstST2, "bstST2", "King of Hearts");
	cout << "\nDisplay bstSt2";
	traverse(bstST2, 1);
	heightAndNodes(bstST2, "bstST2");  // Should be: Height: 9 | Nodes: 27

	cout << "\n\n\nRetrieve the object with title Psycho using contains\n\n\n";
	soundtrack psycho;
	psycho.setTitle("Psycho");
	success = bstST2.contains(psycho);
	if (success)
		cout << "\"Psycho\" found in bstST2\n\n\n";
	else
		cout << "\"Psycho\" NOT found in bstST2\n\n\n";

	cout << "Display bstST2";
	traverse(bstST2, 4);
	heightAndNodes(bstST2, "bstST2");  // Should be: Height: 9 | Nodes: 27

	programBreak();

	// Final stretch...
	cout << "\nCreate bstST3, a pointer to BinarySearchTree, and then assign bstST2 to it\n\n";
	BinarySearchTree<soundtrack>* bstST3 = new BinarySearchTree<soundtrack>;
	*bstST3 = bstST2;
	cout << "Display bstST3";
	traverse(*bstST3, 4);
	heightAndNodes(*bstST3, "bstST3");

	// Program over
	endProgram();

	return 0;
} // end Main

template<class ItemType>
bool readInput(ifstream& inputFile, const string& filename, vector<soundtrack>& cdVector, BinarySearchTree<ItemType>& BST)
{
	inputFile.open(filename);
	if (inputFile.fail())
		return false;
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
void traverse(const BinarySearchTree<ItemType>& BST, const int& version)
{
	switch (version)
	{
	case 1:
		cout << "\nPreorder:\n";
		BST.preorderTraverse(display);
		break;
	case 2:
		cout << "\nInorder:\n";
		BST.inorderTraverse(display);
		break;
	case 3:
		cout << "\nPostorder:\n";
		BST.postorderTraverse(display);
		break;
	case 4:
		cout << "\nPreorder:\n";
		BST.preorderTraverse(display);

		cout << "\nInorder:\n";
		BST.inorderTraverse(display);

		cout << "\nPostorder:\n";
		BST.postorderTraverse(display);

		break;
	default:
		break;
	}  // end switch
}  // end traverse

template<class ItemType>
void heightAndNodes(const BinarySearchTree<ItemType>& BST, const string& treeName)
{
	cout << "\nHeight of " << treeName << " is " << BST.getHeight();
	cout << "\n\nNumber of nodes in " << treeName << " is " << BST.getNumberOfNodes();
}  // end heightAndNodes

template<class ItemType>
void remove(BinarySearchTree<ItemType>& BST, const string& treeName, const string& title)
{
	soundtrack cd;
	cd.setTitle(title);
	bool success = BST.remove(cd);
	if (success)
		cout << "\"" << title << "\"" << " deleted from " << treeName << "\n\n";
	else
		cout << "\"" << title << "\"" << " NOT deleted from " << treeName << "\n";
}  // end remove

void programBreak()
{
	cout << endl << endl;
	cout << "***************************************************************" << endl;
	cout << "Press Enter to continue --> ";
	cin.ignore();
}  // end programBreak

void endProgram()
{
	cout << endl << endl;
	cout << "Program Over\n\n";
	cout << "Press Enter to continue --> ";
	cin.ignore();
}  // end endProgram