#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>

#include "Team.h"
#include "Database.h"
#include "Display.h"

Display::Display(int ile_kolumn, int ile_rekordow, int szerokosci_kolumn[], string zawartosci_kolumn[])
{
    IleKolumn = ile_kolumn;
    DlugosciKolumn =  szerokosci_kolumn;
    NaglowkiKolumn = zawartosci_kolumn;
    SzerokoscBazy = 0;
    Rekordy = ile_rekordow;

    for(int i=0; i<ile_kolumn; i++)
        SzerokoscBazy+=DlugosciKolumn[i];
    SzerokoscBazy += IleKolumn;
}

Display::~Display()
{

}

enum colors
{
    Czarny = 0,
    CiemnyNiebieski = 1,
    CiemnyZielony = 2,
    JasnyNiebieski = 3,
    Czerwony = 4,
    Fioletowy = 5,
    Zolty = 6,
    CiemnyBialy = 7,
    Szary = 8,
    MorskiNiebieski = 9,
    JasnyZielony = 10,
    BlekitnyNiebieski = 11,
    PudrowyRozowy = 12,
    Rozowy = 13,
    Kremowy = 14,
    Bialy = 15,
};

void ZmienKolor(colors tlo, colors tekst)
{
    int k = tlo*16 + tekst;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k );
}

enum lines
{
    vertical = 186,
    horizontal = 205,
    top_right = 187,
    top_left = 201,
    down_right = 188,
    down_left = 200,
    middle = 206,
    middle_vertical_left = 204,
    middle_horizonal_down = 202,
    middle_vertical_right = 185,
    middle_horizonal_top = 203,
};

void Display::WyswietlTytulBazy(string nazwa)
{
    KtoraInstrukcja = 0;
    ZmienKolor(Zolty,Czarny);
    for(int i = 0; i<=SzerokoscBazy; i++)
        cout << char(horizontal);
    WyswietlInstrukcje(0);
    ZmienKolor(Zolty,Czarny);
    int n = (SzerokoscBazy-nazwa.length())/2;
    for(int i = 0; i<n; i++)
        cout << "*";
    cout << nazwa;
    for(int i = 0; i<=n; i++)
        cout << "*";
    WyswietlInstrukcje(0);
    ZmienKolor(Zolty,Czarny);
    for(int i = 0; i<=SzerokoscBazy; i++)
        cout << char(horizontal);
    ZmienKolor(Czarny,Bialy);
    WyswietlInstrukcje(0);

}

void Display::WyswietlNaglowek(bool CzySaJakiesDane)
{
    ZmienKolor(Kremowy, Czerwony);
    cout << char(top_left);
    for(int i = 0; i<IleKolumn; i++)
    {
        for(int j = 0; j<DlugosciKolumn[i]; j++)
            cout << char(horizontal);
        if(i!=IleKolumn-1)
            cout << char(middle_horizonal_top);
    }

    cout << char(top_right);
    ZmienKolor(Czarny, Bialy);
    WyswietlInstrukcje(0);
    ZmienKolor(Kremowy, Czerwony);
    cout << char(vertical);
    for(int i = 0; i<IleKolumn; i++)
    {
        int n = (DlugosciKolumn[i]-(NaglowkiKolumn[i]).length())/2;
        for(int k = 0; k<n; k++)
            cout << " ";
        if((NaglowkiKolumn[i].length()%2 == 1))
           cout << " ";
        cout << NaglowkiKolumn[i];
        for(int k = 0; k<n; k++)
            cout << " ";
        cout << char(vertical);
    }
    WyswietlInstrukcje(0);
    if(CzySaJakiesDane)
    {
        ZmienKolor(Kremowy, Czerwony);
        cout << char(middle_vertical_left);
        for(int i = 0; i<IleKolumn; i++)
        {
            for(int j = 0; j<DlugosciKolumn[i]; j++)
                cout << char(horizontal);

            if(i!=IleKolumn-1)
                cout << char(middle);
        }
        cout << char(middle_vertical_right);
        WyswietlInstrukcje(0);
        ZmienKolor(Czarny, Bialy);
    }
    else
    {
        ZmienKolor(Kremowy, Czerwony);
        cout << char(down_left);
        for(int i = 0; i<IleKolumn; i++)
        {
            for(int j = 0; j<DlugosciKolumn[i]; j++)
                cout << char(horizontal);

            if(i!=IleKolumn-1)
                cout << char(middle_horizonal_down);
        }
        cout << char(down_right);
        ZmienKolor(Czarny,Bialy);
        WyswietlInstrukcje(0);
        for(int m = 1; m<21; m++)
        {
            for(int c = 0; c<=SzerokoscBazy; c++)
                cout << " ";
            WyswietlInstrukcje(2*m-1);
            for(int c = 0; c<=SzerokoscBazy; c++)
                cout << " ";
            WyswietlInstrukcje(2*m);
        }
}
}

