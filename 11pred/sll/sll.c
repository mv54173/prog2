#include <stdio.h>
#include <stdlib.h>

/*
 * JEDNOSTRUKO POVEZANA LISTA (Singly Linked List - SLL)
 *
 * Svaki element liste (čvor / node) sadrži:
 *   - podatak (data)
 *   - pokazivač na sljedeći čvor (next)
 *
 * Vizualno:
 *   head -> [data|next] -> [data|next] -> [data|next] -> NULL
 *
 * Za razliku od niza, čvorovi u memoriji NE moraju biti uzastopni.
 * Veza između čvorova ostvaruje se isključivo pokazivačima.
 */

/* Definicija strukture čvora.
 * Koristimo "struct node *next" unutar same strukture jer u trenutku
 * definicije tip NODE još nije poznat kompajleru - mora se koristiti
 * puno ime "struct node". */
typedef struct node
{
    int data;          /* Podatak koji čvor čuva */
    struct node *next; /* Pokazivač na sljedeći čvor (NULL = kraj liste) */
} NODE;

/*
 * createList - stvara prvu (jedinu) listu s jednim čvorom.
 *
 * Koristi calloc (umjesto malloc) koji uz alokaciju i automatski
 * postavlja sve bajtove na 0 - sigurniji pristup jer "next" odmah
 * dobiva vrijednost NULL (0).
 *
 * Povratna vrijednost: pokazivač na novostvoreni čvor (head),
 *                      ili NULL ako alokacija nije uspjela.
 */
NODE *createList(void)
{
    /* Alociramo memoriju za jedan čvor.
     * calloc(broj_elemenata, veličina_jednog) - sve nule po defaultu. */
    NODE *head = (NODE *)calloc(1, sizeof(NODE));

    /* Uvijek provjeravamo je li alokacija uspjela!
     * Konvencija "NULL == head" (Yoda stil) štiti od slučajnog "head = NULL". */
    if (NULL == head)
    {
        perror("Kreiranje"); /* Ispisuje sistemsku poruku greške */
        return NULL;
    }

    /* Učitavamo podatak izravno u polje "data" novog čvora.
     * "&head->data" je adresa polja, što scanf treba. */
    scanf("%d", &head->data);

    /* Ovo je jedini čvor - nema sljedećeg, pa next = NULL.
     * (calloc bi već postavio na 0/NULL, ali eksplicitno je jasnije.) */
    head->next = NULL;

    return head;
}

/*
 * insertNewNode - umeće novi čvor NA POČETAK liste (prepend).
 *
 * Parametar head: trenutni prvi čvor liste.
 * Povratna vrijednost: novi prvi čvor (postaje novi head).
 *
 * Vizualno prije: head -> [A] -> [B] -> NULL
 * Vizualno poslije: new -> [X] -> [A] -> [B] -> NULL  (new postaje head)
 *
 * VAŽNO: caller mora ažurirati svoju varijablu "head" povratnom vrijednošću!
 *        head = insertNewNode(head);
 */
NODE *insertNewNode(NODE *head)
{
    NODE *new = (NODE *)calloc(1, sizeof(NODE));

    if (NULL == new)
    {
        perror("Ubacivanje");
        /* Ako alokacija ne uspije, vraćamo stari head - lista ostaje netaknuta */
        return head;
    }

    scanf("%d", &new->data);

    /* Ključni korak: novi čvor pokazuje na dosadašnji prvi čvor.
     * Time se novi čvor "zakači" ispred cijele postojeće liste. */
    new->next = head;

    /* Vraćamo novi čvor - on postaje novi head */
    return new;
}

/*
 * traverseList - prolazi kroz cijelu listu i ispisuje sve podatke.
 *
 * Parametar head: pokazivač na prvi čvor (ne mijenjamo ga, lokalna kopija).
 * Povratna vrijednost: broj čvorova u listi.
 *
 * Petlja se vrti dok head != NULL:
 *   - ispiše podatak
 *   - pomakne head na sljedeći čvor (head = head->next)
 * Kada dođemo do NULL, prošli smo sve čvorove.
 */
int traverseList(NODE *head)
{
    int counter = 0;

    /* "while (NULL != head)" isto kao "while (head != NULL)" ili "while (head)" */
    while (NULL != head)
    {
        printf("%d\n", head->data);
        counter++;
        head = head->next; /* Pomak na sljedeći čvor */
    }

    return counter;
}

/*
 * findNode - traži čvor čije je "data" jednako k.
 *
 * Parametar head: pokazivač na prvi čvor.
 * Parametar k: vrijednost koju tražimo.
 * Povratna vrijednost: pokazivač na pronađeni čvor, ili NULL ako nije nađen.
 *
 * Napomena: vraća POKAZIVAČ na čvor unutar liste (ne kopiju!).
 *           Kroz taj pokazivač možemo mijenjati ili brisati pronađeni čvor.
 */
