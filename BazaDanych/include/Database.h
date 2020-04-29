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

/// ********************************************** PUBLICZNE METODY KLASY 'DATABASE' ********************************************** ///
    public:
        /// Konstruktor klasy
        /// Wartosc Kolumny przyjmuje liczbe kolumn bazy danych
        /// Napis Nazwa przyjmuje nazwe bazy danych
        /// Tablica napisow Naglowki przyjmuje tablice z nazwami naglowkow kolumn bazy danych
        /// Wartosc logiczna czyGlowna odnosi sie czy baza danych jest glowna baza danych
        Database(int Kolumny, string Nazwa, string Naglowki[], bool czyGlowna);

        /// Destruktor klasy
        virtual ~Database();

        /// Funkcja interfejs, pozwalajaca na komunikacje uzytkownika z baza danych i wykonywanie w na niej operacji
        void Uruchom();


/// ********************************************** PRYWATNE ATRYBUTY KLASY 'DATABASE' ********************************************** ///
    private:
        string NazwaBazy;           /// Nazwa bazy danych
        int LiczbaRekordow;         /// Liczba rekordow w bazie danych
        int LiczbaKolumn;           /// Liczba kolumn w bazie danych
        int LiczbaStron ;           /// Liczba stron na ktorych wyswietlana jest baza
        int Strona;                 /// Numer aktualnie wyswietlanej strony
        int Pozycja, Poz1, Poz2;    /// Numery aktualnych pozycji kurosora w bazie danych
        bool CzyGlowna;             /// Wartosc logiczna mowiaca o tym, czy aktualnie wyswietlana baza jest baza glowna
        int Instrukcja;              /// Numery mowiace o tresci instrukcji

        list <Team> Dane;           /// Lista przechowujaca rekordy bazy danych
        string* Naglowki;           /// Tablica dynamiczna przechowujaca nazwy naglowkow bazy danych


/// ********************* PRYWATNE METODY KLASY 'DATABASE' POZWALAJACE NA WYKONYWANIE OPERACJI NA BAZIE DANYCH ********************* ///
    private:
        /// Funkcja dodania nowej druzyny- uzytkownik samodzielnie wypelnia pola tworzonej druzyny
        /// Funkcja zawiera zabezpieczenie przed stworzeniem drugiej druzyny o takiej samej nazwie albo druzyny z nieprawidlowymi informacjami
        void DodajTeam();

        /// Funkcja usuniecie istniejacej druzyny;
        /// Wartosc logiczna kilka odnosi sie do tego czy usuwamy jedna druzyne(wowczas kilka = false) czy kilka(wowczas kilka = true)
        /// Usuniecie kilku druzyn mozliwe jest przy uzyciu funkji ZaznaczKilka()
        /// Funkcja zawiera zabezpieczenie przed usunieciem nieistniejacego rekordu
        void UsunTeam(bool kilka);

        /// Funkcja edytujaca informacje na temat istniejacej druzyny
        /// Wartosc nrkolumny wskazuje na numer kolumny ktora chcemy edytowac
        /// Wartosc logiczna dlawszystkich odnosi sie to tego czy edytujemy pojedynczy rekord(wowczas dlawszystkich = false) czy kilka(wowczas kilka = true)
        /// Edytowanie kilku druzyn mozliwe jest przy uzyciu funckji ZaznaczKilka()
        /// Funkcja zawiera zabezpieczenie przed zmiana danych na niewlasciwe lub zmiana nazwy na nazwe druzyny juz istniejacej
        void EdytujTeam(int nrkolumny, bool kilka);

        /// Funkcja zbierajaca i aktualizujaca dane druzyn na podstawie rozegranego meczu
        /// Funkcja sprawdza poprawnosc wprowadzanych danych oraz sprawdza istnienie druzyn w bazie danych
        void DodajMecz();


/// ********************* PRYWATNE METODY KLASY 'DATABASE' POZWALAJACE NA WYKONYWANIE OPERACJI NA BAZIE DANYCH I PLIKU  ********************* ///
    private:
        /// Funkcja wczytujaca nowe druzyny z pliku
        /// Napis NazwaPliku to sciezka do pliku lub nazwa tego pliku, gdy znajduje sie on w folderze programu
        /// Funkcja sprawdza istnienie podanego pliku, zgodnosc jego zawartosci z oczekiwaną oraz sprawdza czy nie proboju sie wczytac juz istniejaca druzyne
        void WczytajZPlikuNoweTeamy(string NazwaPliku);

        /// Funkcja wczytuje mecze z pliku i uaktualnia baze o te informacje
        /// Napis NazwaPliku to sciezka do pliku lub nazwa tego pliku, gdy znajduje sie on w folderze programu
        /// Funkcja sprawdza istnienie podanego pliku, zgodnosc jego zawartosci z oczekiwaną i istnieje aktualizowanych druzyn
        void WczytaZPlikuMecze(string NazwaPliku);

        /// Funkcja otwiera zapisana baze danych z pliku; zawartosc obecnej bazy jest usuwana
        /// Napis NazwaPliku to sciezka do pliku lub nazwa tego pliku, gdy znajduje sie on w folderze programu
        /// Funkcja sprawdza istnienie podanego pliku oraz zgodnosc jego zawartosci z oczekiwaną
        void OtworzBazeZPliku(string NazwaPliku);

        /// Funkcja zapisuje obecnie wyswietlana baze danych do pliku o podanej przez uzytkownika nazwie
        /// Napis NazwaPliku to nazwa pliku wyjsciwego;
        /// Wartosc logiczna wszystko okresla czy do pliku zapisane maja byc wszytskie rekordy czy tylko wybrane, gdy aktywna jest funckja WybierzZawieajace()
        void ZapiszWPlikuBaze(string NazwaPliku, bool wszystko);


