/*************************************************************************
                           Voie  -  description
                             -------------------
    début                : 20/03/2015
    copyright            : (C) 2015 par B3329
*************************************************************************/

//---------- Réalisation de la tâche <Voie> (fichier Voie.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include systèmex
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <set>
//------------------------------------------------------ Include personnel
#include "Voie.h"
#include "Voiture.h"
#include "Mere.h"
#include "Feux.h"
#include "Outils.h"
#include "Menu.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static TypeVoie voie;
static int * mpCouleurFeu;
static set<pid_t> voitures;
//------------------------------------------------------ Fonctions privées
static void finVoie( int noSignal )
// 	Mode d'emploi :
//			- A utiliser lors de la terminaison de la tache	
{
	shmdt(mpCouleurFeu);
	for (set<int>::iterator it=voitures.begin(); it!=voitures.end(); ++it)
	{
		kill(*it, SIGUSR2);
		waitpid(*it, 0, 0);
	}
	exit(0);
}

static void finVoiture( int noSignal )
// 	Mode d'emploi :
// 			- A utiliser lorsqu'une voiture quitte le Carrefour
{
	pid_t idVoiture = wait(NULL);
	voitures.erase(idVoiture);
}

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void ActiverVoie(TypeVoie sense, int balVoituresId, int semCouleurFeuId, int mpCouleurFeuId)
// Algorithme :
//
{
	//Type de Voie
	voie=sense;
	//on arme le signal SIGUSR2 sur finVoie
	struct sigaction finAction;
	finAction.sa_handler = finVoie;
	sigemptyset(&finAction.sa_mask);
	finAction.sa_flags = 0;
	sigaction(SIGUSR2, &finAction, NULL);
	//on arme le signal SIGCHLD sur finVoiture
	struct sigaction arriveVoiture;
	arriveVoiture.sa_handler = finVoiture;
	sigemptyset(&arriveVoiture.sa_mask);
	arriveVoiture.sa_flags = 0; //!
	sigaction(SIGCHLD, &arriveVoiture, NULL);

	//attachement de la memoire du feu
	mpCouleurFeu = (int*) shmat(mpCouleurFeuId, NULL, SHM_RDONLY);
	
	//Moteur
	while(1)
	{
		//Lire et Dessiner un voiture
		struct MsgVoiture message;
		int msg;
		do
		{
			msg = msgrcv(balVoituresId, &message, TAILLE_MSG_VOITURE, (long) voie,1);
		}while(msg == -1);

		struct Voiture voiture;
		voiture=message.uneVoiture;
		DessinerVoitureFeu(voiture.numero, voiture.entree, voiture.sortie);
		OperationVoie(MOINS, voie); // !

		int couleurFeu;
		do
		{
			if(voie==NORD || voie==SUD)
			{
				couleurFeu = lireMP(MP_NS, mpCouleurFeu, semCouleurFeuId);
			}else{
				couleurFeu = lireMP(MP_EO, mpCouleurFeu, semCouleurFeuId);
			}
			
			sleep(1);//!
		}while(couleurFeu != MP_VAL_VERT); 
		
		voitures.insert(DeplacerVoiture(voiture.numero, voiture.entree, voiture.sortie)); //!
	}
		
} //----- fin de Nom

