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
 int k=0;
 long temp=0;
 FILE *f2;
 char buffer[80]="";
 gchar **resultat;
 int nbenrg;

 // pour supprimer \n avec fgets
 char *p="";

 nbenrg=numclient*nummdt;

 for(i=0;i<nbenrg;i++)
 {
  	// printf("Deuxieme lecture\n");
  	//printf("path = %s addip = %s\n",iomds[i].path,iomds[i].addip);

  	// protection contre les entrees vides
  	if(iomds[i].path)
  	{
   		if( NULL == (f2=fopen(iomds[i].path,"r")))
   		{
    			//printf("Impossible de trouver %s\n",iomds[i].path);
    			//printf("Impossible de trouver les stats pour %s\n",iomds[i].nomhost);
   		}
   		else
   		{
    			while(fgets(buffer,80,f2))
    			{
				// on supprime le \n a la fin de la chaine
                                p=strchr(buffer,'\n');
                                if ( p != NULL)
                                        *p='\0';

     				if(strstr(buffer,"open"))
     				{
      					//printf("Pour open\n");
      					//printf("path = %s addip=%s\n",iomds[i].path,iomds[i].addip);
      					//printf("buffer = %s\n",buffer);
      					resultat=g_strsplit(buffer," ",23);

      					temp=atol(resultat[22]);
      					//printf("temp = %ld iomds.i =%ld\n",temp,iomds[i].openf);

      					iomds[i].opf=temp-iomds[i].openf;
      					//printf("resultat = %ld\n",iomds[i].opf);
      					// pour la deuxieme lecture
      					//iomds[i].openf=temp;

					for(k=0;k<22;k++)
                                        	free(resultat[k]);
      					//g_strfreev(resultat);
     				}
     				else if(strstr(buffer,"getattr"))
     				{
      					//printf("Pour getattr\n");
      					//printf("path = %s addip=%s\n",iomds[i].path,iomds[i].addip);
      					//printf("buffer = %s\n",buffer);
      					resultat=g_strsplit(buffer," ",23);

      					temp=atol(resultat[19]);
      					//printf("temp = %ld iomds.i =%ld\n",temp,iomds[i].getattrf);
      					iomds[i].getf=temp-iomds[i].getattrf;
      					//printf("resultat = %ld\n",iomds[i].opf);

					for(k=0;k<22;k++)
                                                free(resultat[k]);
      					//g_strfreev(resultat);
     				}
				else if(strstr(buffer,"unlink"))
				{
					resultat=g_strsplit(buffer," ",23);
					//for(k=0;k<22;k++)
				 	//	printf("k=%d str=%s\n",k,resultat[k]);	
					
					temp=atol(resultat[20]);	
                                        iomds[i].count_unlink=temp-iomds[i].unlink;

					for(k=0;k<22;k++)
                                                free(resultat[k]);	
					//printf("mdt=%s host=%s path = %s unlink = %ld count_unlink = %ld\n",iomds[i].mdt_name,iomds[i].nomhost,iomds[i].path,temp,iomds[i].count_unlink);
				}
     				temp=0;
    			}
    			fclose(f2);
   		}
   		//printf("%s open %ld getattr %ld \n",iomds[i].nomhost,iomds[i].opf,iomds[i].getf);
  	}
 }
}
