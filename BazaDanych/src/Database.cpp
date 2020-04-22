#include <string>
#include <fstream>
#include <iostream>
#include <list>

#include <cstdlib>

#include "Team.h"
#include "Database.h"
#include "Display.h"

using namespace std;

Database::Database(int HowManyColumns, string Name,  string  TablicaNaglowkow[])
{
    NazwaBazy = Name;
    LiczbaKolumn = HowManyColumns;
    LiczbaRekordow = 0;
    Naglowki =  TablicaNaglowkow;
    Strona = 1;
    Pozycja = 1;

}

Database::~Database()
{

}

void Database::DodajTeam(Team team)
{
    LiczbaRekordow++;
    Dane.push_back(team);
    LiczbaKolumn++;
}

void Database::UsunTeam()
{

}

void Database::EdytujTeam()
{

}

void Database::SortujBazePo(int kolumna, bool rosnaco)
{

}

void Database::ZaznaczKilka()
{

}

bool Database::CzyIstnieje(string druzyna)
{
    return true;
}

void Database::WybierzZawierajace()
{

}

void Database::DodajMecz()
{

}


void Database::Wyswietl()
{
    system("cls");

    int dlugosci_kolumn[] = {6,30,30,10,14,14,14,14};
    Display wyswietlacz(8, LiczbaRekordow, dlugosci_kolumn,Naglowki);

    wyswietlacz.WyswietlTytulBazy(NazwaBazy);
    wyswietlacz.WyswietlNaglowek(LiczbaRekordow);

    LiczbaStron = LiczbaRekordow/20;
    if(!(LiczbaRekordow%20))
        LiczbaStron--;
    LiczbaStron++;

    list<Team>::iterator it = Dane.begin();
    int i = 1;
    int n = 20*(Strona-1);
    i+=n;

    for(int p = 0; p<n; p++)
        it++;
    if(LiczbaRekordow)
    {
        for(int j = 0; j<20; j++)
        {
            if(LiczbaRekordow == i || i%20 == 0)
                wyswietlacz.WyswietlRekord(i, Strona, (*it),true, i == Pozycja);
            else
                wyswietlacz.WyswietlRekord(i, Strona, (*it),false, i == Pozycja);

            i++;
            it++;
            if(it == Dane.end())
                break;
        }
    }


    wyswietlacz.WyswietlNumerStrony(Strona);

}

void Database::WczytajZPlikuNoweTeamy(string NazwaPliku)
{
    fstream dane(NazwaPliku, ios::in);
    string linia;
    Team team;
    int i = 1;

    if(!dane.is_open())
        cout << "Plik nie zostal odnaleziony...";
    else
    {
       cout << "Plik otwarto poprawnie..." << endl << endl;

       while(!dane.eof())
       {
           cout << "Proba dodania " << i << " druzyny: ";
           getline(dane, linia);
           team.WgrajTeamZPliku(linia);
           if(!CzyIstnieje(team.Nazwa))
                cout << "BLAD! Druzyna o podanej nazwie (" << team.Nazwa << ") istnieje!" << endl;
           else if(team.Ocena == -1)
                cout << "BLAD! Nieprawidlowa ocena druzyny!" << endl;
           else if(team.Wygrane == -1)
                cout << "BLAD! Nieprawidlowa liczba wygranych spotkan druzyny!" << endl;
           else if(team.Remisy == -1)
                cout << "BLAD! Nieprawidlowa liczba remisowych spotkan druzyny!" << endl;
           else if(team.Przegrane == -1)
                cout << "BLAD! Nieprawidlowa liczba przegranych spotkan druzyny!" << endl;
           else if(team.OstatniMecz == "-1" || team.PrzedOstatniMecz == "-1" || team.PrzedPrzedOstatniMecz == "-1")
                cout << "BLAD! Nieprawidlowy stan jednego z zakonczonych meczow druzyny!" << endl;
           else
           {
               cout << "POWODZENIE!";
               team.WypiszTeam();
               DodajTeam(team);
           }
           i++;
           cout << endl;
       }

       dane.close();
    }

}

void Database::WczytaZPlikuMecze()
{

}

void Database::ZapiszWPlikuBaze()
{

}

void Database::OtworzBazeZPliku()
{

}

bool Database::NastepnaStrona()
{
    int strony = LiczbaRekordow/20;
    if(!(LiczbaRekordow%20))
        strony--;
    strony++;

    if(Strona<strony)
    {
        Strona++;
        Pozycja = (Strona-1)*20+1;
        return true;
    }
    return false;
}

bool Database::PoprzedniaStrona()
{
    if(Strona>1)
    {
        Strona--;
        Pozycja = Strona*20;
        return true;
    }
    return false;

}

bool Database::PozycjaDol()
{
    if(Pozycja<LiczbaRekordow)
    {
        if(!(Pozycja%20))
           Strona++;
        Pozycja++;
        return true;
    }
    return false;
}

bool Database::PozycjaGora()
{
    if(Pozycja>1)
    {
        if(!((Pozycja-1)%20))
            Strona--;
        Pozycja--;
        return true;
    }
    return false;

}

void Database::Zakoncz()
{
    int dlugosci_kolumn[] = {6,30,30,10,14,14,14,14};
    Display wys(8, LiczbaRekordow, dlugosci_kolumn,Naglowki);
    system("cls");
    wys.KolorNormalny();
}


