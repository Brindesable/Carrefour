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

//------------------------------------------------------ Include personnel
#include "Mere.h"
#include "Outils.h"
#include "Clavier.h"
#include "Heure.h"

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
int main ( void )
// Algorithme :
//
{
	pid_t pidC;
	pid_t pidH;
	InitialiserApplication(XTERM);
	if((pidC=fork())==0)
	{
		Clavier();
	}else
	{
		pidH=CreerEtActiverHeure();
		waitpid(pidC,0,0);
		kill(pidH,SIGUSR2);
		waitpid(pidH,0,0);
		TerminerApplication();
	}
	return 0;
} //----- fin de Nom

