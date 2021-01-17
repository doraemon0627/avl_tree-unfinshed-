#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binary_tree.h"
#include "print_BTree.h"


int main(void)
{
    int i = 0;
	BTData data[100];
    BTree *tree = MakeBTree();

	
	memset(tree, 0, sizeof(BTree));

    puts("start"); 

    for (i = 0; i < 100; i++)
    {
        data[i].iKey = i;
        data[i].iValue = i;
    }

    BTInsert(tree, data[1]);
	BTInsert(tree, data[2]);
	BTInsert(tree, data[3]);

	//BTInsert(tree, data[4]);
	//BTInsert(tree, data[5]);

	PrintBTree(tree->root);

    puts("\r\nend");
}