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

    public:
        const int Dlugosc = 150;
        int IleKolumn;
        int Rekordy;
        int SzerokoscBazy;
        int *DlugosciKolumn;
        int KtoraInstrukcja = 0;
        string *NaglowkiKolumn;


    public:
        ///konstruktor
        Display(int ile_kolumn, int ile_rekordow, int szerokosci_kolumn[], string zawartosci_kolumn[]);

        ///destruktor
        virtual ~Display();

        ///dostepne kolory
        ///enum colors{};

        /// zmiana koloru tesktu i tla w konsoli, dostepne kolory
        ///void ZmienKolor(colors tlo, colors tekst);

        /// uzywane linie tabeli
        enum lines{};

        /// wyswietlanie tutulu bazy danych
        void WyswietlTytulBazy(string nazwa);

        /// wyswietlanie naglowka bazy danych
        void WyswietlNaglowek(bool CzySaJakiesDane);

        /// wyswietlanie rekordu srodkowego(gdy rekordow jest wiecej niz jeden)
        void WyswietlRekord(int numer, int strona, Team team, bool CzyOstatni, bool CzyWyrozniony);

        /// wyswietlanie instrukcji obslugi
        void WyswietlInstrukcje(int k);

        /// wyswietlanie numeru strony
        void WyswietlNumerStrony(int s);

        /// zmiana koloru na podtawowy
        void KolorNormalny();

};

#endif /// DISPLAY_H
