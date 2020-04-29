#include <iostream>
#include <fstream>
#include <string>

#include "Team.h"
#include "Database.h"

using namespace std;

///------------------------------------- *** BEGIN *** KONSTRUKTOR ***BEGIN*** ----------------------------------------///
Team::Team(string TeamName, string Country, int SubjectiveRating, int TotalWins, int TotalDraws, int TotalLoses, string LastMatch, string BeforeLastMatch, string BeforeBeforeLastMatch)
{
    Nazwa = TeamName;
    Kraj = Country;
    Ocena = SubjectiveRating;
    Wygrane = TotalWins;
    Remisy = TotalDraws;
    Przegrane = TotalLoses;
    OstatniMecz = LastMatch;
    PrzedOstatniMecz = BeforeLastMatch;
    PrzedPrzedOstatniMecz = BeforeBeforeLastMatch;
    CzyWidoczny = false;
}
///--------------------------------------- *** END *** KONSTRUKTOR ***END*** ------------------------------------------///



///------------------------------------- *** BEGIN *** DESTRUKTOR ***BEGIN*** ----------------------------------------///
Team::~Team()
{

}
///--------------------------------------- *** END *** DESTRUKTOR ***END*** -----------------------------------------///



///---------------------------- *** BEGIN *** PUBLIC STWORZTEAMRECZNIE() ***BEGIN*** --------------------------------///
void Team::StworzTeamRecznie()
{
    string a = "xyz";

    cout << "Podaj nazwe druzyny: ";
    while(Nazwa=="")
        cin >> Nazwa;

    cout << "Podaj kraj z jakiego pochodzi druzyna: ";
    while(Kraj=="")
        cin >> Kraj;

    cout << "Podaj ocene klubu: ";
    while(!CzyPoprawnaOcena(a))
        cin >> a;
    Ocena = stoi(a);

    a = "xyz";
    cout << "Podaj liczbe wygranych spotkan: ";
    while(!CzyPoprawnaLiczba(a))
        cin >> a;
    Wygrane = stoi(a);

    a = "xyz";
    cout << "Podaj liczbe zremisowanych spotkan: ";
    while(!CzyPoprawnaLiczba(a))
        cin >> a;
    Remisy = stoi(a);

    a = "xyz";
    cout << "Podaj liczbe przegranych spotkan: ";
    while(!CzyPoprawnaLiczba(a))
        cin >> a;
    Przegrane = stoi(a);

    a = "xyz";
    cout << "Podaj wynik ostatniego meczu(W,D,L,-): ";
    while(!CzyPoprawnyStan(a))
        cin >> a;
    OstatniMecz = a;

    a = "xyz";
    cout << "Podaj wynik przedostatniego meczu(W,D,L,-): ";
    while(!CzyPoprawnyStan(a))
        cin >> a;
    PrzedOstatniMecz = a;

    a = "xyz";
    cout << "Podaj wynik przed przedostatniego meczu(W,D,L,-): ";
    while(!CzyPoprawnyStan(a))
        cin >> a;
    PrzedPrzedOstatniMecz = a;
}
///------------------------------- *** END *** PUBLIC STWORZTEAMRECZNIE() ***END*** ---------------------------------///



