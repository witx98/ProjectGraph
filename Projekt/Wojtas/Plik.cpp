#pragma once
#include "..\Graf.h"
#include <string>



void plik::Plik::znajdz_funkcje_w_pliku() {
	std::vector<std::string> module_keywords = { "class", "namespace", "struct" };
	std::vector<std::string> key_words{ "int", "void", "string", "vector", "bool","double"};
	std::vector<std::string> przedrostki{ "inline", "const" };
	std::fstream plik_operacyjny;
	std::string linia;
	std::string slowo = "";
	plik_operacyjny.open("..\\temp\\" + nazwa_pliku, std::ios::in);
	while (!plik_operacyjny.eof()) {
		getline(plik_operacyjny, linia);
		std::vector<std::string> slowa_linijki = Wojtas::dzielenie_na_slowa(linia);
		int i = 0;
		int licznik = 0;
		//przechodzenie przez slowa typu const i inline
		while(i < slowa_linijki.size()) {
			for (auto& _przed : przedrostki) {
				if (slowa_linijki[i].find(_przed) == std::string::npos) {
					licznik++;
				}
			}
			if (licznik == przedrostki.size())
				break;
			else
				i++;
		}

		for (auto& _key : key_words) {
			if (slowa_linijki[i].find(_key) != std::string::npos) {
				if(i+1<slowa_linijki.size()){
					if (slowa_linijki[i+1].find("(") != std::string::npos) {
						std::string nazwa = Wojtas::odcinanie_koncowki(slowa_linijki[i+1], "(");
						nazwa = Wojtas::odcinanie_poczatku(nazwa, "::");
						dodaj_niepowtarzajaca_sie_funkcje(nazwa);
						
					}
				}
			}
		}

		/*std::vector<std::string> slowa_linijki = Wojtas::dzielenie_na_slowa(linia);
		int i = 0;
		for (auto& _przedrostek : przedrostki) {
			if (slowa_linijki[i].find(_przedrostek)!=std::string::npos)
				i += 1;
		}
		
		for (auto& _slowo_kluczowe : key_words) {			
			if (slowa_linijki[i].find(_slowo_kluczowe)!=std::string::npos) {
				if (slowa_linijki[i+1].find("(") != std::string::npos &&i+1<slowa_linijki.size()) {
					std::string nazwa = Wojtas::odcinanie_koncowki(slowa_linijki[i], "(");
					nazwa = Wojtas::odcinanie_poczatku(nazwa, "::");
					dodaj_niepowtarzajaca_sie_funkcje(nazwa);
				}
			}			
		}*/
		
		
	}

	plik_operacyjny.close();
}



void plik::Plik::dodaj_niepowtarzajaca_sie_funkcje(std::string nazwa) {
	int licznik_spr = 0;
	for (auto& fun : funkcje) {
		if (fun.nazwa_funkcji != nazwa) {
			licznik_spr++;
		}
	}
	if (licznik_spr == funkcje.size()) {
		funkcje.push_back(nazwa);
	}
}

void plik::Plik::znajdz_moduly() {
	
	std::fstream otwarty_plik;
	std::string linia;
	otwarty_plik.open("..\\temp\\" + nazwa_pliku, std::ios::in);
	while (!otwarty_plik.eof()) {
		getline(otwarty_plik, linia);

		std::vector<std::string> slowa_w_linii = Wojtas::dzielenie_na_slowa(linia); //dla dokladniejszego przeszukiwania
		slowa_w_linii[0] = Wojtas::usuwanie_tabulacji(slowa_w_linii[0]);

		for (int aktualne_slowo = 0; aktualne_slowo < slowa_w_linii.size(); ++aktualne_slowo) {
			if (slowa_w_linii[aktualne_slowo] == "namespace") {									//szukanie definicji namespace
				if (aktualne_slowo + 1 < slowa_w_linii.size()) {
					std::string nazwa_slowa;
					if (slowa_w_linii[aktualne_slowo + 1].find(";") != std::string::npos) {
						nazwa_slowa = Wojtas::odcinanie_koncowki(slowa_w_linii[aktualne_slowo + 1], ";");
						/*size_t pos = slowa_w_linii[aktualne_slowo + 1].find(";");
						nazwa_slowa = slowa_w_linii[aktualne_slowo + 1].substr(0, pos);		*/
					}
					else if (slowa_w_linii[aktualne_slowo + 1].find("{") != std::string::npos) {
						nazwa_slowa = Wojtas::odcinanie_koncowki(slowa_w_linii[aktualne_slowo + 1], "{");
					}
					else {
						nazwa_slowa = slowa_w_linii[aktualne_slowo + 1];																		// licznik sluzy do sprawdzania powtarzania naz
					}
					int licznik = 0;
					for (int i = 0; i < namespacey.size(); i++) {
						if (namespacey[i].nazwa_przestrzeni != nazwa_slowa)
							licznik++;
					}
					if (licznik == namespacey.size()) {
						if (nazwa_slowa != "std") {
							modul::Modul wchodzaca_przestrzen(nazwa_slowa);
							namespacey.push_back(wchodzaca_przestrzen);
						}
					}
					break;
				}
			}
		}
	}
	otwarty_plik.close();
}