/// ************************* PRYWATNE METODY KLASY 'DATABASE' POZWALAJACE NA PORUSZANIE SIĘ PO BAZIE DANYCH ************************* ///
    private:
        /// Funkcja przejscia na kolejna strone bazy dancych; zwraca informacje czy przejscie jest mozliwe
        /// Funkcja sprawdza czy takie przejscie jest mozliwe
        bool NastepnaStrona();

        /// Funkcja powrotu na poprzednia strone bazy dancych; zwraca informacje czy powrot jest mozliwy
        /// Funkcja sprawdza czy taki powrot jest mozliwy
        bool PoprzedniaStrona();

        /// Funkcja przesuwajaca pozycje kursora w dol; zwraca informacje czy przesuniecie kursora jest mozliwe
        /// Funkcja sprawdza czy takie przesuniecie jest mozliwe
        bool PozycjaDol();

        /// Funkcja przesuwajaca pozycje kursora w gore; zwraca informacje czy przesuniecie kursora jest mozliwe
        /// Funkcja sprawdza czy takie przesuniecie jest mozliwe
        bool PozycjaGora();


/// ************************* PRYWATNE METODY KLASY 'DATABASE' DOTYCZACE WYSWIETLANIA I OPRACOWYWANIA DANYCH ************************* ///
    private:
        /// Funkcja sortujaca baze danych
        /// Wartosc kolumna informuje wedlug ktorej kolumny bazy chcemu sortowac rekordy
        /// Wartosc logiczna rosnaco oznacza typ sortowania: rosnaco(wowczas rosnaco = true) lub malejaco(wowczas rosnaco = false)
        /// Funkcja sprawdza czy baza zawiera rekordy do posortowania
        void SortujBazePo(int kolumna, bool rosnaco = true);

        /// Funkcja pozwalajaca na zaznaczanie kilku rekordow jednoczesnie; na tak stworzonej bazie mozemy wykonywac niektore operacje
        void ZaznaczKilka();

        /// Funkcja tworzaca podbaze z rekordami ktore zawieraja okreslona ceche; na tak stworzonej bazie mozemy wykonywac niektore operacje
        void WybierzZawierajace();

        /// Funkcja wyswietlajaca baze danych, gdy kursor zaznaczenie jest pojedynczy, czyli gdy nieaktywna jest funkcja ZaznaczKilka()
        void Wyswietl();

        /// Funkcja wyswietlajaca baze danych, gdy kursor zaznaczenia nie jest pojedynczy, czyli gdy aktywna jest funkcja ZaznaczKilka()
        void Wyswietl2();

        /// Funkcja zwaraca wartosc obliczonej funkcji matematycznej dla okreslonej kolumny
        /// Funkcje matematyczne: max, min, suma, srednia, mediana
        /// Wartosc numerfunkcji oznacza ktora funkcje wybral uzytkownik
        /// Wartosc numerkolumny oznacza numer kolumny w ktorej zostanie wykonana funkcja
        /// Funkcja sprawdza czy baza danych zawiera jakiekolwiek rekordy oraz czy wartosci kolumny to liczby
        float Funkcje(int numerfunkcji, int numerkolumny);

        /// Funckja zwraca wartosc -1 jesli druzyna o podanej nazwie nie istnieje albo jej pozycje w przeciwnym wypadku
        /// Napis druzyna oznacza nazwe druzyny ktorej szukamy
        int CzyIstnieje(string druzyna);


/// **************************************** INNE-POMOCNICZE PRYWATNE METODY KLASY 'DATABASE'  **************************************** ///
    private:
        /// Pomocnicza funkcja funkcji WybierzZawierajace()
        void WarunkiRekordow(int kolumna);

        /// Pomocnicza funkcja funkcji DodajMecz() oraz WczytaZPlikuMecze() aktualizujaca statystyki druzyn w bazie na podstawie wyniku spokania
        /// Napisy gospodarz i gosc to nazwy druzyn, ktore rozegraly ze soba spotkanie
        /// Napisy GoleGospodarza i GoleGosci to liczba zdobytych bramek przez kazda z druzyn zapisana w stringu
        ///Funkcja sprawdza czy druzyny istnieja oraz czy liczba strzelonych goli jest nieujemna
        void Aktualizuj(string gospodarz, string gosc, string GoleGospodarza, string GoleGosci);

        /// Pomocnicza funkcja funkcji OtworzBazeZPliu() usuwajaca wszystkie rekordy z bazy danych
        void Czysc();

        /// Pomocnicza fukcja zwracajaca -1 jesli liczba przekazazna nie jest liczba naturalna(z zerem wlacznie) lub ta liczbe w przeciwnym wypadku
        int CzyLiczbaNaturalna(string dana);


/// *********************************** PRZECIAZENIA OPERATOROW DO POROWNYWANIA DRUZYN KLASY TEAM *********************************** ///

        friend bool operator < (const Team &t1, const Team &t2);

        friend bool operator > (const Team &t1, const Team &t2);

        friend bool operator == (const Team &t1, const Team &t2);

        friend bool operator != (const Team &t1, const Team &t2);


        friend ostream& operator << (ostream& out, const Team &t);

        friend ostream& operator >> (ostream& in, const Team &t);

};

#endif /// DATABASE_H
