#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <conio.h>

#include "Team.h"
#include "Database.h"
#include "Display.h"

using namespace std;

int main()
{

    string TytulyKolumn[] = {"L.P.", "Nazwa klubu", "Kraj pochodzenia", "Ocena", "Wygrane", "Remisy", "Porazki", "Bilans spotkan"};
    Database data(7, "Baza danych klubow pilkarskich",  TytulyKolumn);
    data.WczytajZPlikuNoweTeamy("KilkaDanych.txt");

    char znak = 'x';
    data.Wyswietl();


    while(true)
    {
        znak = getch();
        if(znak == -32)
        {
            znak = getch();

            if(znak == 80)
            {
                if(data.PozycjaDol())
                    data.Wyswietl();
            }

            else if(znak == 72)
            {
                if(data.PozycjaGora())
                    data.Wyswietl();
            }

        }
        else if(znak == 'm' || znak=='M')
        {
         if(data.NastepnaStrona())
            data.Wyswietl();
        }
        else if(znak == 'n' || znak == 'N')
        {
            if(data.PoprzedniaStrona())
                data.Wyswietl();
        }
        else if(znak == 'q' || znak == 'Q')
        {
            data.Zakoncz();
            return 0;
        }

    }

}

