#include <stdio.h>
#include <cmath>
#include <iostream>
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
	
   //   for (int i=0; i < nTaille; i++)
   // {
   //  if ( ImgIn[i] < S) ImgOut[i]=0; else ImgOut[i]=255;
   //  }



 for (int i=0; i < nH; i++){
   for (int j=0; j < nW; j++)
     {
      if(ImgIn[i*nW+j]==0){
        int max=0;
          if(i-1>0){
            max=std::max(max,(int)ImgIn[(i-1)*nW+j]);
            if(j-1>0){
              max=std::max(max,(int)ImgIn[(i-1)*nW+j-1]);
            }
            if(j+1<nW){
              max=std::max(max,(int)ImgIn[(i-1)*nW+j+1]);
            }
          }
          if(j-1>0){
            max=std::max(max,(int)ImgIn[i*nW+j-1]);
          }
          if(j+1<nW){
            max=std::max(max,(int)ImgIn[i*nW+j+1]);
          }
          if(i+1<nH){
            max=std::max(max,(int)ImgIn[(i+1)*nW+j]);
            if(j-1>0){
              max=std::max(max,(int)ImgIn[(i+1)*nW+j-1]);
            }
            if(j+1<nW){
              max=std::max(max,(int)ImgIn[(i+1)*nW+j+1]);
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