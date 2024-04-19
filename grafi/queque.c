struct queue{
	struct element *head;
	struct element * tail;
	int count;
};
typedef struct queue * Queue;
void enqueue(Queue q, int n);
int dequeue(Queue q);
Queue createqueue();
int emptyq(Queue q);
int emptyq(Queue q);
void destroyqueue(Queue q);


//mette un elemento in coda
void enqueue(Queue q, int n){
	struct element *new = malloc(sizeof(struct element));
	new -> n = n;
	new -> next = NULL;
	if(q -> head == NULL){//se coda vuota
		q->head=new;//diventa il primo elemento
	}
	else{
		q->tail->next=new;//altrimenti diventa il next dell'ultimo
	}
	q -> tail = new;
	q -> count++;
}

//toglie l'primo elemento
int dequeue(Queue q){
	struct element * primo = q->head;
	int n = primo->n;
	q->head = q->head->next; //head punta al secondo
	free(primo);
	q->count--;
	return n;
}

Queue createqueue(){
	Queue q = malloc(sizeof(Queue));
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
		dequeue(q);
	}
}
