#include "../Graf.h"
#include <sstream>
#pragma once

void graf::Graf::kopiowanie_do_funkcji()
{
	//dla elementów modu³u
	for (unsigned int i = 0; i < przestrzenie_nazw.size(); i++)
	{
		for (unsigned int j = 0; j < przestrzenie_nazw[i].funkcje_modulu.size(); j++)
		{
			for (unsigned int k = 0; k < wszystkie_funkcje_we_wszystkich_plikach.size(); k++)
			{
				if (przestrzenie_nazw[i].funkcje_modulu[j].nazwa_funkcji == wszystkie_funkcje_we_wszystkich_plikach[k].nazwa_funkcji)
				{
					przestrzenie_nazw[i].funkcje_modulu[j] = wszystkie_funkcje_we_wszystkich_plikach[k];
				}
			}
		}
	}

	//dla funkcji plików
	for (unsigned int i = 0; i < pliki.size(); i++)
	{
		for (unsigned int j = 0; j < pliki[i].funkcje.size(); j++)
		{
			for (unsigned int k = 0; k < wszystkie_funkcje_we_wszystkich_plikach.size(); k++)
			{
				if (pliki[i].funkcje[j].nazwa_funkcji == wszystkie_funkcje_we_wszystkich_plikach[k].nazwa_funkcji)
				{
					pliki[i].funkcje[j] = wszystkie_funkcje_we_wszystkich_plikach[k];
				}
			}
		}
	}

}

void graf::Graf::zlozonosc_na_stringa()
{
	std::ostringstream waga;

	for (unsigned int i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++)
	{
		waga << wszystkie_funkcje_we_wszystkich_plikach[i].zlozonosc;
		wszystkie_funkcje_we_wszystkich_plikach[i].zlozonosc_string = waga.str();
		waga.str("");
		waga.clear();
	}
}