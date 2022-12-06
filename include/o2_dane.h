#ifndef O2_DANE_H
#define O2_DANE_H

typedef struct{
  char typ[2];  /* typ obrazu (P2 czyli PGM lub P3 czyli PPM) */
  int wymx;     /* wymiar x obrazu */
  int wymy;     /* wymiar y obrazu */
  int kolory;   /* ilosc kolorow z jakich sklada sie obraz (1 jesli PGM, 3 jesli PPM) */
  int odcieni;  /* ilosc odcieni kolorow w obrazie */
  int ***pix;   /* wskaznik na tablice przechowujaca obraz */
}t_obraz;

#endif
