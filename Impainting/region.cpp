// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include <cmath>
#include "image_ppm.h"
#include <iostream>
#include <vector>
#include <algorithm>

bool hasBlack(OCTET* tab, int nTaille){
  bool res=false;
  for(int i=0;i<nTaille;i++){
    if(tab[i]==0){
      res=true;
      break;
    }
  }
  return res;
}

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
   lire_image_pgm(cNomImgLue, ImgOut, nH * nW);
   
   int borderi;
   int borderj;
   int indexi;
   int indexj;
   int dist;
   bool check;
    while(hasBlack(ImgOut,nTaille)){
     for(int i=1;i<nH-1;i++){
      for(int j=1;j<nW-1;j++){

        if(ImgIn[i*nW+j]==0){
          check=false;
          for(int k=-1;k<2;k++){
            for(int f=-1;f<2;f++){
              if(ImgIn[(i+k)*nW+j+f]!=0){
                borderi=i+k;
                borderj=j+f;
                check=true;
                break;
              }
            }
            if(check){
              break;
            }
          }
          if(!check){
            break;
          }               
          dist=256;
          indexi=nH;
          indexj=nW;
          for(int k=1;k<nH-1;k++){
            for(int f=1;f<nW-1;f++){
              int somme=0;
              if(k!=borderi and f!=borderj){
                for(int h=-1;h<2;h++){
                  for(int w=-1;w<2;w++){
                    somme+=abs(ImgIn[(k+h)*nW+f+w]-ImgIn[(borderi+h)*nW+borderj+w]);
                  }
                }
                somme/=9;
                if(somme<dist){
                  dist=somme;
                  //index=k*nW+f;
                  indexi=k;
                  indexj=f;
                }
              }
            }
          }
          //ImgOut[i*nW+j]=ImgIn[index];
          for(int h=-1;h<2;h++){
            for(int w=-1;w<2;w++){
              ImgOut[(i+h)*nW+j+w]=ImgIn[(indexi+h)*nW+indexj+w];
              if(ImgOut[(i+h)*nW+j+w]==0){
                ImgOut[(i+h)*nW+j+w]++;
              }
            }
          }
        }
      }
     }
     for(int z=0;z<nTaille;z++){
      ImgIn[z]=ImgOut[z];
     }
   }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
