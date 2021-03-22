#pragma once
#include"..\Graf.h"
#include<sstream>

using namespace std;


string graf::Graf::przygotuj_txt_dla_funkcji_do_visual_paradigma()
{
	std::string strzalka = "->";
	std::string temp;
	std::string tekst;
	std::ostringstream waga_polaczenia;		//definiuje przed bo po co definiowac to samo wiele razy
	string zlozonosc;

	for (size_t i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++)
	{
		//std::cout << wszystkie_funkcje_we_wszystkich_plikach[i].nazwa_funkcji << endl;
		for (size_t j = 0; j < wszystkie_funkcje_we_wszystkich_plikach[i].polaczenia_miedzy_funkcjami.size(); j++)
		{
			if (wszystkie_funkcje_we_wszystkich_plikach[i].polaczenia_miedzy_funkcjami[j].waga != 0)
			{
				for (int k = 0; k < wszystkie_funkcje_we_wszystkich_plikach.size(); k++) {
					if (wszystkie_funkcje_we_wszystkich_plikach[k].nazwa_funkcji == wszystkie_funkcje_we_wszystkich_plikach[i].polaczenia_miedzy_funkcjami[j].nazwa_polaczonego_elementu) {
						zlozonosc = wszystkie_funkcje_we_wszystkich_plikach[k].zlozonosc_string;
					}
				}
				//std::cout << wszystkie_funkcje_we_wszystkich_plikach[i].nazwa_funkcji << endl;
				waga_polaczenia << wszystkie_funkcje_we_wszystkich_plikach[i].polaczenia_miedzy_funkcjami[j].waga;
				std::string sila_polaczenia = waga_polaczenia.str();
				waga_polaczenia.str("");
				waga_polaczenia.clear();


				temp += wszystkie_funkcje_we_wszystkich_plikach[i].nazwa_funkcji + "(" + wszystkie_funkcje_we_wszystkich_plikach[i].zlozonosc_string + ")" + strzalka + wszystkie_funkcje_we_wszystkich_plikach[i].polaczenia_miedzy_funkcjami[j].nazwa_polaczonego_elementu + "(" + zlozonosc + ")" + " : [" + sila_polaczenia + "]\n";

			}
		}
	}

	tekst = temp;		//zawsze zamykajcie nawiasy klamrowe :D

	//std::cout << tekst; 		//tescik

	fstream plik_do_zapisu;
	plik_do_zapisu.open("..\\output\\do_paradigma\\funkcje.txt", ios::out);
	if (plik_do_zapisu.good())
	{
		plik_do_zapisu << tekst;
	}
	plik_do_zapisu.close();

	return tekst;
}


string graf::Graf::przygotuj_txt_dla_plikow_do_visual_paradigma()
{
	string strzala = "->";
	string temp;
	string tekst;
	//std::string liczba;

	ostringstream ss;	//plik.ilosc_linijek_kodu	
	ostringstream ss2;	//dla obydwu
	ostringstream ss3;	//dla wagi polaczenia

	for (size_t i = 0; i < pliki.size(); i++)	//pierwszy plik
	{
		ss << pliki[i].ilosc_linijek_kodu;
		std::string ilosc_lini_pierwszego_pliku = ss.str();
		ss.str("");
		ss.clear();

		for (size_t j = 0; j < pliki[i].polaczenia_miedzy_plikami.size(); j++)		//porownywanie z kazdym innym po kolei		
		{
			if (pliki[i].polaczenia_miedzy_plikami[j].waga != 0)	//zeby nie sparwdzalo dla samego sb(xD)		trzeba dodac warunek ze jak bd waga polaczenia 0 to zeby nie wchodzilo do ifa(xD) - TEN IF JEST WGL NIE POTRZEBNY JAK COS
			{
				std::string ilosc_linii_drugiego_pliku;

				for (int k = 0; k < pliki.size(); k++) {
					if (pliki[k].nazwa_pliku == pliki[i].polaczenia_miedzy_plikami[j].nazwa_polaczonego_elementu) {
						ss2 << pliki[k].ilosc_linijek_kodu;
						ilosc_linii_drugiego_pliku = ss2.str();
						ss2.str("");
						ss2.clear();
					}
				}

				ss3 << pliki[i].polaczenia_miedzy_plikami[j].waga;
				std::string sila_polaczenia = ss3.str();
				ss3.str("");
				ss3.clear();
				temp += pliki[i].nazwa_pliku + "(" + ilosc_lini_pierwszego_pliku + ")" + strzala + pliki[i].polaczenia_miedzy_plikami[j].nazwa_polaczonego_elementu + "(" + ilosc_linii_drugiego_pliku + ")" + " : [" + sila_polaczenia + "]\n";
				//std::cout << temp << endl;
			}
		}
	}
	tekst = temp;	//trzeba pamietac o zamknieciu nawiasu klamrowego

	//std::cout << tekst << endl;		//tescik

	fstream plik_do_zapisu;
	plik_do_zapisu.open("..\\output\\do_paradigma\\pliki.txt", ios::out);
	if (plik_do_zapisu.good())
	{
		plik_do_zapisu << tekst;
	}

	plik_do_zapisu.close();

	return tekst;

}


