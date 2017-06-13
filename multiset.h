#include "listaordenada.h"
#ifndef MULTISET_H_INCLUDED
#define MULTISET_H_INCLUDED

struct trie;
typedef struct Trie tMultiset;

tMultiset* crearMultiset();
void insertarMultiset(tMultiset* M, char* s);
int cantidad(tMultiset* M, char* s);
tListaOrdenada elementos(tMultiset *M, int(*f)(tElemento,tElemento));
void eliminar(tMultiset* M);

#endif // MULTISET_H_INCLUDED
