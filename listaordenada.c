#include "listaordenada.h"
#include <malloc.h>
#include <memory.h>

struct Nodo{
    tElemento elem;
    struct Nodo* next;
};


tListaOrdenada crearLista(int(*f) (tElemento,tElemento)){
    tListaOrdenada *L;
    L = (struct tListaOrdenada*)malloc(sizeof(tListaOrdenada));
    L->header = NULL;
    L->tail = NULL;
    L->size = 0;
    L->comparador = f;
    return *L;
}

void insertar(tListaOrdenada* L, tElemento x){
    tNodo *actual = L->header;
    while((L->comparador(x,actual->elem) < 1) && (actual!= NULL)){
        actual = siguiente(actual);
    }
    tNodo *n = (struct tNodo*) malloc(sizeof(tNodo));
    n->elem = x;
    n->next = actual->next;
    actual->next = n;
    L->size++;
}

tNodo* siguiente(tNodo* pos){
    return pos->next;
}

tNodo* primero(tListaOrdenada L){
    return L.header;
}

tNodo* ultimo(tListaOrdenada L){
    return L.tail;
}

tElemento* elemento(tNodo* pos){
    return &(pos->elem);
}


int listaVacia(tListaOrdenada L){
    return L.size == 0;
}
