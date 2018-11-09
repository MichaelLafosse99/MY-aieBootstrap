#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "BinaryTree.h"
#include <Input.h>
#include <imgui.h>
#include <Font.h>

class CDDS_BinaryTreesApp : public aie::Application
{
public:
	CDDS_BinaryTreesApp();
	~CDDS_BinaryTreesApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;

	BinaryTree			m_binaryTree;
	TreeNode*			m_selectedNode;

	float m_cameraX, m_cameraY;
	float m_timer;
};

