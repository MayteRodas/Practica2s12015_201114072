#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <time.h> 

# define max(A,B) ((A)>(B)?(A):(B))
# define min(A,B) ((A)>(B)?(B):(A))

/////////////////////////////////////////////////////STRUCTS A UTILIZAR///////////////////////////////////////////////////////////////
typedef struct avlnode
{
	int clave;
    int fe; /* Factor de feance -1,0,1 */
    struct avlnode *left, *right;
} nodo, *pnodo;


typedef struct nodoLista
{
    int val;
    struct nodoLista *sig;
} NodoLista;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////METODOS DE CONTROL PARA LA APP////////////////////////////////////////////////
int menuPrincipal();
void CargarDatos();
void DarHora();
int split(char *hora);
clock_t clock(void);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////AQUI ESTAN LOS METODOS DEL AVL///////////////////////////////////////////////////////
pnodo InsertarAVL(int clave, pnodo t);
void inorder(pnodo t, int profundidad);

NodoLista *InsertarLL(NodoLista *head, int val);

//NodoLista *quicksort(NodoLista *primero);
NodoLista *burbuja(NodoLista *head);

////////////////////////////////////////////////////////VARIABLES GLOBALES PARA EL ARBOl////////////////////////////////////////////////////////////
int flag;

int key; 
int alto_avl = 0; 
pnodo raiz=NULL;

NodoLista *head;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
  int op;
	do{
		op=menuPrincipal();	
		switch(op)
		{
				case 1:	{
							//Cargar Datos
							printf("Cargar Datos, si entro ");
							CargarDatos();
							break;
						}
				case 2:	{
							//Ver Tiempos
							printf("Ver Tiempos:");
							DarHora();
							break;
						}
				case 3:	{
							//Mostrar salidas
							printf("Mostrar salidas:");
							
							while(head!=NULL){
								printf("%d\n ", head->val);
								head=head->sig;
							}
							break;
						}
				case 4: {
							//Graficas
							printf("Graficas:");
							tiempo();
							break;
						}
		}
	}while(op!=5);
	
	
	return 0; 
}
/////////////////////////////////////////////////////////////MENU PRINCIPAL/////////////////////////////////////////////////////////////////////////
int menuPrincipal()
{
	int opcion;
	puts("*************           BIENVENIDOS           ************");
	puts("1) Cargar Datos                                        ***");
	puts("2) Ver tiempos                                         ***");
	puts("3) Mostrar salidas                                     ***");
	puts("4) Graficas                                            ***");
	puts("5) Salir                                               ***");
	puts("Ingrese una opcion:");
	scanf("%d",&opcion);
	return opcion;
}

/////////////////////////////////////////////////////////////CARGA DE DATOS//////////////////////////////////////////////////////////////////////

void CargarDatos()
{	
	printf("entro al metodo");
    FILE *fp;
    char *c, cad[100];

	fp=fopen("prueba.txt", "r");

	while((c=fgets(cad,100,fp)))
	{
		//printf("%s",cad); 
		int num = atoi(cad);
		//printf(">>>>>%d<<<<<<<",num);
		raiz=InsertarAVL(num, raiz);
		
		head=InsertarLL(head, num);
		burbuja(head);
		//quicksort(head);
		//MetodoBurbuja(num);
		
	}
	inorder(raiz, 0);
}

///////////////////////////////////////////////////////////////DAR HORA///////////////////////////////////////////////////////////////////////

void DarHora()
{
	time_t tiempo;
	char cad[80];
	struct tm *tmPtr;

	tiempo = time(NULL);
	tmPtr = localtime(&tiempo);
	strftime( cad, 80, "%H:%M:%S, %A de %B de %Y", tmPtr );

	printf( "La hora local es: %s\n", asctime(tmPtr) );
	printf( "La hora y fecha locales son: %s\n", cad );
	split(asctime(tmPtr));
	
} 

/////////////////////////////////////////////////////////////SPLIT/////////////////////////////////////////////////////////////////////////

int split(char *hora){
	int con=1;
	int total=0;
    char *input= hora;
  
	char* token; 
	token = strtok(input," "); 

	while(token != NULL) 
		{ //obtiene el siguiente token 
			token = strtok(NULL," "); 

			if(con==3)
			{
				printf("%s\n",token);
				puts("aqui es dos");
			
				char* token1; 
				int cont=0;
				token1 = strtok(token,":"); 
				printf("%s\n",token1);
				int num = atoi(token1);
				total=total +(num*3600);
				puts("es esta subtotal");
				printf("%d\n",total);
				while(token1 != NULL) 
				{ //obtiene el siguiente token 
					token1 = strtok(NULL,":"); 
					printf("%s\n",token1);
									if(cont==0)
					{
						int num = atoi(token1);
						total=total +(num*60);
									puts("es esta subtotal");
									printf("%d\n",total);
					}
					else
					{				
						int num = atoi(token1);
						total=total +(num);
						puts("es esta subtotal");
						printf("%d\n",total);
					}				
					cont++;
				}
			}
			con++;
		}

    return total;
}

//////////////////////////////////////////////////////////la hora/////////////////////////////////////////////////////////

