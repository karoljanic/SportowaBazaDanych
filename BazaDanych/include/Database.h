#include <string>
#include <fstream>
#include <iostream>
#include <list>

#include"Team.h"

#ifndef DATABASE_H
#define DATABASE_H

using namespace std;

class Database
{
    public:
        string NazwaBazy;
        int LiczbaRekordow;
        int LiczbaKolumn;
        int LiczbaStron ;
        int Strona;
        int Pozycja;

        list <Team> Dane;
        string* Naglowki;

        /// Konstruktor
        Database(int HowManyColumns, string Nazwa, string Naglowki[]);
        ///Destruktor
        ~Database();

        /// Dodanie nowej druzyny(niepowtarzalne nazwy druzyn) wpisujac dane samodzielnie
        void DodajTeam(Team team);

        /// Usuniecie istniejacej druzyny
        void UsunTeam();

        /// Edytowanie danych istniejacego klubu
        void EdytujTeam();

        /// Sortowanie bazy po danej kulumnie
        void SortujBazePo(int kolumna, bool rosnaco  = true);

        /// Zaznaczenie kilku druzyn aby wykonac na nich inne operacje
        void ZaznaczKilka();

        ///Zwraca bool'a okreslajacego czy dryzyna o danej zawie istnieje
        bool CzyIstnieje(string druzyna);

        /// Wyswietlenie rekordow ktore zawieraja okreslona ceche
        void WybierzZawierajace();

        /// Uaktualnienie danych druzynu po zakonczonym meczu(liczba zwyciestw/remisow/przegranych, bilans ostatnich spotkan)
        void DodajMecz();

        /// Wyswietlenie bazy danych
        void Wyswietl();

        /// Wczytanie nowych dru¿yn z pliku
        void WczytajZPlikuNoweTeamy(string NazwaPliku);

        ///Uaktualnienie danych druzyn po zakonczonych meczach(liczba zwyciestw/remisow/przegranych, bilans ostatnich spotkan) wczytanych z pliku
        void WczytaZPlikuMecze();

        /// Zapisanie obecnej bazy do pliku
        void ZapiszWPlikuBaze();

        /// Otwieranie zapisanej wczeœniej bazy danych z pliku
        void OtworzBazeZPliku();

        /// Przejscie na kolejna strone bazy danych
        bool NastepnaStrona();

        /// Przejscie na poprzednia strone
        bool PoprzedniaStrona();

        ///Przesuwanie zaznaczenie w dol
        bool PozycjaDol();

        ///Przesuwanie zaznaczenia w gore
        bool PozycjaGora();

        /// wylaczanie bazy
        void Zakoncz();

};

#endif /// DATABASE_H
