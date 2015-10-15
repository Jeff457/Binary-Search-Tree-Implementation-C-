/************************************************
*			Jeff Stanton						*
*			CS M20   							*
*			Topic D Project						*
*												*
*			BinaryNodeTree.h			 		*
*			Status: Working              		*
************************************************/

#ifndef _BINARY_NODE_TREE
#define _BINARY_NODE_TREE

#include "BinaryNode.h"
#include "PrecondViolatedExcep.h"
#include "NotFoundException.h"
#include <algorithm>

template<class ItemType>
class BinaryNodeTree
{
protected:
	BinaryNode<ItemType>* rootPtr;

	//------------------------------------------------------------
	// Protected Utility Methods Section:
	// Recursive helper methods for the public methods.
	//------------------------------------------------------------
	int getHeightHelper(BinaryNode<ItemType>* subTreePtr) const;
	int getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const;

	// Recursively deletes all nodes from the tree.
	void destroyTree(BinaryNode<ItemType>* subTreePtr);

	// Recursively adds a new node to the tree in a left/right fashion to
	// keep the tree balanced.
	BinaryNode<ItemType>* balancedAdd(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNodePtr);

	// Removes the target value from the tree by calling removeNode which calls removeLeftmostNode
	// if the target has two children.
	BinaryNode<ItemType>* removeValue(BinaryNode<ItemType>* subTreePtr, const ItemType target, bool& success);
	BinaryNode<ItemType>* removeNode(BinaryNode<ItemType>* subTreePtr);
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* subTreePtr, ItemType& inorderSuccessor);

	// Recursively searches for target value in the tree
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType& target, bool& found) const;

	// Copies the tree rooted at treePtr and returns a pointer to
	// the copy.
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* treePtr) const;

	// Recursive traversal helper methods:
	void preorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr)  const;
	void inorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr)   const;
	void postorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const;

public:
	//------------------------------------------------------------
	// Constructor and Destructor Section.
	//------------------------------------------------------------
	BinaryNodeTree();
	BinaryNodeTree(const ItemType& rootItem);
	BinaryNodeTree(const ItemType& rootItem, const BinaryNodeTree<ItemType>* leftTreePtr, const BinaryNodeTree<ItemType>* rightTreePtr);
	BinaryNodeTree(const BinaryNodeTree<ItemType>& tree);
	virtual ~BinaryNodeTree();

	//------------------------------------------------------------
	// Public BinaryTreeInterface Methods Section.
	//------------------------------------------------------------
	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;
	ItemType getRootData() const throw(PrecondViolatedExcep);
	void setRootData(const ItemType& newData);
	bool add(const ItemType& newData); // Adds a node
	bool remove(const ItemType& data); // Removes a node
	void clear();
	ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException);
	bool contains(const ItemType& anEntry) const;

	//------------------------------------------------------------
	// Public Traversals Section.
	//------------------------------------------------------------
	void preorderTraverse(void visit(ItemType&)) const;
	void inorderTraverse(void visit(ItemType&)) const;
	void postorderTraverse(void visit(ItemType&)) const;

	//------------------------------------------------------------
	// Overloaded Operator Section.
	//------------------------------------------------------------
	BinaryNodeTree<ItemType>& operator=(const BinaryNodeTree<ItemType>& rightHandSide);
}; // end BinaryNodeTree



   //////////////////////////////////////////////////////////////
   //      BEGIN BinaryNodeTree IMPLEMENTATION
   //////////////////////////////////////////////////////////////



   //////////////////////////////////////////////////////////////
   //      Protected Utility Methods Section
   //////////////////////////////////////////////////////////////

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(BinaryNode<ItemType>* subTreePtr) const
{
	if (subTreePtr == nullptr)
		return 0;
	else
		return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()),
					   getHeightHelper(subTreePtr->getRightChildPtr()));
}  // end getHeightHelper

template<class ItemType>
inline int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const
{
	if (subTreePtr == nullptr)
		return 0;
	else
		return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr())
				 + getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
} // end getNumberOfNodesHelper

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::balancedAdd(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNodePtr)
{
	if (subTreePtr == nullptr)
		return newNodePtr;
	else
	{
		BinaryNode<ItemType>* leftPtr = subTreePtr->getLeftChildPtr();
		BinaryNode<ItemType>* rightPtr = subTreePtr->getRightChildPtr();

		if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr))
		{
			rightPtr = balancedAdd(rightPtr, newNodePtr);
			subTreePtr->setRightChildPtr(rightPtr);
		}
		else
		{
			leftPtr = balancedAdd(leftPtr, newNodePtr);
			subTreePtr->setLeftChildPtr(leftPtr);
		}  // end if

		return subTreePtr;
	}  // end if
}  // end balancedAdd

