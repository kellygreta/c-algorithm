#include <ctype.h>//serve per implementare funzioni che lavorano su char (come getchar())
#include <stdlib.h> //malloc
#include <stdio.h>

struct element{
	int info ; //valore
	struct element * next ; //puntatore al prossimo element
};
typedef struct element element;

element* insert (int n,element* h);
void printList (element* h);
int isMember (int n, element* h);
element * delete (int n, element * h);
void destroy (element * h);
int* listToArray (element * h ,int n);
void printInv (element * h );
void insertNodeAtBeginning(int n);

int main(void){
	int contatore=0;
	int n;
	char c;
	int * arr;
	element* head = NULL; //puntatore alla testa(lista vuota)

	while((c=getchar())!='f'){
		switch(c){
		case '+':
			scanf("%d", &n);
			head = insert(n,head);
			contatore++;
		break;
		case '-':
			scanf("%d",&n);
			head=delete(n,head);
			contatore--;
		break;
		case '?':
			scanf("%d", &n);
			printf("%d", isMember(n,head));
		break;
		case 'p':
			printList(head);
		break;
		case 'a':
			arr = listToArray(head,contatore);
			for(int j=n-1; j>=0; j--){
				printf("%d ",arr[j]);
			}
			printf("\n");
			free(arr);
		break;
		case 'i':
			 printInv (head);
			 printf("\n");
		break;
		case 't':
			scanf("%d", &n);
			insertNodeAtBeginning(n);
		break;
		case 'd':
			destroy(head);
			head = NULL; // Reset head after destroying the list        
		break;

		}
	}

	destroy(head); // Free any remaining memory
	return 0;
}

void* mymalloc(size_t size){
	void* p = malloc(size);
	if(p==NULL){
		printf(stderr, "ERROR MALLOC");
		exit(EXIT_FAILURE);
	}
	return p;
}

element* insert (int n ,element* h){
	if(isMember(n,h)==0){
		element* e;
		e=mymalloc(sizeof(element));
		e->info=n;
		e->next=h;
		return e;
	}
	else{
		printf("element already in the list");
		return h;
	}
}

void printList ( element * h){
	element* e=h;
	while(e!=NULL){
		printf("%d ",e->info);
		e=e->next;
	}
	printf("\n");
	return;
}

int isMember (int n , element * h){
	element* e=h;
	while(e!=NULL){
		if(e->info==n){
			return 1;
		}
		e=e->next;
	}
	return 0;
}

element * delete (int n , element * h){

	element* e=h;

	if(isMember(n,h)==1){

		if(n==h->info){
			h=h->next;
			free(e); //cancello spazio di memo dedicato al primo elemento
			return h;
		}

		else{
			element* prev=NULL; //precedente
			while(e!=NULL){
				if(e->info==n){
					prev->next=e->next;
					free(e);
				}
				prev=e;
				e=e->next;
			}
			return h;
		}
	}
	else{
		return h;
	}
}

void destroy ( element * h){
	element* e=NULL;
	while(h!=NULL){
		e=h;
		free(e);
		h=h->next;
	}
}

int* listToArray ( element * h ,int n){
	int * arr = malloc(sizeof(int)*n), i=0; //array grande come un solo int
	element* e=h;
	while(e!=NULL){
		*(arr+i)=e->info;
		e=e->next;
		i++;
	}
	return arr;
}

void printInv ( element * h ){
	element* e=h;
	if(e->next==NULL){
		printf("%d ",e->info);
		return;
	}
	printInv(e->next);
	printf("%d ",e->info);
	return;
}

//inserisci un nodo in testa
/*

void insertNodeAtBeginning(element** h, int n) {
    element* new_node = mymalloc(sizeof(element));
    new_node->info = n;
    new_node->next = *h;
    *h = new_node;
}

void insertNodeAtBeginning(element * h,int n){

	element* e;
	e=mymalloc(sizeof(element));
 	e->info=n;

    if(newNode == NULL)
	{
        printf("Unable to allocate memory.");
    }
	else
	{
        newNode->data = data; // Link data part
        newNode->next = head; // Link address part

        head = newNode; // Make newNode as first node

        printf("DATA INSERTED SUCCESSFULLY\n");
    }
}*/
