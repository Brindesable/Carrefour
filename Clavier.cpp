/*************************************************************************
                           Clavier  -  description
                             -------------------
    début                : 20/03/2015
    copyright            : (C) 2015 par B3329
*************************************************************************/

//---------- Réalisation de la tâche <Clavier> (fichier Clavier.cpp) ---

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
#include "Clavier.h"
#include "Menu.h"
#include "Voiture.h"
#include "Mere.h"
#include "Feux.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes
const int dureeInitFeuVertNS = 20;
const int dureeInitFeuVertEO = 10;
//------------------------------------------------------------------ Types
//---------------------------------------------------- Variables statiques
static int balVoitures;
static int * mpDureeFeu;
static int semDureeFeuId;
static pid_t generateur;
//------------------------------------------------------ Fonctions privées
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
void Clavier (pid_t tacheGenerateur, int semDureeFeu, int mpDureeFeuId, int balVoituresId)
// Algorithme :
//
{
	//Phase Initialisation
	//debloquage de sigint
	sigset_t sigint;
	sigemptyset(&sigint);
	sigaddset(&sigint, SIGINT);
	sigprocmask(SIG_UNBLOCK, &sigint, NULL);
	//Attachement en Ecriture a la Memoire Partage DureeFeu
	mpDureeFeu = (int*) shmat(mpDureeFeuId, NULL, 0);
	//Initialization variables
	balVoitures=balVoituresId;
	nbVoiture=1;
	semDureeFeuId=semDureeFeu;
	etatGenerateur=false;
	generateur = tacheGenerateur;
	
	//Phase Moteur
	Menu();
} //----- fin de Nom


void Commande (char code)
// Algorithme :
//
{
	if(code=='q' || code=='Q')
	{
		//Phase Destruction
		if(shmdt(mpDureeFeu)==0){
			exit(0);
		}
	}
	if(code=='g' || code=='G')
	{
		if(etatGenerateur)
		{
			etatGenerateur=false;
			kill(generateur, SIGSTOP);
			Effacer(ETAT_GENERATEUR);
			Afficher(ETAT_GENERATEUR,"OFF\0",GRAS);
		}else{
			etatGenerateur=true;
			kill(generateur, SIGCONT);
			Effacer(ETAT_GENERATEUR);
			Afficher(ETAT_GENERATEUR,"ON\0",GRAS);
		}
	}
} //----- fin de Nom

void Commande (TypeVoie entree, TypeVoie sortie)
{
	struct Voiture voiture;
	voiture.entree=entree;
	voiture.sortie=sortie;
	voiture.numero=nbVoiture;
	
	Afficher(NUMERO,nbVoiture);
	Afficher(ENTREE,entree);
	Afficher(SORTIE,sortie);
	OperationVoie(PLUS,entree);
	
	if(nbVoiture<200)
	{
		nbVoiture++;
	}else{
		nbVoiture=1;
	}
	
	struct MsgVoiture message;
	message.type=(long) entree;
	message.uneVoiture=voiture;
	int msg=msgsnd(balVoitures, &message, TAILLE_MSG_VOITURE,0);
}

void Commande (TypeVoie voie, unsigned int duree)
{
	if(voie==NORD || voie==SUD){
		ecrireMP(MP_NS, duree, mpDureeFeu, semDureeFeuId);
	}else if(voie==EST || voie==OUEST){
		ecrireMP(MP_EO, duree, mpDureeFeu, semDureeFeuId);
	}
}
