#include <stdio.h>
#include <stdlib.h>

struct lapse{
	int start;
	int end;
	int value;
};
typedef struct lapse Lapse;

/*
6 //dimensione della schedule
6-9 4
1-5 2
2-7 4
11-15 1
10-14 2
3-12 7
*/

//Ordina  in base al tempo di fine
void sort(Lapse* schedule, int x);
//legge l'input e mette ogni intervallo in un array di lapse
Lapse* read_schedule(int x);
//stampa la schedule
void print_schedule(Lapse* schedule, int x);
//L'ultimo Lapse che finisce prima di j
int p(Lapse* schedule, int j);
//Valore della soluzione ottimale Sj
int opt(Lapse* schedule, int j);

//void free(Lapse* schedule);

int main(void) {
	int x;
	printf("Quanti intervalli?\n");
	scanf("%d", &x);
	printf("inseire gli intervalli\n");
	Lapse* schedule = read_schedule(x);
	sort(schedule, x);
	print_schedule(schedule, x);
	printf("_____________\n");
	int n = opt(schedule, x);
	printf("Valore massimo %d\n", n);
	printf("_____________\n");
	return 0;
}

Lapse* read_schedule(int x){
	int s, e, v;
	Lapse* schedule = calloc(x,sizeof(Lapse));
	for(int i=1; i<=x; i++){
		scanf("%d-%d %d", &s, &e, &v);
		Lapse q;
		q.start=s;
		q.end=e;
		q.value=v;
		schedule[i]=q;
	}
	return schedule;
}

void sort(Lapse* schedule, int x){
	Lapse temp;
	int scambiato;
	while(scambiato){
		scambiato=0;
		for(int i=2; i<=x; i++){
			if (schedule[i].end < schedule[i-1].end){
					temp=schedule[i];
					schedule[i]=schedule[i-1];
					schedule[i-1]=temp;
					scambiato=1;
			}
		}
	}
}

void print_schedule(Lapse* schedule, int x){
	int s, e, v;
	for (int i=1; i<=x; i++) {
		s = schedule[i].start;
		e = schedule[i].end;
		v = schedule[i].value;
		printf("%d-%d\t%d\n", s, e, v);
	}
	return;
}

int p(Lapse* schedule, int j){
	for(int i=j-1; i>0; i--){
		/*controlla la fine di tutti i lapse(i<j) e li confronta
		con l'inizio del lapse j */
		if (schedule[i].end < schedule[j].start){
			return i;
		}
	}
	return 0;
}

/* implemento la funzione ricorsiva :
	Opt(j) = max { vj + Opt(p(j)) , Opt(j −1) } */

int opt(Lapse* schedule, int j) {
	if(j==0){
		return 0;
	}
	if((schedule[j].value + opt(schedule,p(schedule,j))) > opt(schedule, j-1)) {

		return	schedule[j].value + opt(schedule, p(schedule,j));
	}
	else {

		return opt(schedule, j-1);
	}

}

void print_Lapse(Lapse i){
	printf("%d-%d\t%d\n", i.start, i.end, i.value);
}
