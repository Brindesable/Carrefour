/*************************************************************************
                           Clavier  -  description
                             -------------------
    début                : 20/03/2015
    copyright            : (C) 2015 par B3329
*************************************************************************/

//---------- Interface de la tâche <Clavier> (fichier Clavier.h) -------
#if ! defined ( CLAVIER_H )
#define CLAVIER_H

//------------------------------------------------------------------------
// Rôle de la tâche <Clavier>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include "Outils.h"

//------------------------------------------------------------- Constantes
//------------------------------------------------------------------ Types
static bool etatGenerateur;
static unsigned int nbVoiture;
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Clavier (pid_t tacheGenerateur, int semDureeFeuId, int mpDureeFeu, int balVoitures);
// Mode d'emploi :
//		- Gère les entrées du clavier. Peu mettre à jour la mémoire partagée mpDureeFeu protégée par
// 			le sémaphore repéré par semDureeFeuId. Peu activer/desactiver la tache tacheGenerateur.
//			Peut ajouter des voitures dans la boite aux lettres balVoitures.
// Contrat :
// 

void Commande (char code);
// Mode d'emploi :
//		- Surcharge de la lib tp
// Contrat :
//

void Commande (TypeVoie entree, TypeVoie sortie);
// Mode d'emploi :
//		- Surcharge de la lib tp
// Contrat :
//


void Commande (TypeVoie Voie, unsigned int duree);
// Mode d'emploi :
//		- Surcharge de la lib tp
// Contrat :
//


#endif // CLAVIER_H