void Display::WyswietlRekord(int numer, int Strona, Team team, bool CzyOstatni,bool CzyWyrozniony)
{
    if(CzyWyrozniony)
    {
        if(numer%2)
            ZmienKolor(CiemnyBialy, CiemnyZielony);
        else
            ZmienKolor(CiemnyBialy,CiemnyNiebieski);
    }
    else
    {
        if(numer%2)
            ZmienKolor(Bialy, CiemnyZielony);
        else
            ZmienKolor(Bialy,CiemnyNiebieski);
    }


    cout << char(vertical);

    int n = (DlugosciKolumn[0]-(to_string(numer)).length())/2;
    for(int k = 0; k<n; k++)
        cout << " ";
    cout << numer;
    for(int k = 0; k<n; k++)
        cout << " ";
    if(((to_string(numer)).length())%2 == 1)
        cout << " ";
    cout << char(vertical);

    n = (DlugosciKolumn[1]-team.Nazwa.length())/2;
    for(int k = 0; k<n; k++)
        cout << " ";
    cout << team.Nazwa;
    for(int k = 0; k<n; k++)
        cout << " ";
    if(team.Nazwa.length()%2 == 1)
        cout << " ";
    cout << char(vertical);

    n = (DlugosciKolumn[2]-team.Kraj.length())/2;
    for(int k = 0; k<n; k++)
        cout << " ";
    cout << team.Kraj;
    for(int k = 0; k<n; k++)
        cout << " ";
    if(team.Kraj.length()%2 == 1)
        cout << " ";
    cout << char(vertical);

    n = (DlugosciKolumn[3]-to_string(team.Ocena).length())/2;
    for(int k = 0; k<n; k++)
        cout << " ";
    cout << team.Ocena;
    for(int k = 0; k<n; k++)
        cout << " ";
    if(to_string(team.Ocena).length()%2 == 1)
        cout << " ";
    cout << char(vertical);

    n = (DlugosciKolumn[4]-to_string(team.Wygrane).length())/2;
    for(int k = 0; k<n; k++)
        cout << " ";
    cout << team.Wygrane;
    for(int k = 0; k<n; k++)
        cout << " ";
    if(to_string(team.Wygrane).length()%2 == 1)
        cout << " ";
    cout << char(vertical);

    n = (DlugosciKolumn[5]-to_string(team.Remisy).length())/2;
    for(int k = 0; k<n; k++)
        cout << " ";
    cout << team.Remisy;
    for(int k = 0; k<n; k++)
        cout << " ";
    if(to_string(team.Remisy).length()%2 == 1)
        cout << " ";
    cout << char(vertical);

    n = (DlugosciKolumn[6]-to_string(team.Przegrane).length())/2;
    for(int k = 0; k<n; k++)
        cout << " ";
    cout << team.Przegrane;
    for(int k = 0; k<n; k++)
        cout << " ";
    if(to_string(team.Przegrane).length()%2 == 1)
        cout << " ";
    cout << char(vertical);

    n = (DlugosciKolumn[7]-5)/2;
    for(int k = 0; k<=n; k++)
        cout << " ";
    cout << team.OstatniMecz << "-" << team.PrzedOstatniMecz << "-" << team.PrzedPrzedOstatniMecz;
    for(int k = 0; k<n; k++)
        cout << " ";
    cout << char(vertical);

    WyswietlInstrukcje(2*((numer-20*(Strona-1)))-1);

    if(numer%2)
            ZmienKolor(Bialy, CiemnyZielony);
        else
            ZmienKolor(Bialy,CiemnyNiebieski);

    if(CzyOstatni)
    {
        cout << char(down_left);
        for(int i = 0; i<IleKolumn; i++)
        {
            for(int j = 0; j<DlugosciKolumn[i]; j++)
                cout << char(horizontal);
            if(i!=IleKolumn-1)
                cout << char(middle_horizonal_down);
        }
        cout << char(down_right);

        WyswietlInstrukcje(2*(numer-20*(Strona-1)));

        if(((numer-(Strona-1)*20)%40)<15)
        {
            for(int m = ((numer-(Strona-1)*20)%21); m<20; m++)
            {
                for(int c = 0; c<=SzerokoscBazy; c++)
                    cout << " ";
                WyswietlInstrukcje(2*m-1);
                for(int c = 0; c<=SzerokoscBazy; c++)
                    cout << " ";
                WyswietlInstrukcje(2*m);
            }
        }


        ZmienKolor(Czarny, Bialy);
    }
    else
    {
        cout << char(middle_vertical_left);
        for(int i = 0; i<IleKolumn; i++)
        {
            for(int j = 0; j<DlugosciKolumn[i]; j++)
                cout << char(horizontal);
            if(i!=IleKolumn-1)
                cout << char(middle);
        }
        cout << char(middle_vertical_right);
        WyswietlInstrukcje(2*((numer-20*(Strona-1))));
        ZmienKolor(Czarny, Bialy);
    }


}

