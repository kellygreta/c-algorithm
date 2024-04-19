#include <stdio.h>
#include <stdlib.h>

struct element{
	int n; //o char ch?
	struct element * next;
};
//CODA
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

struct listnode {
	struct listnode * next ;
	int key;
};

struct graph {
	int V, E; //V=numero di nodi, E=numero di archi
	struct listnode ** A; //array di lista di adiacenza
};
typedef struct graph * Graph ;

int degree (Graph g, int v);

// crea un grafo con n nodi
Graph graph_new ( int n );

// distrugge il grafo g
void graph_destroy ( Graph g );

//inserisce i vertici nelle liste di adiacenza
struct listnode *vertexinsert(struct listnode *p, int k);

// inserisce l’arco (a,b) nel grafo g
void graph_edgeinsert ( Graph g , int a , int b );

// legge da standard input un grafo
Graph graph_read ( void );

//stampa su standard output un grafo
void graph_print ( Graph g );

//ATTRAVERSAMENTO IN PROFONDITA'
void dfs1(Graph g, int i, int *aux);
void dfs(Graph g);

//ATTRAVERSAMENTO IN AMPIEZZA
void bfs1(Graph g, int i, int *aux);
void bfs(Graph g);

int degree (Graph g, int v);

int main(void){
	Graph g = graph_read();
	graph_print(g);
	printf("\nVISITA IN AMPIEZZA\n");
	bfs(g);
	graph_destroy(g);
	return 0;
}

Graph graph_new ( int n ){
	int i; Graph g;
	//alloca lo spazio per una struct graph
	g = malloc (sizeof(struct graph ));

	//alloca lo spazio per un array di n puntatori a liste di adiacenza
	g->A= calloc (n , sizeof(struct listnode*));

	for (i=0; i<n; i++){

		// alloca lo spazio per l’array A[i] di n interi, inizialmente nulli
		g->A[i]=NULL;
		//### rimosso calloc perchè sovradimensionava.
		//Ora gli elementi di A puntano tutti a NULL e deleghiamo il problema ad edgeinsert

		g -> V = n;
	}
	return g;
}

void graph_destroy ( Graph g ){
	free(g);
}

void graph_edgeinsert ( Graph g , int a , int b ){

	struct listnode *x = malloc(sizeof(struct listnode));
	struct listnode *y = malloc(sizeof(struct listnode));

	/*###
	La calloc era ridondante perchè la memoria viene
	allocata da queste malloc singole
	###*/

	//creo i nodi e assegno key a, b
	x->key=a;
	y->key=b;

	/*###
	Dobbiamo gestire meglio l'inserimento dei listnode,
	distinguendo il caso di primo inserimento da gli altri.
	###*/

	if(g -> A[b-1] == NULL) {	//Primo inserimento
		g -> A[b-1] = x;		//A[b-1] deve puntare al suo primo (ed unico) elemento
		x -> next = NULL;		//x è ultimo quindi gli segue NULL
	}
	else {						//inserimenti successivi ->solita regola
		//inserisco il nuovo elemento nella lista
		x -> next = g -> A[b-1];

		//aggiorno il puntatore della lista
		g->A[b-1]=x;
	}

	//STESSA COSA MA CON A[a-1]
	if(g -> A[a-1] == NULL) {	//Primo inserimento
		g -> A[a-1] = y;
		y -> next = NULL;
	}
	else {						//inserimenti successivi
		y -> next = g -> A[a-1];
		g -> A[a-1] = y;
	}

	g->E++;	//aumento E(numero di archi)

}

Graph graph_read ( void ){
	int n, v1, v2;
	printf("Numero nodi\n");
	scanf("%d", &n);
	Graph g = graph_new(n);
	printf("Inserire vertici\n");

	for (int i=0; i<n*n; i++) {
		scanf("%d %d", &v1, &v2);
		if (v1 == -1 && v2 == -1) {
			printf("\n");
			break;
		}
		graph_edgeinsert(g, v1, v2);
	}
	return g;
}

void graph_print ( Graph g ){
	for (int i=0; i<g->V; i++){
		int j=i+1;
		printf("%d -> ",j);		//stampo gli indici degli array
		struct listnode * e;
		for (e=g->A[i]; e!=NULL; e=e->next) {
			int n=e->key;
			if(n==0)
				break;
			printf("%d, ", n); //stampo i vertici
		}
		printf("\n");
	}
	return;
}

void dfs1(Graph g, int i, int *aux) {
	struct listnode *t;
	aux[i]=1;
	for(t=g->A[i]; t; t=t->next){
		if(!aux[t->key - 1]) {
			printf("%d,",t->key);
			dfs1(g,t->key-1,aux);
		}
	}
}

void dfs(Graph g) {
	int i, *aux = calloc(g->V,sizeof(int));
	if(!aux) {
		fprintf(stderr,"Errore di Allocazione\n");
		exit(-4);
	}
	for(i = 0; i < g->V; i++){
		if(!aux[i]) {
			printf("\n%d,",i+1);
			dfs1(g,i,aux);
		}
	}
	free(aux);
}

void bfs1(Graph g, int i, int *aux) {
	struct listnode *t;
	Queue q = createqueue();
	enqueue(q,i);
	while(!emptyq(q)) {
		i = dequeue(q);
		aux[i] = 1;
		for(t = g->A[i]; t; t = t->next) {
			if(!aux[t->key - 1]) {
				enqueue(q,t->key -1);
				printf("%d,",t->key);
				aux[t->key-1] = 1;
			}
		}
	}
	destroyqueue(q);
}

void bfs(Graph g) {
	int i, *aux = calloc(g->V,sizeof(int));
	if(!aux){
		fprintf(stderr,"Errore di Allocazione\n");
		exit(-4);
	}
	for(i = 0; i < g->V; i++){
		if(!aux[i]) {
			printf("\n%d:",i+1);
			bfs1(g,i,aux);
			printf("\n");
		}
	}
	free(aux);
}

//calcola il grado del vertice v
int degree (Graph g, int v){
	int c = 0;
	struct listnode * e;
	for (e=g->A[v-1]; e!=NULL; e=e->next) {	//### modificato da A[v] a A[v-1] (partiamo da zero)
		c++;
	}
	return c;
}


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
