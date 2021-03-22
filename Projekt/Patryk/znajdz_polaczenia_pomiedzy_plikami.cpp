#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "..\Graf.h"

using namespace std;

void graf::Graf::znajdz_polaczenia_pomiedzy_plikami()
{
	fstream otwarty_plik;
	string linia;
	//sprawdzam oba ukosniki bo dla obu sciezka jest prawidlowa 
	string ukosnik = "\\";
	string uko2 = "/";

	//w tej peli otwieramy wszystkie pliki po koleii do ostatniego
	for (int i = 0; i < pliki.size(); i++)
	{
		otwarty_plik.open("..\\temp\\" + pliki[i].nazwa_pliku, ios::in);

		//pobieramy linie z obecnie otwartego pliku
		while (getline(otwarty_plik, linia))
		{
			//warunek jest speliony jesi znajdzie include w linii 
				if (linia.find("#include") != string::npos)
				{
					vector <string> slowa = Wojtas::dzielenie_na_slowa(linia);
					for (unsigned int j = 0; j < slowa.size(); j++)
					{
						//sprawdzamy czy include sie konczy na cpp albo h
						if (( (slowa[j][slowa[j].size() - 2] == 'h')&&(slowa[j][slowa[j].size() - 1] == '\"') ) || ((slowa[j][slowa[j].size() - 2] == 'p') && (slowa[j][slowa[j].size() - 1] == '\"')))
						{
							//sprawdzamy czy ma scierzke z ukosnikami ( nie wiem jak to dokladnie opisac :D )
							if ( (slowa[j].find(ukosnik)) != std::string::npos )
							{
								string plik = slowa[j];
								Wojtas::wycinanie_rekurencyjne(&plik,ukosnik,TRUE);
								plik.erase(plik.size() - 1, plik.size());
								polaczenie::Polaczenie obiekt(plik);
								pliki[i].polaczenia_miedzy_plikami.push_back(obiekt);
							}
							else if ((slowa[j].find(uko2)) != std::string::npos)
							{
								string plik = slowa[j];
								Wojtas::wycinanie_rekurencyjne(&plik, uko2, TRUE);
								plik.erase(plik.size() - 1, plik.size());
								polaczenie::Polaczenie obiekt(plik);
								pliki[i].polaczenia_miedzy_plikami.push_back(obiekt);
							}
							else
							{
								string plik = slowa[j];
								plik.erase(0, 1);
								plik.erase(plik.size() - 1, plik.size());
								polaczenie::Polaczenie obiekt(plik);
								pliki[i].polaczenia_miedzy_plikami.push_back(obiekt);
							}
						}
					}
				}
		}
		//zamykamy obecnie otwarty plik
		otwarty_plik.close();
	}



	//sprawdzanie(wypisanie)
	/*
	for (int i = 0; i < pliki.size(); i++)
	{
		for (int j = 0; j < pliki[i].polaczenia_miedzy_plikami.size(); j++)
		{
			cout <<pliki[i].nazwa_pliku<<": " <<pliki[i].polaczenia_miedzy_plikami[j].nazwa_polaczonego_elementu << endl;
		}

	}
	*/
};