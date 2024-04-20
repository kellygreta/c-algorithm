# Algoritmi in c
Il repo copre vari concetti di algoritmi e strutture dati, tra cui pile, code, alberi, grafi e programmazione dinamica. La pila e la coda sono strutture dati LIFO e FIFO rispettivamente, con operazioni specifiche per manipolare i dati. Gli alberi sono strutture dati con nodi e archi, con varie tipologie come gli alberi binari. I grafi sono strutture dati utilizzate per modellare relazioni tra oggetti, con varie rappresentazioni e tecniche di esplorazione. La programmazione dinamica è una tecnica che risolve problemi complessi suddividendoli in sottoproblemi più semplici.
## Pila
La pila è una struttura dati in cui i dati sono impilati uno sopra l'altro e che segue una politica LIFO (Last In, First Out). Con una pila, possiamo eseguire una serie di operazioni:

- Verificare se la pila è vuota con la funzione ```isEmpty()```, che restituisce un valore booleano.
- Inserire un elemento nella pila con la funzione ```push(elemento)```, che posiziona un elemento in cima alla pila.
- Rimuovere un elemento dalla pila con la funzione ```pop()```, che estrae l'elemento in cima alla pila e lo restituisce.
- Verificare qual è l'elemento in cima con la funzione ```top()```, che restituisce l'elemento in cima alla pila senza modificarlo.

Una pila può essere implementata in vari modi, tra cui array e liste.

Gli array presentano alcuni problemi: hanno una dimensione finita e le funzioni pop e top, se la pila è vuota, non puntano a nulla. Le liste risolvono il problema della dimensione finita, ma l'altro problema persiste.
## Coda
Una struttura dati che segue la politica FIFO, First In First Out, è nota come coda.

Una coda può avere elementi con priorità. In particolare, il primo elemento avrà la priorità più alta, mentre l'ultimo avrà la minima. In questo caso, ci riferiamo ad essa come una coda di priorità. Con la coda, possiamo eseguire una serie di operazioni:

- Verificare se la coda è vuota tramite la funzione ```isEmpty()```, che restituisce un valore booleano.
- Inserire un elemento nella coda con la funzione ```enqueue(elemento)```, che aggiunge un elemento alla fine della coda.
- Rimuovere un elemento dalla coda tramite la funzione ```dequeue()```, che estrae il primo elemento della coda e lo restituisce.

La coda può essere implementata tramite array o liste. Con l'array, incontriamo un problema: la coda può esaurirsi. Una possibile soluzione è considerare l'array come circolare, gestendo quindi l'inizio e la fine della coda con due puntatori e basando le operazioni su di essi.

Un'altra implementazione possibile è tramite **liste**.
## Alberi
Un albero è una struttura dati composta da due componenti fondamentali: i nodi e gli archi. I nodi contengono informazioni, mentre gli archi collegano i nodi a coppie.

Un albero è una struttura vuota o un nodo a cui sono associati k≥0 alberi. Ogni nodo ha un solo genitore.

Una foglia è un nodo senza figli, e il grado di un nodo corrisponde al numero dei suoi figli. La profondità o il livello di un nodo è il numero di archi da attraversare per raggiungere quel nodo partendo dalla radice, mentre l'altezza di un albero è la massima profondità a cui si trova una foglia.

Un albero binario è un albero in cui i nodi hanno un grado compreso tra 0 e 2. Il numero minimo di nodi in un albero binario di altezza h è h+1, mentre il numero massimo di nodi è 2<sup>h</sup> - 1. Un albero binario con k foglie ha un'altezza ≥ log k. Se un albero binario ha n nodi, l'altezza sarà n-1 nel caso peggiore (degenere in una lista), oppure O(logn) nel caso migliore.

Esistono due tipi di visite: in ampiezza e in profondità.

- L'algoritmo per la visita in ampiezza segue lo schema: ```dequeue(n)```, ```visita(n)```, ```enqueue(n.sx)```, ```enqueue(n.dx)```, partendo dalla radice fino all'ultima foglia dell'ultimo livello.
- L'algoritmo per la visita in profondità segue lo schema: ```pop(n)```, ```visita(n)```, ```push(n.sx)```, ```push(n.dx)```, partendo dalla radice fino all'ultima foglia dell'ultimo livello. Questa visita presenta tre varianti ricorsive: ordine anticipato, ordine posticipato, ordine simmetrico.

