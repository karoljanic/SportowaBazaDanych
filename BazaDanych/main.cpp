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

    Database data(7, "Baza danych klubow pilkarskich",  TytulyKolumn, true);

    data.Uruchom();




    return 0;
}

