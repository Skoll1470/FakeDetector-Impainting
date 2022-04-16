// blur.cpp : Floute une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"
#include <fstream>
#include <cmath>
#include <iostream>

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  int n;
  float seuil;
  if (argc != 5) 
     {
       printf("Usage: ImageIn.pgm ImgOut.pgm TailleBloc Seuil\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite) ;
   sscanf (argv[3],"%i",&n) ;
   sscanf (argv[4],"%f",&seuil) ;

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);

   int histo[256];
   for(int i=0;i<256;i++){
    histo[i]=0;
   }
   for(int i=0;i<nTaille;i++){
    histo[ImgIn[i]]++;
   }

   float densite[256];
   float s=0;
   for(int i=0;i<256;i++){
    densite[i]=(float)histo[i]/(float)nTaille;
    s+=densite[i];
    std::cout<<i<<" : "<<histo[i]<<" "<<densite[i]<<std::endl;
   }
   s/=(float)nTaille;




   int histoLocal[256];
   float densiteLocale[256];
   float dif[256];
   for(int i=n;i<nH-n;i++){
    for(int j=n;j<nW-n;j++){
      for(int k=0;k<256;k++){
        histoLocal[k]=0;
      }
      for(int k=-n;k<=n;k++){
        for(int l=-n;l<=n;l++){
          histoLocal[ImgIn[(i+k)*nW+j+l]]++;
        }
      }
      for(int k=0;k<256;k++){
        densiteLocale[k]=(float)histoLocal[k]/(float)pow(n*3,2);
      }
      float somme=0;
      for(int k=0;k<256;k++){
        dif[k]=abs(densite[k]-densiteLocale[k]);
        somme+=dif[k];
      }
      float difMoyenne=somme/256.0;
      std::cout<<difMoyenne<<std::endl;
      if(difMoyenne>seuil){
        ImgOut[i*nW+j]=255;
      }
      else{
        ImgOut[i*nW+j]=0;
      }
    }
   }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}