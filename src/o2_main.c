#include "o2_main.h"

int main(int argc, char **argv) {

  t_shell input;   /* struktura przechowujaca argumenty wywolania */
  t_opcje opcje;   /* struktura przechowujaca opcje wywolania (po przetworzeniu argumentow) */
  t_obraz obraz;   /* struktura przechowujaca informacje o obrazie */
  int kod_bledu;

  obraz.pix = NULL; /* inicjalizacja struktury */

  kod_bledu=przetwarzaj_opcje(argc,argv,&opcje, 0);   /* analiza parametrow wywolania, test poprawnosci syntaktycznej */

  if (kod_bledu == TRYB_SHELL){  /* brak opcji -> interfejs shell  */
    printf("Obrazy 2 - shell\n");
    while(kod_bledu != W_OK){            /* kod_bledu == W_OK -> koniec dzialania programu */
      sh_input(&input);                  /* pobranie opcji od uzytkownika */
      kod_bledu = przetwarzaj_opcje(input.count, input.pvalue, &opcje, 1); /* analiza opcji, test poprawnosci syntaktycznej */
      informacja_o_bledzie(kod_bledu);
      if(kod_bledu == TRYB_SHELL){       /* opcje poprawne */
        kod_bledu = interpretuj_opcje(&obraz, &opcje); /* interpretacja opcji, test poprawnosci semantycznej */
        informacja_o_bledzie(kod_bledu);
      }
    }
  }
  else if (kod_bledu){ /* obsluga bledu wywolania */
    informacja_o_bledzie(kod_bledu);
    return kod_bledu;
  }
  else{  /* wywolanie poprawne -> interpretacja opcji */
    printf("Opcje poprawne\n");
    kod_bledu = interpretuj_opcje(&obraz, &opcje); /* interpretacja opcji, test poprawnosci semantycznej */
    informacja_o_bledzie(kod_bledu);
    if(kod_bledu == TRYB_SHELL)  /* niestety, ale niepoprawne rozwiazanie problemu napotkanego w ostatniej chwili */
      kod_bledu = W_OK;
  }
  return kod_bledu;
}

int interpretuj_opcje(t_obraz *obraz, t_opcje *opcje){
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
  /**/ /* Asercje: */                                           /**/
  /**/ assert(obraz!=NULL);                                     /**/
  /**/ assert(opcje!=NULL);                                     /**/
  /****************************************************************/
  for(int i=0; i < opcje->l_opcji; i++){
    switch(opcje->kolejnosc[i]){
      /* negatyw --------------------------------------------------------------------------------------*/
    case NEGATYW:
      if(obraz->pix == NULL){ /* brak obrazu */
        opcje->l_opcji = 0;
        return B_BRAK_OBRAZU;
      }
      else
        negatyw(obraz);
      break;
      /* rozmycie -------------------------------------------------------------------------------------*/
    case ROZMYCIE:
      if(obraz->pix == NULL){ /* brak obrazu */
        opcje->l_opcji = 0;
        return B_BRAK_OBRAZU;
      }
      else
        rozmycie_pion(obraz);
      break;
      /* konturowanie ---------------------------------------------------------------------------------*/
    case KONTUROWANIE:
      if(obraz->pix == NULL){ /* brak obrazu */
        opcje->l_opcji = 0;
        return B_BRAK_OBRAZU;
      }
      else
        konturowanie(obraz);
      break;
      /* progowanie -----------------------------------------------------------------------------------*/
    case PROGOWANIE:
      if(obraz->pix == NULL){ /* brak obrazu */
        opcje->l_opcji = 0;
        return B_BRAK_OBRAZU;
      }
      else if(!(opcje->w_progu >= 0 && opcje->w_progu <= 1)){     /* niepoprawna watosc progu */
        opcje->l_opcji = 0;
        return B_ZLY_PROG;
      }
      else
        progowanie(obraz, opcje->w_progu);
      break;
      /* zmiana poziomow ------------------------------------------------------------------------------*/
    case ZMIANA_POZ:
      if(obraz->pix == NULL){ /* brak obrazu */
        opcje->l_opcji = 0;
        return B_BRAK_OBRAZU;
      }
      else if(opcje->zp_min < 0 || opcje->zp_min > 1 ||      /* niepoprawna watosc progu */
              opcje->zp_maks < 0 || opcje->zp_maks > 1 ||
              opcje->zp_maks <= opcje->zp_min){
        opcje->l_opcji = 0;
        return B_ZLY_PROG;
      }
      else
        zmiana_poziomow(obraz, opcje->zp_min, opcje->zp_maks);
      break;
      /* konwersja do szarosci ------------------------------------------------------------------------*/
    case SZAROSC:
      if(obraz->pix == NULL){ /* brak obrazu */
        opcje->l_opcji = 0;
        return B_BRAK_OBRAZU;
      }
      else if(obraz->kolory != 3){ /* niepoprawny typ obrazu */
        opcje->l_opcji = 0;
        return B_ZLY_TYP;
      }
      else
        do_szarosci(obraz);
      break;
      /* wyswietl aktualny stan obrazu ----------------------------------------------------------------*/
    case WYSWIETL:
      if(obraz->pix == NULL){ /* brak obrazu */
        opcje->l_opcji = 0;
        return B_BRAK_OBRAZU;
      }
      else
        wyswietl(obraz);
      break;
      /* wczytaj plik  --------------------------------------------------------------------------------*/
    case WEJSCIE:
      if(opcje->plik_we == NULL){
        opcje->l_opcji = 0;
        return B_ZLY_PLIK;
      }
      else
        czytaj(opcje->plik_we, obraz);
      break;
      /* zapisz plik ----------------------------------------------------------------------------------*/
    case WYJSCIE:
      if(opcje->plik_wy == NULL){
        opcje->l_opcji = 0;
        return B_ZLY_PLIK;
      }
      else
        zapisz(opcje->plik_wy, obraz);
      break;
      /* wyswietl pomoc -------------------------------------------------------------------------------*/
    case POMOC:
      pomoc();
      break;
      /* zakoncz dzialanie programu -------------------------------------------------------------------*/
    case ZAKONCZ:
      opcje->l_opcji = 0;
      return 0;
    }
  }
  opcje->l_opcji = 0;
  return TRYB_SHELL;
}


