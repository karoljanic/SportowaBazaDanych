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

int PorownywanaKolumna;


Database::Database(int Kolumny, string Name,  string TablicaNaglowkow[], bool czyGlowna)
{
    NazwaBazy = Name;
    LiczbaKolumn = Kolumny;
    LiczbaRekordow = 0;
    Naglowki =  TablicaNaglowkow;
    Strona = 1;
    Pozycja = 1;
    CzyGlowna = czyGlowna;

}

Database::~Database()
{

}

void Database::DodajTeam()
{
    Team team;
    team.StworzTeamRecznie();
    if(CzyIstnieje(team.Nazwa)==-1)
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

void Database::UsunTeam(bool kilka)
{
    if(!kilka)
    {
        cout << "Czy na pewno chcesz usunac druzyne? Jesli tak, nacisnij ENTER, w przeciwnym wypadku nacisnij inny dowolny klawisz!";
        char znak = 0;
        znak = getch();
        if(znak != 13)
            return;
        if(LiczbaRekordow==0)
            return;
    }


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

void Database::EdytujTeam(int nrkolumny, bool kilka)
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
            while(CzyIstnieje(nowynapis)!=-1)
                cin >> nowynapis;
            (*it).Nazwa = nowynapis;
            break;
        }
        case 2:
        {
            cout << "Podaj nowa nazwe kraju: ";
            cin >> nowynapis;
            if(!kilka)
                (*it).Kraj = nowynapis;
            else
            {
                Pozycja = Poz1;
                it = Dane.begin();
                for(int i = 1; i<Pozycja; i++)
                    it++;
                for(Pozycja; Pozycja!=(Poz2+1); Pozycja++)
                {
                    (*it).Kraj = nowynapis;
                    it++;
                }

            }
            break;
        }
        case 3:
        {
            cout << "Podaj nowa ocene druzyny: ";
            cin >> nowynapis;
            while(!team.CzyPoprawnaOcena(nowynapis))
                cin >> nowynapis;
            if(!kilka)
                (*it).Ocena = stoi(nowynapis);
            else
            {

            }
            break;
        }
        case 4:
        {
            cout << "Podaj liczbe wygranych spotkan: ";
            cin >> nowynapis;
            while(!team.CzyPoprawnaLiczba(nowynapis))
                cin >> nowynapis;
            if(!kilka)
                (*it).Wygrane = stoi(nowynapis);
            else
            {

            }
            break;
        }
        case 5:
        {
            cout << "Podaj liczbe zremisowanych spotkan: ";
            cin >> nowynapis;
            while(!team.CzyPoprawnaLiczba(nowynapis))
                cin >> nowynapis;
            if(!kilka)
                (*it).Remisy = stoi(nowynapis);
            else
            {

            }
            break;
        }
        case 6:
        {
            cout << "Podaj liczbe przegranych spotkan: ";
            cin >> nowynapis;
            while(!team.CzyPoprawnaLiczba(nowynapis))
                cin >> nowynapis;
            if(!kilka)
                (*it).Przegrane = stoi(nowynapis);
            else
            {

            }
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
                    if(!kilka)
                        (*it).OstatniMecz = nowynapis;
                    else
                    {

                    }
                    break;
                }
                case 2:
                {
                    if(!kilka)
                        (*it).PrzedOstatniMecz = nowynapis;
                    else
                    {

                    }
                    break;
                }
                case 3:
                {
                    if(!kilka)
                        (*it).PrzedPrzedOstatniMecz = nowynapis;
                    else
                    {

                    }
                    break;
                }

            }
            break;
        }
    }
}

void Database::SortujBazePo(int kolumna, bool rosnaco)
{
    PorownywanaKolumna = kolumna;
    Dane.sort();
    if(!rosnaco)
        Dane.reverse();

    cout << endl << "Posortowano baze po kolumnie " << kolumna;
    if(rosnaco)
        cout << " rosnaco.";
    else
        cout << " malejaco.";
    char znak = 0;

    cout << endl << endl << "Aby kontynuowac nacisnij ENTER!";
    while(znak!=13)
        znak = getch();
    Wyswietl();
}

void Database::ZaznaczKilka()
{

    Poz1 = Pozycja;
    Poz2 = Pozycja;
    char znak;

    znak = getch();

    while(znak!=13)
    {
        if(znak == -32)
        {
            znak = getch();
            if(znak == 80)
            {
                PozycjaDol();
            }
            else if(znak == 72)
            {
                PozycjaGora();
            }
            else if(znak == 83)
            {
                system("cls");
                cout << "Czy na pewno chcesz usunac druzyne? Jesli tak, nacisnij ENTER, w przeciwnym wypadku nacisnij inny dowolny klawisz!";
                char znak = 0;
                znak = getch();
                if(znak != 13)
                    return;

                Pozycja = Poz1;
                for(Poz1; Poz1!=(Poz2+1); Poz1++)
                {
                    UsunTeam(true);
                }
                break;
            }
            Wyswietl2();
        }
        else if(znak == 'e' || znak == 'E')
        {
            system("cls");
            cout << "Czy zmieniec wszystkie kolumny na te sama wartosc?(t/n)";
            znak = 0;
            while(znak != 't' && znak != 'n')
                cin >> znak;
            if(znak == 'n')
            {
                cout << "Ktora kolumne edytowac?<1,7>" << endl;
                string k= "xyz";
                Team t;
                while(!t.CzyPoprawnaLiczba(k))
                    cin >> k;
                if(stoi(k)>0 && stoi(k)<8)
                {
                    Pozycja = Poz1;
                    for(Pozycja; Pozycja!=(Poz2+1); Pozycja++)
                        EdytujTeam(stoi(k), false);
                   k = -1;
                }
                else
                {
                    cout << "Niepoprawny numer kolumny! Aby kontynuowac wcisnij ENTER!";
                    char znak = 0;
                    while(znak != 13)
                        znak = getch();
                }
            }
            else
            {
                cout << "Ktora kolumne edytowac? Pamietaj, ze nie mozesz edytowac 1. kolumny aby nie stracic unikalnosci nazwy druzyny<2,7>" << endl;
                string k= "xyz";
                Team t;
                while(!t.CzyPoprawnaLiczba(k))
                    cin >> k;
                if(stoi(k)>1 && stoi(k)<8)
                {
                    EdytujTeam(stoi(k), true);
                    k = -1;
                }
                else
                {
                    cout << "Niepoprawny numer kolumny! Aby kontynuowac wcisnij ENTER!";
                    char znak = 0;
                    while(znak != 13)
                        znak = getch();
                }
            }

            break;
        }
        else if(znak == 'p' || znak == 'P')
        {
            system("cls");
            string nazwa = "";
            cout << "Wprowadz nazwe wyjsciowego pliku: ";
            while(nazwa == "")
                cin >> nazwa;
            ZapiszWPlikuBaze(nazwa, false);
            break;

        }

        znak = getch();
    }

    Pozycja = 1;
    Strona = 1;

}

