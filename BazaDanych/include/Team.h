#include <string>
#include <fstream>
#include <iostream>

#ifndef TEAM_H
#define TEAM_H

using namespace std;

class Team
{
     public:
        string Nazwa;                             /// Nazwa klubu
        string Kraj;                              /// Kraj z jakigo pochodzi klub
        int Ocena;                                /// Ocena jakosci klubu(1-5)
        int Wygrane;                              /// Suma wygranych spotkan
        int Remisy;                               /// Suma zremisowanych spotkan
        int Przegrane;                            /// Suma przegranych spotkan
        string OstatniMecz;                       /// Rezultat ostatniego spotakania(W,L,R,-)
        string PrzedOstatniMecz;                  /// Rezultat przed ostatniego spotkania(W,L,R,-)
        string PrzedPrzedOstatniMecz;             /// Rezultat przed przed ostatniego spotakania(W,L,R,-)
        bool CzyWidoczny;
        int porownywany;

        /// Konstruktor
        Team(string TeamName = "",
             string Country = "",
             int SubjectiveRating = 0,
             int TotalWins = 0,
             int TotalDraws = 0,
             int TotalLoses = 0,
             string LastMatch = "-",
             string BeforeLastMatch = "-",
             string BeforeBeforeLastMatch = "-");

        /// Destruktor
        virtual ~Team();

        /// Tworzenie druzyny recznie wpisujac dane
        void StworzTeamRecznie();

        /// Tworzenie nowej druzyny z danych pobranych z pliku(1 linia pobrana getlinem)
        void WgrajTeamZPliku(string LiniaDanych);

        /// Wypisanie danych na teamat druzyny
        void WypiszTeam();

        /// Sprawdzenie czy użytkownik wprowadzil poprawne dane w polu Ocena; zwraca -1 gdy wprowadzone dane są niepoprawne lub popranie wprowadzoną wartosc
        bool CzyPoprawnaOcena(string OdpowiedzUzytkownika);

        ///Sprawdzenie czy uzytkownik wprowadzil poprawna liczbe wygranych/zremisowanych/przegranych spotkan
        bool CzyPoprawnaLiczba(string OdpowiedzUzytkownika);

        ///Sprawdzenie czy uzytkownik wprowadzil poprawny status mecze(W,D,l,-)
        bool CzyPoprawnyStan(string OdpowiedzUzytkownika);








};

#endif /// TEAM_H
