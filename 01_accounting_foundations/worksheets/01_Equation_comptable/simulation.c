#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  actif ;
  passif;
  capitaux_propres;
}typecompte;

typedef struct compte{
  int id ;
  int num_compte;
  char nom_compte[50];
  typecompte t_compte ;
  float solde;
}compte;

typedef struct entry{
    int compte.id ;
    char compte.nom_compte[50];
    float debit;
    float credit;
}entry;
