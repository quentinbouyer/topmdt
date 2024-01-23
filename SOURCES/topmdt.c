#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <syslog.h>
#include <glib.h>

#include "topmdt.h"
#include "affiche_mds.h"
#include "initialize_mds.h"
#include "li_stat.h"
#include "parse_arg.h"
#include "compte_mdt.h"
#include "compte_nid.h"
#include "rempli_structure.h"

// GLOBAL VAR

int numclient=0;
char mdt[40]="";
int nbaffich=10;
int nummdt=0;
clitemp *nomip;

// END OF GLOB VAR

io_mds *iomds;

time_t t;

int main( int argc, char *argv[] )
{
	//lecture des arguments
        parse_args (argc, argv);

        //printf ("%d clients max to display\n",nbaffich);

        // on cherche le nombre de mdt
        compte_mdt ();
        printf ("%d mdt\n",nummdt);

	compte_nid();
	printf("%d clients\n", numclient);

	//donnes pour tous les clients de tous les mdt
 	iomds=malloc(numclient * nummdt * sizeof(*iomds));

	//pour stocker provisoirement addip et nom des clients
        nomip=malloc(numclient * sizeof(*nomip));

        // rempli la structure d'un client
        rempli_structure();

	printf("First read\n");

	// initialize pour tous les clients de tous les mdt
	initialize_mds();

	printf("Wait 10s before to read a second time\n");

	sleep(10);

	printf("Second read\n");
  
	li_stat_mds();

	affiche_mds();

	return 0;
}   
