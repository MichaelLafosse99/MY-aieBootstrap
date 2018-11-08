#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	m_pRoot == nullptr;
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
		TreeNode* newd = new TreeNode(a_nValue);
		m_pRoot = newd;
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
			parentNode = currentNode;
			currentNode = currentNode->getLeft();
			continue;
		}
		if (a_nValue > currentNode->getData())
		{
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
}

TreeNode * BinaryTree::find(int a_nValue)
{
	return nullptr;
}

void BinaryTree::draw(aie::Renderer2D * renderer, aie::Font* g_systemFont, TreeNode * selected)
{
	draw(renderer, m_pRoot, 640, 680, 640, g_systemFont, selected);
}

bool BinaryTree::findNode(int a_nSearchValue, TreeNode ** ppOutNode, TreeNode ** ppOutParent)
{
	return false;
}

void BinaryTree::draw(aie::Renderer2D * renderer, TreeNode * pNode, int x, int y, int horizontalSpacing, aie::Font* g_systemFont, TreeNode * selected)
{
	horizontalSpacing /= 2;

	if (pNode)
	{
		if (pNode->hasLeft())
		{
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine(x, y, x - horizontalSpacing, y - 80);
			draw(renderer, pNode->getLeft(), x - horizontalSpacing, y - 80, horizontalSpacing, g_systemFont, selected);
		}
		if (pNode->hasRight())
		{
			renderer->setRenderColour(1, 0, 0);
			renderer->drawLine(x, y, x + horizontalSpacing, y - 80);
			draw(renderer, pNode->getRight(), x + horizontalSpacing, y - 80, horizontalSpacing, g_systemFont,selected);
		}
		pNode->draw(renderer, x, y, g_systemFont, (selected == pNode));
	}
}