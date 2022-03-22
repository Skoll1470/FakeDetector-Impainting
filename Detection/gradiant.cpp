// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include <cmath>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm\n"); 
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
	
   int gv, gh;
   float norm;
   for(int i=0;i<nH;i++){
    for(int j=0;j<nW;j++){
      if(i==nH-1){
        gv=0;
      }
      else{
        gv=ImgIn[(i+1)*nW+j]-ImgIn[i*nW+j];
      }
      if(j==nW-1){
        gh=0;
      }
      else{
        gh=ImgIn[i*nW+j+1]-ImgIn[i*nW+j];
      }
      norm=pow(gh,2)+pow(gv,2);
      norm=sqrt(norm);
      if(norm>255.0){
        norm=255.0;
      }
      ImgOut[i*nW+j]=norm;
    }
   }



   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
