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
using namespace std;
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
{
	shmdt(mpCouleurFeu);
	for (set<int>::iterator it=voitures.begin(); it!=voitures.end(); ++it)
	{
		kill(*it, SIGUSR2);
		waitpid(*it, 0, 0);
	}
	exit(0);
}

static void finVoiture(int sig, siginfo_t *si, void *unused)
{
	voitures.erase(si->si_pid);
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
	//on arme le signal SIGCHLD sur finVoiture
	struct sigaction arriveVoiture;
	/*
	arriveVoiture.sa_handler = finVoiture;
	sigemptyset(&arriveVoiture.sa_mask);
	arriveVoiture.sa_flags = 0;
	sigaction(SIGCHLD, &finAction, NULL);
	*/
	
	arriveVoiture.sa_flags = SA_SIGINFO;
	sigemptyset(&arriveVoiture.sa_mask);
	arriveVoiture.sa_sigaction= finVoiture;
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

		//Lire EtatFeu et DessinerVoiture
		int couleurFeu;
		do
		{
			if(voie==NORD || voie==SUD)
			{
				couleurFeu = lireMP(MP_NS, mpCouleurFeu, semCouleurFeuId);
			}else{
				couleurFeu = lireMP(MP_EO, mpCouleurFeu, semCouleurFeuId);
			}
			
			if(couleurFeu==MP_VAL_VERT)
			{
				voitures.insert(DeplacerVoiture(voiture.numero, voiture.entree, voiture.sortie));
				OperationVoie(MOINS,voie);
			}
		}while(couleurFeu != MP_VAL_VERT);
	}
		
} //----- fin de Nom

