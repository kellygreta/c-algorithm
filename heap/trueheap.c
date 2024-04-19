#include <stdio.h>
#include <stdlib.h>
#define MAX 10


typedef int * Heap ;
struct pqueue {
	Heap h;
	int size , count ;
};

typedef struct pqueue * Pqueue ;

/* crea una coda di priorità vuota che potrà contenere al massimo n Item */
Pqueue pqueue_new ( int n ){
	Pqueue pq = malloc(sizeof (struct pqueue));
	pq -> h = calloc ( n+1 , sizeof(int));
	pq -> size = n;
	pq -> count = 0;  //quanti elementi ci sono
	return pq;
}

/* distrugge la coda di priorità */
void pqueue_destroy ( Pqueue pq ){
	free(pq);
}

/* restituisce la lunghezza della coda di priorità */
int pqueue_length ( Pqueue pq ){
	return (pq -> count); //o size
}

void swap ( Heap h, int i, int j){
	int k = h[i];
	h[i] = h[j];
	h[j] = k;
}

void heapify_up ( Heap h , int i ) {
	if(i > 1) {
		int j = h[i/2]; // father ( i );
		if ( h[i] < h[j] ){
			swap ( h , i , j );
			heapify_up ( h , j );
		}
	}
}

void heapify_down ( Heap h , int i , int n ) {
	if ( 2*i <= n ) {  /* i ha almeno un figlio */
		int j ; 	   /* indice del figlio di i con chiave minore*/
		if ( 2*i == n )/* i ha solo il figlio sinistro */
			j = 2*i;
		else 		   /* i ha due figli */
			j = (h[2*i] < h[2*i+1])	? 2*i : (2*i+1);
		if ( h[j] < h[i] ){
			swap ( h , i , j );
			heapify_down ( h , j , n );
		}
	}
}

/* inserisce l’Item nella coda di priorità */
void pqueue_insert ( Pqueue pq , int n ){
		pq -> h[(pq -> count)+1] = n;		//per via dello zero che non esiste
		(pq -> count++);
		heapify_up(pq->h, (pq-> count)); //qui è fatto lo heap, quindi ogni padre è minore di ogni figlio(in sto caso)
}

/* estrae dalla coda di priorità l’Item con chiave minima */ //lo elimina e si riposiziona tutto?
int pqueue_extractmin ( Pqueue pq){
	int min = (pq->h[1]);
	pq->h[1] = pq->h[pq->count] ;
	(pq -> count --);
	heapify_down(pq->h, 1, (pq->count));

	return min;
}

/* restituisce l’Item con chiave minima nella coda di priorità */
int pqueue_min ( Pqueue pq){
	return (pq-> h[1]); //h[0] non esiste per noi, iniziamo da 1
}


void pqueue_sort ( int a[] , int l , int r ){
	Pqueue new = pqueue_new(r-l);
	for(int i=l; i<r; i++){
		//printf("count : %d\n " ,new -> count);
		pqueue_insert(new, a[i]);
		//printf("count : %d, insered: %d\n " ,new -> count, a[i]);

	}
	int pr;
	printf("\nTrasformato in  heap: ");
	for(int i=l; i<r;i++)
		printf("%d ", new->h[i]);

	printf("\n");
	printf("count : %d\n " ,new -> count);
	printf("\nOrdinato con HeapSort: ");
	while((new->count) > 0){
		pr = pqueue_extractmin(new);
		printf("%d ", pr);
	}
	printf("\n");
	printf("count : %d\n " ,new -> count);
	pqueue_destroy(new);
}

/*crea una nuova coda di priorità Q
inserisci in Q un elemento di a alla volta
finchè Q non è vuota
estrai il minimo m da Q
stampa m*/

//h = {IGNORE , 1, 2, 5, 10, 3, 7, 11, 15, 17, 20, 9, 15, 8, 16}

int main(){
	int h[] = {0, 1, 2, 5, 10, 3, 7, 11, 15, 17, 20, 9, 15, 8, 16};
	for(int i=1; i<15;i++)
		printf("%d ", h[i]);
	printf("\n");

	pqueue_sort(h,1,15);
	return 0;
}
