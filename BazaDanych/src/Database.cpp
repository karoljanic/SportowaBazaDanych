#include <string>
#include <fstream>
#include <iostream>
#include <conio.h>
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

void Database::DodajTeam()
{
    Team team;
    team.StworzTeamRecznie();
    if(!CzyIstnieje(team.Nazwa))
    {
        LiczbaRekordow++;
        Dane.push_back(team);
        cout << endl << "Druzyne wprowadzono poprawnie! Nacisnij ENTER aby kontynuowac!";
    }
    else
    {
        cout << "Taka druzyna juz istnieje! Nacisnij ENTER aby kontynuowac!";
    }
    char znak = 0;
    while(znak != 13)
       znak = getch();

}

void Database::UsunTeam()
{
    cout << "Czy na pewno chcesz usunac druzyne? Jesli tak, nacisnij ENTER, w przeciwnym wypadku nacisnij inny dowolny klawisz!";
    char znak = 0;
    znak = getch();
    if(znak != 13)
        return;
    if(LiczbaRekordow==0)
        return;

    string name;
    list<Team>::iterator it = Dane.begin();
    for(int i = 1; i<Pozycja; i++)
        it++;
    Dane.erase(it);
    LiczbaRekordow--;
    Pozycja--;
    if(Pozycja == 0)
        Pozycja = 1;

}

void Database::EdytujTeam(int nrkolumny)
{
    string nowynapis;

    list<Team>::iterator it = Dane.begin();
    for(int i = 1; i<Pozycja; i++)
        it++;

    Team team;

    switch(nrkolumny)
    {
        case 1:
        {
            cout << "Podaj nowa nazwe druzyny.Pamietaj aby nie pokrywala sie z juz istniejacymi druzynami: ";
            cin >> nowynapis;
            while(CzyIstnieje(nowynapis))
                cin >> nowynapis;
            (*it).Nazwa = nowynapis;
            break;
        }
        case 2:
        {
            cout << "Podaj nowa nazwe kraju: ";
            cin >> nowynapis;
            (*it).Kraj = nowynapis;
            break;
        }
        case 3:
        {
            cout << "Podaj nowa ocene druzyny: ";
            cin >> nowynapis;
            while(!team.CzyPoprawnaOcena(nowynapis))
                cin >> nowynapis;
            (*it).Ocena = stoi(nowynapis);
            break;
        }
        case 4:
        {
            cout << "Podaj liczbe wygranych spotkan: ";
            cin >> nowynapis;
            while(!team.CzyPoprawnaLiczba(nowynapis))
                cin >> nowynapis;
            (*it).Wygrane = stoi(nowynapis);
            break;
        }
        case 5:
        {
            cout << "Podaj liczbe zremisowanych spotkan: ";
            cin >> nowynapis;
            while(!team.CzyPoprawnaLiczba(nowynapis))
                cin >> nowynapis;
            (*it).Remisy = stoi(nowynapis);
            break;
        }
        case 6:
        {
            cout << "Podaj liczbe przegranych spotkan: ";
            cin >> nowynapis;
            while(!team.CzyPoprawnaLiczba(nowynapis))
                cin >> nowynapis;
            (*it).Przegrane = stoi(nowynapis);
            break;
        }
        case 7:
        {
            cout << "Rezultat ktorego spotkania chcesz poprawic?(ostatni-1, przedostatni-2, przed przedostatni-3): ";
            int cyfra = 0;
            while(!(cyfra<4 && cyfra>0))
                cin >> cyfra;
            cout << "Jakim rezultatem zakonczylo sie te spotkanie?(W,D,L,-)";
            nowynapis = "ZnalazlesV2";
            cin>> nowynapis;
            while(!team.CzyPoprawnyStan(nowynapis))
                cin >>  nowynapis;

            switch(cyfra)
            {
                case 1:
                {
                    (*it).OstatniMecz = nowynapis;
                    break;
                }
                case 2:
                {
                    (*it).PrzedOstatniMecz = nowynapis;
                    break;
                }
                case 3:
                {
                    (*it).PrzedPrzedOstatniMecz = nowynapis;
                    break;
                }

            }
            break;
        }
    }
}

void Database::SortujBazePo(int kolumna, bool rosnaco)
{

}

void Database::ZaznaczKilka()
{

}

bool Database::CzyIstnieje(string druzyna)
{
    list<Team>::iterator it = Dane.begin();
    for(it; it != Dane.end(); it++)
    {
        if((*it).Nazwa == druzyna)
            return true;
    }
    return false;
}

void Database::WybierzZawierajace()
{

}

