// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include <cmath>
#include "image_ppm.h"
#include <iostream>
#include <vector>
#include <algorithm>

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
   
   float moy=0;
   float moyc=0;
   for(int i=0;i<nTaille;i++){
    moy+=ImgIn[i];
    moyc+=pow(ImgIn[i],2);
   }
   moyc/=(float)nTaille;
   moy/=(float)nTaille;
   float var=moyc-pow(moy,2);
   float ecart=sqrt(var);
   std::cout<<ecart<<std::endl;

   int seuilTex=ecart/4;
   std::vector<int> med;
   int valMed;
   int imgMed;
   for(int i=0;i<nH;i++){
    for(int j=0;j<nW;j++){
      med.clear();
      med.push_back(ImgIn[i*nW+j]);
      if(i-1>=0){
        med.push_back(ImgIn[(i-1)*nW+j]);
        if(j-1>=0){
          med.push_back(ImgIn[(i-1)*nW+j-1]);
        }
        if(j+1<nW){
          med.push_back(ImgIn[(i-1)*nW+j+1]); 
        }
      }

      if(j-1>=0){
        med.push_back(ImgIn[i*nW+j-1]);   
      }
      if(j+1<nW){
        med.push_back(ImgIn[i*nW+j+1]);
      }

      if(i+1<nH){
        med.push_back(ImgIn[(i+1)*nW+j]);
        if(j-1>=0){
          med.push_back(ImgIn[(i+1)*nW+j-1]);
        }
        if(j+1<nH){
          med.push_back(ImgIn[(i+1)*nW+j+1]);
        }
      }

      std::sort(med.begin(), med.end());

      valMed=med[(med.size()/2)+1];

      if(abs(ImgIn[i*nW+j]-valMed)>seuilTex){
        imgMed=ImgIn[i*nW+j];
        ImgOut[i*nW+j]=0;
      }
      else{
        imgMed=valMed;
        ImgOut[i*nW+j]=128+(ImgIn[i*nW+j]-valMed);
      }

    }
   }   


   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
