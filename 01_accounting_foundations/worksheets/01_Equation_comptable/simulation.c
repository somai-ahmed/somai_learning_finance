#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>/*for exit command*/

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

typedef struct transaction{  
    int id;
    char date[11];
    char description[100];
    Entry entries[MAX_ENTRIES];
    int nombreEntries;
} transaction;


typedef struct journal {
    transaction transactions[MAX_TRANSACTIONS];
    int nbr_transactions;
}journal;

typedef struct GrandLivre{
    Compte comptes[MAX_COMPTES];
    int nombreComptes;
}GrandLivre;

typedef struct
{
    float totalActifs;
    float totalPassifs;
    float totalCapitauxPropres;

} Bilan;

/* -----------------------------
   Etat global (equivalent des variables Python)
----------------------------- */
float cash = 0;
float computer = 0;
float loan = 0;
float owner_capital = 0;
float revenue = 0;

/*declaration du grand livre et le journal*/
GrandLivre gl;
journal jr;

/*trouver le compte a travers le grand livre*/
int trouver_compte(const char *nom) {
    for (int i = 0; i < gl.nombreComptes; i++) {
      /*le parcours du grand livre */
        if (strcmp(gl.comptes[i].nom_compte, nom) == 0) {
            return i;
        }
    }
    return -1; /*non trouve*/
}

int ajouter_compte(const char *nom, typecompte type) {
    int indice = trouver_compte(nom);
    if (indice != -1) return indice;

    if (gl.nombreComptes >= MAX_COMPTES) {
        printf("Erreur: grand livre plein.\n");
        return -1;
    }

    compte c;
    c.id = gl.nombreComptes;
    c.num_compte = 1000 + gl.nombreComptes;
    strncpy(c.nom_compte, nom, sizeof(c.nom_compte) - 1);
    c.nom_compte[sizeof(c.nom_compte) - 1] = '\0';
    c.t_compte = type;
    c.solde = 0.0f;

    gl.comptes[gl.nombreComptes] = c;
    gl.nombreComptes++;
    return gl.nombreComptes - 1;
}

void ajuster_solde(const char *nom, typecompte type, float montant) {
    int indice = ajouter_compte(nom, type);
    if (indice == -1) return;
    gl.comptes[indice].solde += montant;
}

/* -----------------------------
   Rafraichissement / affichage (equivalent de refresh())
----------------------------- */
void refresh(void) {
    float assets = cash + computer;
    float equity = owner_capital + revenue;

    printf("\n================ BILAN COMPTABLE ================\n");
    printf("Tresorerie      :  TND %.2f\n", cash);
    printf("Ordinateur      :  TND %.2f\n", computer);
    printf("---------------------------------------------------\n");
    printf("Total Actifs    :  TND %.2f\n", assets);
    printf("---------------------------------------------------\n");
    printf("Pret bancaire   :  TND %.2f\n", loan);
    printf("Capitaux propres:  TND %.2f\n", equity);
    printf("---------------------------------------------------\n");
    printf("Actifs (%.2f) = Passifs (%.2f) + Capitaux propres (%.2f)\n",
           assets, loan, equity);
    printf("===================================================\n");
}

/* -----------------------------
   Operations comptables (equivalent des callbacks Python)
----------------------------- */
void investir(void) {
    cash += 20000;
    owner_capital += 20000;

    ajuster_solde("Tresorerie", actif, 20000);
    ajuster_solde("Capital", capitaux_propres, 20000);

    refresh();
}

void acheter_ordinateur(void) {
    if (cash >= 3000) {
        cash -= 3000;
        computer += 3000;

        ajuster_solde("Tresorerie", actif, -3000);
        ajuster_solde("Ordinateur", actif, 3000);
    } else {
        printf("Fonds insuffisants pour acheter l'ordinateur.\n");
    }

    refresh();
}

void emprunt_bancaire(void) {
    cash += 10000;
    loan += 10000;

    ajuster_solde("Tresorerie", actif, 10000);
    ajuster_solde("Pret bancaire", passif, 10000);

    refresh();
}

void vente_services(void) {
    cash += 5000;
    revenue += 5000;

    ajuster_solde("Tresorerie", actif, 5000);
    ajuster_solde("Revenus", revenue_t, 5000);

    refresh();
}

/* -----------------------------
   Menu interactif
----------------------------- */
void afficher_menu(void) {
    printf("\n--- Simulation Comptable ---\n");
    printf("1. Investir 20 000  TND \n");
    printf("2. Acheter ordinateur\n");
    printf("3. Emprunt bancaire\n");
    printf("4. Vente de services\n");
    printf("5. Afficher le bilan\n");
    printf("0. Quitter\n");
    printf("Choix : ");
}

int main(void) {
    gl.nombreComptes = 0;
    jr.nbr_transactions = 0;

    int choix;
    int continuer = 1;

    refresh();

    while (continuer) {
        afficher_menu();
        if (scanf("%d", &choix) != 1) {
            /* vider le buffer en cas d'entree invalide */
            while (getchar() != '\n');
            continue;
        }

        switch (choix) {
            case 1: 
              investir();
              break;
          
            case 2: 
                acheter_ordinateur(); 
                break;
            case 3:
                emprunt_bancaire();
                break;
            case 4:
                vente_services();
                break;
            case 5:
                refresh();
                break;
            case 0:
                continuer = 0;
                break;
            default: 
                printf("Choix invalide.\n");
                break;
        }
    }

    printf("Fin de la simulation.\n");
    exit();
    return 0;
}
