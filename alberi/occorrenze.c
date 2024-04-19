#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define WORD 20 //max char per le parole

struct occorrenza {
	char word[WORD];
	int n;
};
typedef struct occorrenza * Occorrenza;

struct bit_node {
	Occorrenza item ;
	struct bit_node *l , *r;
};
typedef struct bit_node* Bit_node ;

//non può esistere un'occorrenza senza un bit_node, quindi creo anche l'occorrenza
Bit_node bist_new ();

int bist_searchparent( Bit_node r , char *parola , Bit_node * parent , Bit_node *p);

void bist_insert ( Bit_node *r , char *parola);

void bist_printnode ( Bit_node p );

//stampa il contenuto dell’albero di ricerca in ordine (dal nodo con chiave minima al nodo con chiave massima)
void bist_orderprint ( Bit_node p );

//ordine inverso
void bist_invorderprint ( Bit_node p );

char *read_word( void );

int main(void){
	//int n = strcmp(const char *s1, const char *s2); come funziona str cmp
	Bit_node root = NULL;
	char *parola;
	int stop=0;
	Bit_node parent;	//Serve per chiamare bist_searchparent
	Bit_node q = root;	//Serve per chiamare bist_searchparent

	while ( (strcmp((parola = read_word()), "STOP") != 0) || stop!=1) {

		if (strcmp(parola, "STOP") == 0) {	// PRIMO STOP

			//STAMPE
			printf("\nOCCORRENZE DI PAROLE NEL TESTO IN ORDINE ALFABETICO\n");
			bist_orderprint (root);
			printf("\nOCCORRENZE DI PAROLE NEL TESTO IN ORDINE INVERSO:\n");
			bist_invorderprint (root);
			printf("\nRICERCA:\n");

			stop++;

			while  ((strcmp((parola = read_word()), "STOP") != 0)) {	// Seconda fase di lettura

				for(int i=0; i<strlen(parola); i++){	//to lower case
					if(isalpha(parola[i])) parola[i] = tolower(parola[i]);
				}

				if (bist_searchparent(root, parola, &parent, &q)==0) {	//NB= se searchparent trova parola, mette in q il nodo che la contiene
					bist_printnode(q);	//Quindi se la trovata stampo q
				} else {	//Altrimenti stampo manualmente " parola : 0 "
					printf("%s : 0\n", parola);
				}

			}

		}

		if (stop)	// Se entra nell'IF mi fermo
			break;

		//Se il programma arriva qui vuol dire che non è arrivato neanche uno stop, quindi prosegue riempiendo l'albero

		for(int i=0; i<strlen(parola); i++){
			if(isalpha(parola[i])) parola[i] = tolower(parola[i]);
		}
		//printf("%s\n", parola);
		bist_insert(&root, parola);
	}

	return 0;
}

char* read_word( void ){
	char *p , c ;
	int n = 0 , size = 2;
	p = malloc(size);
	while ((c=getchar())!= EOF){
		if (n>=size){ //spazio terminato
			size *=2; //raddoppio
			p = realloc (p,size);
		}
		if (c == '\n' || c== ' ') { // fine stringa , interrompo
		  p[n] = '\0';
		  break ;
		}
		if (isalpha(c) == 0)
		  continue;
		p[n++] = c;
	}
	return p ;
}

Bit_node bist_new (){
	Bit_node new = malloc (sizeof (struct bit_node));
	Occorrenza occ = malloc(sizeof (struct occorrenza));
	occ -> n = 1;
	new -> item = occ;
	new -> l = NULL;
	new -> r = NULL;
	return new;
}

int bist_searchparent ( Bit_node r , char *parola , Bit_node * parent , Bit_node *p ) {
	int res;
	*parent=NULL;
	*p=r;
	if(!r){
		return -1;
	}

	while(*p && (res=strcmp( parola, (*p)->item->word)) != 0){
		* parent = *p;
		*p = res < 0 ? (*p)->l : (*p)->r;
	}

	if(*p == NULL) //non ci sono nodi con chiave k
		return -1;
	return 0;
}

void bist_printnode ( Bit_node p ){
	if (p!=NULL){
		printf("%s : %d\n", p->item->word, p->item->n);
	}
	else printf(" ");
}

void bist_orderprint ( Bit_node p ){
	if ( p ) {
		bist_orderprint ( p -> l );
		bist_printnode ( p );
		bist_orderprint ( p -> r );
	}

}
void bist_invorderprint ( Bit_node p ){
	if ( p ) {
		bist_invorderprint (p -> r );
		bist_printnode ( p );
		bist_invorderprint (p -> l );
	}
}

void bist_insert ( Bit_node *r , char *parola){
	Bit_node parent;
	Bit_node new = bist_new();
	Bit_node q = *r;

	//se l’albero e’ vuoto:
	if (q==NULL){
		*r=new;
		strcpy((*r)->item->word , parola); //copia parola in un nuovo nodo
		return;
	}

	//se la chiave c’e’ gia’, non inserisco niente:
	if (bist_searchparent(*r, parola, &parent, &q)==0){//trovo il valore parent!
		q->item->n++;  //aumento il contatore
		free(new);
		return;
	}

	strcpy(new->item->word , parola); ///copia parola in un nuovo nodo
	//altrimenti inserisco il nuovo nodo come figlio di parent
	if (strcmp(parola, parent->item->word)<0){
		parent->l = new;
	}
	else{
		parent->r = new;
	}
}

int bist_search ( Bit_node r, char *parola){
	int sum=0;
	Bit_node parent=NULL, p=NULL;
	if(bist_searchparent(r, parola, &parent , &p)==0){
		sum++;
	}
	return sum;
}
