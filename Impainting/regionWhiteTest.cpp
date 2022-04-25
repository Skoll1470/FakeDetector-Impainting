// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include <cmath>
#include "image_ppm.h"
#include <iostream>
#include <vector>
#include <algorithm>


//détermine s'il reste une zone à compléter
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


//complète les zones en recherchant les régions les plus cohérentes, fonctionne qu'avec des zones blanches
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

   int distanceGauche, distanceDroite, distanceHaut, distanceBas;

   while(hasBlack(ImgIn,nTaille) and interation<100){
    std::cout<<interation<<std::endl;
    for(int i=bloc;i<nH-bloc;i++){

      for(int j=bloc;j<nW-bloc;j++){

        check=false;
        distanceHaut=nH;
        distanceBas=nH;
        distanceGauche=nW;
        distanceDroite=nW;

        if(ImgOut[i*nW+j]==255){

          for(int g=j;g>=0;g--){
            if(ImgIn[i*nW+g]!=255){
              distanceGauche=abs(g-j);
              break;
            }
          }
          for(int d=j;d<nW;d++){
            if(ImgIn[i*nW+d]!=255){
              distanceDroite=abs(d-j);
              break;
            }
          }
          for(int h=i;h>=0;h--){
            if(ImgIn[h*nW+j]!=255){
              distanceHaut=abs(h-i);
              break;
            }
          }
          for(int b=i;b<nH;b++){
            if(ImgIn[b*nW+j]!=255){
              distanceBas=abs(b-i);
              break;
            }
          }
          if(distanceGauche<=distanceDroite and distanceGauche<=distanceHaut and distanceGauche<=distanceBas){
            for(int g=j;g>=0;g--){
              if(ImgOut[i*nW+g]!=255){
                borderi=i;
                borderj=g;
                break;
              }
            }
          }
          if(distanceDroite<=distanceGauche and distanceDroite<=distanceHaut and distanceDroite<=distanceBas){
            for(int d=j;d<nW;d++){
              if(ImgOut[i*nW+d]!=255){
                borderi=i;
                borderj=d;
                break;
              }
            }
          }
          if(distanceHaut<=distanceGauche and distanceHaut<=distanceDroite and distanceHaut<=distanceBas){
            for(int h=i;h>=0;h--){
              if(ImgOut[h*nW+j]!=255){
                borderi=h;
                borderj=j;
                break;
              }
            }
          }
          if(distanceBas<=distanceGauche and distanceBas<=distanceDroite and distanceBas<=distanceHaut){
            for(int b=i;b<nH;b++){
              if(ImgOut[b*nW+j]!=255){
                borderi=b;
                borderj=j;
                break;
              }
            }
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
                  indexi=k;
                  indexj=f;
                }
              }
            }
          }
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