NODE *findNode(NODE *head, int k)
{
    while (head) /* Prolazimo dok ne dođemo do NULL */
    {
        if (head->data == k)
        {
            /* Pronašli smo čvor - vraćamo pokazivač na njega odmah */
            return head;
        }
        head = head->next;
    }

    /* Prošli smo cijelu listu, k nije pronađen */
    return NULL;
}

/*
 * deleteNode - briše određeni čvor iz liste i oslobađa njegovu memoriju.
 *
 * Parametar head: DVOSTRUKI pokazivač (**) jer funkcija može morati
 *                 promijeniti sam "head" (ako brišemo prvi čvor).
 *                 Poziv: deleteNode(&head, target);
 * Parametar target: pokazivač na čvor koji brišemo.
 *
 * Dva slučaja:
 *   1) Brišemo PRVI čvor (target == *head):
 *      - head pomaknemo na sljedeći čvor
 *   2) Brišemo SREDNJI ili ZADNJI čvor:
 *      - moramo pronaći čvor ISPRED targeta i "preskočiti" target
 *
 * Vizualno brisanja sredinjeg čvora [B]:
 *   Prije:  [A] -> [B] -> [C] -> NULL
 *   Poslije: [A] -> [C] -> NULL   (B je freed)
 */
void deleteNode(NODE **head, NODE *target)
{
    /* Zaštita: ne možemo brisati NULL */
    if (target == NULL)
    {
        printf("Nema se što obrisati - target je NULL!");
        return;
    }

    if (*head == target)
    {
        /* SLUČAJ 1: Brišemo prvi čvor.
         * Novi head postaje sljedeći čvor (može biti NULL ako je jedini čvor). */
        *head = (*head)->next;
    }
    else
    {
        /* SLUČAJ 2: Brišemo čvor koji nije prvi.
         * Prolazimo listom tražeći čvor čiji je "next" naš target. */
        NODE *traverse = *head;

        while (traverse->next)
        {
            if (traverse->next == target)
            {
                /* Pronašli smo prethodnika: premošćujemo target.
                 * Prethodnik sada pokazuje na čvor iza targeta. */
                traverse->next = target->next;
                break;
            }
            traverse = traverse->next;
        }
        /* Napomena: ako target uopće nije u listi, while završava bez promjene.
         * free(target) ispod bi tada bio "double free" ili greška - oprezno! */
    }

    /* Oslobađamo memoriju izbrisanog čvora.
     * Nakon free(), pointer "target" postaje dangling pointer - ne koristiti ga! */
    free(target);
}

/*
 * deleteWholeList - briše sve čvorove liste i oslobađa svu memoriju.
 *
 * VAŽNO: Ne smijemo prvo osloboditi čvor pa onda čitati njegov "next"
 *        (oslobođena memorija ne smije se čitati!).
 *        Rješenje: zapamtimo pokazivač na tekući čvor u "toDelete",
 *        pomaknemo head na sljedeći, pa tek onda free(toDelete).
 *
 * Povratna vrijednost: NULL (oslobođena lista "nema" head).
 *                      Dodjeljujemo: head = deleteWholeList(head);
 */
NODE *deleteWholeList(NODE *head)
{
    NODE *toDelete = NULL;

    while (head)
    {
        toDelete = head;   /* Zapamtimo tekući čvor */
        head = head->next; /* Pomaknemo se na sljedeći PRIJE brisanja */
        free(toDelete);    /* Sad je sigurno osloboditi */
    }

    /* head je sada NULL (petlja stala), vraćamo ga kako bi caller mogao
     * svoju varijablu postaviti na NULL: head = deleteWholeList(head); */
    return head;
}

int main(void)
{
    int n;
    scanf("%d", &n); /* Učitavamo broj elemenata koje ćemo dodati */

    /* Stvaramo listu s prvim elementom */
    NODE *head = createList();

    /* Dodajemo preostalih n-1 elemenata na POČETAK liste.
     * Rezultat: elementi su u obrnutom redoslijedu od unosa
     * (zadnji unesen bit će prvi u listi). */
    for (int i = 0; i < n - 1; i++)
    {
        head = insertNewNode(head);
    }

    /* Ispisujemo sve elemente i pamtimo koliko ih ima */
    int elementCount = traverseList(head);

    /* Tražimo čvor s vrijednošću 2 */
    NODE *second = findNode(head, 2);
    printf("%d\n", second->data); /* Pažnja: crash ako findNode vrati NULL! */

    /* Brišemo pronađeni čvor (vrijednost 2) */
    deleteNode(&head, second);

    /* Brišemo trenutni prvi čvor liste */
    deleteNode(&head, head);

    /* Ispisujemo listu nakon brisanja */
    traverseList(head);

    /* Brišemo cijelu listu i postavljamo head na NULL */
    head = deleteWholeList(head);

    if (NULL == head)
        printf("Uspješno obrisana cijela lista!");

    return 0;
}
