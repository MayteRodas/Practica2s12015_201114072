#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

# define max(A,B) ((A)>(B)?(A):(B))
# define min(A,B) ((A)>(B)?(B):(A))
/////////////////////////////////////////////////////STRUCTS A UTILIZAR///////////////////////////////////////////////////////////////
typedef struct avlnode
{
	int clave;
    int fe; 
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


////////////////////////////////////////////////////METODOS DEL AVL y LISTA///////////////////////////////////////////////////////
pnodo InsertarAVL(int clave, pnodo t);
void inorder(pnodo t, int profundidad);
void ImprimeInorder(pnodo t);

NodoLista *InsertarLL(NodoLista *head, int val);
NodoLista *burbuja(NodoLista *head);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////VARIABLES GLOBALES////////////////////////////////////////////////////////////
int flag;

int key; 
int alto_avl = 0; 
pnodo raiz=NULL;

NodoLista *head;
NodoLista *ultimo;

float tim;
clock_t inicio, fin;  

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////MAIN////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
  int op;
	do{
		op=menuPrincipal();	
		switch(op)
		{
				case 1:	{
							//Cargar Datos
							printf("Cargando Datos...\n");
							
							inicio =clock();
								CargarDatos();	
							fin = clock();
							
							printf("Tiempo de Carga de Achivos: %f seg\n",(float)(fin-inicio)/(float)CLOCKS_PER_SEC);
							
							break;
						}
				case 2:	{
							//Ordenar AVL y su tiempo 
							printf("Ordenar Arbol AVL y su tiempo: \n");
							inicio =clock();
								inorder(raiz, 0);
							fin = clock();
							printf("Tiempo Innorden: %f seg\n",(float)(fin-inicio)/(float)CLOCKS_PER_SEC);
							
							break;
						}
				case 3:	{
							//Ordenado BUrbuja y su tiempo
							printf("Ordenar Burbuja y su tiempo:");
							
							FILE *archivo;/*El manejador de archivo*/
							archivo=fopen("burbuja.txt", "w");
							if(archivo==NULL)/*So no lo logramos abrir, salimos*/
								
								printf("\nError no se abrio burbuja\n");
								inicio = clock();	
							    burbuja(head);
							    
							    fprintf(archivo,"set grid \n");
							    fprintf(archivo,"set title \"Ordenamiento burbuja\"\n");
							    fprintf(archivo,"set ylabel \"DATOS INGRESADOS\"\n");
							    fprintf(archivo,"set xlabel \"TIEMPO\"\n");
							    								
								while(head!=NULL){
									fprintf(archivo, "plot [%d:%f] x*exp(2)\n", head->val,tim);
									printf("%d\n ", head->val);
									head=head->sig;
								}
								fprintf(archivo,"pause mouse");
								
								fin = clock();
								tim=(double)(fin-inicio)/(double)CLOCKS_PER_SEC;
								printf("\n Tiempo consumido: %f segundos\n", (double)(fin-inicio)/(double)CLOCKS_PER_SEC);
								
								fclose(archivo);/*Cerramos el archivo*/													
							    break;
						}
						
						
						
			   case 4: {
							//Ordenado quicksort y tiempo
							
							break;
						}
						
				case 5: {
							//Grafica AVL
							printf("Grafica Metodo Ordenamiento Arbol AVL:\n");
							FILE *fp1; 
							fp1 = fopen ( "avl.txt", "a" ); 
							fprintf(fp1,"pause mouse");
							fclose ( fp1 );	
							system("gnuplot avl.txt");
							break;
						}
					
				case 6: {
							//Grafica burbuja
							printf("Grafica Metodo Ordenamiento Burbuja:\n");
							system("gnuplot burbuja.txt");
							break;
						}
						
						
						
				case 7: {
							//Grafica quicksort
							break;
						}
		}
	}while(op!=8);
	return 0; 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////MENU PRINCIPAL/////////////////////////////////////////////////////////////////////////
int menuPrincipal()
{
	int opcion;
	puts("\n");
	puts("****(*)*******(*)*************(*) BIENVENIDOS (*)*******(*)*************(*)****");
	puts("\n");
	puts("   1) Cargar Datos                                                        ***");
	puts("   2) Ordanado Arbol AVL y su tiempo                                      ***");
	puts("   3) Ordenado Burbuja y su tiempo                                        ***");
	puts("   4) Ordenado Quicksort y su tiempo                                      ***");
	puts("   5) Grafica  Ordenamiento Arbol AVL                                     ***");
	puts("   6) Grafica  Ordenamiento Burbuja                                       ***");
	puts("   7) Grafica  Ordenamiento Quicksort                                     ***");
	puts("   8) Salir                                                               ***");
	puts("\n");
	puts("  Ingrese la opcion que desea:");
	scanf("%d",&opcion);
	puts("\n");
	return opcion;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////CARGA DE DATOS//////////////////////////////////////////////////////////////////////

void CargarDatos()
{	
	printf("Archivo Cargado...\n");
	printf("\n");
		FILE *fp;
    char *c, cad[100];

	fp=fopen("prueba2.txt", "r");
	
	while((c=fgets(cad,100,fp)))
	{
		int num = atoi(cad);
		raiz=InsertarAVL(num, raiz);
		head=InsertarLL(head, num);
	}
	fclose ( fp );
	
	FILE *fp1; 
 	fp1 = fopen ( "avl.txt", "w" );
 	fprintf(fp1,"set grid \n");
	fprintf(fp1,"set title \"Ordenamiento Arbol AVL\"\n");
	fprintf(fp1,"set ylabel \"DATOS INGRESADOS\"\n");
	fprintf(fp1,"set xlabel \"TIEMPO\"\n"); 
	fclose ( fp1 );
 	ImprimeInorder(raiz);
}

void ImprimeInorder(pnodo t)
{
if (t != NULL)
    {
        ImprimeInorder(t->left);
        FILE *fp1; 
		fp1 = fopen ( "avl.txt", "a" ); 
		fprintf(fp1, "plot [%d: %f] log(x)\n", t-> clave, tim);
		fclose ( fp1 );		
        ImprimeInorder(t->right);
    }	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////SPLIT LECTURA/////////////////////////////////////////////////////////////////////////
int split(char *hora){
	int con=1;
	int total=0;
    char *input= hora;
  
	char* token; 
	token = strtok(input," "); 

	while(token != NULL) 
		{ 
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
				{  
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
    if (tipo) printf("\n Error en inserción\n");
    else printf("\n Error en descarte\n");
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
        
        if (t->left->fe > 0)
            
            t->left = lrot(t->left);
        t = rrot(t);
        flag = 0; 
    }
    else if (t->fe > 1) 
    {
        
        if (t->right->fe < 0)
           
            t->right = rrot(t->right);
        t = lrot(t); 
        flag = 0; 
    }
    else if (t->fe == 0)
        flag = 0; 
    else 
        flag = 1; 
    return t;
}

pnodo InsertarAVL(int clave, pnodo t)
{
    key = clave; 
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
        printf ("%d\n", t->clave);
        inorder(t->right, profundidad+1);
    }												
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////LISTA DOBLE/////////////////////////////////////////////////////////
NodoLista *InsertarLL(NodoLista *head, int val){
	
	
	NodoLista *nuevo = (NodoLista  *)malloc(sizeof( NodoLista));
	nuevo-> val= val;
	if(head==NULL){
		head=nuevo;
		ultimo=nuevo;
	}
	else{
		NodoLista * aux = head;
		while(aux-> sig!=NULL){
			aux=aux->sig;
		}
		aux->sig = nuevo;
		ultimo=nuevo;
	}
	return head;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////Ordenamiento quicksort/////////////////////////////////////////////////////////
/*
NodoLista *quicksort(NodoLista *primero, NodoLista *ultimo)
{
	
	 printf("SI IMPRIMIO QICKKKKKKK \n"); 

NodoLista *q, *r, *p, *s, *t, *w, *u;
s = u = NULL;
q = primero;
r = ultimo->sig;
p = primero->sig;
if (primero == ultimo)
return primero;
while (p != r){
if(p->valor < q->valor)
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
u->sig = r;
quicksort(w,u);
return quicksort(t,s);

 }
*/
