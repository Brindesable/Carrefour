/*************************************************************************
                           Mere  -  description
                             -------------------
    début                : 20/03/15
    copyright            : (C) 2015 par B3329
    e-mail               : XXX
*************************************************************************/

//---------- Interface de la tâche <Mere> (fichier Mere.h) -------
#if ! defined ( MERE_H )
#define MERE_H

//------------------------------------------------------------------------
// Rôle de la tâche <Mere>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <sstream>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void P(int idSem);
// Mode d'emploi :
//
// Contrat :
//

void V(int idSem);
// Mode d'emploi :
//
// Contrat :
//

void ecrireMP (int i, int val, int * mp, int semId);
// Mode d'emploi :
//
// Contrat :
//

int lireMP (int i, int * mp, int semId);
// Mode d'emploi :
//
// Contrat :
//

int main (void);
// Mode d'emploi :
//
// Contrat :
//

#endif // MERE_H

