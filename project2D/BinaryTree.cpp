#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	m_pRoot = nullptr;
}

BinaryTree::~BinaryTree()
{

}

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
	//creating a parentNode is the same thing as trailptr from linked list.
	currentNode = m_pRoot;
	parentNode = m_pRoot;

	while (currentNode != nullptr)
	{
		//getLeft and getRight are just pointing in that direction,
		//there isn't anything there yet.
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

	//setLeft and setRight are inserting the values in those said directions.
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

	TreeNode** ppOutCurrent = &currentNode;
	TreeNode** ppOutParent = &parentNode;

	//currentNode = *ppOutCurrent;
	//parentNode = *ppOutParent;

	if (findNode(a_nValue, ppOutCurrent, ppOutParent));
	{

		if (currentNode->hasRight())
		{
			TreeNode* ptrCurrent;
			TreeNode* ptrParent;

			ptrCurrent = *ppOutCurrent;
			ptrParent = *ppOutParent;

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
	TreeNode* parentNode;

	currentNode = m_pRoot;
	parentNode = m_pRoot;

	while (currentNode != nullptr)
	{
		if (a_nValue < currentNode->getData())
		{
			if (currentNode->hasLeft())
			{
			currentNode = currentNode->getLeft();
			continue;
			}
		}
		if (a_nValue > currentNode->getData())
		{
			if (currentNode->hasRight())
			{
			parentNode = currentNode;
			currentNode = currentNode->getRight();
			continue;
			}
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
	/*TreeNode* currentNode;
	TreeNode* parentNode;

	currentNode = m_pRoot;
	parentNode = m_pRoot;*/

	while(*ppOutNode != nullptr)
	{
		if (a_nSearchValue == (*ppOutNode)->getData())
		{
			return true;
		}
		else if (a_nSearchValue < (*ppOutNode)->getData())
		{
			*ppOutParent = *ppOutNode;
			*ppOutNode = (*ppOutNode)->getLeft();
		}
		else if (a_nSearchValue > (*ppOutNode)->getData())
		{
			*ppOutParent = *ppOutNode;
			*ppOutNode = (*ppOutNode)->getRight();
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