int tiempo()
{
   clock_t start_t, end_t, total_t;
   int i;

   start_t = clock();
   printf("Starting of the program, start_t = %ld\n", start_t);
    
   printf("Going to scan a big loop, start_t = %ld\n", start_t);
   for(i=0; i< 10000000; i++)
   {
   }
   end_t = clock();
   printf("End of the big loop, end_t = %ld\n", end_t);
   
   total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
   printf("Total time taken by CPU= %ld\n", total_t  );
   printf("Exiting of the program...\n");

   return(0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////ARBOL AVL/////////////////////////////////////////////////////////
/* Rotación Izquierda *
*  A           B
* / \         / \
* a  B ==>   A   c
*   / \     / \
*   b  c    a  b
 */
static pnodo lrot(pnodo t)
{
    pnodo temp;
    int x,y;
    temp = t;
    t = t->right;
    temp->right = t->left;
    t->left = temp;
    //Recalcula factores de balance de los dos nodos
    x = temp->fe; 
    y = t->fe; 
    temp->fe = x-1-max(y, 0); 
    t->fe = min(x-2+min(y, 0), y-1); 
    return t;
}

/* Rotación derecha
*
*   A         B
*  / \       / \
*  B  c ==> a   A
* / \          / \
* a  b        b   c
*
*/
static pnodo rrot(pnodo t)
{
    pnodo temp = t;
    int x,y;
    t = t->left;
    temp->left = t->right;
    t->right = temp;
    x = temp->fe;
    y = t->fe;    
    temp->fe = x+1-min(y, 0); 
    t->fe = max(x+2+max(y, 0), y+1); 
    return t;
}

static void Error(int tipo)
{
    if (tipo) printf("\nError en inserción\n");
    else printf("\nError en descarte\n");
}

int Altura(void)
{
    return alto_avl;
}

pnodo CreaNodo(int key)
{
    pnodo t;
    t = (pnodo) malloc(sizeof(nodo));
    t->clave=key;
    t->left=0;
    t->right=0;
    return t;
}

pnodo insertR(pnodo t)
{
    if (t == NULL)  
    {
        t = CreaNodo(key);
        t->fe = 0;
        flag = 1; 
        return t;
    }
    else if (t->clave < key)
    {
        t->right = insertR(t->right);
        t->fe += flag;
    }
    else if (t->clave > key)
    {
        
        t->left = insertR(t->left);
        t->fe -= flag;
    }
    else   
    {
        Error(1);
        flag = 0;
    }

    if (flag == 0)
        return t;
	if (t->fe < -1)
    {
        /* Quedó desfeanceado por la izquierda. Espejos Casos c y d.*/
        if (t->left->fe > 0)
            /* Si hijo izquierdo está cargado a la derecha */
            t->left = lrot(t->left);
        t = rrot(t);
        flag = 0; /* El subárbol no aumenta su altura */
    }
    else if (t->fe > 1)
    {
        /* Si quedó desfeanceado por la derecha: Casos c y d.*/
        if (t->right->fe < 0)
            /* Si hijo derecho está cargado a la izquierda Caso d.*/
            t->right = rrot(t->right);
        t = lrot(t); /* Caso c.*/
        flag = 0; /* El subárbol no aumenta su altura */
    }
    else if (t->fe == 0)/* La inserción lo feanceo */
        flag = 0; /* El subárbol no aumenta su altura. Caso a*/
    else /* Quedó desfeanceado con -1 ó +1 Caso b */
        flag = 1; /* Propaga ascendentemente la necesidad de refeancear */
    return t;
}

/* Mantiene variable global con el alto del árbol. */
pnodo InsertarAVL(int clave, pnodo t)
{
    key = clave; //pasa argumento a glofe.
    t = insertR(t);
    if (flag == 1)
        alto_avl++;
    return t;
}

void inorder(pnodo t, int profundidad)
{
    if (t != NULL)
    {
        inorder(t->left, profundidad+1);
        printf ("v= %d p=%d fe=%d \n", t->clave, profundidad, t->fe);
        inorder(t->right, profundidad+1);
    }
}

//////////////////////////////////////////////////////////LISTA/////////////////////////////////////////////////////////

NodoLista *InsertarLL(NodoLista *head, int val){
	NodoLista *nuevo = (NodoLista  *)malloc(sizeof( NodoLista));
	nuevo-> val= val;
	if(head==NULL){
		head=nuevo;
	}
	else{
		NodoLista * aux = head;
		while(aux-> sig!=NULL){
			aux=aux->sig;
		}
		aux->sig = nuevo;
	}
	return head;
}

//////////////////////////////////////////////////////////Ordenamiento burbuja/////////////////////////////////////////////////////////
NodoLista *burbuja(NodoLista *head){ 
	NodoLista *actual, *siguiente; 
	int n; 
	actual = head; 
	while(actual->sig != NULL){ 
		siguiente = actual->sig; 
		
		while(siguiente!=NULL){ 
			if(actual->val > siguiente->val){ 
				n = siguiente->val; 
				siguiente->val = actual->val; 
				actual->val = n; 
			} 
			siguiente = siguiente->sig; 
		} 
		actual= actual->sig; 
		siguiente = actual->sig; 
	} 
	printf("La lista fue ordenada exitosamente\n"); 
	return head; 
}
//////////////////////////////////////////////////////////Ordenamiento quicksort/////////////////////////////////////////////////////////
/*
NodoLista *quicksort(NodoLista *primero){
	NodoLista *q, *r, *p, *s, *t, *w, *u, *ultimo;
	s = u = NULL;
	q = primero;
	r = ultimo->sig;
	p = primero->sig;
	
		if (primero == ultimo)
		return primero;
			while (p != r){
			if(p->val < q->val)
				if(s == NULL)
				t = s = p;
				else {
					s->sig = p;
					s = s->sig;
				}
				else
				if(u == NULL)
				w = u = p;
				else {
					u->sig = p;
					u = u->sig;
				}
			p = p->sig;
			}
			
	s->sig = q;
	q->sig = w;
	u->sig = p;
	quicksort(t);
	return quicksort(t);
	return t; en vez de las dos líneas de arriba y retorna la lista con
	el miembro pivot en su lugar
}*/