///----------------------------- *** BEGIN *** PUBLIC WGRAJTEAMZPLIKU() ***BEGIN*** ---------------------------------///
void Team::WgrajTeamZPliku(string LiniaDanych)
{
    int i = 0;
    string dana = "";
    while(char(LiniaDanych[i]) != ' ' && char(LiniaDanych[i]) != 0)
    {
        dana += LiniaDanych[i];
        i++;
    }
    Nazwa = dana;

    dana = "";
    i++;
    while(char(LiniaDanych[i]) != ' ' && char(LiniaDanych[i]) != 0)
    {
        dana += LiniaDanych[i];
        i++;
    }
    Kraj = dana;

    dana = "";
    i++;
    while(char(LiniaDanych[i]) != ' ' && char(LiniaDanych[i]) != 0)
    {
        dana += LiniaDanych[i];
        i++;
    }
    if(CzyPoprawnaOcena(dana))
        Ocena = stoi(dana);
    else
        Ocena = -1;

    dana = "";
    i++;
    while(char(LiniaDanych[i]) != ' ' && char(LiniaDanych[i]) != 0)
    {
        dana += LiniaDanych[i];
        i++;
    }
    if(CzyPoprawnaLiczba(dana))
        Wygrane = stoi(dana);
    else
        Wygrane = -1;

    dana = "";
    i++;
    while(char(LiniaDanych[i]) != ' ' && char(LiniaDanych[i]) != 0)
    {
        dana += LiniaDanych[i];
        i++;
    }
    if(CzyPoprawnaLiczba(dana))
        Remisy = stoi(dana);
    else
        Remisy = -1;

    dana = "";
    i++;
    while(char(LiniaDanych[i]) != ' ' && char(LiniaDanych[i]) != 0)
    {
        dana += LiniaDanych[i];
        i++;
    }
    if(CzyPoprawnaLiczba(dana))
        Przegrane = stoi(dana);
    else
        Przegrane = -1;

    dana = "";
    i++;
    while(char(LiniaDanych[i]) != ' ' && char(LiniaDanych[i]) != 0)
    {
        dana += LiniaDanych[i];
        i++;
    }
    if(CzyPoprawnyStan(dana))
        OstatniMecz = dana;
    else
        OstatniMecz = "-1";

    dana = "";
    i++;
    while(char(LiniaDanych[i]) != ' ' && char(LiniaDanych[i]) != 0)
    {
        dana += LiniaDanych[i];
        i++;
    }
    if(CzyPoprawnyStan(dana))
        PrzedOstatniMecz = dana;
    else
        PrzedOstatniMecz = "-1";

    dana = "";
    i++;
    while(char(LiniaDanych[i]) != ' ' && char(LiniaDanych[i]) != 0)
    {
        dana += LiniaDanych[i];
        i++;
    }
    if(CzyPoprawnyStan(dana))
        PrzedPrzedOstatniMecz = dana;
    else
        PrzedPrzedOstatniMecz = "-1";

}
///-------------------------------- *** END *** PUBLIC WGRAJTEAMZPLIKU() ***END*** ----------------------------------///



///-------------------------------- *** BEGIN *** PUBLIC WYPISZTEAM() ***BEGIN*** -----------------------------------///
void Team::WypiszTeam()
{
    cout << endl << Nazwa << endl << Kraj << endl << Ocena << endl << Wygrane << endl << Remisy << endl << Przegrane << endl;
    cout << OstatniMecz << "-" << PrzedOstatniMecz << "-" << PrzedPrzedOstatniMecz << endl;
}

///---------------------------------- *** END *** PUBLIC WYPISZTEAM() ***END*** -------------------------------------///



///----------------------------- *** BEGIN *** PRIVATE CZYPOPRAWNAOCENA() ***BEGIN*** --------------------------------///
bool Team::CzyPoprawnaOcena(string OdpowiedzUzytkownika)
{
    int n = OdpowiedzUzytkownika.length();

    if(n!=1)
        return false;

    if(!(OdpowiedzUzytkownika[0]<'6' && OdpowiedzUzytkownika[0]>'0'))
        return false;

    return true;
}
///------------------------------- *** END *** PRIVATE CZYPOPRAWNAOCENA() ***END*** ----------------------------------///



///----------------------------- *** BEGIN *** PRIVATE CZYPOPRAWNALICZBA() ***BEGIN*** --------------------------------///
bool Team::CzyPoprawnaLiczba(string OdpowiedzUzytkownika)
{
    int n = OdpowiedzUzytkownika.length();

    for(int i = 0; i<n; i++)
    {
        if(!(OdpowiedzUzytkownika[i]<='9' && OdpowiedzUzytkownika[i]>='0'))
            return false;
    }

    return true;
}
///------------------------------- *** END *** PRIVATE CZYPOPRAWNALICZBA() ***END*** ----------------------------------///



///----------------------------- *** BEGIN *** PRIVATE CZYPOPRAWNYSTAN() ***BEGIN*** --------------------------------///
bool Team::CzyPoprawnyStan(string OdpowiedzUzytkownika)
{
    if(OdpowiedzUzytkownika == "W" || OdpowiedzUzytkownika == "D" || OdpowiedzUzytkownika == "L" || OdpowiedzUzytkownika == "-")
        return true;

    return false;
}
///------------------------------- *** END *** PRIVATE CZYPOPRAWNYSTAN() ***END*** ----------------------------------///











