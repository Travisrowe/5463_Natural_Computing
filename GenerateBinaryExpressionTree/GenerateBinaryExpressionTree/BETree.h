#pragma once
#include "ETNode.h"
#include <iostream>
class BETree
{
private:
	ETNode * root;
	void BuildTreeAux(ETNode *&);
	void PrintAux(ETNode *);
public:
	BETree();
	~BETree();
	void BuildRandTree();
	void Print(); //Pre-order print
};

