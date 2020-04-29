#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>

#include "Team.h"
#include "Database.h"
#include "Display.h"

///------------------------------------- *** BEGIN *** KONSTRUKTOR ***BEGIN*** ----------------------------------------///
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
///--------------------------------------- *** END *** KONSTRUKTOR ***END*** ------------------------------------------///



///------------------------------------- *** BEGIN *** DESTRUKTOR ***BEGIN*** ----------------------------------------///
Display::~Display()
{

}

///--------------------------------------- *** END *** DESTRUKTOR ***END*** ------------------------------------------///


///------------------------------------ *** BEGIN *** ENUM COLORS ***BEGIN*** --------------------------------------///
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
///------------------------------------- *** END *** ENUM COLORS ***END*** -----------------------------------------///



///------------------------------------ *** BEGIN *** ZMIEN KOLOR ***BEGIN*** --------------------------------------///
void ZmienKolor(colors tlo, colors tekst)
{
    int k = tlo*16 + tekst;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k );
}
///-------------------------------------- *** END *** ZMIEN KOLOR ***END*** ----------------------------------------///



///------------------------------------ *** BEGIN *** ENUM LINES ***BEGIN*** --------------------------------------///
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
///--------------------------------------- *** END *** ENUM LINES ***END*** ---------------------------------------///



///----------------------------- *** BEGIN *** PUBLIC WYSWIETLTYTULBAZY() ***BEGIN*** --------------------------------///
void Display::WyswietlTytulBazy(string nazwa)
{
    KtoraInstrukcja = 0;
    ZmienKolor(Zolty,Czarny);
    for(int i = 0; i<=SzerokoscBazy; i++)
        cout << char(horizontal);
    WyswietlInstrukcje(0, 1);
    ZmienKolor(Zolty,Czarny);
    int n = (SzerokoscBazy-nazwa.length())/2;
    for(int i = 0; i<n; i++)
        cout << "*";
    cout << nazwa;
    for(int i = 0; i<=n; i++)
        cout << "*";
    WyswietlInstrukcje(0,1);
    ZmienKolor(Zolty,Czarny);
    for(int i = 0; i<=SzerokoscBazy; i++)
        cout << char(horizontal);
    ZmienKolor(Czarny,Bialy);
    WyswietlInstrukcje(0,1);

}
///------------------------------- *** END *** PUBLIC WYSWIETLTYTULBAZY() ***END*** ----------------------------------///



///----------------------------- *** BEGIN *** PUBLIC WYSWIETLNAGLOWEK() ***BEGIN*** --------------------------------///
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
    WyswietlInstrukcje(0,1);
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
    WyswietlInstrukcje(0,1);
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
        WyswietlInstrukcje(0,1);
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
        WyswietlInstrukcje(0,1);
        for(int m = 1; m<21; m++)
        {
            for(int c = 0; c<=SzerokoscBazy; c++)
                cout << " ";
            WyswietlInstrukcje(2*m-1,1);
            for(int c = 0; c<=SzerokoscBazy; c++)
                cout << " ";
            WyswietlInstrukcje(2*m,1);
        }
    }
}
///------------------------------- *** END *** PUBLIC WYSWIETLNAGLOWEK() ***END*** ----------------------------------///



///------------------------------ *** BEGIN *** PUBLIC WYSWIETLREKORD() ***BEGIN*** ---------------------------------///
void Display::WyswietlRekord(int numer, int Strona, Team team, bool CzyOstatni,bool CzyWyrozniony, int p)
{

    int s = Rekordy/20;
    if(Rekordy%20)
        s++;

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

    WyswietlInstrukcje(2*((numer-20*(Strona-1)))-1,p);

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

        WyswietlInstrukcje(2*(numer-20*(Strona-1)),p);

        if(((numer-(Strona-1)*20)%40)<15)
        {
            for(int m = ((numer-(Strona-1)*20)%21); m<20; m++)
            {
                for(int c = 0; c<=SzerokoscBazy; c++)
                    cout << " ";
                WyswietlInstrukcje(2*m-1,p);
                for(int c = 0; c<=SzerokoscBazy; c++)
                    cout << " ";
                WyswietlInstrukcje(2*m,p);
            }
            ZmienKolor(Czarny, Bialy);

        }
        else if(Strona == s)
        {
            int h = Rekordy%20;
            if(h>14)
            {
                for(int i = 0; i<(20-h)*2; i++)
                    cout << endl;
            }
        }
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
        WyswietlInstrukcje(2*((numer-20*(Strona-1))),p);
        ZmienKolor(Czarny, Bialy);

    }
}
///-------------------------------- *** END *** PUBLIC WYSWIETLREKORD() ***END*** -----------------------------------///



