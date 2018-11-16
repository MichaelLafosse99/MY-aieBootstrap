#pragma once
#include "Application2D.h"

class TreeNode
{
private:
	// this could als be a pointer to another object if you like
	int m_value;

	// node's children
	TreeNode* m_left;
	TreeNode* m_right;
public:
	TreeNode(int value);
	~TreeNode();
	//Returns true if the left or right isn't set to nullptr
	bool hasLeft() { return (m_left != nullptr); }
	bool hasRight() { return (m_right != nullptr); }
	//Data returns the value of a node, left and right
	//return the value of the current node left and/or right children.
	int getData() { return m_value; }
	TreeNode* getLeft() { return m_left; }
	TreeNode* getRight() { return m_right; }
	//This sets the values of either the current node, current nodes left child,
	//or current nodes right child.
	void setData(int value) { m_value = value; }
	void setLeft(TreeNode* node) { m_left = node; }
	void setRight(TreeNode* node) { m_right = node; }
	
	void draw(aie::Renderer2D*, int x, int y, aie::Font* g_systemFont, bool selected = false);
};