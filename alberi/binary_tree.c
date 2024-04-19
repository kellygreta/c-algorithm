#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
//1 2 3 4 5
struct bit_node {
	int info;
	struct bit_node *l , *r;
};
typedef struct bit_node* Bit_node; //puntatore a bitnode

Bit_node bit_new ( int n );

void bit_printnode ( Bit_node );

void bit_preorder ( Bit_node );
void bit_inorder ( Bit_node );
void bit_postorder ( Bit_node );

Bit_node bit_arr2tree ( int a[] , int size , int i);

void bit_printassummary ( Bit_node p , int spaces);

int main(void){

	int a[4] ={1,2,3,4};
	Bit_node root = bit_arr2tree(a,4,0);

	printf("summary: \n");
	bit_printassummary (root , 0);

	printf("\n");
	printf("PRE: ");
	bit_preorder ( root );

	printf("\n");
	printf("IN: ");
 	bit_inorder ( root );

	printf("\n");
	printf("POST: ");
	bit_postorder ( root );
	printf("\n");

}

void bit_inorder ( Bit_node p ){
	if (p) {
		bit_inorder (p->l);
		bit_printnode (p);
		bit_inorder (p->r);
	}
}
void bit_preorder ( Bit_node p ){
	if (p) {
		bit_printnode (p);
		bit_preorder (p->l);
		bit_preorder (p->r);
	}
}
void bit_postorder ( Bit_node p ){
	if (p){
		bit_postorder (p->l);
		bit_postorder (p->r);
		bit_printnode (p);
	}
}

void bit_printnode ( Bit_node p ){
	if(p!=NULL){
		printf("%d ", p->info);
	}
}


Bit_node bit_new (int n){
	Bit_node r = malloc (sizeof(struct bit_node));
 	r->info=n;
	r -> l = NULL;
	r -> r = NULL;
	return r;
}

Bit_node bit_arr2tree ( int a[] , int size , int i){
	if(i>=size){
		return NULL;
	}
	else{
		Bit_node r = bit_new(a[i]);
		r->l = bit_arr2tree(a,size, 2*i+1);
	 	r->r = bit_arr2tree(a,size, 2*i+2);
		return r;
	}
}

void bit_printassummary ( Bit_node p , int spaces){
	for(int i=0; i<spaces; i++){
		printf(" ");
	}
	if(p){
		printf("*");
		bit_printnode(p);
		printf("\n");
		if(p->l!=NULL || p->r!=NULL){
			bit_printassummary(p->l, spaces+2);
			bit_printassummary(p->r, spaces+2);
		}
	}
	else{
		printf("*\n");
	}
}
