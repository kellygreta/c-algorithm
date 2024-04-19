#include <stdio.h>
#include <stdlib.h>

//elemeto della coda (implementazione tramite lista)
struct element{
	int n;
	struct element * next;
};
//CODA
struct queue{
	struct element *head;
	struct element * tail;
	int count;
};
typedef struct queue * Queue;

//mette un elemento in coda
void enqueue(Queue q, int n){
	struct element *new = malloc(sizeof(struct element));
	if (new == NULL) {
        // Gestisce l'errore di allocazione della memoria
        return;
    }
	new->n=n;
	new ->next=NULL;
	if(q->head==NULL){//se coda vuota
		q->head=new;//diventa il primo elemento
	}
	else{
		q->tail->next=new;//altrimenti diventa il next dell'ultimo
	}
	q->tail=new;
	q->count++;
}

//toglie il primo elemento
int dequeue(Queue q){
	if (q->head == NULL) {
        // Gestisce l'underflow (queue è empty)
        return -1; // indica errore
    }
	struct element * primo = q->head;
	int n = primo->n;
	q->head = q->head->next; //head punta al secondo
	free(primo);
	q->count--;
	return n;
}

Queue createqueue(){
	Queue q = malloc(sizeof(Queue));
	if (new == NULL) {
        // Gestisce l'errore di allocazione della memoria
        return;
    }
	q -> head = NULL;
	q -> tail = NULL;
	q -> count = 0;
	return q;
}

int emptyq(Queue q){
	struct element * primo = q->head;
	if(primo!=NULL){
		return 0;
	}
	return 1;
}

void destroyqueue(Queue q){
	while(!emptyq(q)){
		int n = dequeue(q);
	}
	 free(q); // Free the memory allocated for the queue structure
}
