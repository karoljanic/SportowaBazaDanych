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

    char znak = 'x';
    string sciezka = "";
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
            else if(znak == 82)
            {
                system("cls");
                data.DodajTeam();
                data.Wyswietl();
            }
            else if(znak == 83)
            {
                if(data.LiczbaRekordow == 0)
                {
                    system("cls");
                    cout << "Nie ma czego usunac! Aby kontynuowac wcisnij ENTER!";
                    while(znak!=13)
                        znak = getch();
                }
                else
                {
                    system("cls");
                    data.UsunTeam();
                }

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
        else if(znak == 'e' || znak == 'E')
        {
            system("cls");
            znak = 0;
            if(data.LiczbaRekordow == 0)
            {
                cout << "Nie mozesz edytowac nieistniejach rekordow! Aby kontynuowac wcisnij ENTER!";
                char znak = 0;
                while(znak!=13)
                    znak = getch();
                data.Wyswietl();
                continue;
            }
            cout << "Ktora kolumne edytowac?<1,7>";
            int k;
            k = getch();
            k -= '0';
            if(k>0 && k<8)
            {
               data.EdytujTeam(k);
               k = -1;
            }

            else
            {
                cout << "Niepoprawny numer kolumny! Aby kontynuowac wcisnij ENTER!";
                char znak = 0;
                while(znak != 13)
                    znak = getch();
            }
            data.Wyswietl();
        }
        else if(znak == 'j' || znak == 'J')
        {
            system("cls");
            sciezka = "";
            cout << "Wprowadz sciezke dostepu do pliku z danymi lub nazwe pliku jesli znajduje sie on w folderze programu(nazwa_pliku.txt) ";
            while(sciezka=="")
                cin >> sciezka;

            data.WczytajZPlikuNoweTeamy(sciezka);
            data.Wyswietl();
        }
        else if(znak == 'o' || znak == 'O')
        {
            system("cls");
            sciezka = "";
            cout << "Wprowadz sciezke dostepu do pliku z danymi lub nazwe pliku jesli znajduje sie on w folderze programu(nazwa_pliku.txt) ";
            while(sciezka=="")
                cin >> sciezka;
            data.OtworzBazeZPliku(sciezka);
            data.Wyswietl();
        }
        else if(znak == 'p' || znak == 'P')
        {
            system("cls");
            string nazwa = "";
            cout << "Wprowadz nazwe wyjsciowego pliku: ";
            while(nazwa == "")
                cin >> nazwa;
            data.ZapiszWPlikuBaze(nazwa);
            data.Wyswietl();
        }
        else if(znak == 'd' || znak == 'D')
        {
            system("cls");
            data.DodajMecz();
            data.Wyswietl();
        }
        else if(znak == 'a' || znak == 'A')
        {
            system("cls");
            sciezka = "";
            cout << "Wprowadz sciezke dostepu do pliku z danymi lub nazwe pliku jesli znajduje sie on w folderze programu(nazwa_pliku.txt) ";
            while(sciezka=="")
                cin >> sciezka;
            system("cls");
            data.WczytaZPlikuMecze(sciezka);
            data.Wyswietl();
        }

    }

/*
    while(1)
    {
        znak = getch();
        cout << int(znak) << "   ";
    }*/
}

