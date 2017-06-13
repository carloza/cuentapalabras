#include "multiset.h"
#include <malloc.h>
#include <memory.h>
#include <string.h>

struct Trie{
	int cantidad;
	struct Trie *siguiente[27];
};


tMultiset* crearMultiset(){
	tMultiset* T;
	T = (struct tMultiset*) malloc (sizeof(tMultiset));
	T->cantidad = 0;
	return T;
}

void insertarMultiset(tMultiset* M, char* s){
    int pos = 0;
    tMultiset *sig;
    if(*s != '\0'){
        pos = s[0] - 'a';
        sig = M->siguiente[pos];
        if (sig == NULL ){
            sig = crearMultiset();
            M->siguiente[pos] = sig;
        }
        insertarMultiset(sig, s[1]);
    }
    else{
        M->cantidad++;
    }
}

int cantidad(tMultiset* M, char* s){
    int pos = 0;
    int cant = 0;
    tMultiset *sig;
    if(*s != '\0'){
        pos = s[0] - 'a';
        sig = M->siguiente[pos];
        if ( sig!=NULL ){
            cant= cantidad(sig, &s[1]);
        }
    }
    else{
        cant = M->cantidad;
    }
    return cant;
}

tListaOrdenada elementos(tMultiset *M, int(*f)(tElemento,tElemento)){
    tListaOrdenada L = crearLista(f);
    char palabra[250] = "";
    insertarPreorderTrie(M,L,palabra);
    return L;
}

void insertarPreorderTrie(tMultiset *M, tListaOrdenada *L, char *S){
    if(M->cantidad != 0){
        //aca hago una copia del string que me pasaron
        char * str;
        strcpy(str,S);
        //aca creo el elemento nuevo
        tElemento e;
        e.a = M->cantidad;
        e.b = str;
        //y lo agrego a la lista
        insertar(L,e);
    }
    int i = 0;
    //aca saco la longitud del estring que entra
    int l = strlen(S);
    for(i= 0, i<27;i++;){
        if(M->siguiente[i] !=NULL){
            S[l] = 'a'+ i;
            S[l+1] = '\0';
            insertarPreorderTrie(M->siguiente[i], L, S);
            S[l] = '\0';
        }
    }
};

void eliminar(tMultiset* M){
    eliminarPosOrden(M);
};

void eliminarPosOrden(tMultiset *M){
    int i = 0;
    for(i= 0, i<27;i++;){
        if(M->siguiente[i] !=NULL){
            eliminarPosOrden(M->siguiente[i]);
        }
    }
    free(M);
}








