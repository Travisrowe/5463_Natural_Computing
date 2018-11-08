#pragma once
#include <random>

enum class NodeType {op, var, val};

class ETNode
{
public:
	ETNode * left;
	ETNode * right;
	NodeType NType; // op, var, or val
	int val; // 0 - 10
	char op; // + - * /
	char var; // x, y, or z
public:
	ETNode();
	~ETNode();
	/*ETNode * GetLeft();
	ETNode * GetRight();*/
};

