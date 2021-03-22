#pragma once
#include "..\Graf.h"



void graf::Graf::znajdz_elementy_przestrzeni_nazw() {
	for (auto &_przestrzen : przestrzenie_nazw) {
		if (_przestrzen.nazwa_przestrzeni == "std") {
			_przestrzen.elementy_modulu = { "string", "ios", "cout",
				"endl", "list", "stringstream", "ofstringstream", "fstream" };
		}
		else {
			for (auto& _aktualny_plik : pliki) {
				fstream otwarty_plik;
				for (auto& _aktualny_modul : przestrzenie_nazw) {
				otwarty_plik.open("..\\temp\\" + _aktualny_plik.nazwa_pliku, std::ios::in);
				_aktualny_modul.znajdz_elementy_modulu(otwarty_plik);
				otwarty_plik.close();
				}
			}
			
		}
	}
}
