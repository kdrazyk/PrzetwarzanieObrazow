#include "o2_edycja.h"

void filtrowanie(t_obraz *obraz, float filtr[][3]){
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
  /**/ /* Asercje: */                                                        /**/
  /**/ assert(obraz != NULL);                                                /**/
  /**/ assert(obraz->pix != NULL);                                           /**/
  /**/ assert(obraz->wymx > 0);                                              /**/
  /**/ assert(obraz->wymy > 0);                                              /**/
  /**/ assert(obraz->kolory == 1 || obraz->kolory == 3);                     /**/
  /**/ assert(filtr != NULL);                                                /**/
  /*****************************************************************************/
  int ***pix;     /* wskaznik na tablice z obrazem */
  int z,y,x;      /* iteratory */
  int brzeg = 1;  /* szerokosc "brzegu", ktory zostaje odciety (minimum 1) */
  pix = obraz->pix;        /* zachowaj wskaznik na tablice z obrazem           */
  obraz->pix = NULL;       /* wyzeruj wskaznik w strukturze                    */
  obraz->wymx -= 2*brzeg;  /* zmodyfikuj wymiary na wymiary obrazu wyjsciowego */
  obraz->wymy -= 2*brzeg;
  alokuj_obraz(obraz);     /* alokuj pamiec pod obraz wyjsciowy                */
  /* Poruszamy sie po tablicy obrazu (z-kolor y-rzad x-kolumna) */
  for(z=0; z < obraz->kolory; z++)
    for(y=brzeg; y < obraz->wymy+brzeg ;y++)     /* pomijamy wartosci na brzegu */
      for(x=brzeg; x < obraz->wymx+brzeg;x++){
        obraz->pix[z][y-brzeg][x-brzeg] = 0;     /* reset wartosci w danym punkcie */
        for(int i=0; i < 3; i++)                 /* bierzemy pod uwage kwadrat 3x3 z nasza wartoscia w srodku */
          for(int j=0; j < 3; j++)
            /* ustalamy nowa wartosc punktu na podstawie filtra.         */
            /* stosujemy round() aby zachowac zgodnosc formatow danych.  */
            obraz->pix[z][y-brzeg][x-brzeg] += round(pix[z][(y-1)+i][(x-1)+j] * filtr[i][j]);
      }
  free(pix);           /* mozemy zwolnic pamiec z obrazem wejsciowym */
  normalizacja(obraz); /* dokonujemy normalizacji, aby wartosci zgadzaly sie z iloscia odcieni */
}

void progowanie(t_obraz *obraz, float prog){
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
  /**/ /* Asercje: */                                                                 /**/
  /**/ assert(obraz != NULL);                                                         /**/
  /**/ assert(obraz->pix != NULL);                                                    /**/
  /**/ assert(obraz->wymx > 0);                                                       /**/
  /**/ assert(obraz->wymy > 0);                                                       /**/
  /**/ assert(obraz->kolory == 1 || obraz->kolory == 3);                              /**/
  /**/ assert(obraz->odcieni > 0);                                                    /**/
  /**/ assert(prog >= 0 && prog <= 1);                                                /**/
  /**************************************************************************************/
  int odcien_progowy;
  odcien_progowy = round(obraz->odcieni * prog); /* przelozenie ulamku zakresu na konkretna wartosc szarosci */
  if(obraz->kolory != 1)                         /* obraz kolorowy -> konwertuj od szarosci */
    do_szarosci(obraz);
  /* Poruszamy sie po tablicy obrazu i porownujemy wartosci z wartoscia progowa */
  for(int y=0; y < obraz->wymy; y++)
    for(int x=0; x < obraz->wymx; x++){
      if(obraz->pix[0][y][x] > odcien_progowy)
        obraz->pix[0][y][x] = obraz->odcieni;
      else
        obraz->pix[0][y][x] = 0;
    }
}

