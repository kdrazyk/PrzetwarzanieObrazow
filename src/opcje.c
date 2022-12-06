/********************************************************************/
/*                                                                  */
/* ALTERNATYWNA DO PRZEDSTAWIONEJ NA WYKLADZIE WERSJA OPRACOWANIA   */
/* PARAMETROW WYWOLANIA PROGRAMU UWZGLEDNIAJACA OPCJE Z PARAMETRAMI */
/* Z ODPOWIEDNIO ZAPROPONOWANYMI STRUKTURAMI DANYCH PRZEKAZUJACYMI  */
/* WCZYTANE USTAWIENIA                                              */
/*                                    COPYRIGHT (c) 2007-2020 KCiR  */
/*                                                                  */
/* Autorzy udzielaja kazdemu prawa do kopiowania tego programu      */
/* w calosci lub czesci i wykorzystania go w dowolnym celu, pod     */
/* warunkiem zacytowania zrodla                                     */
/*                                                                  */
/********************************************************************/

/********************************************************************/
/* Uwaga:                                                           */
/* Wprowadzono znaczne modyfikacje w zasadzie dzialania wzgledem    */
/* implementacji oryginalnej.                                       */
/********************************************************************/


#include "opcje.h"

/*******************************************************/
/* Funkcja inicjuje strukture wskazywana przez wybor   */
/* PRE:                                                */
/*      poprawnie zainicjowany argument wybor (!=NULL) */
/* POST:                                               */
/*      "wyzerowana" struktura wybor wybranych opcji   */
/*******************************************************/

void wyzeruj_opcje(t_opcje * wybor) {
  wybor->plik_we=NULL;
  wybor->plik_wy=NULL;
  wybor->pomoc=0;
  wybor->l_opcji=0;
}

int przetwarzaj_opcje(int argc, char **argv, t_opcje *wybor, int shell) {
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
  int i;                 /* iterator */
  float prog;            /* progowanie */
  char *nazwa_pliku_we;
  char *nazwa_pliku_wy;
  float zp_min;          /* zmiana poziomow, prog dolny */
  float zp_maks;         /* zmiana poziomow, prog gorny */

  if(!shell){
    wyzeruj_opcje(wybor);
    if(argc==1)               /* brak parametrow -> uruchom interfejs shell */
      return TRYB_SHELL;
    wybor->plik_wy=stdout;    /* na wypadek gdy nie podano opcji "-o" */
  }

  for (i=1; i<argc; i++) {
    if (argv[i][0] != '-')  /* blad: to nie jest opcja - brak znaku "-" */
      return B_NIEPOPRAWNAOPCJA; 
    switch (wybor->kolejnosc[wybor->l_opcji++]=argv[i][1]) {

    case WEJSCIE: {                 /* opcja z nazwa pliku wejsciowego */
      if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
        nazwa_pliku_we=argv[i];
        if (strcmp(nazwa_pliku_we,"-")==0) /* gdy nazwa jest "-"        */
          wybor->plik_we=stdin;            /* ustwiamy wejscie na stdin */
        else                               /* otwieramy wskazany plik   */
          wybor->plik_we=fopen(nazwa_pliku_we,"r");
      }
      else
        return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
      break;
    }

    case WYJSCIE: {                 /* opcja z nazwa pliku wyjsciowego */
      if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
        nazwa_pliku_wy=argv[i];
        if (strcmp(nazwa_pliku_wy,"-")==0)/* gdy nazwa jest "-"         */
          wybor->plik_wy=stdout;          /* ustwiamy wyjscie na stdout */
        else                              /* otwieramy wskazany plik    */
          wybor->plik_wy=fopen(nazwa_pliku_wy,"w");
      }
      else
        return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
      break;
    }

    case PROGOWANIE: {
      if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu */
        if (sscanf(argv[i],"%f",&prog)==1) {
          wybor->w_progu=prog;
        }
        else
          return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
      }
      else
        return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
      break;
    }

    case ZMIANA_POZ:{
      if(++i<argc){                       /* wczytaj pierwsza wartosc  */
        if (sscanf(argv[i],"%f",&zp_min)==1)
          wybor->zp_min = zp_min;
        else
          return B_BRAKWARTOSCI;          /* blad: brak wartosci progu */
      }
     if(++i<argc){                        /* wczytaj druga wartosc     */
        if (sscanf(argv[i],"%f",&zp_maks)==1)
          wybor->zp_maks = zp_maks;
        else
          return B_BRAKWARTOSCI;          /* blad: brak wartosci progu */
      }
      break;
    }



      /* pozostale funkcje nie wymagaja dodatkowych czynnosci */
    case POMOC: break;
    case ZAKONCZ: break;
    case WYSWIETL: break;
    case NEGATYW: break;
    case ROZMYCIE: break;
    case KONTUROWANIE: break;
    case SZAROSC: break;

    default:                    /* nierozpoznana opcja */
      return B_NIEPOPRAWNAOPCJA;
    } /* koniec switch */
  } /* koniec for */

  if(shell)                    /* obsluga interfejsu shell  */
    return TRYB_SHELL;

  if (wybor->plik_we!=NULL)     /* ok: wej. strumien danych zainicjowany */
    return W_OK;
  else 
    return B_BRAKPLIKU;         /* blad:  nie otwarto pliku wejsciowego  */
}

