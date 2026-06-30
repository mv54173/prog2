#ifndef SLLIST_H
#define SLLIST_H

#include "sll_data_type.h"

int      inputNodeData(SLLNODE *node);
SLLNODE* createSLList(void);
SLLNODE* insertNewNodeSLList(SLLNODE *headNode);
int      traverseSLList(SLLNODE *traverseNode);
SLLNODE* searchSLList(SLLNODE *traverseNode, int ramGB);
void     deleteNodeSLList(SLLNODE **headNode, SLLNODE *targetNode);
SLLNODE* deleteWholeSLList(SLLNODE *traverseNode);

#endif //SLLIST_H