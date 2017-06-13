#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>


int main (int argc, char *argv[1])
{
    if((argc==1)||(strcmp(argv[1],"-h")==1))
    {
        printf("Cuentpalabras es una aplicación que lee todos los archivos de un directorio dado y crea dos archivos:           'cadauno.out', que contiene la cantidad de apariciones de todas las palabras de cada uno de los archivos; y 'totales.out', el cual contiene la cantidad total de apariciones de cada palabra en el conjunto de archivos.");
    }
    else
    {
        FILE *f;
        DIR *dp;
        struct dirent *ep;
        dp = opendir (argv[1]);

        if (dp != NULL)
        {
            //definimos las variables
            char c;
            char *ruta[250];
            char *nomfile;
            char *rutaActual[250];
            //aca va el url ingresado por el usuario
            strcpy(ruta,argv[1]);
            int longRuta = strlen(ruta);
            while (ep = readdir (dp))
            {
                if (ep->d_name[0]!='.')
                {

                    nomfile = ep->d_name;
                    printf("%s\n",nomfile);


                    strcpy(rutaActual,ruta);
                    strcat(rutaActual,nomfile);
                    printf("%s\n",rutaActual);

                    f = fopen(rutaActual,"r");
                    if(f!=NULL)
                    {
                        //lee el primer caracter del archivo leido y lo imprime
                        c = fgetc(f);
                        printf("%c\n",c);
                    }
                    else
                    {
                        printf("file vacio. \n");
                    }
                    fclose(f);
                }
            }
            (void) closedir (dp);
        }
        else
        {
            perror ("No se pudo abrir el directorio.");
        }
    }


    return 0;
}