void sh_input(t_shell *input){
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
  char buf[COM_LEN*ARG_MAX];       /* bufor pomocniczy*/
  int i=0,j=0,k=1;                 /* iteratory */
  input->count = 0;                /* reset wartosci */
  printf(SHELL_NAME);
  fgets(buf,COM_LEN,stdin);        /* pobranie opcji */
  for(;buf[i]!='\0';i++){          /* podzial ciagu znakow na opcje i ich argumenty */
    if(buf[i]==' ' || buf[i]=='\n'){
      input->value[k][j] = '\0';
      j=0;
      k++;                         /* zliczanie opcji */
    }
    else
      input->value[k][j++] = buf[i];
  }
  input->count = k;  /* ilosc opcji */
  for(i=0;i<k;i++)
    input->pvalue[i] = &input->value[i][0];  /* utworzenie tablicy wskaznikow */
}

void pomoc(){
  /******************************************************/
  /* Funkcja wyswietla informacje o dzialaniu programu. */
  /* PRE: brak                                          */
  /* POST: brak                                         */
  /******************************************************/
  printf(POMOC1);
  /*printf(POMOC2);*/
  printf(POMOC3);
  printf(POMOC4,WEJSCIE);
  printf(POMOC5,WYJSCIE);
  printf(POMOC6,WYSWIETL);
  printf(POMOC7,NEGATYW);
  printf(POMOC8,ROZMYCIE);
  printf(POMOC9,KONTUROWANIE);
  printf(POMOC10,PROGOWANIE);
  printf(POMOC11,ZMIANA_POZ);
  printf(POMOC12,SZAROSC);
  printf(POMOC13,POMOC);
  printf(POMOC14,ZAKONCZ);
  printf(POMOC15);
}

int informacja_o_bledzie(int kod_bledu){
  /****************************************************************/
  /* Funkcja wypisuje na stderr informacje o bledzie na podstawie */
  /* kodu bledu                                                   */
  /* PRE: brak                                                    */
  /* POST: brak                                                   */
  /****************************************************************/
  switch(kod_bledu){
  case B_BRAK_OBRAZU:
    fprintf(stderr,"Blad: wczytaj obraz\n");
    break;
  case B_ZLY_PROG:
    fprintf(stderr,"Blad: zla wartosc progu\n");
    break;
  case B_ZLY_TYP:
    fprintf(stderr,"Blad: zly typ obrazu\n");
    break;
  case B_ZLY_PLIK:
    fprintf(stderr,"Blad: brak uchwytu pliku\n");
    break;
  case B_NIEPOPRAWNAOPCJA:
    fprintf(stderr,"Blad: niepoprawna opcja\n");
    break;
  case B_BRAKNAZWY:
    fprintf(stderr,"Blad: brak nazwy\n");
    break;
  case B_BRAKWARTOSCI:
    fprintf(stderr,"Blad: brak wartosci\n");
    break;
  case B_BRAKPLIKU:
    fprintf(stderr,"Blad: brak pliku\n");
    break;
  default:
    return 0;
  }
  return kod_bledu;
}
