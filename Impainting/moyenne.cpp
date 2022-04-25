// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"
#include <iostream>

bool hasZero(OCTET* Img, int nTaille){
  bool res=false;
  for(int i=0;i<nTaille;i++){
    if(Img[i]<=3){
      res=true;
    }
  }
  return res;
}


//applique la valeur moyenne de ses voisins à un pixel
int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm Seuil \n"); 
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
   float k;
	 //while(hasZero(ImgIn,nTaille)){
     for(int i=0;i<nH;i++){
      for(int j=0;j<nW;j++){
        moy=0;
        k=0;
        //std::cout<<(int)ImgIn[i*nW+j]<<std::endl;
        if(ImgIn[i*nW+j]==0){
          for(int z=-1;z<=1;z++){
            for(int y=-1;y<=1;y++){
              if((i+z)*nW+j+y>0 and (i+z)*nW+j+y<nTaille){
                k++;
                moy+=ImgIn[(i+z)*nW+j+y];
              }
            }
          }
          if(k>0){
            std::cout<<k<<" "<<moy<<std::endl;
            moy/=k;
            if(moy>255){
              moy=255;
            }
            //std::cout<<moy<<std::endl;
            ImgIn[i*nW+j]=moy;
          }
        }
      }
     }
   //}

   for(int i=0;i<nTaille;i++){
    ImgOut[i]=ImgIn[i];
   }



   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
