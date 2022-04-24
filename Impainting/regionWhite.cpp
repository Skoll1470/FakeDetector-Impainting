// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include <cmath>
#include "image_ppm.h"
#include <iostream>
#include <vector>
#include <algorithm>

bool hasBlack(OCTET* tab, int nTaille){
  bool res=false;
  for(int i=1;i<nTaille-1;i++){
    if(tab[i]==255){
      res=true;
      break;
    }
  }
  return res;
}

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, bloc;
  
  if (argc != 4) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm TailleBloc\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[3],"%i",&bloc);

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
   int interation=0;
    while(hasBlack(ImgIn,nTaille) and interation<100){
      std::cout<<interation<<std::endl;
     for(int i=bloc;i<nH-bloc;i++){
      for(int j=bloc;j<nW-bloc;j++){

        if(ImgOut[i*nW+j]==255){
          check=false;
          for(int k=-bloc;k<=bloc;k++){
            for(int f=-bloc;f<=bloc;f++){
              if(ImgOut[(i+k)*nW+j+f]!=255){
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
          for(int k=bloc;k<nH-bloc;k++){
            for(int f=bloc;f<nW-bloc;f++){
              int somme=0;
              if(k!=borderi and f!=borderj){
                for(int h=-bloc;h<=bloc;h++){
                  for(int w=-bloc;w<=bloc;w++){
                    somme+=abs(ImgIn[(k+h)*nW+f+w]-ImgOut[(borderi+h)*nW+borderj+w]);
                  }
                }
                somme/=pow(bloc*2+1,2);
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
          for(int h=-bloc;h<=bloc;h++){
            for(int w=-bloc;w<=bloc;w++){
              if(ImgIn[(indexi+h)*nW+indexj+w]!=255){
                ImgOut[(i+h)*nW+j+w]=ImgIn[(indexi+h)*nW+indexj+w];
              }
            }
          }
        }
      }
     }
     interation++;
   }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
