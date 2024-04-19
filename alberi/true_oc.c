#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define WORD 30 //max char per le parole

struct occorrenza {
	char word[WORD] ;
	int n;
};
typedef struct occorrenza * Occorrenza;

struct bit_node {
	Occorrenza item ;
	struct bit_node *l , *r;
};
typedef struct bit_node * bit_node ;

bit_node bist_new (){  //non può esistere un'occorrenza senza un bit_node -> creo anche l'occorrenza
	bit_node new = malloc (sizeof (struct bit_node));
	Occorrenza occ = malloc(sizeof (struct occorrenza));
	occ -> n = 1;
	new -> item = occ;
	new -> l = NULL;
	new -> r = NULL;
	return new;
}

int bist_searchparent(bit_node r , char *stringa , bit_node * parent , bit_node *p){
	int res ;
	* parent = NULL ;
	*p = r;
	if ( !r )
		return -1;
	while ( *p && (res = strcmp(stringa, (*p)->item->word)) != 0 ){
		printf("s:%s res:%d\n",(*p)->item->word,res);
		*parent = *p;
		*p = res < 0 ? (*p) -> l : (*p) -> r;
	}
	if ( *p == NULL ) /* non ci sono nodi con chiave k */
		return -1;
	return 0;
}

void bist_insert ( bit_node *r , char *stringa) {
	bit_node parent, new = bist_new();
	bit_node q = *r;

	/* se l’albero e’ vuoto: */
	if ( q == NULL ) {
		*r = new ;
		//(*r)->item->n = 1; 	//setto a 1 l'occorenza della parola
		strcpy((*r)->item->word , stringa);
		printf("albero vuoto %s nuova occorrenza inserita nell'albero \n", stringa);
		return;
	}
	/* se la chiave c’e’ gia’ no, qui devo aumentare il contatore di occorrenze */
	int par =  bist_searchparent ( *r , stringa , &parent , &q );
	if ( par == 0 ) {
		q->item->n++;  //aumento il contatore
		printf ( "%s c'è già , aumentato il contatore: %d\n", stringa, q->item->n );
		free(new);
		return;
	}

	/* altrimenti inserisco il nuovo nodo come figlio di parent: */
	strcpy(new->item->word , stringa);
	printf("parent: %s\n",parent->item->word);
	printf("new : %s\n", new->item->word);
	printf("%s nuova occorrenza inserita nell'albero \n", stringa);
	if (strcmp(stringa, parent->item->word) < 0)
		parent -> l = new ;
	else
		parent -> r = new ;
}

void bist_printnode ( bit_node p ){
	if (p != NULL){
		printf("%s , %d\n", p -> item ->word , p->item->n);
	}
	else printf(" ");
}

void bist_orderprint ( bit_node p ){
	if ( p ) {
		bist_orderprint ( p -> l );
		bist_printnode ( p );
		bist_orderprint ( p -> r );
	}
}

void bist_invorderprint ( bit_node p ){
	if ( p ) {
		bist_invorderprint (p -> r );
		bist_printnode ( p );
		bist_invorderprint (p -> l );
	}
}

char *read_word( void ){
	char *p , c ;
	int n = 0 , size = 2;
	p = malloc ( size );
	while ( ( c = getchar () ) != ' ' ) {
		if ( n >= size ) {
			size *=2;
			p = realloc ( p , size );
		}
		if (isalpha(c) == 0){
			p[n] = '\0';
			break;
		}
		p[n++]=c;
	}
	return p ;
}

int main(){
	bit_node root = NULL;
	char *stringa;
	while (strcmp((stringa = read_word()), "STOP") != 0){  //it works bitch
		for(int i=0; i<strlen(stringa); i++){ //rendo minuscole tutte le parole
			if(isalpha(stringa[i])) stringa[i] = tolower(stringa[i]);
		}
		printf("%s\n", stringa);
		bist_insert(&root,stringa);
	}
	printf("STAMPA ORDINATA: \n");
	bist_orderprint(root);
	printf("STAMPA ORDINATA INVERTITA: \n");
	bist_invorderprint(root);
	return 0;
}
