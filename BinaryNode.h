/************************************************
*			Jeff Stanton						*
*			CS M20   							*
*			Topic D Project						*
*												*
*			BinaryNode.h			 			*
*			Status: Working              		*
************************************************/

#ifndef _BINARY_NODE
#define _BINARY_NODE

template<class ItemType>
class BinaryNode
{
private:
	ItemType              item;           // Data portion
	BinaryNode<ItemType>* leftChildPtr;   // Pointer to left child
	BinaryNode<ItemType>* rightChildPtr;  // Pointer to right child

public:
	BinaryNode()					   :               leftChildPtr(nullptr), rightChildPtr(nullptr)  {}
	BinaryNode(const ItemType& anItem) : item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr)  {}
	BinaryNode(const ItemType& anItem, BinaryNode<ItemType>* leftPtr, BinaryNode<ItemType>* rightPtr) 
									   : item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr) {}


	void setItem(const ItemType& anItem)				  { item = anItem; }
	void setLeftChildPtr(BinaryNode<ItemType>* leftPtr)   { leftChildPtr = leftPtr; }
	void setRightChildPtr(BinaryNode<ItemType>* rightPtr) { rightChildPtr = rightPtr; }


	bool isLeaf() const { return ( leftChildPtr == nullptr && rightChildPtr == nullptr ); }


	ItemType getItem()						 const { return item; }
	BinaryNode<ItemType>* getLeftChildPtr()	 const { return leftChildPtr;  }
	BinaryNode<ItemType>* getRightChildPtr() const { return rightChildPtr; }
}; // end BinaryNode

#endif