void normalizacja(t_obraz *obraz){
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
  /**/ /* Asercje: */                                                                /**/
  /**/ assert(obraz != NULL);                                                        /**/
  /**/ assert(obraz->pix != NULL);                                                   /**/
  /**/ assert(obraz->wymx > 0);                                                      /**/
  /**/ assert(obraz->wymy > 0);                                                      /**/
  /**/ assert(obraz->kolory == 1 || obraz->kolory == 3);                             /**/
  /**/ assert(obraz->odcieni > 0);                                                   /**/
  /*************************************************************************************/
  int maks,min; /* minimalna i maksymalna wartosc szarosci znaleziona w obrazie */
  int x,y,z;    /* iteratory */
  /* Ustalenie poczatkowej wartosci szarosci, aby moc pozniej robic porownania */
  maks = obraz->pix[0][0][0];
  min = maks;
  /* Przechodzimy po obrazie i szukamy najmniejszej oraz najwiekszej wartosci  */
  for(z=0; z < obraz->kolory; z++)
    for(y=0; y < obraz->wymy; y++)
      for(x=0; x < obraz->wymx; x++){
        if(obraz->pix[z][y][x] > maks)     /* wartosc wieksza od aktualnej maksymalnej -> zapisz  */
          maks = obraz->pix[z][y][x];
        else if(obraz->pix[z][y][x] < min) /* wartosc mniejsza od aktualnej minimalnej -> zapisz  */
          min = obraz->pix[z][y][x];
      }
  /* Ponowne przejscie po tablicy obrazu i normalizacja wartosci */
  for(z=0; z < obraz->kolory; z++)
    for(y=0; y < obraz->wymy; y++)
      for(x=0; x < obraz->wymx; x++){
        obraz->pix[z][y][x] = ((obraz->pix[z][y][x] - min) * obraz->odcieni) / (maks - min);
      }
}


void do_szarosci(t_obraz *obraz){
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
  /**/ /* Asercje: */                                                                /**/
  /**/ assert(obraz != NULL);                                                        /**/
  /**/ assert(obraz->pix != NULL);                                                   /**/
  /**/ assert(obraz->wymx > 0);                                                      /**/
  /**/ assert(obraz->wymy > 0);                                                      /**/
  /**/ assert( obraz->kolory == 3);                                                  /**/
  /**/ assert(obraz->odcieni > 0);                                                   /**/
  /*************************************************************************************/
  int y,x;     /* iteratory */
  int ***pix;  /* wskaznik na tablice z obrazem */
  pix = obraz->pix;     /* zachowaj wskaznik na tablice z obrazem           */
  obraz->pix = NULL;    /* wyzeruj wskaznik w strukturze                    */
  obraz->typ[1] = '2';  /* zmien typ obrazu                                 */
  obraz->kolory = 1;
  alokuj_obraz(obraz);  /* alokuj pamiec pod obraz wyjsciowy                */
  /* Przechodzimy po tablicy obrazu wejsciowego i kopiujemy      */
  /* wartosci do talbicy obrazu wyjsciowego uwzgledniajac wagi.  */
  for(y=0; y < obraz->wymy; y++)
    for(x=0; x < obraz->wymx; x++){
      obraz->pix[0][y][x] =  round(pix[0][y][x] * GS_R +
                                   pix[1][y][x] * GS_G +
                                   pix[2][y][x] * GS_B );
    }
  free(pix); /* zwalniamy pamiec po obrazie wejsciowym */
}