template<class ItemType>
inline BinaryNode<ItemType>* BinaryNodeTree<ItemType>::removeValue(BinaryNode<ItemType>* subTreePtr, const ItemType target, bool & success)
{
	BinaryNode<ItemType>* tempPtr;

	if (subTreePtr == nullptr)  // Item not found
	{
		success = false;
		return nullptr;
	}  // end if
	else if (subTreePtr->getItem() == target)  // Item found
	{
		subTreePtr = removeNode(subTreePtr);  // Remove node
		success = true;
		return subTreePtr;
	}  // end else if
	else
	{
		tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);  // Search the left subtree
		if (success)
			subTreePtr->setLeftChildPtr(tempPtr);
		else  // Search the right subtree
		{
			tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
			subTreePtr->setRightChildPtr(tempPtr);
		}
		return subTreePtr;
	}  // end else
} // end removeValue

template<class ItemType>
inline BinaryNode<ItemType>* BinaryNodeTree<ItemType>::removeNode(BinaryNode<ItemType>* subTreePtr)
{
	BinaryNode<ItemType>* nodeToConnectPtr;
	ItemType newNodeValue;

	if (subTreePtr->isLeaf())  // If the node is a leaf, remove from the tree
	{
		delete subTreePtr;
		subTreePtr = nullptr;
		return subTreePtr;
	} // end if

	// Node has 1 child
	else if (subTreePtr->getLeftChildPtr() == nullptr || subTreePtr->getRightChildPtr() == nullptr)
	{
		if (subTreePtr->getRightChildPtr() == nullptr)  // Node has a left child
			nodeToConnectPtr = subTreePtr->getLeftChildPtr();
		else  // Node has a right child
			nodeToConnectPtr = subTreePtr->getRightChildPtr();
		
		delete subTreePtr;
		subTreePtr = nullptr;
		return nodeToConnectPtr;
	} // end else if
	
	// Node has 2 children
	else
	{
		// Find the inorder successor of the entry in the node: in the left subtree of
		// the node's right child
		nodeToConnectPtr = removeLeftmostNode(subTreePtr->getRightChildPtr(), newNodeValue);
		subTreePtr->setRightChildPtr(nodeToConnectPtr);
		subTreePtr->setItem(newNodeValue);
		return subTreePtr;
	} // end else
}  // end removeNode

template<class ItemType>
inline BinaryNode<ItemType>* BinaryNodeTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* subTreePtr, ItemType & inorderSuccessor)
{
	BinaryNode<ItemType>* tempPtr;

	if (subTreePtr->getLeftChildPtr() == nullptr)  // Has no left child (might have a right child)
	{
		inorderSuccessor = subTreePtr->getItem();
		return removeNode(subTreePtr);
	}
	else  // Continue to search
	{
		tempPtr = removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessor);
		subTreePtr->setLeftChildPtr(tempPtr);
		return subTreePtr;
	}
}

template<class ItemType>
inline BinaryNode<ItemType>* BinaryNodeTree<ItemType>::findNode(BinaryNode<ItemType>* treePtr, const ItemType & target, bool & found) const
{
	BinaryNode<ItemType>* nodePtr;

	if (treePtr == nullptr)  // The desired item is not found
	{
		found = false;
		return nullptr;
	}
	else if (treePtr->getItem() == target)  // The desired item is found
	{
		found = true;
		return treePtr;
	}
	else  // Search subtrees
	{
		// Search left children for target
		nodePtr = findNode(treePtr->getLeftChildPtr(), target, found);
		if (!found)  // Not in the left nodes
		{
			// Search right children for target
			nodePtr = findNode(treePtr->getRightChildPtr(), target, found);
			if (!found)  // Item not in tree
				return nullptr;
		} // end if
		else  // Return found node
			return nodePtr;
	} // end else
}

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::copyTree(const BinaryNode<ItemType>* treePtr) const
{
	BinaryNode<ItemType>* newTreePtr = nullptr;

	// Copy tree nodes during a preorder traversal
	if (treePtr != nullptr)
	{
		// Copy node
		newTreePtr = new BinaryNode<ItemType>(treePtr->getItem(), nullptr, nullptr);
		newTreePtr->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
		newTreePtr->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));
	}  // end if

	return newTreePtr;
}  // end copyTree

template<class ItemType>
void BinaryNodeTree<ItemType>::destroyTree(BinaryNode<ItemType>* subTreePtr)
{
	if (subTreePtr != nullptr)
	{
		destroyTree(subTreePtr->getLeftChildPtr());
		destroyTree(subTreePtr->getRightChildPtr());
		delete subTreePtr;
		subTreePtr = nullptr;
	}  // end if

	rootPtr = nullptr;
}  // end destroyTree

   //////////////////////////////////////////////////////////////
   //      Protected Tree Traversal Sub-Section
   //////////////////////////////////////////////////////////////

template<class ItemType>
inline void BinaryNodeTree<ItemType>::preorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const
{
	if (treePtr != nullptr)
	{
		ItemType theItem = treePtr->getItem();
		visit(theItem);
		preorder(visit, treePtr->getLeftChildPtr());
		preorder(visit, treePtr->getRightChildPtr());
	} // end if
} // end preorder