int Database::CzyIstnieje(string druzyna)
{
    list<Team>::iterator it = Dane.begin();

    int k = 0;
    for(it; it != Dane.end(); it++)
    {
        k++;
        if((*it).Nazwa == druzyna)
            return k;
    }
    return -1;
}

void Database::WybierzZawierajace()
{
    system("cls");

    Team t;
    string ktora = "zycie";

    cout << "Podaj kolumne wobec ktorej chcesz zastosowac warunek<1,7>: ";
    while(!t.CzyPoprawnaLiczba(ktora))
        cin >> ktora;

    int k = stoi(ktora);

    if(k<1 || k>7)
    {
        cout << "Niepoprawny numer kolumny. Aby kontynuowac wcisnij ENTER!";
        char znak = 0;
        while(znak!=13)
        znak = getch();
             Wyswietl();
    }
    else
    {
        CzyGlowna = false;
        WarunkiRekordow(k);
        CzyGlowna = true;
        Wyswietl();
    }




}

void Database::WarunkiRekordow(int kolumna)
{
    string TytulyKolumn[] = {"L.P.", "Nazwa klubu", "Kraj pochodzenia", "Ocena", "Wygrane", "Remisy", "Porazki", "Bilans spotkan"};

    Database data2(7, "Baza danych klubow pilkarskich",  TytulyKolumn, false);

    list<Team>::iterator it = Dane.begin();

    string op = "zycie";
    string klucz = "";
    Team t;
    switch(kolumna)
    {
        case 1:
        {
            cout << "Napisz operator('==', '!=') i to do czego chcesz porownywac druzyny z rekordow. Oddziel je spacja(np. == nazwa_klubu)" << endl;
            cin >> op >> klucz;
            if(!(( op == "==" || op == "!=" ) && klucz !=""))
            {
                cout << "Blad danych. Aby kontynuowac wcisnij ENTER!";
                char znak = 0;
                while(znak!=13)
                    znak = getch();
                return;
            }
            else
            {
                if(op == "==")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Nazwa == klucz)
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }
                }
                else if(op == "!=")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Nazwa != klucz)
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }

                }
                data2.Uruchom();
            }

            break;
        }
        case 2:
        {
            cout << "Napisz operator('==', '!=') i to do czego chcesz porownywac kraje z rekordow. Oddziel je spacja(np. != kraj)" << endl;
            cin >> op >> klucz;
            if(!(( op == "==" || op == "!=" ) && klucz !=""))
            {
                cout << "Blad danych. Aby kontynuowac wcisnij ENTER!";
                char znak = 0;
                while(znak!=13)
                    znak = getch();
                return;
            }
            else
            {
                if(op == "==")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Kraj == klucz)
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }
                }
                else if(op == "!=")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Kraj != klucz)
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }

                }
                data2.Uruchom();
            }

            break;
        }
        case 3:
        {
            cout << "Napisz operator('==', '!=', '<', '>', '<=', '>=' i to do czego chcesz porownywac oceny z rekordow. Oddziel je spacja(np. < ocena)" << endl;
            cin >> op >> klucz;
            if(!(( op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=") && t.CzyPoprawnaLiczba(klucz)))
            {
                cout << "Blad danych. Aby kontynuowac wcisnij ENTER!";
                char znak = 0;
                while(znak!=13)
                    znak = getch();
                return;
            }
            else
            {
                if(op == "==")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Ocena == stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }
                }
                else if(op == "!=")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Ocena != stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }

                }
                else if(op == "<")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Ocena < stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }
                }
                else if(op == ">")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Ocena > stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }

                }
                else if(op == "<=")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Ocena <= stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }

                }
                else if(op == ">=")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Ocena >= stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }

                }
                data2.Uruchom();
            }


            break;
        }
        case 4:
        {
            cout << "Napisz operator('==', '!=', '<', '>', '<=', '>=' i to do czego chcesz porownywac wygrane z rekordow. Oddziel je spacja(np. <= liczba_wygranych)" << endl;
            cin >> op >> klucz;
            if(!(( op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=") && t.CzyPoprawnaLiczba(klucz)))
            {
                cout << "Blad danych. Aby kontynuowac wcisnij ENTER!";
                char znak = 0;
                while(znak!=13)
                    znak = getch();
                return;
            }
            else
            {
                if(op == "==")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Wygrane == stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }
                }
                else if(op == "!=")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Wygrane != stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }

                }
                else if(op == "<")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Wygrane < stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }
                }
                else if(op == ">")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Wygrane > stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }

                }
                else if(op == "<=")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Wygrane <= stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }

                }
                else if(op == ">=")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Wygrane >= stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }

                }
                data2.Uruchom();
            }

            break;
        }
        case 5:
        {
            cout << "Napisz operator('==', '!=', '<', '>', '<=', '>=' i to do czego chcesz porownywac remisy z rekordow. Oddziel je spacja(np. >= liczba_remosow)" << endl;
            cin >> op >> klucz;
            if(!(( op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=") && t.CzyPoprawnaLiczba(klucz)))
            {
                cout << "Blad danych. Aby kontynuowac wcisnij ENTER!";
                char znak = 0;
                while(znak!=13)
                    znak = getch();
                return;
            }
            else
            {
                if(op == "==")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Remisy == stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }
                }
                else if(op == "!=")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Remisy != stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }

                }
                else if(op == "<")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Remisy < stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }
                }
                else if(op == ">")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Remisy > stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }

                }
                else if(op == "<=")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Remisy <= stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }

                }
                else if(op == ">=")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Remisy >= stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }

                }
                data2.Uruchom();
            }


            break;
        }
        case 6:
        {
            cout << "Napisz operator('==', '!=', '<', '>', '<=', '>=' i to do czego chcesz porownywac przegrane z rekordow. Oddziel je spacja(np. > liczba_przegranych)" << endl;
            cin >> op >> klucz;
            if(!(( op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=") && t.CzyPoprawnaLiczba(klucz)))
            {
                cout << "Blad danych. Aby kontynuowac wcisnij ENTER!";
                char znak = 0;
                while(znak!=13)
                    znak = getch();
                return;
            }
            else
            {
                if(op == "==")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Przegrane == stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }
                }
                else if(op == "!=")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Przegrane != stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }

                }
                else if(op == "<")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Przegrane < stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }
                }
                else if(op == ">")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Przegrane > stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }

                }
                else if(op == "<=")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Przegrane <= stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }

                }
                else if(op == ">=")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Przegrane >= stoi(klucz))
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }

                }
                data2.Uruchom();
            }

            break;
        }
        case 7:
        {
            cout << "Napisz operator('==', '!=') i to do czego chcesz porownywac bilansy z rekordow. Oddziel je spacja(np. == bilans_spotkan)" << endl;
            cin >> op >> klucz;
            cin >> op >> klucz;
            if(!(( op == "==" || op == "!=" ) && klucz !=""))
            {
                cout << "Blad danych. Aby kontynuowac wcisnij ENTER!";
                char znak = 0;
                while(znak!=13)
                    znak = getch();
                Wyswietl();
            }
            else
            {
                if(op == "==")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Nazwa == klucz)
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }
                }
                else if(op == "!=")
                {
                    for(it; it!=Dane.end(); it++)
                    {
                        if((*it).Nazwa != klucz)
                        {
                            data2.Dane.push_back(*it);
                            data2.LiczbaRekordow++;
                        }

                    }

                }
            }

            break;
        }
    }




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
    if(CzyGlowna)
        cout << "                                                 ...Zwykly tryb bazy danych... " << endl;
    else
        cout << "                                                 ...Baza z rekordami zawierajacymi..." << endl;

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
    if(CzyGlowna)
        cout << "  " << endl;
    else
        cout << "Aby wrocic do glownej bazy - 'Q', aby uzyc funkcji matematycznej - 'F', aby sortowac - 'S', aby zapisac rekordy do pliku - 'P'" << endl;

}
//////////////////////////////////////
void Database::Wyswietl2()
{
    system("cls");
    if(CzyGlowna)
        cout << "                                                   ...Tryb zaznaczania kilku danych... " << endl;
    else
        cout << "                          ...Tryb zaznaczania kilku danych(Tabela rekordow zawierajacych)... " << endl;

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
                wyswietlacz.WyswietlRekord(i, Strona, (*it),true, (i>=Poz1 && i<=Poz2));
            else
                wyswietlacz.WyswietlRekord(i, Strona, (*it),false, (i>=Poz1 && i<=Poz2));

            i++;
            it++;
            if(it == Dane.end())
                break;
        }
    }


    wyswietlacz.WyswietlNumerStrony(Strona);
    wyswietlacz.KolorNormalny();
    cout << "             Aby zakonczyc nie wprowadzajac zmian-Enter, aby usunac-Delete, aby edytowac- 'E', aby zapisac rekordy do pliku- 'P'";

}
/////////////////////////////////////////////////////
void Database::WczytajZPlikuNoweTeamy(string NazwaPliku)
{
    fstream dane(NazwaPliku, ios::in);
    string linia;
    Team team;
    int i = 1;

    try
    {
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
                   if(CzyIstnieje(team.Nazwa) != -1)
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
    }
    catch(...)
    {
        cout << "BLAD! Nieprawidlowe dane w pliku" << endl;
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
    char znak;

    try
    {
        if(!dane.is_open())
        {
            cout << "Plik nie zostal odnaleziony..." << endl << "Aby kontynuowac wcisnij ENTER!";
            znak = 0;
            while(znak!=13)
                znak = getch();
        }

        else
        {
            cout << "Plik otwarto poprawnie..." << endl << endl;if(CzyGlowna)
        cout << "                                                   ...Tryb zaznaczania kilku danych... " << endl;
    else
        cout << "                          ...Tryb zaznaczania kilku danych(Tabela rekordow zawierajacych)... " << endl;

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

                    Team t;

                    if(!t.CzyPoprawnaLiczba(GoleGospodarza))
                        cout << "Niepoprawne dane w pliku!" << endl;
                    else if(!t.CzyPoprawnaLiczba(GoleGosci))
                        cout << "Niepoprawne dane w pliku!" << endl;
                    else
                    {
                        Aktualizuj(gospodarz, gosc, GoleGospodarza, GoleGosci);
                    }
                }
            }

            char znak = 0;
            cout << endl << "Aby kontynuowac wcisnij ENTER!";
            while(znak!=13)
                znak = getch();
        }
    }
    catch(...)
    {
        cout << "BLAD! Nieprawidlowe dane w pliku" << endl;
    }
}

