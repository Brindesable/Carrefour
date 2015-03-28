/*************************************************************************
                           Clavier  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- Réalisation de la tâche <Clavier> (fichier Clavier.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <stdlib.h>
#include <signal.h>
//------------------------------------------------------ Include personnel
#include "Clavier.h"
#include "Menu.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
//------------------------------------------------------ Fonctions privées
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
//{
//} //----- fin de nom

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Clavier ()
// Algorithme :
//
{
	//debloquage de sigint
	sigset_t sigint;
	sigemptyset(&sigint);
	sigaddset(&sigint, SIGINT);
	sigprocmask(SIG_UNBLOCK, &sigint, NULL);

	etatGenerateur=false;
	Menu();
} //----- fin de Nom


void Commande (char code)
// Algorithme :
//
{
	if(code=='q' || code=='Q')
	{
		exit(0);
	}
	if(code=='g' || code=='G')
	{
		if(etatGenerateur)
		{
			etatGenerateur=false;
			Effacer(ETAT_GENERATEUR);
			Afficher(ETAT_GENERATEUR,"OFF\0",GRAS);
		}else{
			etatGenerateur=true;
			Effacer(ETAT_GENERATEUR);
			Afficher(ETAT_GENERATEUR,"ON\0",GRAS);
		}
	}
} //----- fin de Nom

void Commande (TypeVoie entree, TypeVoie sortie)
{
}

void Commande (TypeVoie Voie, unsigned int duree)
{
}
