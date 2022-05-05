#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <dirent.h>

#include "topmdt.h"

#define FILENAME_CONF "/etc/topmdt.conf"

// GLOB VAR

extern int numclient;
extern char mdt[40];
extern io_mds *iomds;
extern time_t t;
extern clitemp *nomip;

// END OF GLOB VAR

void read_conf_file( int flag )
{
 // field in conf file
 char *CHAMP2="client";

 // pointer for char split whit oss and remove \n
 char *pos=NULL;
 char *p=NULL;
 int i=0;
 gchar **resultat;

 //for conf file
 FILE *f;
 char buffer[80]="";
 char temp[80]="";

 //sep caracter for config file
 char *sep_egal="=";
 char *sep_virgule=",";

 //DIR *directory=NULL;

 if ( NULL==(f=fopen(FILENAME_CONF,"r")))
 {
  printf("Impossible de trouver le fichier de config /etc/topmdt.conf");
  exit (EXIT_FAILURE);
 }

 if ( flag == 0 )
 {
  while( fgets(buffer,sizeof(buffer),f) != NULL )
  {
   if (strstr(buffer,CHAMP2))
   {
    numclient++;
   }
  }
  if(numclient == 0 )
  {
   printf("Il faut au moins un client dans /etc/topmdt.conf\n");
   exit(EXIT_FAILURE);
  }
  //printf("mdt=%s nbclient=%d \n",mdt,numclient);
 }
else if ( flag == 1 )
 {

  while( fgets(buffer,sizeof(buffer),f) != NULL )
  {
   if (strstr(buffer,CHAMP2))
   {
    //on supprime le \n a la fin de la chaine
    p=strchr(buffer,'\n');
    if ( p != NULL) *p='\0';

    //go to the field in the str
    pos=strtok(buffer,sep_egal);
    pos=strtok(NULL,sep_egal);
    memcpy(temp,pos,strlen(pos));
    resultat=g_strsplit(temp,",",0);
    if(resultat[0] == NULL)
    {
     printf("Erreur de syntaxe dans topmdt.conf pour\n");
     printf("%s\n",resultat[0]);
     exit(EXIT_FAILURE);
    }
    else
    {
     //strcpy(iomds[i].nomhost,resultat[0]);
     strcpy(nomip[i].nomcli,resultat[0]);
    }
    if(resultat[1] == NULL)
    {
     printf("Erreur de syntaxe dans topmdt.conf pour\n");
     printf("%s\n",resultat[0]);
     exit(EXIT_FAILURE);
    }
    else
    {
     //strcpy(iomds[i].addip,resultat[1]);
     //sprintf(iomds[i].path,"%s/%s/stats",chemin,iomds[i].addip);
     strcpy(nomip[i].ipcli,resultat[1]);
    }
    g_strfreev(resultat);
    //printf("nom client = %s addip = %s\n",nomip[i].nomcli,nomip[i].ipcli);
    i++;
    // remise a zero des buffers
    memset(&buffer[0],0,sizeof(buffer));
    memset(&temp[0],0,sizeof(temp));
   }
  }
 }
 //close the conf file
 fclose(f);
}
