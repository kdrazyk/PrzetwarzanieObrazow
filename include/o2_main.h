#ifndef O2_MAIN_H
#define O2_MAIN_H

#include "o2_dane.h"
#include "o2_io.h"
#include "o2_edycja.h"
#include "opcje.h"

#include <stdio.h>

#define B_BRAK_OBRAZU -10
#define B_ZLY_PROG -11
#define B_ZLY_TYP -12
#define B_ZLY_PLIK -13

#define POMOC1 "obrazy2 - pomoc\n"
#define POMOC2 "Program obrazy2 posiada wbudowany interfejs shell, a takze\njest w stanie przyjac opcje jako argumenty wywolania programu.\n"
#define POMOC3 "Dostepne opcje:\n"
#define POMOC4 "\t-%c sciezka/do/pliku - wczytaj obraz z pliku, podanie \"-\" jako sciezki pozwala na czytanie z stdin\n"
#define POMOC5 "\t-%c sciezka/do/pliku - zapisz aktualny stan obrazu do pliku, podanie \"-\" jako sciezki pozwala na pisanie do stdout\n"
#define POMOC6 "\t-%c - wyswietl aktualny stan obrazu\n"
#define POMOC7 "\t-%c - negatyw\n"
#define POMOC8 "\t-%c - rozmycie pionowe\n"
#define POMOC9 "\t-%c - konturowanie\n"
#define POMOC10 "\t-%c prog - progowanie (wartosc progu: 0.0-1.0)\n"
#define POMOC11 "\t-%c prog_dolny prog_gorny - zmiana poziomow (wartosc progow 0.0-1.0)\n"
#define POMOC12 "\t-%c - konwersja obrazu kolorowego na czarno-bialy\n"
#define POMOC13 "\t-%c - pomoc\n"
#define POMOC14 "\t-%c - zakoncz dzialanie programu\n"
#define POMOC15 "Opcje sa wykonywane zgodnie z kolejnoscia wywolania.\n"

#define SHELL_NAME "obrazy2> "
#define COM_LEN 100 /* maksymalna dlugosc pojedynczego argumentu */
#define ARG_MAX 100 /* maksymalna ilosc argumentow wywolania     */


typedef struct{ /* struktura przechowujaca argumenty wywolania */
  char value[ARG_MAX][COM_LEN];   /* tablica argumetow */
  char *pvalue[ARG_MAX];          /* tablica wskaznikow na argumenty */
  int count;                      /* ilosc argumentow */
}t_shell;

void pomoc();
/******************************************************/
/* Funkcja wyswietla informacje o dzialaniu programu. */
/* PRE: brak                                          */
/* POST: brak                                         */
/******************************************************/

int interpretuj_opcje(t_obraz *obraz, t_opcje *opcje);
/****************************************************************/
/* Funkcja interpretuje opcje zgodnie z kolejnoscia wywolania,  */
/* sprawdzajac przed wywolaniem funkcji jego poprawnosc.        */
/*                                                              */
/* Argumenty funkcji:                                           */
/* obraz - wskaznik na strukture z obrazem do modyfikacji       */
/* opcje - wskaznik na strukture z informacja o funkcjach       */
/*         do wywolania                                         */
/* PRE: brak                                                    */
/* POST:                                                        */
/* Funkcja wywoluje zadane funkcje lub zwraca kod bledu,        */
/* jesli poprawne wywolanie jest niemozliwe.                    */
/****************************************************************/

void sh_input(t_shell *input);
/****************************************************************/
/* Funkcja pobiera od uzytkownia opcje i zapisuje je w formacie */
/* analogicznym do argc i argv.                                 */
/*                                                              */
/* Argumenty funkcji:                                           */
/* input - wskaznik na strukture przechowujaca opcje            */
/*                                                              */
/* PRE: brak                                                    */
/* POST:                                                        */
/* W strukturze input zostaje zapisana liczba, a takze tresc    */
/* argumentow oraz tworzona jest tablica ze wskaznikami na      */
/* odpowiednie argumenty (wystapil problem ze zgodnoscia typow) */
/****************************************************************/

int informacja_o_bledzie(int kod_bledu);
/****************************************************************/
/* Funkcja wypisuje na stderr informacje o bledzie na podstawie */
/* kodu bledu                                                   */
/* PRE: brak                                                    */
/* POST: brak                                                   */
/****************************************************************/

#endif
