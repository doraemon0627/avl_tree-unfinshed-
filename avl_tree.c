#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "binary_tree.h"
#include "avl_tree.h"

int IfRRCase(BTreeNode *btnode)
{
	int result = false;

	if (GetRightSubTree(btnode) != NULL)
		if (GetRightSubTree(GetRightSubTree(btnode)) != NULL)
			result = true;

	return result;
}

int IfLLCase(BTreeNode *btnode)
{
	int result = false;

	if (GetLeftSubTree(btnode) != NULL)
		if (GetLeftSubTree(GetLeftSubTree(btnode)) != NULL)
			result = true;

	return result;
}

int IfRLCase(BTreeNode *btnode)
{
	int result = false;

	if (GetRightSubTree(btnode) != NULL)
		if (GetLeftSubTree(GetRightSubTree(btnode)) != NULL)
			result = true;

	return result;
}

int IfLRCase(BTreeNode *btnode)
{
	int result = false;

	if (GetLeftSubTree(btnode) != NULL)
		if (GetRightSubTree(GetLeftSubTree(btnode)) != NULL)
			result = true;

	return result;
}

void RRCaseRebalance(BTreeNode *btnode, BTree *bt)
{
	BTreeNode *tempnode, *rootnode;
	
	BTreeNode *pWhere;
	BTreeNode *pP, *pC;
	pWhere = btnode;
	pP = btnode;
	pC = btnode->right;
	
	//pC->left->parents = pC->parents;
	
	//pP->right = pC->left;
	ChangeRightSubTree(pP, GetLeftSubTree(pC));
	
	printf("1\r\n");
	
	//pC->left = pP;
	ChangeLeftSubTree(pC, pP);
	
	printf("2\r\n");
	
	//pP->parents = pC;
	   
	//*GetParents(pP) = pC;
	*GetParentsSpace(pP) = pC;
	
	printf("3\r\n");
	
	// pWhere->parents->leftxx
	if (bt->root == pWhere)
	bt->root = pC;
	else
	{
	if(GetLeftSubTree(GetParents(pWhere)) == pWhere)
	    ChangeLeftSubTree(GetParents(pWhere), pC);
	else
	    ChangeRightSubTree(GetParents(pWhere), pC);
	}
	printf("4\r\n");

     *GetParentsSpace(pC) = GetParents(pWhere);
}

void LLCaseRebalance(BTreeNode *btnode)
{
	BTreeNode *tempnode = GetRightSubTree(GetLeftSubTree(btnode));

	ChangeRightSubTree(GetLeftSubTree(btnode), btnode);
	if (tempnode != NULL)
		ChangeLeftSubTree(btnode, tempnode);
	else
		ChangeLeftSubTree(btnode, NULL);
}

void RLCaseRebalance(BTreeNode *bt)
{
	ChangeRightSubTree(GetLeftSubTree(GetRightSubTree(bt)), GetRightSubTree(bt));
	ChangeRightSubTree(bt, GetLeftSubTree(GetRightSubTree(bt)));
	ChangeLeftSubTree(GetRightSubTree(GetRightSubTree(bt)), NULL);
}	

void LRCaseRebalance(BTreeNode *bt)
{
	ChangeLeftSubTree(GetRightSubTree(GetLeftSubTree(bt)), GetLeftSubTree(bt));
	ChangeLeftSubTree(bt, GetRightSubTree(GetLeftSubTree(bt))); 
	ChangeRightSubTree(GetLeftSubTree(GetLeftSubTree(bt)), NULL);
}

void FindAvlCaseAndRebalnce(BTree *bt, BTreeNode *btnode)
{
	printf("rebalance");
	if (IfLLCase(btnode))
	{
	    printf("LL case \r\n");
		if (bt->root == btnode)
		{
			bt->root = GetLeftSubTree(btnode);
			LLCaseRebalance(btnode);
		}
		else
			LLCaseRebalance(btnode, bt);
	}
	else if (IfRRCase(btnode))
	{
	    printf("RR case \r\n");
		RRCaseRebalance(btnode);
	}
	else if (IfLRCase(btnode))
		LRCaseRebalance(btnode);
	else if (IfRLCase(btnode))
		RLCaseRebalance(btnode);
	else
	{
		fprintf(stderr, "rebalance exception\n");
		exit(EXIT_FAILURE);
	}
}




int AvlRebalance(BTree *bt, BTreeNode *btnode)
{
	int leftH;
	int rightH;

	if (btnode == NULL)
		return 0;

	leftH = AvlRebalance(bt, GetLeftSubTree(btnode));
	rightH = AvlRebalance(bt, GetRightSubTree(btnode));

	if (abs(leftH - rightH) > 1)
	{
		FindAvlCaseAndRebalnce(bt, btnode);
		printf("%d, ", abs(leftH - rightH));
		printf("%d \r\n", btnode->data.iKey);

		if (leftH > rightH)
			return leftH;
		else 
			return rightH;
	}

	if (leftH > rightH)
		return leftH + 1;
	else 
		return rightH + 1;
}


