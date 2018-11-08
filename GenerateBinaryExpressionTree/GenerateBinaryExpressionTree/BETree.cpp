#include "pch.h"
#include "BETree.h"


BETree::BETree()
{
	root = nullptr;
}


BETree::~BETree()
{
	
}

void BETree::BuildRandTree()
{
	BuildTreeAux(root);
}

void BETree::BuildTreeAux(ETNode *& r)
{
	r = new ETNode();
	if (r->NType == NodeType::op)
	{
		BuildTreeAux(r->left);
		BuildTreeAux(r->right);
	}
}

void BETree::Print()
{
	PrintAux(root);
	std::cout << '\n';
}

void BETree::PrintAux(ETNode * r)
{
	switch (r->NType)
	{
	case NodeType::op:
		std::cout << r->op << ' ';
		PrintAux(r->left);
		PrintAux(r->right);
		break;
	case NodeType::var:
		std::cout << r->var << ' ';
		break;
	case NodeType::val:
		std::cout << r->val << ' ';
		break;
	}
}