void Database::DodajMecz()
{
    string gospodarz = "", gosc = "";
    string GoleGosci, GoleGospodarza;

    Team t;

    cout << "Podaj druzyne gospodarza: ";
    gospodarz = "";
    while(gospodarz=="")
        cin >> gospodarz;

    cout << "Podaj druzyne gosci: ";
    gosc = "";
    while(gosc=="")
        cin >> gosc;

    cout << "Podaj liczbe goli zdobytych przez gospodarza: ";
    GoleGospodarza = "-1";
    while(!t.CzyPoprawnaLiczba(GoleGospodarza))
        cin>>GoleGospodarza;

    cout << "Podaj liczbe goli zdobytych przez gosci: ";
    GoleGosci = "-1";
    while(!t.CzyPoprawnaLiczba(GoleGosci))
        cin>>GoleGosci;

    Aktualizuj(gospodarz, gosc, GoleGospodarza, GoleGosci);

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
    wyswietlacz.KolorNormalny();

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
            if(linia=="")
                cout << "Pusta linia" << endl;
            else
            {
               team.WgrajTeamZPliku(linia);
               if(CzyIstnieje(team.Nazwa))
               {
                  cout << "BLAD! Druzyna o podanej nazwie (" << team.Nazwa << ") istnieje!" << endl;
                  continue;
               }

               else if(team.Ocena == -1)
               {
                   cout << "BLAD! Nieprawidlowa ocena druzyny!" << endl;
                   continue;
               }

               else if(team.Wygrane == -1)
               {
                   cout << "BLAD! Nieprawidlowa liczba wygranych spotkan druzyny!" << endl;
                   continue;
               }

               else if(team.Remisy == -1)
               {
                   cout << "BLAD! Nieprawidlowa liczba remisowych spotkan druzyny!" << endl;
                   continue;
               }

               else if(team.Przegrane == -1)
               {
                 cout << "BLAD! Nieprawidlowa liczba przegranych spotkan druzyny!" << endl;
                 continue;
               }

               else if(team.OstatniMecz == "-1" || team.PrzedOstatniMecz == "-1" || team.PrzedPrzedOstatniMecz == "-1")
               {
                  cout << "BLAD! Nieprawidlowy stan jednego z zakonczonych meczow druzyny!" << endl;
                  continue;
               }

               else
               {
                   cout << "POWODZENIE!";
                   team.WypiszTeam();
                   Dane.push_back(team);
                   LiczbaRekordow++;
               }
               i++;
               cout << endl;
            }
       }

       dane.close();
    }

    cout <<  endl << "Aby kontynuowac wcisnij ENTER!";
    char znak;
    znak = getch();
    while(znak != 13)
        znak = getch();

}

void Database::WczytaZPlikuMecze(string NazwaPliku)
{
    fstream dane(NazwaPliku, ios::in);
    string LiniaDanych, dana;
    string gospodarz="", gosc="";
    string GoleGospodarza="", GoleGosci="";
    int i;

    if(!dane.is_open())
    {
        cout << "Plik nie zostal odnaleziony..." << endl << "Aby kontynuowac wcisnij ENTER!";
        char znak = 0;
        while(znak!=13)
            znak = getch();
    }

    else
    {
        cout << "Plik otwarto poprawnie..." << endl << endl;

        while(!dane.eof())
        {
            getline(dane, LiniaDanych);
            if(LiniaDanych=="")
                cout << "Pusta linia" << endl;
            else
            {
                i = 0;
                dana = "";
                while(char(LiniaDanych[i]) != ' ' && char(LiniaDanych[i]) != 0)
                {
                    dana += LiniaDanych[i];
                    i++;
                }
                gospodarz = dana;

                i++;
                dana = "";
                while(char(LiniaDanych[i]) != ' ' && char(LiniaDanych[i]) != 0)
                {
                    dana += LiniaDanych[i];
                    i++;
                }
                gosc = dana;

                i++;
                dana = "";
                while(char(LiniaDanych[i]) != ' ' && char(LiniaDanych[i]) != 0)
                {
                    dana += LiniaDanych[i];
                    i++;
                }
                GoleGospodarza = dana;

                i++;
                dana = "";
                while(char(LiniaDanych[i]) != ' ' && char(LiniaDanych[i]) != 0)
                {
                    dana += LiniaDanych[i];
                    i++;
                }
                GoleGosci = dana;

                Aktualizuj(gospodarz, gosc, GoleGospodarza, GoleGosci);
            }
        }
    }
}

void Database::ZapiszWPlikuBaze(string NazwaPliku)
{
    fstream WynikowyPlik(NazwaPliku, ios::out);
    list<Team>::iterator it = Dane.begin();
    for(it; it!= Dane.end(); it++)
        WynikowyPlik << (*it).Nazwa << " " << (*it).Kraj << " " << (*it).Ocena << " " << (*it).Wygrane << " " << (*it).Remisy << " " << (*it).Przegrane << " " << (*it).OstatniMecz << " " << (*it).PrzedOstatniMecz << " " << (*it).PrzedPrzedOstatniMecz << endl;
    WynikowyPlik.close();
}

void Database::OtworzBazeZPliku(string NazwaPliku)
{
    Czysc();
    WczytajZPlikuNoweTeamy(NazwaPliku);
}

