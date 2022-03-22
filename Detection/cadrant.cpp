// blur.cpp : Floute une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"
#include <cmath>
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  int som;
  if (argc != 2) 
     {
       printf("Usage: ImageIn.pgm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;

   OCTET *ImgIn;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

   float moyc;
   float moy;
   float var;
   std::vector<float> ecarts;

    int stepH=nH/16;
    int stepW=nW/16;
    if(stepH<=0){
      stepH=1;
    }
    if(stepW<=0){
      stepW=1;
    }
    std::cout<<stepH<<" "<<stepW<<std::endl;
    std::cout<<"allo\n"<<std::endl;
    for(int i=0;i<nH;i+=stepH){
      for(int j=0;j<nW;j+=stepW){
        moy=0;
        moyc=0;
        for(int x=i;x<i+stepH;x++){
          for(int y=j;y<j+stepW;y++){
            moy+=ImgIn[x*nW+y];
            moyc+=pow(ImgIn[x*nW+y],2);
          }
        }
        moy/=(float)(stepH*stepW);
        moyc/=(float)(stepH*stepW);
        var=moyc-pow(moy,2);
        ecarts.push_back(sqrt(var));
      }
    }

    for(unsigned int i=0;i<ecarts.size();i++){
      std::cout<<ecarts[i]<<std::endl;
    }

   free(ImgIn);
   return 1;
}