// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"
#include <iostream>


//applique la valeur moyenne de ses voisins à un pixel
int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm Seuil \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille*3);
   lire_image_ppm(cNomImgLue, ImgIn, nTaille);
   allocation_tableau(ImgOut, OCTET, nTaille);

   int moy=0;
   for(int i=0;i<nTaille*3;i+=3){
    moy=0;
    moy+=ImgIn[i];
    moy+=ImgIn[i+1];
    moy+=ImgIn[i+2];
    moy/=3;
    if(moy>255){
      moy=255;
    }
    if(moy<0){
      moy=0;
    }
    ImgOut[i/3]=moy;
   }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
