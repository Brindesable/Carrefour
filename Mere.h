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
// 		- Realise l'operation P sur le semaphore de numero idSem
// Contrat :
//		- idSem est un id de Semaphore valide

void V(int idSem);
// Mode d'emploi :
// 		- Realise l'operation V sur le semaphore de numero idSem
// Contrat :
//		- idSem est un id de Semaphore valide

void ecrireMP (int i, int val, int * mp, int semId);
// Mode d'emploi :
//		- Ecrit la valeur val dans la case de rang i de la memoire partagee mp protégéée par le sémaphore d'id semId
// Contrat :
//		- mp contient au moins i+1 cases et semId repère un sémaphore valide

int lireMP (int i, int * mp, int semId);
// Mode d'emploi :
//		- Ecrit la valeur val dans la case de rang i de la memoire partagee mp protégéée par le sémaphore d'id semId
// Contrat :
//		- mp contient au moins i+1 cases et semId repère un sémaphore valide

int main (void);
// Mode d'emploi :
//
// Contrat :
//

#endif // MERE_H

