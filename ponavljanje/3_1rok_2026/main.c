/*==========================================================
Primjer ulazni podataka
5
10 20 30 40 50
30

Primjer izlaznih podataka
REZULTATI:
50 40 30 20 10
50 40 20 10

Ne mijenjati napisani kôd! U suprotnom se zadatak poništava!
=============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "sll_data_type.h"
#include "sllist.h"

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        return 1;
    }

    SLLNODE *headNode = NULL;
    if (n > 0) {
        headNode = createSLList();
        if (headNode == NULL) {
            return 1;
        }
        for (int i = 1; i < n; i++) {
            SLLNODE *newHead = insertNewNodeSLList(headNode);
            if (newHead == headNode) {
                headNode = deleteWholeSLList(headNode);
                return 1;
            }
            headNode = newHead;
        }
    }

    printf("REZULTATI:\n");
    traverseSLList(headNode);

    int x;
    if (scanf("%d", &x) != 1) {
        headNode = deleteWholeSLList(headNode);
        return 1;
    }

    SLLNODE *targetNode = searchSLList(headNode, x);
    if (targetNode == NULL) {
        printf("Nije pronadjeno\n");
    } else {
        deleteNodeSLList(&headNode, targetNode);
        traverseSLList(headNode);
    }

    headNode = deleteWholeSLList(headNode);
    return 0;
}
