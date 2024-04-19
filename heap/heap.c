#include <stdlib.h>
#include <stdio.h>
//HEAP
typedef int * Heap ;

struct pqueue {
Heap h;
int size , count ;
};
//CODA DI PRIORITA'
typedef struct pqueue* Pqueue ;

/*crea una coda di priorità vuota che potrà contenere al massimo n int*/
Pqueue pqueue_new ( int n );

void pqueue_destroy ( Pqueue pq);

int pqueue_length ( Pqueue pq );

/*inserisce n nella coda di priorità*/
void pqueue_insert ( Pqueue pq , int n);

/*estrae dalla coda di priorità int con chiave minima*/
int pqueue_extractmin ( Pqueue pq );

/*restituisce int con chiave minima nella coda di priorità*/
int pqueue_min ( Pqueue pq );

//INSERIMENTO
void heapify_up (Heap h, int i);
//CANCELLAZIONE
void heapify_down (Heap h, int i, int n);

int father(Heap h, int i);
void swap(Heap h, int a, int b);

//ordina la porzione compresa tra gli indici l e r dell’array a
void pqueue_sort (int a[], int l, int r);

int main(void){

	int h[] = {0, 1, 2, 5, 10, 3, 7, 11, 15, 17, 20, 9, 15, 8, 16};

	printf("array iniziale: ");
	for(int i=1; i<15;i++)
		printf("%d ", h[i]);
	printf("\n");

	// 1 2 3 5 7 8 9 10 11 15 15 16 17 20
	pqueue_sort(h,1,15);

	/*printf("LUNGHEZZA : %d\n", pqueue_length (pq));
	printf("MINIMO ESTRATTO : %d\n", pqueue_extractmin(pq));
	printf("LUNGHEZZA dopo : %d\n", pqueue_length (pq));*/
	return 0;
}

int father( Heap h, int i){
	return h[i/2];
}
void swap(Heap h, int a, int b){
	int k;
	k = h[a];
	h[a] = h[b];
	h[b] = k;
}

void heapify_up ( Heap h , int i ) {
	if (i>1){
		int j=father(h, i);
		if (h[i]<h[j]) {
			swap (h, i, j);
			heapify_up (h, j);
		}
	}
}

void heapify_down (Heap h, int i, int n){
	if ( 2*i <= n ) { // i ha almeno un figlio
		int j ; // indice del figlio di i con chiave minore
		if ( 2*i == n ){ // i ha solo il figlio sinistro
			j = 2* i ;
		}
		else{// i ha due figli
			j = h[2*i] < h[2*i+1] ?  2*i : 2*i+1;
		}
		if (h[j]<h[i]){
			swap (h, i, j);
			heapify_down (h, j, n);
		}
	}
}

Pqueue pqueue_new ( int n ){
	Pqueue pq = malloc(sizeof(struct pqueue));
	pq->h = malloc(sizeof(int)*(n+1));
	pq->size = n;
	pq->count = 0;
	return pq;
}

void pqueue_destroy ( Pqueue pq ){
	free(pq);
}

int pqueue_length ( Pqueue pq ){
	return pq-> count;
}

void pqueue_insert ( Pqueue pq , int n){
	pq->h[(pq->count)+1]=n;
	pq->count++;
	heapify_up (pq->h,pq->count);
}

int pqueue_extractmin ( Pqueue pq ){
	int min = pq->h[1];
	pq->h[1] = pq->h[pq->count];
	pq->count--;
	heapify_down(pq->h, 1, pq->count);
	return min;
}

int pqueue_min ( Pqueue pq){
	return pq-> h[1];
}


void pqueue_sort ( int a[] , int l , int r ){
	Pqueue pq = pqueue_new(r); //crea una nuova coda di priorità Q
	for(int i=l; i<r; i++){//inserisci in Q un elemento di a alla volta
		pqueue_insert(pq,a[i]);
	}
	printf("pq->h[i]: ");
	for(int i=l; i<r;i++){
		printf("%d ", pq->h[i]);
	}
	printf("\n");

	int min;	
	printf("pqueue_sort: ");
	while(pq->count>0){//finchè Q non è vuota
		min = pqueue_extractmin(pq);//estrai il minimo m da Q
		printf("%d " ,min);//stampa m
	}
	printf("\n");
	pqueue_destroy(pq);
}
