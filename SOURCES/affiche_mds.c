#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "topmdt.h"


// GLOB VAR

extern int nbaffich;
extern int numclient;
extern int nummdt;
extern char mdt[40];
extern io_mds *iomds;
extern time_t t;

// END OF GLOB VAR


//fonctions pour le qsort

long compareio_openf(const void *v1, const void *v2)
{
  const io_mds *u1 = v1;
  const io_mds *u2 = v2;
  return (u2->opf - u1->opf);
}

long compareio_getattrf( const void *v1, const void *v2)
{
  const io_mds *u1 = v1;
  const io_mds *u2 = v2;
  return ( u2->getf - u1->getf);
}


void affiche_mds()
{
 FILE *load;
 float load1=0;
 float load5=0;
 float load15=0;
 char loadchaine[80]="";
 int i=0;
 int nbenrg=0;

 time(&t);

 nbenrg=numclient*nummdt;

 //printf ("Nb enrg = %d\n",nbenrg);

 // lecture du load average
 if(NULL==(load=fopen("/proc/loadavg","r")))
 {
  printf("Impossible de trouver loadavg\n");
  exit(EXIT_FAILURE);
 }
 fscanf(load,"%f %f %f %s",&load1,&load5,&load15,&loadchaine);
 fclose(load);

 qsort(iomds,nbenrg,sizeof(io_mds),compareio_openf);
 //qsort(iomds,numclient,sizeof(io_mds),compareio_getattrf);
 printf("--------------------------------------------------------------------------\n");
 printf("Open\n");
 printf("MDT \t\tCLIENT \tNB OPEN FILE\n");
 printf("--------------------------------------------------------------------------\n");

 if ( nbenrg < nbaffich )
  nbaffich = nbenrg -1;

 for(i=0; i < nbaffich; i++)
 {
  if(iomds[i].opf>0)
  {
   printf("%s\t%8s\t%ld\t\n",iomds[i].mdt_name, iomds[i].nomhost, iomds[i].opf);
  }
 }

 qsort(iomds,nbenrg,sizeof(io_mds),compareio_getattrf);
 printf("--------------------------------------------------------------------------\n");
 printf("Get attribute\n");
 printf("MDT \t\tCLIENT \tNB GET ATTRIBUTE\n");
 printf("--------------------------------------------------------------------------\n");

 for(i=0; i < nbaffich; i++)
 {
  if(iomds[i].getf>0)
  {
   printf("%s\t%8s\t%ld\t\n",iomds[i].mdt_name, iomds[i].nomhost, iomds[i].getf);
  }
 }

 printf("\nLoad : %.2f %.2f %.2f\n",load1,load5,load15);

}
