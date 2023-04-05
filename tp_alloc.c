#include <stdio.h>
#include <string.h>
#include "affiche_tas.c"

#define FREE_BLOCK -1

char* first_fit( int taille);
char *tas_malloc( int taille);
void tas_free(void *ptr);


int main()
{

    tas_init();

    char *p1, *p2, *p3, *p4, *p5;
    p1 = (char *) tas_malloc(10); 
    p2 = (char *) tas_malloc(9);
    p3 = (char *) tas_malloc(5);   
    strcpy(p1, "tp 1" );
    strcpy(p2, "tp 2" );
    strcpy(p3, "tp 3" );
    tas_free(p2);
    p4 = (char *) tas_malloc(8);
    strcpy(p4,"systeme");
    afficher_tas();

    return 0;
}


char* first_fit(int taille)
{
    int indiceJump;
    char *ptrVersBuffer = tas+libre;

    while(ptrVersBuffer < tas+TAILTAS-1)
    {
        if(*ptrVersBuffer >= taille  && *(ptrVersBuffer+1) == FREE_BLOCK) 
        {
            return ptrVersBuffer;
        }     
        indiceJump = *ptrVersBuffer+1;
        ptrVersBuffer = ptrVersBuffer + indiceJump;
    }

    return NULL;
}

static unsigned int ESPACE_OCCUPE = 0;

char *tas_malloc(int taille)
{
    // Si il n'a pas assez d'espace disponible
    char *adresse = first_fit(taille);
    if(adresse == NULL)
    {
        printf("%s\n", "Il n y a pas assez d'espace disponible");
        return NULL;
    }
    
    char miette = *adresse - taille;
    ESPACE_OCCUPE += taille + 1; // Incrementation de la taille occupée dans le tas

    if (miette == 0){
            // le buffer fait pille la taille à allouer
            *adresse = taille;
            *(adresse + 1) = 0;
            *(adresse + taille + 2) = FREE_BLOCK;

            return (adresse + 1);
    }
    else if (miette > 1){
            // on doit créer un nouveau buffer libre 
            *adresse = taille;
            *(adresse + 1) = 0;
            return (adresse + 1);
    }
    else {
            *adresse = taille;
            *(adresse + 1) = 0;
          // on doit rajoueter 1 à la taille du buffer (subtilité du système)
          //*adresse = (adresse + 1);
    }
    
    /*
    if()
    {
        // Attribution/Bornage du buffer
        *adresse = taille; //1er bloc du buffer - taille de l'allocation
        *(adresse + taille + 2) = FREE_BLOCK; //dernier bloc du buffer -1
        *(adresse + 1) = 0; // 2e bloc du buffer -> mise à 0
        *(adresse + taille + 1) = TAILTAS-ESPACE_OCCUPE; // Avant dernier bloc -> espace restant dans le tas
        return (adresse + 1); // Renvoi l'adresse à laquelle commencer à ecrire
    }
    else
    {
        *adresse = taille; //1er bloc du buffer - taille de l'allocation
        *(adresse + 1) = 0; // 2e bloc du buffer -> mise à 0
        return (adresse + 1);
    }
    */
}


void tas_free(void *ptr)
{
    // Ajout de -1 à l'adresse passée en parametre
    char *adresse = ptr;
    *adresse = FREE_BLOCK;
 
}
