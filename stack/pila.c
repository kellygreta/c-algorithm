#include <stdlib.h>
#include <stdio.h>

struct listnode {
  struct listnode* next;
  int v;
};


struct pila{	//Solo la testa
	struct listnode* testa;	//La cima della pila
};



struct pila* createPila(){
	struct pila* p = malloc( sizeof (struct pila));
	p -> testa = NULL;
	return p;
}

void push ( struct pila *p, int i ){	//Inserisce i in cima a p

	//crea un nodo
	struct listnode *new = malloc( sizeof( struct listnode ));
	new -> v = i;


	//Se la pila è vuota
	if (p -> testa==NULL)
		new -> next = NULL;	//New è il primo (ed ultimo) elemento

	//Altrimenti
	else
		new -> next = p -> testa;	//New va in cima e si concatena alla ex testa

	//In entrambi i casi devo aggiornare il valore di testa perchè ora deve puntare a new, la nuova cima
	p -> testa = new;
}

int pop( struct pila* p ){	// Rimuove e restituisce l'elemento in cima
	struct listnode* h = p -> testa;	//Inizializzo l'elemento da restituire
	int res = h -> v;		//Mi salvo il suo valore
	p -> testa = h -> next;	//Aggiorno la testa in modo che punti al prossimo
	free(h);				//Libero lo spazio
	return res;
}

/* restituisce 1 se la pila e' vuota, 0 altrimenti */
int isEmpty( struct pila* p ) {
	if ( p == NULL || p -> testa == NULL)
		return 1;
	else
		return 0;
}

/* stampa il contenuto della pila, partendo dal top. */
void printList ( struct listnode * h){
	struct listnode* e=h;
	while(e!=NULL){
		printf("|%d|\n",e->v);
		e=e->next;
	}
	printf("\n");
	return;
}

int main(void){

	struct pila* x = createPila();

	printf("[push(1)]\n");
	push(x,1);

	printf("pila:\n");
	printList (x->testa);

	printf("[push(3)]\n");
	push(x,3);

	printf("pila:\n");
	printList (x->testa);

	printf("[push(5)]\n");
	push(x,5);

	printf("pila:\n");
	printList (x->testa);

	printf("[pop() -> %d]\n", pop(x));
	printf("pila:\n");
	printList (x->testa);

}
