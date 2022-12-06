#ifndef O2_EDYCJA_H
#define O2_EDYCJA_H

#include "o2_pamiec.h"
#include "o2_dane.h"

#include <stdio.h>
#include <math.h>
#include <assert.h>

/* wagi konwersji obrazow kolorowych do szarosci          */
/* (ten sposob konwersji daje znacznie lepszy efekt niz   */
/* srednia wartosci RGB i nie wymaga korekcji gammy       */
/* w przeciwienstwie do metody "prawidlowej")             */
#define GS_R 0.3
#define GS_G 0.59
#define GS_B 0.11

void filtrowanie(t_obraz *obraz, float filtr[][3]);
/*****************************************************************************/
/* Funkcja wykonuje operacje splotu na wskazanym obrazie,                    */
/* korzystajac z podanego filtra.                                            */
/*                                                                           */
/* Argumenty funkcji:                                                        */
/* obraz - struktura danych zawierajaca obraz                                */
/* filtr[][3] - tablica 3x3 z filtrem                                        */
/*                                                                           */
/* PRE:                                                                      */
/* Funkcja obsluguje obrazy PGM i PPM.                                       */
/*                                                                           */
/* POST:                                                                     */
/* Funkcja  modyfikuje wartosci pikseli wskazanego obrazu zgodnie z filtrem, */
/* a nastepnie dokonuje normalizacji. Obraz wyjsciowy ma mniejsze wymiary    */
/* od obrazu wejsciowego o minimum 2 piksele.                                */
/*****************************************************************************/

void progowanie(t_obraz *obraz, float prog);
/**************************************************************************************/
/* Funkcja wykonuje operacje progowania na wskazanym obrazie.                         */
/*                                                                                    */
/* Argumenty funkcji:                                                                 */
/* obraz - struktura danych zawierajaca obraz                                         */
/* prog - wartosc progu                                                               */
/*                                                                                    */
/* PRE:                                                                               */
/* Funkcja obsluguje obrazy PGM i PPM.                                                */
/* Wartosc progu musi zawierac sie w przedziale (0.0;1.0)                             */
/*                                                                                    */
/* POST:                                                                              */
/* Funkcja modyfikuje wartosci pikseli wskazanego obrazu na podstawie wartosci progu. */
/**************************************************************************************/


void normalizacja(t_obraz *obraz);
/*************************************************************************************/
/* Funkcja wykonuje operacje normalizacji na wskazanym obrazie.                      */
/*                                                                                   */
/* Argumenty funkcji:                                                                */
/* obraz - struktura danych zawierajaca obraz                                        */
/*                                                                                   */
/* PRE:                                                                              */
/* Funkcja obsluguje obrazy PGM i PPM.                                               */
/*                                                                                   */
/* POST:                                                                             */
/* Funkcja skaluje wartosci pikseli zmodyfikowanego obrazu,                          */
/* aby byly zgodne z wartoscia szarosci obrazu oryginalnego.                         */
/*************************************************************************************/


void do_szarosci(t_obraz *obraz);
/*************************************************************************************/
/* Funkcja konwertuje obraz kolorowy do szarosci.                                    */
/*                                                                                   */
/* Argumenty funkcji:                                                                */
/* obraz - struktura danych zawierajaca obraz                                        */
/*                                                                                   */
/* PRE:                                                                              */
/* Funkcja obsluguje obrazy PPM.                                                     */
/*                                                                                   */
/* POST:                                                                             */
/* Funkcja konwertuje obraz kolorowy na szary. Alokowana zostaje nowy, mniejszy      */
/* blok pamieci, a stary jest zwalniany. Konwersja odbywa się w oparciu o wagi       */
/* kolorow GS_R, GS_G, i GS_B.                                                       */
/*************************************************************************************/

void zmiana_poziomow(t_obraz *obraz, float min, float maks);
/*************************************************************************************/
/* Funkcja wykonuje operacje zmiany poziomow na wskazanym obrazie.                   */
/*                                                                                   */
/* Argumenty funkcji:                                                                */
/* obraz - struktura danych zawierajaca obraz                                        */
/* min - dolny prog                                                                  */
/* maks - gorny prog                                                                 */
/*                                                                                   */
/* PRE:                                                                              */
/* Funkcja obsluguje obrazy PGM i PPM.                                               */
/* Wartosci progow musza zawierac sie w przedziale (0.0;1.0).                        */
/* Prog dolny < Prog gorny                                                           */
/*                                                                                   */
/* POST:                                                                             */
/* Funkcja zmienia wartosc pikseli:                                                  */
/* - na 0, jesli ich wartosc jest mniejsza niz prog dolny                            */
/* - na wartosc maksymalna, jesli ich wartosc jest wieksza lub rowna progowi gornemu */
/* - o wartosciach pomiedzy progami, rozciagajac je na nowym zakresie                */
/*************************************************************************************/

/*******************************************************************************************/
/* Ponizsze funkcje oparte sa o funkcje filtrowanie() z zastosowaniem odpowiedniego filtru */
/*******************************************************************************************/
void negatyw(t_obraz *obraz);
/**********************************************************************/
/* Funkcja wykonuje operacje negatywu na wskazanym obrazie.           */
/* Filtr:                                                             */
/* {0, 0,0}                                                           */
/* {0,-1,0}                                                           */
/* {0, 0,0}                                                           */
/**********************************************************************/

void rozmycie_pion(t_obraz *obraz);
/**********************************************************************/
/* Funkcja wykonuje operacje rozmycia pionowego na wskazanym obrazie. */
/* Filtr:                                                             */
/* {0,0.33,0}                                                         */
/* {0,0.33,0}                                                         */
/* {0,0.33,0}                                                         */
/**********************************************************************/

void konturowanie(t_obraz *obraz);
/**********************************************************************/
/* Funkcja wykonuje operacje kontrowania na wskazanym obrazie.        */
/* Obrazy kolorowe sa najpierw konwertowane do szarosci przy pomocy   */
/* funkcji do_szarosci().                                             */
/* Filtr:                                                             */
/* { 0,0,0}                                                           */
/* {-1,0,0}                                                           */
/* { 0,1,0}                                                           */
/**********************************************************************/

#endif
