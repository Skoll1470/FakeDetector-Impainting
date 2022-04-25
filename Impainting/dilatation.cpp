#include <stdio.h>
#include <cmath>
#include <iostream>
#include "image_ppm.h"


//applique la dilatation sur chaque pixel à compléter
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
	
   //   for (int i=0; i < nTaille; i++)
   // {
   //  if ( ImgIn[i] < S) ImgOut[i]=0; else ImgOut[i]=255;
   //  }



 for (int i=0; i < nH; i++){
   for (int j=0; j < nW; j++)
     {
      if(ImgIn[i*nW+j]==0){
        int max=0;
        for(int z=-1;z<=1;z++){
          for(int y=-1;y<=1;y++){
            if((i+z)*nW+j+y>0 and (i+z)*nW+j+y<nTaille){
              max=std::max(max,(int)ImgIn[(i+z)*nW+j+y]);  
            }
          }
        }  
        ImgIn[i*nW+j]=max;
       }
      }
    }
   ecrire_image_pgm(cNomImgEcrite, ImgIn,  nH, nW);
   free(ImgIn);
   return 1;
}