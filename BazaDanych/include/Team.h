#include <string>
#include <fstream>
#include <iostream>

#ifndef TEAM_H
#define TEAM_H

using namespace std;

class Team
{

/// ************************************************* PUBLICZNE METODY KLASY 'TEAM' ************************************************* ///

     public:
        /// Konstruktor klasy
        /// Napis TeamName to nazwa druzyny
        /// Napis Coutry to nazwa kraju z jakiego pochodzi ta druzyna
        /// Liczba SubjectiveRating to subiektywna ocena druzyna w skali 1-5
        /// Liczby TotalWins, TotalDraws, TotalLoses to kolejno liczby wygranych, zremisowanych i przegranych meczow
        /// Napisy LastMatch, BeforeLastMatch, BeforeBeforeLastMatch oznaczaja stan ostatniego meczu
        /// Stany ostatnich meczow: "W" - wygrana, "D" - remis, "L" - porazka, "-" - brak danych
        Team(string TeamName = "",
             string Country = "",
             int SubjectiveRating = 0,
             int TotalWins = 0,
             int TotalDraws = 0,
             int TotalLoses = 0,
             string LastMatch = "-",
             string BeforeLastMatch = "-",
             string BeforeBeforeLastMatch = "-");

        /// Destruktor klasy
        virtual ~Team();

        /// Funkcja tworzaca nowa druzyne; uzytkownik wpisuje dane na jej temat samodzielnie
        /// Funkcja sprawdza czy podawane informacje na temat druzyny sa w dobrym formacie
        void StworzTeamRecznie();

        /// Tworzenie nowej druzyny z danych pobranych z pliku(1 linia pobrana getlinem)
        /// Funkcja tworzaca nowa druzyne na podstawie lini pobranej z pliku getlinem
        /// Napis LiniaDanych to jedna linia pliku pobrana funkcja getline
        /// Funkcja sprawdza czy podawane informacje na temat druzyny sa w oczekiwanym formacie
        void WgrajTeamZPliku(string LiniaDanych);

        /// Funkcja wypisujaca dane na temat druzyny
        void WypiszTeam();


/// ************************************************* PRYWATNE ATRYBUTY KLASY 'TEAM' ************************************************* ///

    public:///
        string Nazwa;                             /// Nazwa klubu
        string Kraj;                              /// Kraj z jakigo pochodzi klub
        int Ocena;                                /// Ocena jakosci klubu(1-5)
        int Wygrane;                              /// Suma wygranych spotkan
        int Remisy;                               /// Suma zremisowanych spotkan
        int Przegrane;                            /// Suma przegranych spotkan
        string OstatniMecz;                       /// Rezultat ostatniego spotakania("W","L","R","-")
        string PrzedOstatniMecz;                  /// Rezultat przed ostatniego spotkania("W","L","R","-")
        string PrzedPrzedOstatniMecz;             /// Rezultat przed przed ostatniego spotakania("W","L","R","-")
        bool CzyWidoczny;


/// ************************************************* PRYWATNE METODY KLASY 'TEAM' ************************************************* ///
    public:///
        /// Funkcja sprawdza czy podana ocena jest poprawna, czyli czy jest liczba calkowita zakresu 1-5
        /// Funkcja zwraca false jesli podana ocena jest niepoprawna lub true w przeciwnym wypadku
        bool CzyPoprawnaOcena(string OdpowiedzUzytkownika);

        /// Funkcja sprawdza czy podana liczba jest poprawna liczba wygranych/zremisowanych/przegranych spotakn, czyli czy jest liczba naturalna
        /// Funkcja zwraca false jesli podana liczba jest niepoprawna lub true w przeciwnym wypadku
        bool CzyPoprawnaLiczba(string OdpowiedzUzytkownika);

        /// Funkcja sprawdza czy podany stan meczy jest prawidlowy, czyli czy zawiera sie w zbiorze {"W", "D", "L", "-"}
        /// Funkcja zwraca false jesli podany stan jest niepoprawny lub true w przeciwnym wypadku
        bool CzyPoprawnyStan(string OdpowiedzUzytkownika);

};

#endif /// TEAM_H
