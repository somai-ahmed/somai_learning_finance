#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 20
#define MAX_TRANSACTIONS 1000
#define MAX_COMPTES 500

typedef enum {
  actif ;
  passif;
  capitaux_propres;
  revenue;
  charge;
}typecompte;

typedef struct Date {
    int jour;
    int mois;
    int annee;
}Date;

typedef struct compte{
  int id ;
  int num_compte;
  char nom_compte[50];
  typecompte t_compte ;
  float solde;
}compte;

typedef struct entry{
    int compteID;
    float debit;
    float credit;
}entry;