Nel caso degli alberi binari di ricerca, per ogni nodo padre, i valori del sottoalbero sinistro sono minori del padre, e i valori del sottoalbero destro sono maggiori del padre. 

Un albero è perfettamente bilanciato se per ogni nodo il numero di nodi del sottoalbero sinistro differisce al massimo di uno dal numero di nodi del sottoalbero destro. Un albero è bilanciato se per ogni nodo, l'altezza del sottoalbero sinistro differisce al massimo di uno dall'altezza del sottoalbero destro. 

## Grafi

Un grafo è una struttura dati utilizzata per modellare situazioni reali in cui vari oggetti vengono messi in relazione. È composto da vertici (o nodi) e archi. I vertici contengono le informazioni, mentre gli archi collegano i nodi tra loro. Il grafo può essere orientato o non orientato.

Nel grafo orientato, la disposizione dei nodi è importante nella definizione degli archi. Supponendo di avere due nodi A e B, l'arco (A,B) indica che possiamo andare dal nodo A al nodo B, ma non viceversa. L'arco esce da A ed entra in B. Al contrario, in un grafo non orientato, l'arco (A,B) indica che è possibile percorrere l'arco da A a B e viceversa.

Se vogliamo verificare i nodi adiacenti a un vertice X in un grafo orientato, dobbiamo fare attenzione alla direzione dell'arco. Se (x, y) è un arco del grafo, questo incide sui vertici x e y.

Supponendo di avere un grafo G=(<V,E>), consideriamo i nodi A -> B -> C.

- Catena: sequenza di vertici A,B,C che posso percorrere da A a C e da C ad A.
- Cammino: sequenza di vertici A,B,C che posso percorrere solo da A a C, non viceversa, perché segue la direzione degli archi.
- Circuito: catena con vertice iniziale uguale al vertice finale, quindi che partendo da un vertice arriva a quel vertice.
- Ciclo: cammino da un vertice x al vertice x stesso. Un ciclo semplice è senza ripetizioni.

Un grafo si dice connesso se per ogni vertice x, y esiste una catena da x a y. Un grafo è fortemente connesso se per ogni vertice x, y esiste un cammino da x a y. Nei grafi non orientati, catena equivale a cammino, quindi un grafo non orientato connesso è anche fortemente connesso.

Un sottografo è un qualsiasi grafo che ha l'insieme dei vertici minore dell'insieme dei vertici di un altro grafo e l'insieme degli archi contenuto nell'insieme degli archi dell'altro grafo. È un sottoinsieme del grafo di partenza. Un sottografo indotto ha come insieme degli archi tutti gli archi del grafo di partenza incidenti sui vertici del sottografo considerato.

Una componente connessa è un sottografo indotto connesso, mentre una componente fortemente connessa è un sottografo indotto fortemente connesso.

Alcuni termini importanti: 
- Cricca: grafo con tutti i vertici collegati tra loro.
- Albero: grafo non orientato, connesso e privo di cicli.
- Foresta: insieme di alberi non connessi tra loro.

Le rappresentazioni di un grafo possono essere: lista di archi, lista di adiacenza, matrice di adiacenza, lista di incidenza, matrice di incidenza.

Esistono due tecniche principali per esplorare un grafo: visita in ampiezza e visita in profondità.

Con queste visite, è possibile creare alberi di supporto minimi. In particolare, ci sono due algoritmi: Kruskal e Prim, che prendono in input dei grafi in cui ogni arco ha un suo peso. Il peso è una funzione ω che associa a ogni arco un numero.
## Programmazione Dinamica
La programmazione dinamica è una tecnica che consiste nel risolvere un problema cercando versioni semplificate dello stesso. Si creano n versioni del problema e si risolvono una per una, dal più semplice al più complesso. La soluzione al problema originale sarà una di queste soluzioni prese singolarmente o l'unione di queste soluzioni con altre istruzioni. La principale differenza rispetto ad altre tecniche di programmazione è che, mentre "divide et impera" tratta i sottoproblemi come se fossero indipendenti, la programmazione dinamica risolve i sottoproblemi utilizzando anche le soluzioni già trovate.