template<class ItemType>
inline void BinaryNodeTree<ItemType>::inorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const
{
	if (treePtr != nullptr)
	{
		inorder(visit, treePtr->getLeftChildPtr());
		ItemType theItem = treePtr->getItem();
		visit(theItem);
		inorder(visit, treePtr->getRightChildPtr());
	}  // end if
}  // end inorder

template<class ItemType>
inline void BinaryNodeTree<ItemType>::postorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const
{
	if (treePtr != nullptr)
	{
		postorder(visit, treePtr->getLeftChildPtr());
		postorder(visit, treePtr->getRightChildPtr());
		ItemType theItem = treePtr->getItem();
		visit(theItem);
	} // end if
} // end postorder

   //////////////////////////////////////////////////////////////
   //      PUBLIC METHODS BEGIN HERE
   //////////////////////////////////////////////////////////////

   //////////////////////////////////////////////////////////////
   //      Constructor and Destructor Section
   //////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree() : rootPtr(nullptr)
{
}  // end default constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem)
{
	rootPtr = new BinaryNode<ItemType>(rootItem, nullptr, nullptr);
}  // end constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem,
										 const BinaryNodeTree<ItemType>* leftTreePtr,
										 const BinaryNodeTree<ItemType>* rightTreePtr)
{
	rootPtr = new BinaryNode<ItemType>(rootItem, 
									   copyTree(leftTreePtr->rootPtr),
									   copyTree(rightTreePtr->rootPtr));
}  // end constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType>& treePtr)
{
	rootPtr = copyTree(treePtr.rootPtr);
}  // end copy constructor

template<class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree()
{
	destroyTree(rootPtr);
}  // end destructor

   //////////////////////////////////////////////////////////////
   //      Public BinaryTreeInterface Methods Section
   //////////////////////////////////////////////////////////////

template<class ItemType>
inline bool BinaryNodeTree<ItemType>::isEmpty() const
{
	return rootPtr == nullptr;
} // end isEmpty

template<class ItemType>
inline int BinaryNodeTree<ItemType>::getHeight() const
{
	return getHeightHelper(rootPtr);
} // end getHeight

template<class ItemType>
inline int BinaryNodeTree<ItemType>::getNumberOfNodes() const
{
	return getNumberOfNodesHelper(rootPtr);
} // end getNumberOfNodes

template<class ItemType>
inline ItemType BinaryNodeTree<ItemType>::getRootData() const throw(PrecondViolatedExcep)
{
	if ( isEmpty() )
		throw PrecondViolatedExcep("getRootData() called with empty tree.");

	return rootPtr->getItem();
} // end getRootData

template<class ItemType>
inline void BinaryNodeTree<ItemType>::setRootData(const ItemType & newData)
{
	if ( isEmpty() )
		rootPtr = new BinaryNode<ItemType>(newData, nullptr, nullptr);
	else
		rootPtr->setItem(newData);
} // end setRootData

template<class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
	rootPtr = balancedAdd(rootPtr, newNodePtr);
	return true;
}  // end add

template<class ItemType>
inline bool BinaryNodeTree<ItemType>::remove(const ItemType & data)
{
	bool success = false;
	
	rootPtr = removeValue(rootPtr, data, success);

	return success;
} // end remove

template<class ItemType>
inline void BinaryNodeTree<ItemType>::clear()
{
	if ( !isEmpty() )
		destroyTree(rootPtr);
} // end clear

template<class ItemType>
inline ItemType BinaryNodeTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException)
{
	bool found = false;

	if ( isEmpty() )  // Empty Tree
		throw(PrecondViolatedExcep("getEntry() called with empty tree."));
	else
	{
		BinaryNode<ItemType>* nodePtr = findNode(rootPtr, anEntry, found);
		if (nodePtr == nullptr)  // Item not found
			throw(NotFoundException());
		else  // Item found
			return nodePtr->getItem();
	}
		
} // end getEntry

template<class ItemType>
inline bool BinaryNodeTree<ItemType>::contains(const ItemType & anEntry) const
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
} // end contains

   //////////////////////////////////////////////////////////////
   //      Public Traversals Section
   //////////////////////////////////////////////////////////////

template<class ItemType>
inline void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
	preorder(visit, rootPtr);
} // end preorderTraverse

template<class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
	inorder(visit, rootPtr);
}  // end inorderTraverse

template<class ItemType>
inline void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType&)) const
{
	postorder(visit, rootPtr);
} // end postorderTraverse

template<class ItemType>
inline BinaryNodeTree<ItemType> & BinaryNodeTree<ItemType>::operator=(const BinaryNodeTree<ItemType> & rightHandSide)
{
	if ( this == &rightHandSide )
		return *this;
	
	clear();

	if ( rightHandSide.rootPtr == nullptr )
		rootPtr = nullptr;
	else
		rootPtr = copyTree(rightHandSide.rootPtr);

	return *this;
} // end overloaded = operator

#endif
