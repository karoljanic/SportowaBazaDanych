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
    private:
        string NazwaBazy;
        int LiczbaRekordow;
        int LiczbaKolumn;
        int LiczbaStron ;
        int Strona;
        int Pozycja, Poz1, Poz2;
        bool CzyGlowna;

        list <Team> Dane;
        string* Naglowki;

    public:
        /// Konstruktor
        Database(int HowManyColumns, string Nazwa, string Naglowki[], bool czyGlowna);
        ///Destruktor
        ~Database();

        /// Dodanie nowej druzyny(niepowtarzalne nazwy druzyn) wpisujac dane samodzielnie
        void DodajTeam();

        /// Usuniecie istniejacej druzyny
        void UsunTeam(bool kilka);

        /// Edytowanie danych istniejacego klubu
        void EdytujTeam(int nrkolumny, bool dlawszystkich);

        /// Sortowanie bazy po danej kulumnie
        void SortujBazePo(int kolumna, bool rosnaco  = true);

        /// Zaznaczenie kilku druzyn aby wykonac na nich inne operacje
        void ZaznaczKilka();

        ///Zwraca bool'a okreslajacego czy dryzyna o danej zawie istnieje
        int CzyIstnieje(string druzyna);

        /// Wyswietlenie rekordow ktore zawieraja okreslona ceche
        void WybierzZawierajace();

        void WarunkiRekordow(int kolumna);

        /// Uaktualnienie danych druzynu po zakonczonym meczu(liczba zwyciestw/remisow/przegranych, bilans ostatnich spotkan)
        void DodajMecz();

        /// Wyswietlenie bazy danych
        void Wyswietl();

        void Wyswietl2();

        /// Wczytanie nowych dru¿yn z pliku
        void WczytajZPlikuNoweTeamy(string NazwaPliku);

        ///Uaktualnienie danych druzyn po zakonczonych meczach(liczba zwyciestw/remisow/przegranych, bilans ostatnich spotkan) wczytanych z pliku
        void WczytaZPlikuMecze(string NazwaPliku);

        /// Zapisanie obecnej bazy do pliku
        void ZapiszWPlikuBaze(string NazwaPliku, bool wszystko);

        /// otwiera zapisana baze danych z pliku(kasuje to co jest obecnie w bazie)
        void OtworzBazeZPliku(string NazwaPliku);

        /// Usuwanie wszystkich danych z bazy
        void Czysc();

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

        /// aktualizuje dane druzyn w oparciu o wynik meczu
        void Aktualizuj(string gospodarz, string gosc, string GoleGospodarza, string GoleGosci);

        int Uruchom();

        float Funkcje(int numerfunkcji, int numerkolumny);

        friend bool operator < (const Team &t1, const Team &t2);

        friend bool operator > (const Team &t1, const Team &t2);

        friend bool operator == (const Team &t1, const Team &t2);

        friend bool operator != (const Team &t1, const Team &t2);


        friend ostream& operator << (ostream& out, const Team &t);

        friend ostream& operator >> (ostream& in, const Team &t);




};

#endif /// DATABASE_H
