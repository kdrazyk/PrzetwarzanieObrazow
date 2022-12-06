#include "o2_main.h"

int main(){
  char wybor[2]="  ";    /* wybor w menu*/
  char wybor2[2]="  ";   /* wybor w podmenu  */
  float prog;            /* prog dla operacji progowania */
  FILE *plik;
  int odczytano = 0;
  char nazwa[100];

  /* Filtry */
  float f_negatyw[3][3] = {{0,0,0},{0,-1,0},{0,0,0}};
  float f_konturowanie[3][3] = {{0,0,0},{-1,0,0},{0,1,0}};
  float f_rozmycie_pion[3][3] = {{0,0.33,0},{0,0.33,0},{0,0.33,0}};
  float f_uzytkownika[3][3];

  t_obraz obraz1;
  obraz1.pix = NULL;

  while(wybor[0] != '0'){
    printf("Menu:\n");
    printf("\t1 - Wczytaj obraz\n");
    printf("\t2 - Zapisz obraz\n");
    printf("\t3 - Wyswietl obraz\n");
    printf("\t4 - Negatyw\n");
    printf("\t5 - Progowanie\n");
    printf("\t6 - Konturowanie\n");
    printf("\t7 - Rozmycie pionowe\n");
    printf("\t8 - Maski/filtry\n");
    printf("\t9 - Zmiana poziomow\n");
    printf("\t0 - Zakoncz dzialanie\n");

    printf("Twoj wybor: ");
    scanf("%1s",wybor);

    switch(wybor[0]){

      /* Wczytanie zawartosci wskazanego pliku do pamieci */
    case '1' :
      printf("Podaj nazwe pliku:\n");
      scanf("%s",nazwa);
      plik=fopen(nazwa,"r");

      if (plik != NULL) {
        odczytano = czytaj(plik, &obraz1);
        fclose(plik);
      }
      break;

      /* Zapisanie informacji z pamieci do pliku o wskazanej nazwie */
    case '2' :
      printf("Podaj nazwe pliku:\n");
      scanf("%s",nazwa);
      plik=fopen(nazwa,"w");
      zapisz(plik, &obraz1);
      fclose(plik);
      break;

      /* Wyswietlenie poprawnie wczytanego obrazu zewnetrznym programem */
    case '3' :
      if (odczytano != 0){
        plik = fopen(PLIK_TMP,"w");
        zapisz(plik, &obraz1); /* Utworzenie pliku tymczasowego */
        wyswietl(PLIK_TMP);
        fclose(plik);
      }
      break;

      /* Negatyw */
    case '4' :
      filtrowanie(&obraz1, f_negatyw);
      break;

      /* Progowanie */
    case '5' :
      printf("Prog (np. 0.2): ");
      scanf("%f",&prog); /* Pobranie wartosci progu od uzytkownika */
      progowanie(&obraz1, prog);
      break;

      /* Konturowanie */
    case '6' :
      filtrowanie(&obraz1, f_konturowanie);
      break;

      /* Rozmycie pionowe  */
    case '7' :
      filtrowanie(&obraz1, f_rozmycie_pion);
      break;

      /* Filtrowanie przy uzyciu filtru podanego przez uzytkownika  */
    case '8' :
      wybor2[0] = ' ';

      while((wybor2[0] != '1')&&(wybor2[0] != '0')){
        /* Pobranie filtru i zapisanie w tabeli */
        printf("Wprowadz filtr wedlug ponizszego wzoru\n");
        printf("(0,0),(0,1),(0,2)\n(1,0),(1,1),(2,1)\n(2,0),(2,1),(2,2)\n");
        for(int i=0;i<3;i++)
          for(int j=0;j<3;j++){
            printf("(%i,%i): ",i,j);
            scanf("%f",&(f_uzytkownika[i][j]));
          }

        /* Podmenu */
        printf("\nFiltr wprowadzony\n");
        printf("\t1 - Zastosuj filtr\n");
        printf("\t2 - Wpisz ponownie\n");
        printf("\t0 - Powrot do menu\n");
        printf("Twoj wybor: ");
        scanf("%1s",wybor2);
      }

      /* Filtrowanie */
      if(wybor2[0]=='1')
        filtrowanie(&obraz1, f_uzytkownika);
      break;

    case '9' :
      zmiana_poziomow(&obraz1, 0.4, 0.8);

      break;

    case '0' :
      printf("Koniec!\n");
      if(obraz1.pix != NULL)
        free(obraz1.pix);
      break;
    default : printf("To nie jest poprawna opcja\n");
    }
  }

  return 0;
}
