#include "o2_io.h"

int czytaj(FILE *plik_we, t_obraz *obraz) {
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
  /* Na podstawie pobranych wymiarow alokowana jest  tablica         */
  /* i zostaja w niej zapisane informacje o pikselach.               */
  /* Funkcja zwraca wczytana ilosc pikseli lub wartosc 0 i komunikat */
  /* o bledzie, jesli taki wystapil.                                 */
  /*******************************************************************/
  /**/ /* Asercje: */                                              /**/
  /**/ assert(obraz != NULL);                                      /**/
  /**/ assert(plik_we != NULL);                                    /**/
  /*******************************************************************/
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy          */
  int koniec = 0;          /* czy napotkano koniec danych w pliku                */
  int z,y,x;               /* iteratory                                          */
  /* Usuniecie poprzedniego obrazu z pamieci */
  if (obraz->pix != NULL){
    free(obraz->pix);
    obraz->pix = NULL;
    }
  /* Odczytanie "numeru magicznego" */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec = 1;                            /* Nie udalo sie? Koniec danych!             */
  else {
    obraz->typ[0] = buf[0];                /* numer odczytany -> zapisz w strukturze    */
    obraz->typ[1] = buf[1];
  }
  /* Kontrola poprawnosci numeru */
  if ((obraz->typ[0]!='P') || (obraz->typ[1]!='2' && obraz->typ[1]!='3') || koniec){
    fprintf(stderr,"Blad: To nie jest plik PGM/PPM\n");
    return(0);
  }
  /* Pominiecie komentarzy */
  do {
    if (( znak = fgetc(plik_we) ) == '#') {   /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
        koniec = 1;                           /* Zapamietaj ewentualny koniec danych    */
    }
    else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii  */
    }                                         /* nie jest '#' zwroc go                  */
  } while (znak=='#' && !koniec);             /* Powtarzaj dopoki sa linie komentarza   */
                                              /* i nie nastapil koniec danych           */
  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d",&obraz->wymx,&obraz->wymy,&obraz->odcieni)!=3) {
    printf("%d %d %d %s\n", obraz->wymx,obraz->wymy,obraz->odcieni, obraz->typ);
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  /* Alokacja tabelicy obrazu */
  if (obraz->typ[1] == '2')
    obraz->kolory = 1; /* obraz PGM */
  else
    obraz->kolory = 3; /* obraz PPM */
  alokuj_obraz(obraz); /* alokuj w pamieci tablice 2D/3D na wczytywany obraz*/
  /* Wczytanie pikseli i zapisanie w tablicy */
  for (y=0; y < obraz->wymy; y++)
    for (x=0; x < obraz->wymx; x++)
      for (z=0; z < obraz->kolory; z++)
        if (fscanf(plik_we,"%d",&(obraz->pix[z][y][x]))!=1) {
          fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
          return(0);
        }
  return obraz->wymx * obraz->wymy;   /* Czytanie zakonczone sukcesem    */
}                                     /* Zwroc liczbe wczytanych pikseli */

void wyswietl(t_obraz *obraz) {
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
  /**/ /* Asercje: */                                                       /**/
  /**/ assert(obraz->pix != NULL);                                          /**/
  /****************************************************************************/
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */
  FILE *plik;                    /* uchwyt pliku tymczasowego                 */
  plik = fopen(PLIK_TMP,"w");    /* utworzenie pliku tymczasowego             */
  zapisz(plik, obraz);           /* zapisanie obrazu do pliku tymczasowego    */
  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci             */
  strcat(polecenie,PLIK_TMP);    /* display "nazwa_pliku" &                   */
  strcat(polecenie," &");
  /*printf("%s\n",polecenie);*/      /* wydruk kontrolny polecenia                */
  system(polecenie);             /* wykonanie polecenia                       */
  fclose(plik);
}

void zapisz(FILE *plik_wy,t_obraz *obraz) {
  /****************************************************************************************/
  /* Funkcja zapisuje obraz zawarty we wskazanej strukturze danych do pliku .pgm lub      */
  /* .ppm                                                                                 */
  /*                                                                                      */
  /* Argumenty funkcji:                                                                   */
  /* FILE* - uchwyt do pliku wyjsciowego                                                  */
  /* obraz - struktura danych zawierajaca obraz                                           */
  /*                                                                                      */
  /* PRE:                                                                                 */
  /* Funkcja obsluguje obrazy PGM i PPM.                                                  */
  /*                                                                                      */
  /* POST:                                                                                */
  /* Funkcja zapisuje w pliku informacje o typie pliku (magiczna liczba),                 */
  /* wymiarach i ilosci odcieni oraz poszczegolnych pikselach zgodnie z formatem PGM/PPM. */
  /****************************************************************************************/
  /**/ /* Asercje: */                                                                   /**/
  /**/ assert(plik_wy != NULL);                                                         /**/
  /**/ assert(obraz != NULL);                                                           /**/
  /****************************************************************************************/
  int z,y,x; /* iteratory */
  fprintf(plik_wy,"%c%c\n",obraz->typ[0],obraz->typ[1]);                   /* magiczna liczba */
  fprintf(plik_wy,"%i %i %i\n", obraz->wymx, obraz->wymy, obraz->odcieni); /* wymiary i ilosc odcieni */
  for (y=0; y < obraz->wymy ;y++)                         /* y-rzad    */
    for (x=0; x < obraz->wymx ;x++)                       /* x-kolumna */
      for (z=0; z < obraz->kolory; z++){                  /* z-kolor   */
        fprintf(plik_wy, "%i", obraz->pix[z][y][x]);      /* Wypisanie wartosci poszczegolnych pikseli */
        /* ograniczenie ilosci znakow w linii */
        fprintf(plik_wy, (z == obraz->kolory-1)&&((y*obraz->wymx+x)%5==0) ? "\n" : " ");
      }
}
