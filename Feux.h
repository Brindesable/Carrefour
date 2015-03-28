/*************************************************************************
                           Feux  -  description
                             -------------------
    début                : XXX
    copyright            : (C) XXX par XXX
    e-mail               : XXX
*************************************************************************/

//---------- Interface de la tâche <XXX> (fichier XXX.h) -------
#if ! defined ( FEUX_H )
#define FEUX_H

//------------------------------------------------------------------------
// Rôle de la tâche <Feux>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes
const int dureeInitFeuVertNS = 20;
const int dureeInitFeuVertEO = 10;
const int dureeFeuOrange = 3;
const int dureeFeuRougeSimultane = 2;

enum CouleurFeu{ VERT, ORANGE, ROUGE};
//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Feux(int semDureeFeuId, int mpDureeFeu, int semCouleurFeuId, int mpCouleurFeu);
// Mode d'emploi :
//
// Contrat :
//

#endif // FEUX_H