void Database::ZapiszWPlikuBaze(string NazwaPliku, bool wszystko)
{
    fstream WynikowyPlik(NazwaPliku+".txt", ios::out);
    if(wszystko)
    {
        list<Team>::iterator it = Dane.begin();
        for(it; it!= Dane.end(); it++)
            WynikowyPlik << (*it).Nazwa << " " << (*it).Kraj << " " << (*it).Ocena << " " << (*it).Wygrane << " " << (*it).Remisy << " " << (*it).Przegrane << " " << (*it).OstatniMecz << " " << (*it).PrzedOstatniMecz << " " << (*it).PrzedPrzedOstatniMecz << endl;
    }
    else
    {
        Pozycja = Poz1;
        list<Team>::iterator it = Dane.begin();
        for(int i = 0; i<Pozycja; i++)
            it++;
        it--;
        for(Pozycja; Pozycja!=(Poz2+1);Pozycja++)
        {
            WynikowyPlik << (*it).Nazwa << " " << (*it).Kraj << " " << (*it).Ocena << " " << (*it).Wygrane << " " << (*it).Remisy << " " << (*it).Przegrane << " " << (*it).OstatniMecz << " " << (*it).PrzedOstatniMecz << " " << (*it).PrzedPrzedOstatniMecz << endl;
            it++;
        }
    }

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
        Poz2++;
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
        Poz2--;
        if(Poz2<Poz1)
            Poz2++;
        return true;
    }
    return false;

}