///---------------------------- *** BEGIN *** PUBLIC WYSWIETLNUMERSTRONY() ***BEGIN*** ------------------------------///
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
///------------------------------ *** END *** PUBLIC WYSWIETLNUMERSTRONY() ***END*** --------------------------------///



///----------------------------- *** BEGIN *** PUBLIC KOLORNORMALNY() ***BEGIN*** -----------------------------------///
void Display::KolorNormalny()
{
    ZmienKolor(Czarny, Bialy);
}
///-------------------------------- *** END *** PUBLIC KOLORNORMALNY() ***END*** ------------------------------------///



///----------------------------- *** BEGIN *** PRIVATE WYSWIETLINSTRUKCJE() ***BEGIN*** ----------------------------------///
void Display::WyswietlInstrukcje(int k, int n)
{
    if(k>30)
        k = 0;

    string instrukcje1[] =  {"",  "###################################################################",
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
                                 "  ZACZNIJ ZAZNACZAC KILKA                                     'R'  ",
                                 "  SORTUJ BAZE PO...                                           'S'  ",
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
                                 "  NASTEPNA STRONA                                             'M'  ",
                                 "  POPRZEDNIA STRONA                                           'N'  ",
                                 "  WYJSCIE DO MENU                                             'Q'  ",
                                 "",
                                 "###################################################################",
                                 "                        KLAWISZE FUNKCYJNE                         ",
                                 "###################################################################",
                                 };

    string instrukcje2[] =  {"",  "###################################################################",
                                 "                        KLAWISZE FUNKCYJNE                         ",
                                 "###################################################################",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "  PRZESUN KURSOR W GORE                                  ARROW UP  ",
                                 "  PRZESUN KURSOR W DOL                                 ARROW DOWN  ",
                                 "  USUN REKORD                                              DELETE  ",
                                 "  EDYTUJ REKORD                                               'E'  ",
                                 "  ZAKONCZ NIE WPROWADZAJAC ZMIAN                            ENTER  ",
                                 "  ZAPISZ DO PLIKU                                             'P'  ",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "###################################################################",
                                 "                        KLAWISZE FUNKCYJNE                         ",
                                 "###################################################################",
                                 };

    string instrukcje3[] =  {"",  "###################################################################",
                                 "                        KLAWISZE FUNKCYJNE                         ",
                                 "###################################################################",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "  PRZESUN KURSOR W GORE                                  ARROW UP  ",
                                 "  PRZESUN KURSOR W DOL                                 ARROW DOWN  ",
                                 "  SORTUJ BAZE PO...                                           'S'  ",
                                 "  CZY BAZA ZAWIERA DRUZYNE...?                                'Z'  ",
                                 "  FUNKCJA MATEMATYCZNA                                        'F'  ",
                                 "  ZAPISZ DO PLIKU                                             'P'  ",
                                 "  NASTEPNA STRONA                                             'M'  ",
                                 "  POPRZEDNIA STRONA                                           'N'  ",
                                 "  WYJSCIE DO BAZY GLOWNEJ                                     'Q'  ",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "",
                                 "###################################################################",
                                 "                        KLAWISZE FUNKCYJNE                         ",
                                 "###################################################################",
                                 };

    ZmienKolor(Czarny, Czarny);
    cout << char(vertical) << char(vertical);
    ZmienKolor(Bialy, Fioletowy);
    switch(n)
    {
        case 1:
        {
            cout << instrukcje1[k];
            break;
        }
        case 2:
        {
            cout << instrukcje2[k];
            break;
        }
        case 3:
        {
            cout << instrukcje3[k];
            break;
        }
    }
    ZmienKolor(Czarny, Bialy);
    cout << endl;
}
///-------------------------------- *** END *** PRAVATE WYSWIETLINSTRUKCJE() ***END*** -----------------------------------///