string graf::Graf::przygotuj_txt_dla_modulu_do_visual_paradigma()
{
	std::string strzalka = "->";
	std::string temp = "";
	std::string tekst;
	std::string sila_polaczenia = "999";
	std::ostringstream waga_polaczenia;


	for (unsigned int i = 0; i < przestrzenie_nazw.size(); i++)
	{
		for (unsigned int j = 0; j < przestrzenie_nazw[i].polaczenia_miedzy_namespaceami.size(); j++)
		{
			waga_polaczenia << przestrzenie_nazw[i].polaczenia_miedzy_namespaceami[j].waga;
			std::string sila_polaczenia = waga_polaczenia.str();
			waga_polaczenia.str("");
			waga_polaczenia.clear();

			temp += przestrzenie_nazw[i].nazwa_przestrzeni + strzalka + przestrzenie_nazw[i].polaczenia_miedzy_namespaceami[j].nazwa_polaczonego_elementu + " : [" + sila_polaczenia + "]\n";
		}
	}
	tekst = temp;
	//std::cout << tekst;

	fstream plik_do_zapisu;
	plik_do_zapisu.open("..\\output\\do_paradigma\\moduly.txt", ios::out);
	if (plik_do_zapisu.good())
	{
		plik_do_zapisu << tekst;
	}
	plik_do_zapisu.close();

	return tekst;
}


string graf::Graf::przygotuj_txt_dla_modulow_i_funkcji_do_visual_paradigma(string moduly_txt, string funkcje_txt)
{
	string trzecia_czesc_stringa;
	string temp;
	ostringstream ss;

	for (unsigned int i = 0; i < przestrzenie_nazw.size(); i++)
	{
		for (unsigned int j = 0; j < przestrzenie_nazw[i].funkcje_modulu.size(); j++)
		{
			temp = przestrzenie_nazw[i].funkcje_modulu[j].nazwa_funkcji + "(" + przestrzenie_nazw[i].funkcje_modulu[j].zlozonosc_string + ")" + "->" + przestrzenie_nazw[i].nazwa_przestrzeni + "\n";
			trzecia_czesc_stringa = trzecia_czesc_stringa + temp;
		}

	}
	string scalone =  moduly_txt + funkcje_txt + trzecia_czesc_stringa;
	
	fstream plik_do_zapisu;
	plik_do_zapisu.open("..\\output\\do_paradigma\\moduly_i_funkcje.txt", ios::out);
	if (plik_do_zapisu.good())
	{
		plik_do_zapisu << scalone;
	}
	plik_do_zapisu.close();

	return scalone;
}


string graf::Graf::przygotuj_txt_dla_plikow_i_funkcji_do_visual_paradigma(string pliki_txt, string funkcje_txt)
{
	string polaczenia_miedzy_funkcjami_a_plikiami;
	string temp;
	ostringstream ss;

	for (unsigned int i = 0; i < pliki.size(); i++)
	{
		for (unsigned int j = 0; j < pliki[i].funkcje.size(); j++)
		{
			ss << pliki[i].ilosc_linijek_kodu;
			string ile_linii = ss.str();
			ss.str("");
			ss.clear();
			temp = pliki[i].nazwa_pliku + "(" + ile_linii + ")->" + pliki[i].funkcje[j].nazwa_funkcji + " : " + "\n";
			polaczenia_miedzy_funkcjami_a_plikiami = polaczenia_miedzy_funkcjami_a_plikiami + temp;
		}
	}
	//cout << polaczenia_miedzy_funkcjami_a_plikiami << endl;

	string scalone = pliki_txt + funkcje_txt + polaczenia_miedzy_funkcjami_a_plikiami;

	fstream plik_do_zapisu;
	plik_do_zapisu.open("..\\output\\do_paradigma\\pliki_i_funkcje.txt", ios::out);
	if (plik_do_zapisu.good())
	{
		plik_do_zapisu << scalone;
	}
	plik_do_zapisu.close();

	return scalone;
}

void graf::Graf::przygotuj_txt_dla_wszystkiego_do_visual_paradigma(string pliki_funkcje, string moduly_funkcje)
{
	string scalone = pliki_funkcje + moduly_funkcje;
	fstream plik_do_zapisu;
	plik_do_zapisu.open("..\\output\\do_paradigma\\wszystko.txt", ios::out);
	if (plik_do_zapisu.good())
	{
		plik_do_zapisu << scalone;
	}
	plik_do_zapisu.close();
}