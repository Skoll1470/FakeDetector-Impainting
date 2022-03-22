// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
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

   float moy;
	
   for(int i=0;i<nH;i++){
    for(int j=0;j<nW;j++){
      int k=1;
      moy=ImgIn[i*nW+j];
      if(i-1>0){
        k++;
        moy+=ImgIn[(i-1)*nW+j];
        if(j-1>0){
          k++;
          moy+=ImgIn[(i-1)*nW+j-1];
        }
        if(j+1<nW){
          k++;
          moy+=ImgIn[(i-1)*nW+j+1];
        }
      }
      if(j-1>0){
        k++;
        moy+=ImgIn[i*nW+j-1];
      }
      if(j+1<nW){
        k++;
        moy+=ImgIn[i*nW+j+1];
      }
      if(i+1<nH){
        k++;
        moy+=ImgIn[(i+1)*nW+j];
        if(j-1>0){
          k++;
          moy+=ImgIn[(i+1)*nW+j-1];
        }
        if(j+1<nW){
          k++;
          moy+=ImgIn[(i+1)*nW+j+1];
        }
      }
      moy/=(float)k;
      ImgOut[i*nW+j]=moy;
    }
   }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
