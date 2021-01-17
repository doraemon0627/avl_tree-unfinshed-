#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"
#include "avl_tree.h"

#define AVL_REBALANCE
BTree *MakeBTree(void)
{
    BTree *pNewTree;
    pNewTree = calloc(1, sizeof(BTree));
    pNewTree->iNumOfNode = 0;
	return pNewTree;
}

BTreeNode *MakeBTreeNode(void)
{
	return calloc(1, sizeof(BTreeNode));
}

BTData GetData(BTreeNode *bt)
{
	return bt->data;
}

void setData(BTreeNode *bt, BTData data)
{
	bt->data = data;
}

BTreeNode *GetLeftSubTree(BTreeNode *bt)
{
	return bt->left;
}

BTreeNode *GetRightSubTree(BTreeNode *bt)
{
	return bt->right;
}

void ChangeLeftSubTree(BTreeNode *dest, BTreeNode *src)
{
	dest->left = src;
}

void ChangeRightSubTree(BTreeNode *dest, BTreeNode *src)
{
	dest->right = src;
}

BTreeNode *GetParents(BTreeNode *bt)
{
    return bt->parents;
}

BTreeNode **GetParentsSpace(BTreeNode *bt)
{
    return &bt->parents;
}

void BTInsert(BTree *bt, BTData data)
{
	BTreeNode *current_node = bt->root;
	BTreeNode *newnode = calloc(1, sizeof(BTreeNode));

	newnode->data = data;

	if (bt->root == NULL)
	{
		bt->root = newnode;
		return;
	}
	
	bt->iNumOfNode++;

	while (1)
	{
		if (data.iKey < current_node->data.iKey)
		{
		    //input key is lower than current key
			if (GetLeftSubTree(current_node) == NULL)
			{
			    //input node to currnet's left 
				ChangeLeftSubTree(current_node, newnode);
				GetLeftSubTree(current_node)->parents = current_node;
				break;
			}
			else
			{
				//GetLeftSubTree(current_node)->parents = current_node;
				current_node = GetLeftSubTree(current_node);
			}
		}
		else if (data.iKey > current_node->data.iKey)
		{
			if (GetRightSubTree(current_node) == NULL)
			{
				ChangeRightSubTree(current_node, newnode);
				GetRightSubTree(current_node)->parents = current_node;
				break;
			}
			else
			{
				//GetRightSubTree(current_node)->parents = current_node;
				current_node = GetRightSubTree(current_node);
			}
		}
		else
		{
			fprintf(stderr, "iKey is overlaped\n");
			bt->iNumOfNode;
			free(newnode);
			break;
		}
	}
#ifdef AVL_REBALANCE
	AvlRebalance(bt, bt->root);
#endif
}

BTreeNode *BTSearchNode(BTree *bt, TData iKey)
{
	BTreeNode *current_node = bt->root;
	BTreeNode *found_node = NULL;
	int flag = false; /* true is found, false is not found */

	while (current_node != NULL)
	{
		if (current_node->data.iKey == iKey)
		{
			found_node = current_node;
			flag = true;
			break;
		}
		else if (iKey > current_node->data.iKey)
			current_node = GetLeftSubTree(current_node);
		else if (iKey < current_node->data.iKey)
			current_node = GetRightSubTree(current_node);
	}

	if (flag == false)
	{
		fprintf(stderr, "No data was found");
		return NULL;
	}

	return found_node;
}

#if 0

TData BTSearchData(BTree *bt, TData ikey)
{
	BTreeNode *current_node = bt->root;
	int found_data;
	int flag = false; /* true is found, false is not found */

	while(current_node != NULL)
	{
		if (rootnode == iKey)
		{
			found_data = current_node->data.iValue;
			flag = true;
		}
		else if (iKey > current_node->data.iKey)
			current_node = GetLeftSubTree(current_node);
		else if (iKet < current_node->data.iKey)
			current_node = GetRightSubTree(current_node);
	}

	if (flag = false)
	{
		puts("Data not found");
		return NOT_FOUND;
	}

	return found_data;
}

#endif

TData BTSearchData(BTree *bt, TData iKey)
{
	return BTSearchNode(bt, iKey)->data.iValue;
}

int BTDelete(BTree *bt, TData iKey)
{
	int flag = false, i = 0;
	BTreeNode *current_node = NULL, *target_node, *found_node;
	BTreeNode *target_left_node, *target_right_node, *stored_node[2] = {0}, *prev_node_of_target_node = NULL;
	current_node = bt->root;

	while (current_node != NULL) /* finds target node */
	{
		if (current_node->data.iKey == iKey)
		{
			found_node = current_node;
			flag = true;
			break;
		}
		else if (iKey > current_node->data.iKey)
			current_node = GetLeftSubTree(current_node);
		else if (iKey < current_node->data.iKey)
			current_node = GetRightSubTree(current_node);

		stored_node[i++ % 2] = current_node;
	}

	target_node = current_node;

	if (flag == false)
		return false;

	target_left_node = GetLeftSubTree(target_node);
	target_right_node = GetRightSubTree(target_node);

	current_node = target_node;

	prev_node_of_target_node = stored_node[(i - 1) % 2 - 1];

	if (target_left_node == NULL && target_right_node == NULL) /* delete case 1 */
	{
		if (i > 0)
		{
			if (prev_node_of_target_node->right == target_node)
				prev_node_of_target_node->right = NULL;
			else if (prev_node_of_target_node->left == target_node)
				prev_node_of_target_node->left = NULL;
			else
			{
				fprintf(stderr, "delete exception 1\n");
				exit(EXIT_FAILURE);
			}
		}
		free(target_node);
		return true;
	}
	else if (target_left_node != NULL) /* delete case 2 */
	{
		target_node->data.iKey = target_left_node->data.iKey; /* swap */
		target_node->data.iValue = target_left_node->data.iValue;

		if (i > 0)
		{
			if (prev_node_of_target_node->right == target_node)
				prev_node_of_target_node->right = NULL;
			else if (prev_node_of_target_node->left == target_node)
				prev_node_of_target_node->left = NULL;
			else
			{
				fprintf(stderr, "delete exception 2\n");
				exit(EXIT_FAILURE);
			}
		}
		free(target_left_node);
	}
	else if (target_right_node != NULL) /* delete case 3 */
	{
		target_node->data.iKey = target_right_node->data.iKey; /* swap */
		target_node->data.iValue = target_right_node->data.iValue;

		if (i > 0)
		{
			if (prev_node_of_target_node->right == target_node)
				prev_node_of_target_node->right = NULL;
			else if (prev_node_of_target_node->left == target_node)
				prev_node_of_target_node->left = NULL;
			else
			{
				fprintf(stderr, "delete exception 3\n");
				exit(EXIT_FAILURE);
			}
		}
		free(target_right_node);
	}
	else
	{
		while (GetLeftSubTree(current_node)) /* gets smallest number on the left side */
			current_node = GetLeftSubTree(current_node);

		target_node->data.iKey = current_node->data.iKey; /* swap */
		target_node->data.iValue = current_node->data.iValue;

		target_node->left = NULL;

		free(target_left_node);
	}

	return true;
}


int GetBTreeHeight(BTreeNode *bt)
{
	int leftH;
	int rightH;

	if (bt == NULL)
		return 0;

	leftH = GetBTreeHeight(GetLeftSubTree(bt));
	rightH = GetBTreeHeight(GetRightSubTree(bt));

	if (leftH > rightH)
		return leftH + 1;
	else
		return rightH + 1;
}
