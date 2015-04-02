/*************************************************************************
                           Voie  -  description
                             -------------------
    début                : 20/03/2015
    copyright            : (C) 2015 par B3329
*************************************************************************/

//---------- Interface de la tâche <Voie> (fichier Voie.h) -------
#if ! defined ( VOIE_H )
#define VOIE_H

//------------------------------------------------------------------------
// Rôle de la tâche <Voie>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include "Outils.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void ActiverVoie(TypeVoie sense, int balVoituresId, int semCouleurFeuId, int mpCouleurFeuId);
// Mode d'emploi :
//		- La voie est caracterisee par TypeVoie (il y en 4 en tout). Elle lit dans la boite aux lettre balVoituresId,
//			et consulte la couleur des feu indiqué par mpCouleurFeuId avant de lancer une voiture. Cette mp est protégée
//			par le sempahore semCouleurFeuId
// Contrat :
//

#endif // VOIE_H
