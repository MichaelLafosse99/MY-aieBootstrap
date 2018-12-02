#include "BinaryTree.h"

//constructor that sets the root to null.
BinaryTree::BinaryTree()
{
	m_pRoot = nullptr;
}

BinaryTree::~BinaryTree()
{

}

//if the root is null then the tree is empty.
bool BinaryTree::isEmpty() const
{
	if (m_pRoot == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//insert simply just inserts a new node into the tree.
void BinaryTree::insert(int a_nValue)
{
	if (isEmpty())
	{
		//this makes a new node then assigns root to the newd pointer.
		//setting the value as the root.
		m_pRoot = new TreeNode(a_nValue);
		return;
	}

	TreeNode* currentNode;
	TreeNode* parentNode;
	//creating a parentNode is the same thing as
	//trailptr from linked list.
	currentNode = m_pRoot;
	parentNode = m_pRoot;

	while (currentNode != nullptr)
	{
		//getLeft and getRight are just returning the left or right node,
		//if there is any for the current node.

		//The purpose of if the value is less than, greater than, or equal
		//to the current node's data, is to see if the spot is taken or not.
		if (a_nValue < currentNode->getData())
		{
			//this makes a new node to be inserted.
			TreeNode* newd = new TreeNode(a_nValue);
			parentNode = currentNode;
			currentNode = currentNode->getLeft();
			continue;
		}
		if (a_nValue > currentNode->getData())
		{
			TreeNode* newd = new TreeNode(a_nValue);
			parentNode = currentNode;
			currentNode = currentNode->getRight();
			continue;
		}
		if (a_nValue == currentNode->getData())
		{
			return;
		}
	}

	//setLeft and setRight are inserting the values in those
	//said directions if they aren't taken.
	if (a_nValue < parentNode->getData())
	{
		TreeNode* newd = new TreeNode(a_nValue);
		parentNode->setLeft(newd);
	}
	if (a_nValue > parentNode->getData())
	{
		TreeNode* newd = new TreeNode(a_nValue);
		parentNode->setRight(newd);
	}
}

void BinaryTree::remove(int a_nValue)
{
	TreeNode* currentNode = m_pRoot;
	TreeNode* parentNode = m_pRoot;

	//This is a pointer of a pointer, it points to the
	//address of the pointer it's pointing to.
	TreeNode** ppOutCurrent = &currentNode;
	TreeNode** ppOutParent = &parentNode;

	if (findNode(a_nValue, ppOutCurrent, ppOutParent))
	{
		//Checking to see if the currentNode has a right branch.
		if (currentNode->hasRight())
		{
			//This makes a "copy"  or iterator of the currentNode pointer
			//basically just a way to iterate through the tree
			TreeNode* ptrCurrent;
			TreeNode* ptrParent;

			ptrCurrent = *ppOutCurrent;
			ptrParent = *ppOutParent;
			//if the iterator current has a right branch it
			if (ptrCurrent->hasRight())
			{
				//This sets the copy parent to the copy current,
				//then sets the copy current to point to its right.
				ptrParent = ptrCurrent;
				ptrCurrent = ptrCurrent->getRight();
			}
			//This is to find the minimum value of the right branch.
			while (ptrCurrent->hasLeft())
			{
				ptrParent = ptrCurrent;
				ptrCurrent = ptrCurrent->getLeft();
			}
			//this is what sets the copy's value to the currentNode pointer's value.
			currentNode->setData(ptrCurrent->getData());
			//These two conditionals are what move the node around.
			//This one sets the parents left, the current nodes right.
			if (ptrParent->getLeft() == ptrCurrent)
			{
				ptrParent->setLeft(ptrCurrent->getRight());
			}
			//and this one sets the parents right the current nodes right
			else if (ptrParent->getRight() == ptrCurrent)
			{
				ptrParent->setRight(ptrCurrent->getRight());
			}

			delete ptrCurrent;
		}
		//This is for if the current node doesn't have a right branch.
		else
		{
			if (parentNode->getLeft() == currentNode)
			{
				parentNode->setLeft(currentNode->getLeft());
			}
			else if (parentNode->getRight() == currentNode)
			{
				parentNode->setRight(currentNode->getLeft());
			}
			else if (m_pRoot == currentNode)
			{
				m_pRoot = currentNode->getLeft();
			}
			delete currentNode;
		}
	}
}
//This function is what locates a node in the tree, if it exsists.
TreeNode * BinaryTree::find(int a_nValue)
{
	TreeNode* currentNode;

	currentNode = m_pRoot;
	//The following conditionals check to see if the current nodes value is
	//less than, greater than, or equal to the value "inserted" or chosen.
	//Depending on the condition, it sets the currentNode pointer to the
	//current nodes left, right, or it just returns itself.
	while (currentNode != nullptr)
	{
		if (a_nValue < currentNode->getData())
		{
			currentNode = currentNode->getLeft();
			continue;
		}
		if (a_nValue > currentNode->getData())
		{
			currentNode = currentNode->getRight();
			continue;
		}
		if (a_nValue == currentNode->getData())
		{
			return currentNode;
		}
	}
	return false;
}
//This draws the root
void BinaryTree::draw(aie::Renderer2D * renderer, aie::Font* g_systemFont, TreeNode * selected)
{
	draw(renderer, m_pRoot, 640, 680, 640, g_systemFont, selected);
}
//This is similar to find, but is useful in the remove function.
bool BinaryTree::findNode(int a_nSearchValue, TreeNode ** ppOutNode, TreeNode ** ppOutParent)
{
	TreeNode* currentNode;
	TreeNode* parentNode;

	currentNode = m_pRoot;
	parentNode = m_pRoot;
	//While the current node isn't nullptr, it checks to see
	//if the search value is less than, greater than, or equal to
	//the current nodes value. Until the value is found, the function
	//searches through the tree. If not found, the function returns false.
	//If found it sets both of the pointer of a pointer(s) to their matching pointers.
	//Basically it helps change the value of the current node and parent node in the
	//remove function, because in the remove function, the pointers are set to the root,
	//the find functions sets the pointers in place where they need to be.
	while(currentNode != nullptr)
	{
		if (a_nSearchValue == currentNode->getData())
		{
			*ppOutNode = currentNode;
			*ppOutParent = parentNode;
			return true;
		}
		else if (a_nSearchValue < currentNode->getData())
		{
				parentNode = currentNode;
				currentNode = currentNode->getLeft();
		}
		else if (a_nSearchValue > currentNode->getData())
		{
				parentNode = currentNode;
				currentNode = currentNode->getRight();
		}
	}
	return false;
}

void BinaryTree::draw(aie::Renderer2D * renderer, TreeNode * pNode, int x, int y, int horizontalSpacing, aie::Font* g_systemFont, TreeNode * selected)
{
	horizontalSpacing /= 2;

	if (pNode)
	{
		if (pNode->hasLeft())
		{
			renderer->setRenderColour(1, 1, 1);
			renderer->drawLine(x, y, x - horizontalSpacing, y - 80);
			draw(renderer, pNode->getLeft(), x - horizontalSpacing, y - 80, horizontalSpacing, g_systemFont, selected);
		}
		if (pNode->hasRight())
		{
			renderer->setRenderColour(1, 1, 1);
			renderer->drawLine(x, y, x + horizontalSpacing, y - 80);
			draw(renderer, pNode->getRight(), x + horizontalSpacing, y - 80, horizontalSpacing, g_systemFont,selected);
		}
		pNode->draw(renderer, x, y, g_systemFont, (selected == pNode));
	}
}