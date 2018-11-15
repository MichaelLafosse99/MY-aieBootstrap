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
			TreeNode* ptrCurrent;
			TreeNode* ptrParent;

			ptrCurrent = *ppOutCurrent;
			ptrParent = *ppOutParent;

			if (ptrCurrent->hasRight())
			{
				ptrParent = ptrCurrent;
				ptrCurrent = ptrCurrent->getRight();
			}

			while (ptrCurrent->hasLeft())
			{
				ptrParent = ptrCurrent;
				ptrCurrent = ptrCurrent->getLeft();
			}

			currentNode->setData(ptrCurrent->getData());

			if (ptrParent->getLeft() == ptrCurrent)
			{
				ptrParent->setLeft(ptrCurrent->getRight());
			}

			else if (ptrParent->getRight() == ptrCurrent)
			{
				ptrParent->setRight(ptrCurrent->getRight());
			}

			delete ptrCurrent;
		}
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

TreeNode * BinaryTree::find(int a_nValue)
{
	TreeNode* currentNode;

	currentNode = m_pRoot;

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
}

void BinaryTree::draw(aie::Renderer2D * renderer, aie::Font* g_systemFont, TreeNode * selected)
{
	draw(renderer, m_pRoot, 640, 680, 640, g_systemFont, selected);
}

bool BinaryTree::findNode(int a_nSearchValue, TreeNode ** ppOutNode, TreeNode ** ppOutParent)
{
	TreeNode* currentNode;
	TreeNode* parentNode;

	currentNode = m_pRoot;
	parentNode = m_pRoot;

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