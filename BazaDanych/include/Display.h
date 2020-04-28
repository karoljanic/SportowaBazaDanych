#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>

#include "Team.h"
#include "Database.h"

#ifndef DISPLAY_H
#define DISPLAY_H


class Display
{

/// ************************************************* PUBLICZNE METODY KLASY 'DISPLAY' ************************************************* ///

    public:
        /// Konstruktor klasy
        /// Liczby ile_kolumn, ile_rekordow oznaczaja odpowiednio liczbe kolumn i liczbe rekordow w bazie danych
        /// Tablica liczb szerokosci_kolumn przekazuje informaje o szerokosciach poszczegolnych kolumn bazy danych
        /// Tablica napisow zawartosci_kolumn przekazuja naglowki bazy danych
        Display(int ile_kolumn, int ile_rekordow, int szerokosci_kolumn[], string zawartosci_kolumn[]);

        /// Destruktor klasy
        virtual ~Display();

        /// Funkcja wyswietlajaca wysrodkowany tytyl bazy danych przekazany przez argument
        /// Napis nazwa to przekazywany tytul bazy danych
        void WyswietlTytulBazy(string nazwa);

        /// Funkcja wyswietlajaca wysrodkowane naglowki bazy danych; dolne zakonczenie naglowkow zalezne jest od wartosci logicznej CzySaJakiesDane
        /// Jesli CzySaJakiesDane = true to dolne zakonczenie jest tak dobrane aby mozna bylo kontynuowac wypisywanie
        /// Jesli CzySaJakiesDane = false to dolne zakonczenie jest tak dobrane aby bylo ladnie zakonczone
        void WyswietlNaglowek(bool CzySaJakiesDane);

        /// Funkja wyswietla jeden z rekordow bazy danych
        /// Liczba numer informuje o numerze rekordu
        /// Liczba strona informuje o numerze strony na ktorym rekord sie znajduje
        /// Team team to druzyna ktora znajsuje sie w aktualnym rekordzie
        /// Wartosc logiczna CzyOstatni informuje czy rekord jest ostatni, czyli czy anlezy zmienic sposob dolnego obramowania bazy
        /// Wartosc logiczna CzyWyrozniony informuje czy rekord ma zostac podswietlony
        void WyswietlRekord(int numer, int strona, Team team, bool CzyOstatni, bool CzyWyrozniony);

        /// Funckja wyswietlajaca numer strony przekazany przez argument
        /// Liczba s to numer aktualnie wyswietlanej strony
        void WyswietlNumerStrony(int s);

        /// Zmiana koloru tla na czarny, a tekstu na bialy
        void KolorNormalny();


/// ************************************************* PRYWATNE ATRYBUTY KLASY 'DISPLAY' ************************************************* ///

    private:
        int IleKolumn;                  /// Informacja o liczbie kolumn bazy danych
        int Rekordy;                    /// Informacja o liczbie rekordow bazy danych
        int SzerokoscBazy;              /// Informacja o calkowitek dlugosci bazy danych
        int *DlugosciKolumn;            /// Tablica dlugosci kolumn bazy danych
        int KtoraInstrukcja = 0;        /// Informacja o numerze wyswietlanej instrukcji
        string *NaglowkiKolumn;         /// Tablica z nazwami naglowkow bazy danych


/// ************************************************* PRYWATNE METODY KLASY 'DISPLAY' ************************************************* ///

    private:
        /// Funkcja wyswietlajaca odpowiednia linie instrukcji w zaleznosci od numeru wiersza k
        /// Liczba k to numer wiersza wskazujacy jaka linie instrukcji nalezy wyswietlic
        void WyswietlInstrukcje(int k);

        /// Typ wyliczenioowy zawierajacy dostepne kolory
        enum colors{};

        /// Funkcja zmieniajaca kolor tla i tekstu na dowolnie wybrany z typu wyliczeniowego colors
        ///void ZmienKolor(colors tlo, colors tekst);

        /// Typ wyliczeniowy zawierajacy uzywane obramowania bazy danych
        enum lines{};

};

#endif /// DISPLAY_H
