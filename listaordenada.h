#ifndef LISTAORDENADA_H_INCLUDED
#define LISTAORDENADA_H_INCLUDED

struct Elemento{
    int a;
    char* b;
};
typedef struct Elemento tElemento;

struct Nodo;
typedef struct Nodo tNodo;

struct Lista{
    tNodo* header;
    tNodo* tail;
    int size;
    int (*comparador) (tElemento,tElemento);
};
typedef struct Lista tListaOrdenada;

tListaOrdenada crearLista(int(*f) (tElemento,tElemento));

void insertar(tListaOrdenada* L, tElemento x);

tNodo* siguiente(tNodo* pos);

tNodo* primero(tListaOrdenada L);

tNodo* ultimo(tListaOrdenada L);

tElemento* elemento(tNodo* pos);

int listaVacia(tListaOrdenada L);





#endif // LISTAORDENADA_H_INCLUDED
