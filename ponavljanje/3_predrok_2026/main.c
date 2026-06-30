/* ===================================================================================================
   VAZNA NAPOMENA: 
   Kod unutar ove datoteke (main.c) NE SMIJE se mijenjati! 
   Sav vas kod i implementacija trazenih funkcija moraju biti napisani 
   iskljucivo unutar datoteke 'sllist.c'. 
   U slučaju izmjene pripremljenog koda zadatak se poništava!
   ===================================================================================================
   
   OPIS RADA GLAVNOG PROGRAMA (main.c):
   1. Ucitava ukupan broj racunala (n) sa standardnog ulaza.
   2. Stvara jednostruko povezani popis (JPP) i umeće 'n' racunala na POČETAK popisa.
   3. Ispisuje trenutno stanje popisa.
   4. Ucitava kolicinu RAM-a koja sluzi kao kriterij za pretragu.
   5. Pretražuje popis: 
      - Ako pronadje racunalo s trazenom kolicinom RAM-a, brise ga iz popisa 
        i ponovno ispisuje azurirani popis.
      - Ako ga ne pronadje, ispisuje poruku "Nije pronadjeno".
   6. Na kraju iterativno oslobadja svu dinamicki alociranu memoriju.

   =================================================================================================== 
   
   PRIMJER RADA PROGRAMA:
    Ulaz: 
        3
        Acer Swift 8 850.00
        MSI Katana 16 1300.00
        Razer Blade 32 2900.99
    Izlaz:    
        REZULTATI:
        Razer Blade 32 2900.99
        MSI Katana 16 1300.00
        Acer Swift 8 850.00
    Ulaz: 
        32
    Izlaz: 
        MSI Katana 16 1300.00
        Acer Swift 8 850.00
   =================================================================================================== */

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

    int searchRamGB;
    if (scanf("%d", &searchRamGB) != 1) {
        headNode = deleteWholeSLList(headNode);
        return 1;
    }

    SLLNODE *targetNode = searchSLList(headNode, searchRamGB);
    if (targetNode == NULL) {
        printf("Nije pronadjeno\n");
    } else {
        deleteNodeSLList(&headNode, targetNode);
        traverseSLList(headNode);
    }

    headNode = deleteWholeSLList(headNode);
    return 0;
}
