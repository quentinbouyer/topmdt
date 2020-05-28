#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>

#include "topmdt.h"

// GLOB VAR

extern io_mds *iomds;
extern int numclient;
extern int nummdt;

// END OF GLOB VAR

void li_stat_mds()
{
 int i=0;
 int j=0;
 long temp=0;
 FILE *f2;
 char buffer[80]="";
 gchar **resultat;
 int nbenrg;

 nbenrg=numclient*nummdt;

 for(i=0;i<nbenrg;i++)
 {
  //printf("path = %s addip = %s\n",iomds[i].path,iomds[i].addip);

  // protection contre les entrees vides
  if(iomds[i].path)
  {
   if( NULL == (f2=fopen(iomds[i].path,"r")))
   {
    //iomds[i].opf=0;
    //iomds[i].getf=0;
    printf("Impossible de trouver %s\n",iomds[i].path);
   }
   else
   {
    while(fgets(buffer,80,f2))
    {
     if(strstr(buffer,"open"))
     {
      resultat=g_strsplit(buffer," ",0);
      temp=atol(resultat[22]);
      iomds[i].opf=temp-iomds[i].openf;
      // pour la deuxieme lecture
      //iomds[i].openf=temp;
      g_strfreev(resultat);
     }
     else if(strstr(buffer,"getattr"))
     {
      resultat=g_strsplit(buffer," ",0);
      temp=atol(resultat[19]);
      iomds[i].getf=temp-iomds[i].getattrf;
      g_strfreev(resultat);
     }
    }
    fclose(f2);
   }
  }
  else
   printf("iomds path est vide %s\n",iomds[i].path);
 }
}
