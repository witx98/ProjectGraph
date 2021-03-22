#include "../Graf.h"
#pragma once

using namespace std;

void graf::Graf::polaczenia_i_wagi_modulow()
{
	//modul_przeszukiwany - jego polaczen szukamy obecnie
	//modul_sprawdzany - z nim szukamy polaczen dla przeszukiwanego

	int licznik_polaczen = 0;
	int licznik_test = 0;

	for (unsigned int modul_przeszukiwany = 0; modul_przeszukiwany < przestrzenie_nazw.size(); modul_przeszukiwany++)
	{
		for (unsigned int modul_sprawdzany = 0; modul_sprawdzany < przestrzenie_nazw.size(); modul_sprawdzany++)
		{
			if (modul_przeszukiwany != modul_sprawdzany)// Nie sprawdza sam siebie
			{
				for (unsigned int i = 0; i < przestrzenie_nazw[modul_przeszukiwany].funkcje_modulu.size(); i++)
				{
					for (unsigned int j = 0; j < przestrzenie_nazw[modul_przeszukiwany].funkcje_modulu[i].polaczenia_miedzy_funkcjami.size(); j++)
					{
						for (unsigned int k = 0; k < przestrzenie_nazw[modul_sprawdzany].funkcje_modulu.size(); k++)
						{
							if (przestrzenie_nazw[modul_przeszukiwany].funkcje_modulu[i].polaczenia_miedzy_funkcjami[j].nazwa_polaczonego_elementu == przestrzenie_nazw[modul_sprawdzany].funkcje_modulu[k].nazwa_funkcji)
							{	
								licznik_polaczen = 0;
								if (przestrzenie_nazw[modul_przeszukiwany].polaczenia_miedzy_namespaceami.size() == 0)
								{
									przestrzenie_nazw[modul_przeszukiwany].polaczenia_miedzy_namespaceami.push_back(przestrzenie_nazw[modul_sprawdzany].nazwa_przestrzeni);
									przestrzenie_nazw[modul_przeszukiwany].polaczenia_miedzy_namespaceami[licznik_polaczen].waga++;
									//cout << przestrzenie_nazw[modul_przeszukiwany].nazwa_przestrzeni << " -> " << przestrzenie_nazw[modul_przeszukiwany].polaczenia_miedzy_namespaceami[licznik_polaczen].nazwa_polaczonego_elementu << endl;
									licznik_polaczen++;
								}
								else
								{
									for (unsigned int dodane_przestrzenie = 0; dodane_przestrzenie < przestrzenie_nazw[modul_przeszukiwany].polaczenia_miedzy_namespaceami.size(); dodane_przestrzenie++)
									{
										if (przestrzenie_nazw[modul_przeszukiwany].polaczenia_miedzy_namespaceami[dodane_przestrzenie].nazwa_polaczonego_elementu == przestrzenie_nazw[modul_sprawdzany].nazwa_przestrzeni)
										{
											licznik_test++;
											przestrzenie_nazw[modul_przeszukiwany].polaczenia_miedzy_namespaceami[licznik_polaczen].waga++;
											//cout << przestrzenie_nazw[modul_przeszukiwany].nazwa_przestrzeni << " -> " << przestrzenie_nazw[modul_przeszukiwany].polaczenia_miedzy_namespaceami[licznik_polaczen].nazwa_polaczonego_elementu << ", Waga:" << przestrzenie_nazw[modul_przeszukiwany].polaczenia_miedzy_namespaceami[licznik_polaczen].waga << endl;
										}
									}
									if (licznik_test == 0)
									{
										przestrzenie_nazw[modul_przeszukiwany].polaczenia_miedzy_namespaceami.push_back(przestrzenie_nazw[modul_sprawdzany].nazwa_przestrzeni);
										przestrzenie_nazw[modul_przeszukiwany].polaczenia_miedzy_namespaceami[licznik_polaczen].waga++;
										//cout << przestrzenie_nazw[modul_przeszukiwany].nazwa_przestrzeni << " -> " << przestrzenie_nazw[modul_przeszukiwany].polaczenia_miedzy_namespaceami[licznik_polaczen].nazwa_polaczonego_elementu << ", Waga:" << przestrzenie_nazw[modul_przeszukiwany].polaczenia_miedzy_namespaceami[licznik_polaczen].waga << endl;
										licznik_polaczen++;
									}
									
									licznik_test = 0;
								}
							}
						}
					}
				}
				
			}
		}
	}
}