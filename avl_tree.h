#ifndef AVL_TREE_H
#define AVL_TREE_H
#include "binary_tree.h"

#define true 1
#define false 0

typedef struct _avll
{
	BTreeNode *prevnode;
	int depth;
	unsigned char rebalance_flag;
	unsigned char side;
}AVLL;

int AvlRebalance(BTree *bt, BTreeNode *btnode);



#endif