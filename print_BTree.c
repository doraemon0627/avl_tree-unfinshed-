#include <stdio.h>
#include <math.h>

#include "binary_tree.h"

void PrintBTreeToScreen(BTreeNode *bt, long long width, long long height);
long long LongPow(long long x, long long y);

long long LongPow(long long x, long long y)
{
    long long i = 0, sum = x;

    for (i = 1; i < y; i++)
    {
        sum *= x;
    }

    return sum;
}

long long GetBTreeMaxWidth(long long height)
{
    return LongPow(2, height);
}

void PrintBTreeToScreen(BTreeNode *bt, long long width, long long side)
{
    if (bt == NULL)
    {
        printf("%s \n", "null");
        return;
    }

//    for (i = 0; i < width; i++)
  //      printf(" ");

	printf("%d ", bt->data.iValue);
	
    //printf("%s %d\n", (side)? "left" : "right");
	//if(bt->left != NULL)
	//{
	  //
	  //printf("%s %d\n", (side)? "left" : "right", bt->data.iValue);
        printf("%s","left ");
        PrintBTreeToScreen(bt->left, width - width / 2, 0);
        printf("%s","right ");
        PrintBTreeToScreen(bt->right, width + width / 2, 1);

	//printf("\n");
}
void PrintBTree(BTreeNode *bt)
{
    long long width, height;

    height = GetBTreeHeight(bt);
    width = GetBTreeMaxWidth(height - 1);

    //printf("%d", height);

    PrintBTreeToScreen(bt, width * 2, 1);
}
