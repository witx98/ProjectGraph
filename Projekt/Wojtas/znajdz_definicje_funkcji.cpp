#pragma once
#include "..\Graf.h"


void graf::Graf::znajdz_definicje_funkcji() {
	for (auto &_ktory_plik : pliki) {
		
		_ktory_plik.znajdz_funkcje_w_pliku();

		for (const auto& _funkcja_pliku : _ktory_plik.funkcje) {
			unsigned int licznik_spr = 0;
			//za pomoca tego licznika sprawdzam, ilosc NIEwystepowania tej nazwy w vectorze, przez co wiadomo kiedy push_backowac
			//dodaje funkcje znalezioan w piku do zbioru wszystkich funkcji programu
			for (auto& nr_funkcji : wszystkie_funkcje_we_wszystkich_plikach) {
				if (_funkcja_pliku.nazwa_funkcji != nr_funkcji.nazwa_funkcji)
					licznik_spr++;			
			}
			if (licznik_spr >= wszystkie_funkcje_we_wszystkich_plikach.size()) {

				wszystkie_funkcje_we_wszystkich_plikach.push_back(_funkcja_pliku.nazwa_funkcji);
			}
		}	
	}
}
