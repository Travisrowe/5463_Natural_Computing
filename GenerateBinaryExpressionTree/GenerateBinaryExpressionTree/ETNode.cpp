#include "pch.h"
#include "ETNode.h"


ETNode::ETNode()
{
	int ntSelector = rand() % 3; //randomly select nodetype
	int varSelector, opSelector;
	switch (ntSelector)
	{
	case 0: //operator
		NType = NodeType::op;
		opSelector = rand() % 4; //randomly select operator
		switch (opSelector)
		{
		case 0: // +
			op = '+';
			break;
		case 1: // -
			op = '-';
			break;
		case 2: // *
			op = '*';
			break;
		case 3: // /
			op = '/';
			break;
		}
		break;

	case 1: //var
		NType = NodeType::var;
		varSelector = rand() % 3;
		this->var = 'X' + varSelector; // X, Y, or Z
		break;
	case 2: //val
		NType = NodeType::val;
		this->val = rand() % 11; //0 - 10
		break;
	}
}


ETNode::~ETNode()
{
}