void Database::Czysc()
{
    list<Team>::iterator it = Dane.begin();
    for(it; it != Dane.end(); it++)
    {
        Dane.erase(it);
        LiczbaRekordow--;
        Pozycja--;
        if(Pozycja == 0)
            Pozycja = 1;
    }

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

void Database::Aktualizuj(string gospodarz, string gosc, string GoleGospodarza, string GoleGosci)
{
    if(CzyIstnieje(gospodarz) && CzyIstnieje(gosc))
    {
        cout << "Trwa aktualizowanie danych obu druzyn..." << endl;

        list<Team>::iterator it = Dane.begin();
        for(it; it!=Dane.end(); it++)
        {
            if((*it).Nazwa == gospodarz)
            {
                (*it).PrzedPrzedOstatniMecz = (*it).PrzedOstatniMecz;
                (*it).PrzedOstatniMecz = (*it).OstatniMecz;

                if(stoi(GoleGospodarza)>stoi(GoleGosci))
                {
                   (*it).Wygrane++;
                   (*it).OstatniMecz = "W";
                }

                else if(GoleGospodarza == GoleGosci)
                {
                    (*it).Remisy++;
                    (*it).OstatniMecz = "D";
                }

                else
                {
                    (*it).Przegrane++;
                    (*it).OstatniMecz = "L";
                }

            }
            else if((*it).Nazwa == gosc)
            {
                (*it).PrzedPrzedOstatniMecz = (*it).PrzedOstatniMecz;
                (*it).PrzedOstatniMecz = (*it).OstatniMecz;

                if(stoi(GoleGospodarza)<stoi(GoleGosci))
                {
                   (*it).Wygrane++;
                   (*it).OstatniMecz = "W";
                }

                else if(GoleGospodarza == GoleGosci)
                {
                    (*it).Remisy++;
                    (*it).OstatniMecz = "D";
                }

                else
                {
                    (*it).Przegrane++;
                    (*it).OstatniMecz = "L";
                }
            }
        }
    }
    else if(!(CzyIstnieje(gospodarz) || CzyIstnieje(gosc)))
    {
        cout << endl << "Nie mozna zaaktualizowac danych poniewaz zadna z druzyn nie istnieje w bazie. Mozesz je dodac uzywajac klawisza 'Insert'" << endl;
        cout << "Aby kontynuowac nacisnij klawisz ENTER";
        char znak = 0;
        while(znak!=13)
            znak = getch();
    }
    else if(CzyIstnieje(gospodarz) && !CzyIstnieje(gosc))
    {
        cout << "W bazie danych istnieje tylko druzyna " << gospodarz << " czy pomimo tego chcesz zaaktualizowac jej dane?(t/n)";
        char znak = 0;
        while(znak != 't' && znak != 'n' && znak != 'T' && znak != 'N')
            znak = getch();
        if(znak == 't' || znak == 'T')
        {
            list<Team>::iterator it = Dane.begin();
            for(it; it!=Dane.end(); it++)
            {
                if((*it).Nazwa == gospodarz)
                {
                    (*it).PrzedPrzedOstatniMecz = (*it).PrzedOstatniMecz;
                    (*it).PrzedOstatniMecz = (*it).OstatniMecz;

                    if(stoi(GoleGospodarza)>stoi(GoleGosci))
                    {
                       (*it).Wygrane++;
                       (*it).OstatniMecz = "W";
                    }

                    else if(GoleGospodarza == GoleGosci)
                    {
                        (*it).Remisy++;
                        (*it).OstatniMecz = "D";
                    }

                    else
                    {
                        (*it).Przegrane++;
                        (*it).OstatniMecz = "L";
                    }
                }
            }

        }
    }
    else
    {
        cout << "W bazie danych istnieje tylko druzyna " << gosc << " czy pomimi tego chcesz zaaktualizowac jej dane?(t/n)";
        char znak = 0;
        while(znak != 't' && znak != 'n' && znak != 'T' && znak != 'N')
            znak = getch();
        if(znak == 't' || znak == 'T')
        {
            list<Team>::iterator it = Dane.begin();
            for(it; it!=Dane.end(); it++)
            {
                if((*it).Nazwa == gosc)
                {
                    (*it).PrzedPrzedOstatniMecz = (*it).PrzedOstatniMecz;
                    (*it).PrzedOstatniMecz = (*it).OstatniMecz;

                    if(stoi(GoleGospodarza)<stoi(GoleGosci))
                    {
                       (*it).Wygrane++;
                       (*it).OstatniMecz = "W";
                    }

                    else if(GoleGospodarza == GoleGosci)
                    {
                        (*it).Remisy++;
                        (*it).OstatniMecz = "D";
                    }

                    else
                    {
                        (*it).Przegrane++;
                        (*it).OstatniMecz = "L";
                    }
                }
            }
        }
    }
}


