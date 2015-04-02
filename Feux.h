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

//valeurs du sujet
const int DUREE_INIT_FEU_VERT_NS = 20;
const int DUREE_INIT_FEU_VERT_EO = 10;
const int DUREE_FEU_ORANGE = 3;
const int DUREE_FEU_ROUGE_SIMULTANE = 2;

//rang dans la memoire partagée
const int MP_NS = 0;
const int MP_EO = 1;

//val dans la memoire partagee
const int MP_VAL_VERT = 0;
const int MP_VAL_ORANGE = 1;
const int MP_VAL_ROUGE = 2;

enum CouleurFeu{ VERT, ORANGE, ROUGE};
//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Feux(int semDureeFeuId, int mpDureeFeuId, int semCouleurFeuId, int mpCouleurFeuId);
// Mode d'emploi :
//		- Lit dans la memoire partagée mpDureeFeuId protégée par le sémaphore semDureeFeuId les durées des feux verts.
// 			Met à jour la couleur des feux dans la memoire partagee mpCouleurFeuId protegee par le semaphore semCouleurFeuId
// Contrat :
//

#endif // FEUX_H

