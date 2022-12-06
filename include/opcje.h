#ifndef O2_OPCJE_H
#define O2_OPCJE_H

#include<stdio.h>
#include<string.h>

#define W_OK 0                   /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1    /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY   -2
#define B_BRAKWARTOSCI  -3
#define B_BRAKPLIKU   -4
#define TRYB_SHELL 1
#define L_OPCJI 20

#define WEJSCIE 'i'
#define WYJSCIE 'o'
#define WYSWIETL 'd'
#define NEGATYW 'n'
#define ROZMYCIE 'r'
#define KONTUROWANIE 'k'
#define PROGOWANIE 'p'
#define ZMIANA_POZ 'z'
#define SZAROSC 's'
#define POMOC 'h'
#define ZAKONCZ 'e'

/* strukura do zapamietywania opcji podanych w wywolaniu programu */
typedef struct {
  FILE *plik_we, *plik_wy;    /* uchwyty do pliku wej. i wyj. */
  int pomoc;                  /* flaga wyswietl pomoc dla uzytkownika */
  float w_progu;              /* wartosc progu dla opcji progowanie */
  float zp_min;               /* wartosc progu dolnego dla funkcji zmiana poziomow */
  float zp_maks;               /* wartosc progu gornego dla funkcji zmiana poziomow */
  char kolejnosc[L_OPCJI];    /* tablica przechowujaca rodzaj i kolejnosc opcji do wykonania */
  int l_opcji;                /*  */
} t_opcje;


void wyzeruj_opcje(t_opcje * wybor);
/*******************************************************/
/* Funkcja inicjuje strukture wskazywana przez wybor   */
/* PRE:                                                */
/*      poprawnie zainicjowany argument wybor (!=NULL) */
/* POST:                                               */
/*      "wyzerowana" struktura wybor wybranych opcji   */
/*******************************************************/

int przetwarzaj_opcje(int argc, char **argv, t_opcje *wybor, int shell);
/************************************************************************/
/* Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv  */
/* i zapisuje je w strukturze wybor                                     */
/* Skladnia opcji wywolania programu                                    */
/*         program {[-i nazwa] [-o nazwa] [-p liczba] [-n] [-r] [-d]    */
/*                  [-s] [-z liczba liczba] [-h] [-e]}                  */
/* Argumenty funkcji:                                                   */
/*         argc  -  liczba argumentow wywolania wraz z nazwa programu   */
/*         argv  -  tablica argumentow wywolania                        */
/*         wybor -  struktura z informacjami o wywolanych opcjach       */
/*         shell -  flaga okreslajaca tryb wywolania                    */
/*                  (1 - interfejs shell, 0 - analiza opcji wywolania)  */
/* PRE:                                                                 */
/*      brak                                                            */
/* POST:                                                                */
/*      funkcja otwiera odpowiednie pliki, zwraca uchwyty do nich       */
/*      w strukturze wybór, do tego zapisuje takze identyfikatory       */
/*      wywolanych funkcji zgodnie z kolejnoscia wywolania              */
/*      zwraca wartosc W_OK (0), gdy wywolanie bylo poprawne,           */
/*      ewentualnie TRYB_SHELL (1), jesli analizowane sa opcje wywolania*/
/*      oraz argc wynosi 1 lub kod bledu zdefiniowany stalymi B_* (<0)  */
/* UWAGA:                                                               */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow         */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL         */
/************************************************************************/

#endif
