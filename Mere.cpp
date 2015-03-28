/*************************************************************************
                           Mere  -  description
                             -------------------
    début                : 20/03/15
    copyright            : (C) 2015 par B3329
    e-mail               : XXX
*************************************************************************/

//---------- Réalisation de la tâche <Mere> (fichier Mere.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <iostream>
#include <fstream>

//------------------------------------------------------ Include personnel
#include "Mere.h"
#include "Outils.h"
#include "Clavier.h"
#include "Heure.h"
#include "Feux.h"

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
void log(string log)
{
	ofstream myfile;
  	myfile.open ("log", ios::app);
  	myfile << log << endl;
  	myfile.close();
}

int main ( void )
// Algorithme :
//
{
	pid_t pidC;
	pid_t pidH;
	pid_t pidF;
	InitialiserApplication(XTERM);

	//bloquage de sigint
	sigset_t sigint;
	sigemptyset(&sigint);
	sigaddset(&sigint, SIGINT);
	sigprocmask(SIG_BLOCK, &sigint, NULL);

	//recuperation de la cle
	key_t key = ftok("./Carrefour", 0);
	//creation des semaphores
	int semDureeFeuId = semget(key, 1, IPC_CREAT | IPC_EXCL | 0600);
	int semCouleurFeuId = semget(key, 1, IPC_CREAT | IPC_EXCL | 0600);
	//initialisation des semaphores
	semctl(semDureeFeuId, 0, SETVAL, 1);
	semctl(semCouleurFeuId, 0, SETVAL, 1);

	//creation des memoires partagees
	int mpDureeFeu = shmget(key, sizeof(int) * 2, IPC_CREAT | IPC_EXCL | 0600);
	int mpCouleurFeu = shmget(key, sizeof(int) * 2, IPC_CREAT | IPC_EXCL | 0600);

	//creation d'un boite aux lettres
	int balVoitures = msgget(key, IPC_CREAT | IPC_EXCL | 0600);

	if((pidC=fork())==0)
	{
		Clavier();
	}
	else
	{
		if((pidF=fork())==0)
		{
			Feux(semDureeFeuId, mpDureeFeu, semCouleurFeuId, mpCouleurFeu);
		}
		else
		{
			pidH = CreerEtActiverHeure();
			
			//on attend la terminaison du clavier (par q ou sigint)
			waitpid(pidC, 0, 0);
			//on envoie le signal de fin à la tache heure
			kill(pidH, SIGUSR2);
			waitpid(pidH, 0, 0);
			//on envoie le signal de fin à la tache feux
			kill(pidF, SIGUSR2);
			waitpid(pidF, 0, 0);

			//suppression de la B.A.L.
			msgctl(balVoitures, IPC_RMID, 0);

			//suppression des memoires partagees
			shmctl(mpDureeFeu, IPC_RMID, 0);
			shmctl(mpCouleurFeu, IPC_RMID, 0);

			//supression des semaphores
			semctl(semDureeFeuId, 0, IPC_RMID, 0);
			semctl(semCouleurFeuId, 0, IPC_RMID, 0);

			TerminerApplication();
		}
	}
	//return ou exit ?
	return 0;
} //----- fin de Nom

