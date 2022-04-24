// blur.cpp : Floute une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"
#include <iostream>

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  int som;
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
   lire_image_pgm(cNomImgEcrite, ImgOut, nH * nW);

   float verite=0.0;
   float count=0.0;
   float accuracy=0.0;
   float vraiPositif=0.0;
   float fauxPositif=0.0;
   float vraiNegatif=0.0;
   float fauxNegatif=0.0;
   for(int i=0;i<nTaille;i++){
    if(ImgIn[i]==255){
      verite++;
    }
   }

   for(int i=0;i<nTaille;i++){
    if(ImgOut[i]==255){
      if(ImgIn[i]==255){
        vraiPositif++;
      }
      else{
        fauxPositif++;
      }
      count++;
    }
   }

    for(int i=0;i<nTaille;i++){
    if(ImgOut[i]==0){
      if(ImgIn[i]==0){
        vraiNegatif++;
      }
      else{
        fauxNegatif++;
      }
      count++;
    }
   }   

   accuracy=(vraiPositif+vraiNegatif)/(vraiPositif+vraiNegatif+fauxPositif+fauxNegatif);
   std::cout<<accuracy<<std::endl;

   free(ImgIn);free(ImgOut);
   return 1;
}