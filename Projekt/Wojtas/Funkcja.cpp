#pragma once
#include "..\Graf.h"

void funkcja::Funkcja::znajdz_polaczone_funkcje(Funkcja sprawdzana_fun, std::fstream& otwarty_plik) {
	
	std::string szukany_string = Wojtas::odcinanie_poczatku(sprawdzana_fun.nazwa_funkcji, "::");
	std::string linia;
	int licznik = polaczenia_miedzy_funkcjami.size();
	int licznik_klamer = 0;
	while (getline(otwarty_plik, linia)) {
		if (linia.find(nazwa_funkcji) != std::string::npos)
		{
			//uzywane w ten sposob przed whilem i po whilu, w zaleznosci od tego jak kto daje klamry
			Wojtas::szukanie_klamer(linia, licznik_klamer);
		
			while (getline(otwarty_plik, linia)) {
				Wojtas::szukanie_klamer(linia, licznik_klamer);
				//wyjscie z szukania gdy zamknie sie funkcja
				if (licznik_klamer == 0) {
					return;
				}
				if (linia.find(szukany_string + "(") != std::string::npos) {
					if (polaczenia_miedzy_funkcjami.size() == licznik) {
						polaczenie::Polaczenie temp(sprawdzana_fun.nazwa_funkcji);
						polaczenia_miedzy_funkcjami.push_back(temp);
					}
					else {
						polaczenia_miedzy_funkcjami[licznik].waga += 1;
						
					}
				}
			}
		}
		Wojtas::szukanie_klamer(linia, licznik_klamer);
	}
}