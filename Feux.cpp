/*************************************************************************
                           Feux  -  description
                             -------------------
    début                : XXX
    copyright            : (C) XXX par XXX
    e-mail               : XXX
*************************************************************************/

//---------- Réalisation de la tâche <Feux> (fichier feux.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
//------------------------------------------------------ Include personnel
#include "Outils.h"
#include "Feux.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
static void finFeux( int noSignal )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
	exit(0);
} //----- fin de fin

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Feux(int semDureeFeuId, int mpDureeFeu, int semCouleurFeuId, int mpCouleurFeu)
// Algorithme :
//
{
	//on arme le signal SIGUSR2 sur finFeux
	struct sigaction finAction;
	finAction.sa_handler = finFeux;
	sigemptyset(&finAction.sa_mask);
	finAction.sa_flags = 0;
	sigaction(SIGUSR2, &finAction, NULL);

	int dureeFeuNS = dureeInitFeuVertNS;
	//le temps que le feu NS passe de vert a rouge + 2s
	int dureeFeuEO = dureeInitFeuVertNS + dureeFeuOrange + dureeFeuRougeSimultane;

	CouleurFeu couleurFeuNS = VERT;
	Afficher(COULEUR_AXE_NS, "VERT");
	CouleurFeu couleurFeuEO = ROUGE;
	Afficher(COULEUR_AXE_EO, "ROUGE");

	while(1)
	{
		if(dureeFeuNS == 0)
		{
			switch(couleurFeuNS)
			{
				case VERT :
					couleurFeuNS = ORANGE;
					dureeFeuNS = 3;
					Afficher(COULEUR_AXE_NS, "ORANGE");
					break;
				case ORANGE :
					couleurFeuNS = ROUGE; 
					dureeFeuNS = dureeInitFeuVertEO + dureeFeuOrange + 2 * dureeFeuRougeSimultane;
					Afficher(COULEUR_AXE_NS, "ROUGE ");
					break;
				case ROUGE :
					couleurFeuNS = VERT;
					dureeFeuNS = dureeInitFeuVertNS;
					Afficher(COULEUR_AXE_NS, "VERT  ");
					break;
			}
		}
		
		if(dureeFeuEO == 0)
		{
			switch(couleurFeuEO)
			{
				case VERT :
					couleurFeuEO = ORANGE;
					dureeFeuEO = 3;
					Afficher(COULEUR_AXE_EO, "ORANGE");
					break;
				case ORANGE :
					couleurFeuEO = ROUGE; 
					dureeFeuEO = dureeInitFeuVertNS + dureeFeuOrange + 2 * dureeFeuRougeSimultane;
					Afficher(COULEUR_AXE_EO, "ROUGE ");
					break;
				case ROUGE :
					couleurFeuEO = VERT;
					dureeFeuEO = dureeInitFeuVertEO;
					Afficher(COULEUR_AXE_EO, "VERT  ");
					break;
			}
		}
		Afficher(TEMPS_AXE_NS, dureeFeuNS);
		Afficher(TEMPS_AXE_EO, dureeFeuEO);
		sleep(1);
		dureeFeuNS--;
		dureeFeuEO--;		
	}
} //----- fin de Feux

