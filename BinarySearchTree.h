#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryNodeTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>
{
protected:
	//------------------------------------------------------------
	// Protected Utility Methods Section:
	// Recursive helper methods for the public methods.
	//------------------------------------------------------------
	// Recursively finds where the given node should be placed and
	// inserts it in a leaf at that point.
	BinaryNode<ItemType>* insertInorder(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNode);

	// Removes the given target value from the tree while maintaining a
	// binary search tree.
	BinaryNode<ItemType>* removeValue(BinaryNode<ItemType>* subTreePtr, const ItemType& target, bool& success);

	// Returns a pointer to the node containing the given value,
	// or nullptr if not found.
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType& target) const;

public:
	//------------------------------------------------------------
	// Constructor and Destructor Section.
	//------------------------------------------------------------
	BinarySearchTree();
	BinarySearchTree(const ItemType& rootItem);
	BinarySearchTree(const BinarySearchTree<ItemType>& tree);
	virtual ~BinarySearchTree();

	//------------------------------------------------------------
	// Public Methods Section.
	//------------------------------------------------------------
	bool add(const ItemType& newEntry);
	bool remove(const ItemType& anEntry);
	ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException);
	bool contains(const ItemType& anEntry) const;

	//------------------------------------------------------------
	// Overloaded Operator Section.
	//------------------------------------------------------------
	BinarySearchTree<ItemType>& operator=(const BinarySearchTree<ItemType>& rightHandSide);
}; // end BinarySearchTree



   //////////////////////////////////////////////////////////////
   //      BEGIN BinaryNodeTree IMPLEMENTATION
   //////////////////////////////////////////////////////////////



   //////////////////////////////////////////////////////////////
   //      Protected Utility Methods Section
   //////////////////////////////////////////////////////////////

template<class ItemType>
inline BinaryNode<ItemType>* BinarySearchTree<ItemType>::insertInorder(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNode)
{
	BinaryNode<ItemType>* tempPtr;

	// Order is: leftChild < root < rightChild

	if (subTreePtr == nullptr)  // Tree is empty or found a leaf
		return newNode;
	else if (subTreePtr->getItem() > newNode->getItem())  // Root's item is > newNode's item, insert as leftChild
	{
		tempPtr = insertInorder(subTreePtr->getLeftChildPtr(), newNode);
		subTreePtr->setLeftChildPtr(tempPtr);
	}
	else  // Root's item is < newNode's item, insert as rightChild
	{
		tempPtr = insertInorder(subTreePtr->getRightChildPtr(), newNode);
		subTreePtr->setRightChildPtr(tempPtr);
	}

	return subTreePtr;
} // end insertInorder

template<class ItemType>
inline BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeValue(BinaryNode<ItemType>* subTreePtr, const ItemType& target, bool & success)
{
	BinaryNode<ItemType>* tempPtr;

	if (subTreePtr == nullptr)
	{
		success = false;
		return nullptr;
	}  // end can't find case

	else if (subTreePtr->getItem() == target)
	{
		// Item is in the root of some subtree
		subTreePtr = BinaryNodeTree<ItemType>::removeNode(subTreePtr);
		success = true;
		return subTreePtr;
	}  // end found case

	else if (subTreePtr->getItem() > target)
	{
		// Search the left subtree
		tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
		subTreePtr->setLeftChildPtr(tempPtr);
		return subTreePtr;
	}  // end search left subtree

	else
	{
		// Search the right subtree
		tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
		subTreePtr->setRightChildPtr(tempPtr);
		return subTreePtr;
	}  // end search right subtree
} // end removeValue

template<class ItemType>
inline BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const
{
	if (treePtr == nullptr)  // Not found
		return nullptr;
	else if (treePtr->getItem() == target)  // Found
		return treePtr;
	else if (treePtr->getItem() > target)  // Search left subtree
		return findNode(treePtr->getLeftChildPtr(), target);
	else  // Search right subtree
		return findNode(treePtr->getRightChildPtr(), target);
} // end findNode

//////////////////////////////////////////////////////////////
//      PUBLIC METHODS BEGIN HERE
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//      Constructor and Destructor Section
//////////////////////////////////////////////////////////////

template<class ItemType>
inline BinarySearchTree<ItemType>::BinarySearchTree()
{
	BinaryNodeTree<ItemType>::BinaryNodeTree();
} // end default constructor

template<class ItemType>
inline BinarySearchTree<ItemType>::BinarySearchTree(const ItemType & rootItem)
{
	rootPtr = new BinaryNode<ItemType>(rootItem, nullptr, nullptr);
} // end constructor

template<class ItemType>
inline BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& tree)
{
	rootPtr = copyTree(tree.rootPtr);
} // end constructor

template<class ItemType>
inline BinarySearchTree<ItemType>::~BinarySearchTree()
{
	BinaryNodeTree<ItemType>::destroyTree(rootPtr);
}

//////////////////////////////////////////////////////////////
//      Public BinaryTreeInterface Methods Section
//////////////////////////////////////////////////////////////

template<class ItemType>
inline bool BinarySearchTree<ItemType>::add(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);  // Create a new node
	rootPtr = insertInorder(rootPtr, newNodePtr);  // Insert at appropriate position

	return true;
} // end add

template<class ItemType>
inline bool BinarySearchTree<ItemType>::remove(const ItemType& anEntry)
{
	bool success = false;

	rootPtr = removeValue(rootPtr, anEntry, success);

	return success;
}  // end remove

template<class ItemType>
inline ItemType BinarySearchTree<ItemType>::getEntry(const ItemType & anEntry) const throw(NotFoundException)
{
	if ( isEmpty() )  // Empty tree
		throw(PrecondViolatedExcep("getEntry() called with empty tree."));
	else
	{
		BinaryNode<ItemType>* nodePtr = findNode(rootPtr, anEntry);
		if (nodePtr == nullptr)  // Item not found
			throw(NotFoundException());
		else  // Item found
			return nodePtr->getItem();
	}
}  // end getEntry

template<class ItemType>
inline bool BinarySearchTree<ItemType>::contains(const ItemType & anEntry) const
{
	bool contains = true;

	if (isEmpty())  // Empty tree
		throw(PrecondViolatedExcep("contains() called with empty tree."));
	else
	{
		try {
			getEntry(anEntry);  // Find the entry
		}
		catch (exception notFound) {
			contains = false;  // Entry not found
		}
	}

	return contains;
}  // end contains

template<class ItemType>
inline BinarySearchTree<ItemType>& BinarySearchTree<ItemType>::operator=(const BinarySearchTree<ItemType>& rightHandSide)
{
	BinaryNodeTree<ItemType>::operator = (rightHandSide);
	return *this;
} // end overloaded = operator

#endif