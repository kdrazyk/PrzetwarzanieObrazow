#include "o2_pamiec.h"

int ***alokuj_obraz(t_obraz *obraz){
  /***********************************************************************/
  /* PRE: wymiary tablicy musza byc poprawne (>0),                       */
  /*      wskaznik na tablice musi byc wolny (==NULL)                    */
  /* POST: funkcja alokuje w pamieci tablice 3D o zadanych wymiarach     */
  /*       i zwraca wskaznik na tablice obraz->pix[Z][Y][X]              */
  /***********************************************************************/
  /* Argumenty funkcji:                                                  */
  /*    t_obraz *obraz - wskaznik na strukture zdefiniowana w o2_dane.h  */
  /*                     zawierajaca informacje o obrazie                */
  /***********************************************************************/
  /* Format tablicy 3D w pamieci:                                        */
  /* | Tablica 1D int** Z->Y | Tablica 2D int* Y->X | Tablica 3D int X | */
  /* ^                       ^                      ^                    */
  /* obraz->pix              ptr_z                  ptr_y                */
  /***********************************************************************/
  /**/ /* Asercje */                                                   /**/
  /**/ assert(obraz->wymx > 0);                                        /**/
  /**/ assert(obraz->wymy > 0);                                        /**/
  /**/ assert(obraz->kolory == 1 || obraz->kolory == 3);               /**/
  /**/ assert(obraz->pix == NULL);                                     /**/
  /***********************************************************************/
  int **ptr_z; /* offset Z  */
  int *ptr_y;  /* offset Y  */
  int z,y;     /* iteratory */
  /* Alokacja bloku pamieci */
  obraz->pix = (int ***)malloc( (sizeof(int **) * obraz->kolory ) +
                                (sizeof(int *)  * obraz->kolory * obraz->wymy ) +
                                (sizeof(int)    * obraz->kolory * obraz->wymy * obraz->wymx ));
  assert(obraz->pix != NULL); /* test poprawnosci alokacji pamieci  */
  /* Przypisanie wskaznikow Z->Y */
  ptr_z = (int **)(obraz->pix + obraz->kolory);
  for (z=0; z < obraz->kolory; z++)
    obraz->pix[z] = (ptr_z +
                     z * obraz->wymy );
  /* Przypisanie wskaznikow Y->X */
  ptr_y = (int *)(ptr_z + obraz->wymy * obraz->kolory);
  for (z=0; z < obraz->kolory; z++)
    for (y=0; y < obraz->wymy; y++)
      obraz->pix[z][y] = (ptr_y +
                          y * obraz->wymx +
                          z * obraz->wymx * obraz->wymy );
  return obraz->pix;
}