void zmiana_poziomow(t_obraz *obraz, float min, float max){
  /*************************************************************************************/
  /* Funkcja wykonuje operacje zmiany poziomow na wskazanym obrazie.                   */
  /*                                                                                   */
  /* Argumenty funkcji:                                                                */
  /* obraz - struktura danych zawierajaca obraz                                        */
  /* min - dolny prog                                                                  */
  /* max - gorny prog                                                                  */
  /*                                                                                   */
  /* PRE:                                                                              */
  /* Funkcja obsluguje obrazy PGM i PPM.                                               */
  /* Wartosci progow musza zawierac sie w przedziale (0;1).                            */
  /* Prog dolny < prog gorny                                                           */
  /*                                                                                   */
  /* POST:                                                                             */
  /* Funkcja zmienia wartosc pikseli:                                                  */
  /* - na 0, jesli ich wartosc jest mniejsza niz prog dolny                            */
  /* - na wartosc maksymalna, jesli ich wartosc jest wieksza lub rowna progowi gornemu */
  /* - o wartosciach pomiedzy progami, rozciagajac je na nowym zakresie                */
  /*************************************************************************************/
  /**/ /* Asercje: */                                                                /**/
  /**/ assert(obraz != NULL);                                                        /**/
  /**/ assert(obraz->pix != NULL);                                                   /**/
  /**/ assert(obraz->wymx > 0);                                                      /**/
  /**/ assert(obraz->wymy > 0);                                                      /**/
  /**/ assert(obraz->kolory == 1 || obraz->kolory == 3);                             /**/
  /**/ assert(obraz->odcieni > 0);                                                   /**/
  /**/ assert(min >= 0 && min <= 1);                                                 /**/
  /**/ assert(max >= 0 && max <= 1);                                                 /**/
  /**/ assert(max > min);                                                            /**/
  /*************************************************************************************/
  int z,y,x;               /* iteratory */
  int prog_min,prog_max;   /* odcien progowy */
  int war_min, war_max;    /* minimalna i maksymalna wartosc szarosci znaleziona w obrazie */
  prog_min = round(obraz->odcieni*min);  /* zamiana progu ulamkowego na konkretny odcien progowy */
  prog_max = round(obraz->odcieni*max);
  war_min = prog_max;                    /* wartosci poczatkowe */
  war_max = prog_min;
  /* Przejscie po tablicy obrazu, modyfikacja wartosci pikseli */
  /* poza progami i analiza wartosci pomiedzy progami          */
  for(z=0; z < obraz->kolory; z++)
    for(y=0; y < obraz->wymy; y++)
      for(x=0; x < obraz->wymx; x++){
        if(obraz->pix[z][y][x] <= prog_min)        /* wartosc ponizej progu min -> 0 */
          obraz->pix[z][y][x] = 0;
        else if(obraz->pix[z][y][x] >= prog_max)   /* wartosc powyzej progu maks -> maksymalna wartosc odcieni */
          obraz->pix[z][y][x] = obraz->odcieni;
        else{
          if(obraz->pix[z][y][x] < war_min)        /* wartosc ponizej wartosci min -> zapisz */
            war_min = obraz->pix[z][y][x];
          if(obraz->pix[z][y][x] > war_max)      /* wartosc powyzej wartosci maks -> zapisz */
            war_max = obraz->pix[z][y][x];
        }
      }
  /* Ponowne przejscie po tablicy obrazu i rozciagniecie wartosci pikseli, */
  /* ktore znalazly sie pomiedzy progami */
  for(z=0; z < obraz->kolory; z++)
    for(y=0; y < obraz->wymy; y++)
      for(x=0; x < obraz->wymx; x++)
        if((obraz->pix[z][y][x] > prog_min)&&(obraz->pix[z][y][x] < prog_max))
          obraz->pix[z][y][x] = ((obraz->pix[z][y][x] - war_min) * obraz->odcieni) / (war_max - war_min);
}

void negatyw(t_obraz *obraz){
  /**********************************************************************/
  /* Funkcja wykonuje operacje negatywu na wskazanym obrazie.           */
  /* Filtr:                                                             */
  /* {0, 0,0}                                                           */
  /* {0,-1,0}                                                           */
  /* {0, 0,0}                                                           */
  /**********************************************************************/
  float f_negatyw[3][3] = {{0,0,0},{0,-1,0},{0,0,0}};
  filtrowanie(obraz, f_negatyw);
}

void rozmycie_pion(t_obraz *obraz){
  /**********************************************************************/
  /* Funkcja wykonuje operacje rozmycia pionowego na wskazanym obrazie. */
  /* Filtr:                                                             */
  /* {0,0.33,0}                                                         */
  /* {0,0.33,0}                                                         */
  /* {0,0.33,0}                                                         */
  /**********************************************************************/
  float f_rozmycie_pion[3][3] = {{0,0.33,0},{0,0.33,0},{0,0.33,0}};
  filtrowanie(obraz, f_rozmycie_pion);
}

void konturowanie(t_obraz *obraz){
  /**********************************************************************/
  /* Funkcja wykonuje operacje kontrowania na wskazanym obrazie.        */
  /* Obrazy kolorowe sa najpierw konwertowane do szarosci przy pomocy   */
  /* funkcji do_szarosci().                                             */
  /* Filtr:                                                             */
  /* { 0,0,0}                                                           */
  /* {-1,0,0}                                                           */
  /* { 0,1,0}                                                           */
  /**********************************************************************/
  float f_konturowanie[3][3] = {{0,0,0},{-1,0,0},{0,1,0}};
  if(obraz->kolory != 1)
    do_szarosci(obraz);
  filtrowanie(obraz, f_konturowanie);
}
