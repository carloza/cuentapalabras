#include "listaordenada.h"
#include <malloc.h>
#include <memory.h>


struct Nodo{
    tElemento elem;
    struct Nodo* next;
};


tListaOrdenada crearLista(int(*f) (tElemento,tElemento)){
    tListaOrdenada L;
    L.header = NULL;
    L.tail = NULL;
    L.size = 0;
    L.comparador = f;
    return L;
}

void insertar (tListaOrdenada* L, tElemento x){
    tNodo *n = (tNodo *)malloc(sizeof(tNodo));
    n->elem = x;
    n->next = NULL;
    tNodo *prim = L->header;
    tNodo *ulti = L->tail;
    if(L->size==0){
        //aqui miro si la lista es vacia
        L->header = n;
        L->tail = n;
    }
    else{
        //aca miro si tiene que ir antes del primero
        if(L->comparador(x, prim->elem)<0){
            L->header = n;
            n->next = prim;
        }
        else{
            //aca miro si tiene que ir despues del ultimo
            if((L->comparador(x, ulti->elem)>0)||(L->comparador(x,ulti->elem)==0)){
                ulti->next=n;
                L->tail=n;
            }
            else{
                //aca inserto entre el primero y el ultimo
                tNodo*actual = L->header;
                tNodo*anterior;
                int frenar = 0;
                while(frenar==0){
                    anterior = actual;
                    actual = actual->next;
                    if (L->comparador(x,actual->elem)<0){
                        frenar = 1;
                    }

                }
                anterior->next = n;
                n->next = actual;
            }
        }
    }
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


void eliminarLista(tListaOrdenada *L){
    tNodo *actual = L->header;
    tNodo *sig;
    while(actual){
        sig = siguiente(actual);
        free(actual);
        actual = sig;
    }
    L->header = NULL;
    L->tail = NULL;
    L->size = 0;
    L = NULL;
    L==NULL;
}


tElemento* elemento(tNodo* pos){
    return &(pos->elem);
}
