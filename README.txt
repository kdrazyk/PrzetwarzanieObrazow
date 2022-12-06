SPRAWOZDANIE

Kacper Drazyk 263462
Laboratorium 5 – Przetwarzanie obrazów 2
17.01.2021r.

Testy:
Zapisanie poszczegolnych testow jest problematyczne z uwagi na obszernosc programu i bardzo duza ilosc dostepnych kombinacji danych wejsciowych. Piszac program skupilem sie na weryfikacji poprawnosci dzialania poszczegolnych funkcji i modulow przed rozpoczeciem pracy nad kolejnymi. Po ukonczeniu programu zweryfikowalem dodatkowo poprawnosc dzialania wszystkich dostepnych funkcji w sposob analogiczny do normalnego uzytkowania programu.

Informacje dodatkowe:
Interfejs shell zostal zaimplementowany w dosyc prymitywny sposob, poniewaz wymaga korzystania z tego samego formatu opcji co wywolanie programu. Pomimo tego na podstawie testow moge stwierdzic, ze spelnia swoje zadanie i znacznie ulatwia korzystanie z programu.

Modyfikacja implementacji przetwarzania opcji poza zachowaniem kolejnosci wywolania pozwala na wielokrotne wywolanie opcji, ktore nie posiadaja dodatkowych argumentow (np. -i obraz.ppm -d -k -d -n -d -p 0.5 -n -o obraz2.pgm). Jest to przydatny efekt uboczny, ale nie zostal w pelni rozwiniety.

Wszystkie funkcje edycji sa w stanie przetwarzac pliki PPM i domyslnie nie sa one przetwarzane na PGM (poza konturowaniem i progowaniem, gdzie wynika to z zasady dzialania). Aby program zachowywal sie w pelni zgodnie z zalozeniami nalezy najpierw dokonac konwersji (-s).

Moduly:
o2_main.c   & o2_main.h      - interfejs uzytkownika
o2_io.c     & o2_io.h        - funkcje obslugi plikow
o2_edycja.c & o2_edycja.h    - funkcje edycji obrazow
o2_pamiec.c & o2_pamiec.h    - dynamiczna alokacja pamieci
opcje.c     & opcje.h        - przetwarzanie argumentow wywolania (zmodyfikowane rozwiazanie przykladowe)
o2_dane.h                    - struktura danych przechowujaca informacje o obrazie



Wnioski:
Na podstawie przeprowadzonych testow stwierdzam, ze program dziala zgodnie z zalozeniami, chociaz nie jestem w stanie wykluczyc istnienia tzw. edge-case'ow.
