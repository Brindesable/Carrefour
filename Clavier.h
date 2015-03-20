/*************************************************************************
                           Clavier  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) ${year} par ${user}
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
bool etatGenerateur;
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Clavier ();
// Mode d'emploi :
//
// Contrat :
//

void Commande (char code);
// Mode d'emploi :
//
// Contrat :
//

void Commande (TypeVoie entree, TypeVoie sortie);
// Mode d'emploi :
//
// Contrat :
//


void Commande (TypeVoie Voie, unsigned int duree);
// Mode d'emploi :
//
// Contrat :
//


#endif // CLAVIER_H

