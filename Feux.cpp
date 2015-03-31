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
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
//------------------------------------------------------ Include personnel
#include "Outils.h"
#include "Feux.h"
#include "Mere.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static int * mpCouleurFeu;
static int * mpDureeFeu;

//------------------------------------------------------ Fonctions privées
static void finFeux( int noSignal )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
	shmdt(mpCouleurFeu);
	shmdt(mpDureeFeu);
	exit(0);
} //----- fin de fin

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
void Feux(int semDureeFeuId, int mpDureeFeuId, int semCouleurFeuId, int mpCouleurFeuId)
// Algorithme :
//
{
	//on arme le signal SIGUSR2 sur finFeux
	struct sigaction finAction;
	finAction.sa_handler = finFeux;
	sigemptyset(&finAction.sa_mask);
	finAction.sa_flags = 0;
	sigaction(SIGUSR2, &finAction, NULL);

	//attachement de la memoire du feu
	mpCouleurFeu = (int*) shmat(mpCouleurFeuId, NULL, 0);
	mpDureeFeu = (int*) shmat(mpDureeFeuId, NULL, SHM_RDONLY);

	int dureeRestanteFeuNS = DUREE_INIT_FEU_VERT_NS;
	//le temps que le feu NS passe de vert a rouge + 2s
	int dureeRestanteFeuEO = DUREE_INIT_FEU_VERT_NS + DUREE_FEU_ORANGE + DUREE_FEU_ROUGE_SIMULTANE;

	//on assigne les valeurs initiales du feu
	CouleurFeu couleurFeuNS = VERT;
	Afficher(COULEUR_AXE_NS, "VERT  ");
	ecrireMP(MP_NS, MP_VAL_VERT, mpCouleurFeu, semCouleurFeuId);

	CouleurFeu couleurFeuEO = ROUGE;
	Afficher(COULEUR_AXE_EO, "ROUGE ");
	ecrireMP(MP_EO, MP_VAL_ROUGE, mpCouleurFeu, semCouleurFeuId);

	while(1)
	{
		int dureeFeuEO = lireMP(MP_NS, mpDureeFeu, semDureeFeuId);
		int dureeFeuNS = lireMP(MP_EO, mpDureeFeu, semDureeFeuId);
		if(dureeRestanteFeuNS == 0)
		{
			switch(couleurFeuNS)
			{
				case VERT :
					couleurFeuNS = ORANGE;
					dureeRestanteFeuNS = 3;
					Afficher(COULEUR_AXE_NS, "ORANGE");
					ecrireMP(MP_NS, MP_VAL_ORANGE, mpCouleurFeu, semCouleurFeuId);
					break;
				case ORANGE :
					couleurFeuNS = ROUGE; 
					dureeRestanteFeuNS = dureeFeuEO + DUREE_FEU_ORANGE + 2 * DUREE_FEU_ROUGE_SIMULTANE;
					Afficher(COULEUR_AXE_NS, "ROUGE ");
					ecrireMP(MP_NS, MP_VAL_ROUGE, mpCouleurFeu, semCouleurFeuId);
					break;
				case ROUGE :
					couleurFeuNS = VERT;
					dureeRestanteFeuNS = dureeFeuNS;
					Afficher(COULEUR_AXE_NS, "VERT  ");
					ecrireMP(MP_NS, MP_VAL_VERT, mpCouleurFeu, semCouleurFeuId);
					break;
			}
		}
		
		if(dureeRestanteFeuEO == 0)
		{
			switch(couleurFeuEO)
			{
				case VERT :
					couleurFeuEO = ORANGE;
					dureeRestanteFeuEO = 3;
					Afficher(COULEUR_AXE_EO, "ORANGE");
					ecrireMP(MP_EO, MP_VAL_ORANGE, mpCouleurFeu, semCouleurFeuId);
					break;
				case ORANGE :
					couleurFeuEO = ROUGE; 
					dureeRestanteFeuEO = dureeFeuNS + DUREE_FEU_ORANGE + 2 * DUREE_FEU_ROUGE_SIMULTANE;
					Afficher(COULEUR_AXE_EO, "ROUGE ");
					ecrireMP(MP_EO, MP_VAL_ROUGE, mpCouleurFeu, semCouleurFeuId);
					break;
				case ROUGE :
					couleurFeuEO = VERT;
					dureeRestanteFeuEO = dureeFeuEO;
					Afficher(COULEUR_AXE_EO, "VERT  ");
					ecrireMP(MP_EO, MP_VAL_VERT, mpCouleurFeu, semCouleurFeuId);
					break;
			}
		}
		Afficher(TEMPS_AXE_NS, dureeRestanteFeuNS);
		Afficher(TEMPS_AXE_EO, dureeRestanteFeuEO);
		Afficher(DUREE_AXE_NS, dureeFeuNS);
		Afficher(DUREE_AXE_EO, dureeFeuEO);
		sleep(1);
		dureeRestanteFeuNS--;
		dureeRestanteFeuEO--;
	}
} //----- fin de Feux