void Database::Aktualizuj(string gospodarz, string gosc, string GoleGospodarza, string GoleGosci)
{
    if(CzyIstnieje(gospodarz)!=-1 && CzyIstnieje(gosc)!=-1)
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
    else if(!(CzyIstnieje(gospodarz)!=-1 || CzyIstnieje(gosc)!=-1))
    {
        cout << endl << "Nie mozna zaaktualizowac danych poniewaz zadna z druzyn nie istnieje w bazie. Mozesz je dodac uzywajac klawisza 'Insert'" << endl;
        cout << "Aby kontynuowac nacisnij klawisz ENTER";
        char znak = 0;
        while(znak!=13)
            znak = getch();
    }
    else if(CzyIstnieje(gospodarz)!=-1 && CzyIstnieje(gosc)==-1)
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

void Database:: Uruchom()
{
    char znak = 'x';
    string sciezka = "";
    Wyswietl();

    while(true)
    {
        znak = getch();
        if(znak == -32)
        {
            znak = getch();

            if(znak == 80)
            {
                if(PozycjaDol())
                    Wyswietl();
            }
            else if(znak == 72)
            {
                if(PozycjaGora())
                    Wyswietl();
            }
            else if(znak == 82)
            {
                if(CzyGlowna)
                {
                    system("cls");
                    DodajTeam();
                    Wyswietl();
                }

            }
            else if(znak == 83)
            {
                if(CzyGlowna)
                {
                    if(LiczbaRekordow == 0)
                    {
                    system("cls");
                    cout << "Nie ma czego usunac! Aby kontynuowac wcisnij ENTER!";
                    while(znak!=13)
                        znak = getch();
                    }
                    else
                    {
                        system("cls");
                        UsunTeam(false);
                    }
                    Wyswietl();
                }
            }
        }
        else if(znak == 'm' || znak=='M')
        {
         if(NastepnaStrona())
            Wyswietl();
        }
        else if(znak == 'n' || znak == 'N')
        {
            if(PoprzedniaStrona())
                Wyswietl();
        }
        else if(znak == 'q' || znak == 'Q')
        {

            system("cls");
            return ;

        }
        else if((znak == 'e' || znak == 'E') && CzyGlowna)
        {
            system("cls");
            znak = 0;
            if(LiczbaRekordow == 0)
            {
                cout << "Nie mozesz edytowac nieistniejach rekordow! Aby kontynuowac wcisnij ENTER!";
                char znak = 0;
                while(znak!=13)
                    znak = getch();
                Wyswietl();
                continue;
            }
            cout << "Ktora kolumne edytowac?<1,7>" << endl;
            string k= "xyz";
            Team t;
            while(!t.CzyPoprawnaLiczba(k))
                cin >> k;
            if(stoi(k)>0 && stoi(k)<8)
            {
               EdytujTeam(stoi(k),false);
               k = -1;
            }
            else
            {
                cout << "Niepoprawny numer kolumny! Aby kontynuowac wcisnij ENTER!";
                char znak = 0;
                while(znak != 13)
                    znak = getch();
            }
            Wyswietl();
        }
        else if(znak == 'j' || znak == 'J')
        {
            if(CzyGlowna)
            {
                system("cls");
                sciezka = "";
                cout << "Wprowadz sciezke dostepu do pliku z danymi lub nazwe pliku jesli znajduje sie on w folderze programu(nazwa_pliku.txt) ";
                while(sciezka=="")
                    cin >> sciezka;

                WczytajZPlikuNoweTeamy(sciezka);
                Wyswietl();
            }

        }
        else if(znak == 'o' || znak == 'O')
        {
            if(CzyGlowna)
            {
                system("cls");
                sciezka = "";
                cout << "Wprowadz sciezke dostepu do pliku z danymi lub nazwe pliku jesli znajduje sie on w folderze programu(nazwa_pliku.txt) ";
                while(sciezka=="")
                    cin >> sciezka;
                OtworzBazeZPliku(sciezka);
                Wyswietl();
            }

        }
        else if(znak == 'p' || znak == 'P')
        {
            system("cls");
            string nazwa = "";
            cout << "Wprowadz nazwe wyjsciowego pliku: ";
            while(nazwa == "")
                cin >> nazwa;
            ZapiszWPlikuBaze(nazwa, true);
            Wyswietl();
        }
        else if(znak == 'd' || znak == 'D')
        {
            if(CzyGlowna)
            {
                system("cls");
                DodajMecz();
                Wyswietl();
            }

        }
        else if(znak == 'a' || znak == 'A')
        {
            if(CzyGlowna)
            {
                system("cls");
                sciezka = "";
                cout << "Wprowadz sciezke dostepu do pliku z danymi lub nazwe pliku jesli znajduje sie on w folderze programu(nazwa_pliku.txt) ";
                while(sciezka=="")
                    cin >> sciezka;
                system("cls");
                WczytaZPlikuMecze(sciezka);
                Wyswietl();
            }

        }
        else if(znak == 'z' || znak == 'Z')
        {
            system("cls");
            string nazwa;
            cout << "Jakiej druzyny szukasz?";
            cin >> nazwa;
            if(CzyIstnieje(nazwa)!=-1)
                cout << endl << "Druzyna " << nazwa << " znajduje sie w bazie danych na pozycji " << CzyIstnieje(nazwa);
            else
                cout << endl << "Druzyna " << nazwa << " nie znajduje sie w bazie danych!";
            cout << endl << "Aby kontynuowac wcisnij ENTER!";
            char znak = 0;
            while(znak!=13)
                znak = getch();

            Wyswietl();
        }
        else if(znak == 'f' || znak=='F')
        {
            int poz = 0;
            znak = 0;

            while(znak!=13)
            {
                system("cls");
                cout << "Wybierz funkcje matematycznej ktora chcesz uzyc." << endl << "Pamietaj, ze funkcje matematyczne sa dostepne tylko dla danych liczbowych!" << endl << endl;
                string funkcje[] = {"Maximum", "Minimum", " Suma ", "Srednia", "Mediana"};

                for(int i = 0; i<5; i++)
                {
                    if(i == poz)
                        cout << "                         ==> ";
                    else
                        cout << "                             ";
                   cout << funkcje[i];
                   if(i == poz)
                      cout << " <==";

                    cout << endl;
                }
                znak = getch();
                if(znak == -32)
                {
                    znak = getch();

                    if(znak == 80)
                    {
                        poz++;
                        if(poz>4)
                            poz = 4;
                    }

                    else if(znak == 72)
                    {
                        poz--;
                        if(poz<0)
                            poz = 0;
                    }
                }

            }
            cout << endl;
            string ktora;
            Team t;
            switch(poz)
            {
                case 0:
                {
                    ktora = -1;
                    cout << "W ktorej kolumnie chcesz znalezc maksimum?" << endl;
                    while(!(t.CzyPoprawnaLiczba(ktora) && stoi(ktora)>2 && stoi(ktora)<7))
                        cin >> ktora;
                    cout << "Maksimum kolumny " << ktora << ": ";
                    if(Funkcje(1,stoi(ktora))!=-1)
                        cout << Funkcje(1,stoi(ktora));
                    else
                        cout << "Brak danych!";
                    break;
                }
                case 1:
                {
                    ktora = -1;
                    cout << "W ktorej kolumnie chcesz znalezc minimum?" << endl;
                    while(!(t.CzyPoprawnaLiczba(ktora) && stoi(ktora)>2 && stoi(ktora)<7))
                        cin >> ktora;
                    cout << "Minimum kolumny " << ktora << ": ";
                    if(Funkcje(2,stoi(ktora))!=-1)
                        cout << Funkcje(2,stoi(ktora));
                    else
                        cout << "Brak danych!";
                    break;
                }
                case 2:
                {
                    ktora = -1;
                    cout << "Ktora kolumne chcesz zsumowac?" << endl;
                    while(!(t.CzyPoprawnaLiczba(ktora) && stoi(ktora)>2 && stoi(ktora)<7))
                        cin >> ktora;
                    cout << "Suma kolumny " << ktora << ": ";
                    if(Funkcje(3,stoi(ktora))!=-1)
                        cout << Funkcje(3,stoi(ktora));
                    else
                        cout << "Brak danych!";
                    break;
                }
                case 3:
                {
                    ktora = -1;
                    cout << "Srednia ktorej kolumny chcesz obliczyc?" << endl;
                    while(!(t.CzyPoprawnaLiczba(ktora) && stoi(ktora)>2 && stoi(ktora)<7))
                        cin >> ktora;
                    cout << "Srednia kolumny " << ktora << ": ";
                    if(Funkcje(4,stoi(ktora))!=-1)
                        cout << Funkcje(4,stoi(ktora));
                    else
                        cout << "Brak danych!";
                    break;
                }
                case 4:
                {
                    ktora = -1;
                    cout << "Mediane ktorej kolumny chcesz wyznaczyc?" << endl;
                    while(!(t.CzyPoprawnaLiczba(ktora) && stoi(ktora)>2 && stoi(ktora)<7))
                        cin >> ktora;
                    cout << "Mediana kolumny " << ktora << ": ";
                    if(Funkcje(5,stoi(ktora))!=-1)
                        cout << Funkcje(5,stoi(ktora));
                    else
                        cout << "Brak danych!";
                    break;
                }
            }
            cout << endl << endl << "Aby kontynuowac nacisnij ENTER!";
            znak = 0;
            while(znak!=13)
                znak = getch();

            Wyswietl();

        }
        else if(znak == 'r' || znak == 'R')
        {
            if(LiczbaRekordow!=0)
            {
                ZaznaczKilka();
                Wyswietl();
            }
            else
            {
                cout << "Brak danych! Aby kontynuowac wcisnij ENTER!";
                znak = 0;
                while(znak!=13)
                    znak = getch();
                Wyswietl();
            }
        }
        else if(znak == 's' || znak == 'S')
        {
            string ktora, ros = "";
            Team t;
            if(LiczbaRekordow==0)
            {
                cout << "Brak danych! Aby kontynuowac wcisnij ENTER!";
                znak = 0;
                while(znak!=13)
                    znak = getch();
                Wyswietl();
            }
            else
            {
                system("cls");
                cout << "Po ktorej kolumnie posortowac dane?<1,7> ";
                ktora = -1;
                while(!(t.CzyPoprawnaLiczba(ktora) && stoi(ktora)>0 && stoi(ktora)<8))
                    cin >> ktora;

                cout << endl << "Czy rosnaco?(t/n)";
                while(ros!="t" && ros!="n")
                    cin >> ros;

                if(ros == "t")
                    SortujBazePo(stoi(ktora), true);
                else
                    SortujBazePo(stoi(ktora), false);

            }

        }
        if(znak == 'w' || znak == 'W')
        {
            if(CzyGlowna)
                WybierzZawierajace();
        }

    }
}

float Database::Funkcje(int numerfunkcji, int numerkolumny) ///numery funkcji:1-max, 2-min, 3-suma, 4-srednia, 5-mediana
{
    float suma = 0;
    int maks = 0;
    int mini = 0;
    list<int> mediana;

    switch(numerkolumny)
    {
        case 3:
        {
            list<Team>::iterator it = Dane.begin();
            maks = (*it).Ocena;
            mini = (*it).Ocena;
            for(it; it!=Dane.end();it++)
            {
                suma+=(*it).Ocena;

                mediana.push_back((*it).Ocena);
            }

            break;
        }
        case 4:
        {
            list<Team>::iterator it = Dane.begin();
            maks = (*it).Wygrane;
            mini = (*it).Wygrane;
            for(it; it!=Dane.end();it++)
            {
                suma+=(*it).Wygrane;

                mediana.push_back((*it).Wygrane);
            }

            break;
        }
        case 5:
        {
            list<Team>::iterator it = Dane.begin();
            maks = (*it).Remisy;
            mini = (*it).Remisy;
            for(it; it!=Dane.end();it++)
            {
                suma+=(*it).Remisy;

                mediana.push_back((*it).Remisy);
            }

            break;
        }
        case 6:
        {
            list<Team>::iterator it = Dane.begin();
            maks = (*it).Przegrane;
            mini = (*it).Przegrane;
            for(it; it!=Dane.end();it++)
            {
                suma+=(*it).Przegrane;

                mediana.push_back((*it).Przegrane);
            }

            break;
        }

    }

    mediana.sort();
//    list<int>::iterator it = mediana.begin();
//    for(it; it!=mediana.end(); it++)
//        cout << (*it) << "    ";

    switch(numerfunkcji)
    {
        case 1:
        {
            if(LiczbaRekordow == 0)
                return -1;
            mediana.reverse();
            return *(mediana.begin());
        }
        case 2:
        {
            if(LiczbaRekordow == 0)
                return -1;
            return *(mediana.begin());
        }
        case 3:
        {
            if(LiczbaRekordow == 0)
                return -1;
           return suma;
        }
        case 4:
        {
            if(LiczbaRekordow == 0)
                return -1;
            return suma/LiczbaRekordow;
        }
        case 5:
        {
            if(LiczbaRekordow == 0)
                return -1;
            if(LiczbaRekordow%2 == 1)
            {
                int p = LiczbaRekordow/2;
                list<int>::iterator it = mediana.begin();
                for(int i = 0; i<p; i++)
                    it++;

                return (*it);
            }
            else
            {
                float m = 0;
                int p = LiczbaRekordow/2;
                list<int>::iterator it = mediana.begin();
                for(int i = 0; i<p; i++)
                    it++;
                m+= (*it);
                it--;
                m+= (*it);

                m/=2.0;

                return m;
            }

        }

    }

}

bool operator < (const Team &t1, const Team &t2)
{
    switch(PorownywanaKolumna)
    {
        case 1:
        {
            if(t1.Nazwa<t2.Nazwa)
                return true;
            else
                return false;
        }
        case 2:
        {
            if(t1.Kraj<t2.Kraj)
                return true;
            else
                return false;
        }
        case 3:
        {
            if(t1.Ocena<t2.Ocena)
                return true;
            else
                return false;
        }
        case 4:
        {
            if(t1.Wygrane<t2.Wygrane)
                return true;
            else
                return false;
        }
        case 5:
        {
            if(t1.Remisy<t2.Remisy)
                return true;
            else
                return false;
        }
        case 6:
        {
            if(t1.Przegrane<t2.Przegrane)
                return true;
            else
                return false;
        }
        case 7:
        {
            string s1="", s2="";

            if(t1.OstatniMecz == "-")
                s1+="a";
            else if(t1.OstatniMecz == "L")
                s1+="b";
            else if(t1.OstatniMecz == "D")
                s1+="c";
            else if(t1.OstatniMecz == "W")
                s1+="d";

            if(t1.PrzedOstatniMecz == "-")
                s1+="a";
            else if(t1.PrzedOstatniMecz == "L")
                s1+="b";
            else if(t1.PrzedOstatniMecz == "D")
                s1+="c";
            else if(t1.PrzedOstatniMecz == "W")
                s1+="d";

            if(t1.PrzedPrzedOstatniMecz == "-")
                s1+="a";
            else if(t1.PrzedPrzedOstatniMecz == "L")
                s1+="b";
            else if(t1.PrzedPrzedOstatniMecz == "D")
                s1+="c";
            else if(t1.PrzedPrzedOstatniMecz == "W")
                s1+="d";

            if(t2.OstatniMecz == "-")
                s2+="a";
            else if(t2.OstatniMecz == "L")
                s2+="b";
            else if(t2.OstatniMecz == "D")
                s2+="c";
            else if(t2.OstatniMecz == "W")
                s2+="d";

            if(t2.PrzedOstatniMecz == "-")
                s2+="a";
            else if(t2.PrzedOstatniMecz == "L")
                s2+="b";
            else if(t2.PrzedOstatniMecz == "D")
                s2+="c";
            else if(t2.PrzedOstatniMecz == "W")
                s2+="d";

            if(t2.PrzedPrzedOstatniMecz == "-")
                s2+="a";
            else if(t2.PrzedPrzedOstatniMecz == "L")
                s2+="b";
            else if(t2.PrzedPrzedOstatniMecz == "D")
                s2+="c";
            else if(t2.PrzedPrzedOstatniMecz == "W")
                s2+="d";

            if(s1<s2)
                return true;
            else
                return false;

        }


    }
}

bool operator > (const Team &t1, const Team &t2)
{
    switch(PorownywanaKolumna)
    {
        case 1:
        {
            if(t1.Nazwa>t2.Nazwa)
                return true;
            else
                return false;
        }
        case 2:
        {
            if(t1.Kraj>t2.Kraj)
                return true;
            else
                return false;
        }
        case 3:
        {
            if(t1.Ocena>t2.Ocena)
                return true;
            else
                return false;
        }
        case 4:
        {
            if(t1.Wygrane>t2.Wygrane)
                return true;
            else
                return false;
        }
        case 5:
        {
            if(t1.Remisy>t2.Remisy)
                return true;
            else
                return false;
        }
        case 6:
        {
            if(t1.Przegrane>t2.Przegrane)
                return true;
            else
                return false;
        }
        case 7:
        {
            string s1="", s2="";

            if(t1.OstatniMecz == "-")
                s1+="a";
            else if(t1.OstatniMecz == "L")
                s1+="b";
            else if(t1.OstatniMecz == "D")
                s1+="c";
            else if(t1.OstatniMecz == "W")
                s1+="d";

            if(t1.PrzedOstatniMecz == "-")
                s1+="a";
            else if(t1.PrzedOstatniMecz == "L")
                s1+="b";
            else if(t1.PrzedOstatniMecz == "D")
                s1+="c";
            else if(t1.PrzedOstatniMecz == "W")
                s1+="d";

            if(t1.PrzedPrzedOstatniMecz == "-")
                s1+="a";
            else if(t1.PrzedPrzedOstatniMecz == "L")
                s1+="b";
            else if(t1.PrzedPrzedOstatniMecz == "D")
                s1+="c";
            else if(t1.PrzedPrzedOstatniMecz == "W")
                s1+="d";

            if(t2.OstatniMecz == "-")
                s2+="a";
            else if(t2.OstatniMecz == "L")
                s2+="b";
            else if(t2.OstatniMecz == "D")
                s2+="c";
            else if(t2.OstatniMecz == "W")
                s2+="d";

            if(t2.PrzedOstatniMecz == "-")
                s2+="a";
            else if(t2.PrzedOstatniMecz == "L")
                s2+="b";
            else if(t2.PrzedOstatniMecz == "D")
                s2+="c";
            else if(t2.PrzedOstatniMecz == "W")
                s2+="d";

            if(t2.PrzedPrzedOstatniMecz == "-")
                s2+="a";
            else if(t2.PrzedPrzedOstatniMecz == "L")
                s2+="b";
            else if(t2.PrzedPrzedOstatniMecz == "D")
                s2+="c";
            else if(t2.PrzedPrzedOstatniMecz == "W")
                s2+="d";

            if(s1>s2)
                return true;
            else
                return false;

        }


    }
}

bool operator == (const Team &t1, const Team &t2)
{
    switch(PorownywanaKolumna)
    {
        case 1:
        {
            if(t1.Nazwa==t2.Nazwa)
                return true;
            else
                return false;
        }
        case 2:
        {
            if(t1.Kraj==t2.Kraj)
                return true;
            else
                return false;
        }
        case 3:
        {
            if(t1.Ocena==t2.Ocena)
                return true;
            else
                return false;
        }
        case 4:
        {
            if(t1.Wygrane==t2.Wygrane)
                return true;
            else
                return false;
        }
        case 5:
        {
            if(t1.Remisy==t2.Remisy)
                return true;
            else
                return false;
        }
        case 6:
        {
            if(t1.Przegrane==t2.Przegrane)
                return true;
            else
                return false;
        }
        case 7:
        {
            string s1="", s2="";

            if(t1.OstatniMecz == "-")
                s1+="a";
            else if(t1.OstatniMecz == "L")
                s1+="b";
            else if(t1.OstatniMecz == "D")
                s1+="c";
            else if(t1.OstatniMecz == "W")
                s1+="d";

            if(t1.PrzedOstatniMecz == "-")
                s1+="a";
            else if(t1.PrzedOstatniMecz == "L")
                s1+="b";
            else if(t1.PrzedOstatniMecz == "D")
                s1+="c";
            else if(t1.PrzedOstatniMecz == "W")
                s1+="d";

            if(t1.PrzedPrzedOstatniMecz == "-")
                s1+="a";
            else if(t1.PrzedPrzedOstatniMecz == "L")
                s1+="b";
            else if(t1.PrzedPrzedOstatniMecz == "D")
                s1+="c";
            else if(t1.PrzedPrzedOstatniMecz == "W")
                s1+="d";

            if(t2.OstatniMecz == "-")
                s2+="a";
            else if(t2.OstatniMecz == "L")
                s2+="b";
            else if(t2.OstatniMecz == "D")
                s2+="c";
            else if(t2.OstatniMecz == "W")
                s2+="d";

            if(t2.PrzedOstatniMecz == "-")
                s2+="a";
            else if(t2.PrzedOstatniMecz == "L")
                s2+="b";
            else if(t2.PrzedOstatniMecz == "D")
                s2+="c";
            else if(t2.PrzedOstatniMecz == "W")
                s2+="d";

            if(t2.PrzedPrzedOstatniMecz == "-")
                s2+="a";
            else if(t2.PrzedPrzedOstatniMecz == "L")
                s2+="b";
            else if(t2.PrzedPrzedOstatniMecz == "D")
                s2+="c";
            else if(t2.PrzedPrzedOstatniMecz == "W")
                s2+="d";

            if(s1==s2)
                return true;
            else
                return false;

        }


    }
}

bool operator != (const Team &t1, const Team &t2)
{
    switch(PorownywanaKolumna)
    {
        case 1:
        {
            if(t1.Nazwa!=t2.Nazwa)
                return true;
            else
                return false;
        }
        case 2:
        {
            if(t1.Kraj!=t2.Kraj)
                return true;
            else
                return false;
        }
        case 3:
        {
            if(t1.Ocena!=t2.Ocena)
                return true;
            else
                return false;
        }
        case 4:
        {
            if(t1.Wygrane!=t2.Wygrane)
                return true;
            else
                return false;
        }
        case 5:
        {
            if(t1.Remisy!=t2.Remisy)
                return true;
            else
                return false;
        }
        case 6:
        {
            if(t1.Przegrane!=t2.Przegrane)
                return true;
            else
                return false;
        }
        case 7:
        {
            string s1="", s2="";

            if(t1.OstatniMecz == "-")
                s1+="a";
            else if(t1.OstatniMecz == "L")
                s1+="b";
            else if(t1.OstatniMecz == "D")
                s1+="c";
            else if(t1.OstatniMecz == "W")
                s1+="d";

            if(t1.PrzedOstatniMecz == "-")
                s1+="a";
            else if(t1.PrzedOstatniMecz == "L")
                s1+="b";
            else if(t1.PrzedOstatniMecz == "D")
                s1+="c";
            else if(t1.PrzedOstatniMecz == "W")
                s1+="d";

            if(t1.PrzedPrzedOstatniMecz == "-")
                s1+="a";
            else if(t1.PrzedPrzedOstatniMecz == "L")
                s1+="b";
            else if(t1.PrzedPrzedOstatniMecz == "D")
                s1+="c";
            else if(t1.PrzedPrzedOstatniMecz == "W")
                s1+="d";

            if(t2.OstatniMecz == "-")
                s2+="a";
            else if(t2.OstatniMecz == "L")
                s2+="b";
            else if(t2.OstatniMecz == "D")
                s2+="c";
            else if(t2.OstatniMecz == "W")
                s2+="d";

            if(t2.PrzedOstatniMecz == "-")
                s2+="a";
            else if(t2.PrzedOstatniMecz == "L")
                s2+="b";
            else if(t2.PrzedOstatniMecz == "D")
                s2+="c";
            else if(t2.PrzedOstatniMecz == "W")
                s2+="d";

            if(t2.PrzedPrzedOstatniMecz == "-")
                s2+="a";
            else if(t2.PrzedPrzedOstatniMecz == "L")
                s2+="b";
            else if(t2.PrzedPrzedOstatniMecz == "D")
                s2+="c";
            else if(t2.PrzedPrzedOstatniMecz == "W")
                s2+="d";

            if(s1!=s2)
                return true;
            else
                return false;

        }


    }
}

 bool operator < (const int &t1, const string &t2)
 {
    if(t1 < stoi(t2))
        return true;
    else
        return false;
 }

 bool operator > (const int &t1, const string &t2)
 {
     if(t1 > stoi(t2))
        return true;
    else
        return false;
 }

 bool operator == (const int &t1, const string &t2)
 {
     if(t1 == stoi(t2))
        return true;
    else
        return false;
 }

 bool operator != (const int &t1, const string &t2)
 {
     if(t1 != stoi(t2))
        return true;
    else
        return false;
 }



