#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <dirent.h>


#include "topmdt.h"

// GLOB VAR

extern io_mds *iomds;
extern clitemp *nomip;
extern int numclient;
extern int nummdt;

// END OF GLOB VAR

void initialize_mds()
{
 int i=0;
 int j=0;
 int co=0;
 DIR *rep = NULL;
 struct dirent *fichierlu = NULL;

 // pour le split de chaine
 gchar **resultat;

 FILE *f2;

 // nb total d'enregistrement
 int nbenrg=0;

 //pour supprimer le caractere \n dans le fgets
 char *p="";

 char buffer[80]="";

 char *li = NULL;

 if ( nummdt > 0 )
 {
  if(NULL==(rep=opendir("/proc/fs/lustre/mdt")))
  {
   fprintf(stderr,"Impossible de trouver /proc/fs/lustre/mdt\n");
   exit(EXIT_FAILURE);
  }
  for(i=0;i<nummdt+2;i++)
  {
   fichierlu=readdir(rep);
   if(fichierlu->d_name && strcmp(fichierlu->d_name,".") && strcmp(fichierlu->d_name,".."))
   {
    for(j=0;j<numclient;j++)
    {
     strcpy(iomds[co].mdt_name,fichierlu->d_name);
     //printf("iomds.mdt_name=%s\n",iomds[co].mdt_name);
     sprintf(iomds[co].path,"/proc/fs/lustre/mdt/%s/exports/%s/stats",fichierlu->d_name,nomip[j].ipcli);
     //printf("iomds.path=%s\n",iomds[co].path);
     strcpy(iomds[co].addip,nomip[j].ipcli);
     //printf("iomds.addip=%s\n",iomds[co].addip);
     strcpy(iomds[co].nomhost,nomip[j].nomcli);
     //printf("iomds.nomhost=%s\n",iomds[co].nomhost);
     co++;
    }
   }
  }
  closedir(rep);
  co=0;
 }
 else
 {
  fprintf(stderr,"Aucun mdt\n");
  exit(EXIT_FAILURE);
 }

/// NOUVELLE BOUCLE A FAIRE DE 0 A NUMCLIENT * NUMOST ET LIRE LES INFOS

 nbenrg=numclient*nummdt;

 for(i=0;i<nbenrg;i++)
 {
  if( NULL==(f2=fopen(iomds[i].path,"r")))
  {
   //printf("Impossible de trouver %s\n",iomds[i].path);
   printf("Impossible de trouver les stats pour %s\n",iomds[i].nomhost);
  }
  else
  {
   while(fgets(buffer,80,f2))
   {
    if(strstr(buffer,"open"))
    {
     //printf("path = %s addip=%s\n",iomds[i].path,iomds[i].addip);
     //printf("buffer = %s\n",buffer);
     resultat=g_strsplit(buffer," ",0);
     iomds[i].openf=atol(resultat[22]);
     g_strfreev(resultat);
     //printf("open %s %ld\n",iomds[i].addip,iomds[i].openf);
    }
    else if(strstr(buffer,"getattr"))
    {
     //printf("path = %s addip=%s\n",iomds[i].path,iomds[i].addip);
     //printf("buffer = %s\n",buffer);
     resultat=g_strsplit(buffer," ",0);
     iomds[i].getattrf=atol(resultat[19]);
     g_strfreev(resultat);
    }
   }
   fclose(f2);
  }
  //printf("%s open %ld getattr %ld \n",iomds[i].nomhost,iomds[i].openf,iomds[i].getattrf);
 }
}