void Display::WyswietlInstrukcje(int k)
{
    if(k>30)
        k = 0;

    string instrukcje[] =  {"", "###################################################################",
                                 "                        KLAWISZE FUNKCYJNE                         ",
                                 "###################################################################",
                                 "",
                                 "  PRZESUN KURSOR W GORE                                  ARROW UP  ",
                                 "  PRZESUN KURSOR W DOL                                 ARROW DOWN  ",
                                 "  DODAJ NOWY REKORD                                        INSERT  ",
                                 "  DODAJ REKORDY Z PLIKU                                       'J'  ",
                                 "  USUN REKORD                                              DELETE  ",
                                 "  EDYTUJ REKORD                                               'E'  ",
                                 "  ZATWIERDZ                                                 ENTER  ",
                                 "  ZACZNIJ ZAZNACZAC KILKA                                   SHIFT  ",
                                 "  SORTUJ BAZE PO...                                           'S'  " ,
                                 "  CZY BAZA ZAWIERA DRUZYNE...?                                'Z'  ",
                                 "  WYSWIETL REKORDY ZAWIERAJACE...                             'W'  ",
                                 "  FUNKCJA MATEMATYCZNA                                        'F'  ",
                                 "",
                                 "  ZAPISZ BAZE DO PLIKU                                        'P'  ",
                                 "  OTWORZ ISTNIEJACA BAZE Z PLIKU                              'O'  ",
                                 "",
                                 "  DODAJ REZULTAT ZAKONCZONEGO MECZU                           'D'  ",
                                 "  DODAJ REZULTATY ZAKONCZONYCH MECZOW Z PLIKU                 'A'  ",
                                 "",
                                 "  NASTEPNA STRONA(JESLI ISTNIEJE)                             'M'  ",
                                 "  POPRZEDNIA STRONA(JESLI ISTNIEJE)                           'N'  ",
                                 "  WYJSCIE DO MENU                                             'Q'  ",
                                 "",
                                 "###################################################################",
                                 "                        KLAWISZE FUNKCYJNE                         ",
                                 "###################################################################",
                                 };

    ZmienKolor(Czarny, Czarny);
    cout << char(vertical) << char(vertical);
    ZmienKolor(Bialy, Fioletowy);
    cout << instrukcje[k];
    ZmienKolor(Czarny, Bialy);
    cout << endl;
}

void Display::WyswietlNumerStrony(int s)
{
    ZmienKolor(Czarny, Zolty);
    string napis = "Strona " + to_string(s);

    int n = (SzerokoscBazy-napis.length())/2;

    for(int i = 0; i<n; i++)
        cout << " ";
    cout << napis;
    for(int i = 0; i<=n; i++)
        cout << " ";
    ZmienKolor(Czarny, Czarny);
    cout << "znalazles" << endl;
}

void Display::KolorNormalny()
{
    ZmienKolor(Czarny, Bialy);
}




