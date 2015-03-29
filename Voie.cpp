/*************************************************************************
                           Voie  -  description
                             -------------------
    début                : 20/03/2015
    copyright            : (C) 2015 par B3329
*************************************************************************/

//---------- Réalisation de la tâche <Voie> (fichier Voie.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
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
//static vector<pid_t> voitures;
//------------------------------------------------------ Fonctions privées
static void finVoie( int noSignal )
{
	shmdt(mpCouleurFeu);
	exit(0);
}

static void P(int idSem)
{
	struct sembuf buffer;
	buffer.sem_num = 0;
	buffer.sem_op = -1;
	//buffer.sem_flg = IPC_UNDO;
	semop(idSem, &buffer, 1);
}

static void V(int idSem)
{
	struct sembuf buffer;
	buffer.sem_num = 0;
	buffer.sem_op = 1;
	//buffer.sem_flg = IPC_UNDO;
	semop(idSem, &buffer, 1);
}

static void ecrireMP (int i, int val, int * mp, int semId)
{
	P(semId);
	mp[i] = val;
	stringstream ss;
	ss << val;
	log(ss.str());
	V(semId);
}

static int lireMP (int i, int * mp, int semId)
{
	P(semId);
	int val = mp[i];
	V(semId);
	return val;
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

	//attachement de la memoire du feu
	mpCouleurFeu = (int*) shmat(mpCouleurFeuId, NULL, SHM_RDONLY);
	
	//Moteur
	while(1)
	{
		struct MsgVoiture message;
		int msg = msgrcv(balVoituresId, &message, TAILLE_MSG_VOITURE, (long) voie,0);
		struct Voiture voiture;
		message.uneVoiture=voiture;
		Afficher(MESSAGE,(long)voiture.entree);
		DessinerVoitureFeu(voiture.numero, voiture.entree, voiture.sortie);
	}
		
} //----- fin de Nom

