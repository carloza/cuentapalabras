#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "listaordenada.h"
#include "multiset.h"

int (*f)(tElemento,tElemento);


//Ordena los elementos de Menor a Mayor
int comp(tElemento A,tElemento B)
{
    if(A.a>B.a) {return 1;}
    else
    {
        if(A.a<B.a) {return -1;}
        else {return 0;}
    }
}

//Ordena los elementos de Mayor a Menor
int compInv(tElemento A,tElemento B)
{
    if(A.a<B.a) {return 1;}
    else
    {
        if(A.a>B.a) {return -1;}
        else {return 0;}
    }
}



int main (int argc, char *argv[1])
{
    int f = comp;

    printf("bienvenidos a cuenta palabra!!! \n");

    if((argc==1)||(strcmp(argv[1],"-h")==0))
    {
            printf("Cuentpalabras es una aplicación que lee todos los archivos de un directorio dado y crea dos archivos: \n");
            printf("'cadauno.out' que contiene la cantidad de apariciones de todas las palabras de cada uno de los archivos \n");
            printf("'totales.out': el cual contiene la cantidad total de apariciones de cada palabra en el conjunto de archivos. \n");
    }
    else{
        int longDir = strlen(argv[1]);
        if(argv[1][longDir-1]!='/'){
            argv[1][longDir]='/';
            argv[1][longDir+1]='\0';
        }
        printf("el directorio a leer es %s \n",argv[1]);

        FILE *archivito;
        DIR *dp;
        struct dirent *ep;
        dp = opendir (argv[1]);

        if (dp != NULL)
        {
			printf("Directorio habierto con exito \n");
            //definimos las variables
            char * palabras = (char *)malloc(sizeof(char)*250);
            char ruta[250];        //aqui almacenamos la ruta pasada por parámetro
            strcpy(ruta,argv[1]);  //hacemos una copia de la ruta
            char *nomfile;         //aqui almacenamos el nombre del archivo encontrado
            char rutaActual[250];  //aqui almacenamos la ruta completa del archivo encontrado

            tMultiset *MultisetCadaArchivo;
            tMultiset *MultisetTotalArchivos = crearMultiset();

            FILE *cadauno = fopen("cadauno.out","w");
            FILE *totales = fopen("totales.out","w");

            while (ep = readdir (dp))
            {

                if (ep->d_name[0]!='.')
                {

                    nomfile = ep->d_name;

                    strcpy(rutaActual,ruta);                 //creamos la ruta completa
                    strcat(rutaActual,nomfile);              //del archivo encontrado
                    archivito = fopen(rutaActual,"r");       //abrimos el archivo
                    if (archivito!=NULL)
                    {
                        //creamos el multiset de cada archivo
                        MultisetCadaArchivo = crearMultiset();

                        //procesamos el archivo
                        while(feof(archivito)==0)
                        {
                            fscanf(archivito,"%s",palabras);
                            insertarMultiset(MultisetCadaArchivo,palabras);
                            insertarMultiset(MultisetTotalArchivos,palabras);
                        }

                        //guardamos los elementos en una lista
                        tListaOrdenada aux = elementos(MultisetCadaArchivo,f);
                        tNodo *actual = primero(aux);
                        fprintf(cadauno,nomfile);
                        while(actual!=NULL)
                        {
                            //imprimimos la palabra encontrada y su cantidad de aparciones
                            fprintf(cadauno,"\n");
                            fprintf(cadauno,"%i",elemento(actual)->a);
                            fprintf(cadauno, " ");
                            fprintf(cadauno,"%s",elemento(actual)->b);
                            actual = siguiente(actual);
                        }
                        fclose(archivito);
                        fprintf(cadauno,"\n");

						//liberamos memoria de la lista y multiset usados en este bucle
						eliminar(&MultisetCadaArchivo);
						eliminarLista(&aux);
                    }
                    else
                    {
                        printf("file vacio. \n");
                    }

                }
            }
            f = compInv;
            tListaOrdenada aux2 = elementos(MultisetTotalArchivos,f);
            fprintf(totales,"Totales: ");
            tNodo *actual2 = primero(aux2);
            while(actual2!=NULL)
            {
                //imprimimos la palabra encontrada y su cantidad de aparciones
                fprintf(totales,"\n");
                fprintf(totales,"%i",elemento(actual2)->a);
                fprintf(totales, " ");
                fprintf(totales,"%s",elemento(actual2)->b);
                actual2 = siguiente(actual2);
            }
            fclose(cadauno);
            fclose(totales);
            (void) closedir (dp);

			eliminar(&MultisetTotalArchivos);
			eliminarLista(&aux2);
        }
        else
        {
            printf("No se pudo abrir el directorio.");
        }
    }
    printf("proceso finalizado con exito");

    return 0;
}
