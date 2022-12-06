/* Dynamiczna alokacja pamieci pod obraz PGM/PPM */

#include "o2_dane.h" /* definicja struktury t_obraz */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int ***alokuj_obraz(t_obraz *obraz);
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
