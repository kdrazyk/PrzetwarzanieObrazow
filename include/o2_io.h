#ifndef O2_IO_H
#define O2_IO_H

#include "o2_pamiec.h" /* dynamiczna alokacja pamieci */
#include "o2_dane.h"   /* definicja struktury t_obraz */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define DL_LINII 1024  /* Dlugosc buforow pomocniczych */
#define PLIK_TMP ".obrazy2.tmp"  /* Nazwa pliku tymczasowego dla funkcji wyswietl */

int czytaj(FILE *plik_we, t_obraz *obraz);
/*******************************************************************/
/* Funkcja wczytuje obraz z pliku do pamieci.                      */
/*                                                                 */
/* Argumenty funkcji:                                              */
/* FILE* - uchwyt pliku zawierajacego obraz                        */
/* obraz - struktura danych, w ktorej zostanie zapisany obraz      */
/*                                                                 */
/* PRE:                                                            */
/* Funkcja obsluguje pliki w formacie .pgm i .ppm.                 */
/*                                                                 */
/* POST:                                                           */
/* Funkcja pobiera informacje o typie pliku (magiczna liczba),     */
/* wymiarach obrazu oraz ilosci odcieni.                           */
/* Na podstawie pobranych wymiarow alokowana zostaje tablica       */
/* i zostaja w niej zapisane informacje o pikselach.               */
/* Funkcja zwraca wczytana ilosc pikseli lub wartosc 0 i komunikat */
/* o bledzie, jesli taki wystapil.                                 */
/*******************************************************************/

void wyswietl(t_obraz *obraz);
  /****************************************************************************/
  /* Funkcja wyswietla wskazany obraz korzystajac z pakietu ImageMagick.      */
  /*                                                                          */
  /* Argumenty funkcji:                                                       */
  /* t_obraz *obraz - wskaznik na strukture z obrazem do wyswietlenia         */
  /*                                                                          */
  /* PRE:                                                                     */
  /* Funkcja obsluguje pliki w formacie .pgm i .ppm.                          */
  /* Do dzialania wymagany jest pakiet ImageMagick.                           */
  /*                                                                          */
  /* POST:                                                                    */
  /* Utworzony zostaje ukryty plik tymczasowy o nazwie okreslonej przez       */
  /* PLIK_TMP                                                                 */
  /****************************************************************************/

void zapisz(FILE *plik_wy, t_obraz *obraz);
/****************************************************************************************/
/* Funkcja zapisuje obraz zawarty we wskazanej strukturze danych do pliku .pgm lub      */
/* .ppm                                                                                 */
/*                                                                                      */
/* Argumenty funkcji:                                                                   */
/* FILE* - uchwyt do pliku wyjsciowego                                                  */
/* obraz - struktura danych zawierajaca obraz                                           */
/*                                                                                      */
/*                                                                                      */
/* PRE:                                                                                 */
/* Funkcja obsluguje obrazy PGM i PPM.                                                  */
/*                                                                                      */
/* POST:                                                                                */
/* Funkcja zapisuje w pliku informacje o typie pliku (magiczna liczba),                 */
/* wymiarach i ilosci odcieni oraz poszczegolnych pikselach zgodnie z formatem PGM/PPM. */
/****************************************************************************************/

#endif
