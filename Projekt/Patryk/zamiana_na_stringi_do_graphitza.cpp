#pragma once
#include "..\Graf.h"
#include <sstream>

using namespace std;

string graf::Graf::zamien_na_string_dla_plikow_do_grafu()
{
	std::string strzala = "->";
	std::string poczatek = "digraph G {\nbgcolor=\"#66cc99:#009966\"\n";
	std::string temp;
	std::string tekst;

	std::string node = "node [shape=folder fillcolor=\"#99CCFF:#0066CC\" style=\"filled\" gradientangle=120]\n"; //żeby to ładniej wyglądało
	std::string styl_strzalki = "[color=\"#3366FF\", penwidth = 1.2]";	//żeby strzalki inny kolor mialy

	std::ostringstream ss;	//plik.ilosc_linijek_kodu	
	std::ostringstream ss2;	//dla obydwu
	std::ostringstream ss3;	//dla wagi polaczenia

	temp += node;

	for (size_t i = 0; i < pliki.size(); i++)	//pierwszy plik
	{
		ss << pliki[i].ilosc_linijek_kodu;
		std::string ilosc_lini_pierwszego_pliku = ss.str();
		ss.str("");
		ss.clear();

		temp += "\"" + pliki[i].nazwa_pliku + "(" + ilosc_lini_pierwszego_pliku + ")\";\n";
	}
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
				//std::cout << "nazwa pliku: " <<  pliki[i].nazwa_pliku << endl;
				//std::cout << "nazwa poloczonego elementu: " << pliki[i].polaczenia_miedzy_plikami[j].nazwa_polaczonego_elementu << endl;
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
				temp += "\"" + pliki[i].nazwa_pliku + "(" + ilosc_lini_pierwszego_pliku + ")\"" + strzala + "\"" + pliki[i].polaczenia_miedzy_plikami[j].nazwa_polaczonego_elementu + "(" + ilosc_linii_drugiego_pliku + ")\"" + "[ label = \"" + sila_polaczenia + "\" ]" + styl_strzalki + ";\n";
				//std::cout << temp << endl;
			}
		}
	}
	tekst = poczatek + temp + "}";	//trzeba pamietac o zamknieciu nawiasu klamrowego

	//std::cout << tekst << endl;		//tescik
	return tekst;

}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

string graf::Graf::zamien_na_string_dla_funkcji_do_grafu()
{
	std::string strzalka = "->";
	std::string poczatek = "digraph G {\nbgcolor=\"#66cc99:#009966\"\n";
	std::string temp;
	std::string tekst;
	std::ostringstream waga_polaczenia;		//definiuje przed bo po co definiowac to samo wiele razy
	string zlozonosc;

	std::string node = "node[shape = box fillcolor = \"#FF3366:#CC3366\" style = \"filled\" gradientangle = 120]\n"; //żeby to ładniej wyglądało
	std::string styl_strzalki = "[color=\"#990033\", penwidth = 1.2]";	//żeby strzalki inny kolor mialy

	temp += node;


	for (size_t i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++)
	{
		temp += "\"" + wszystkie_funkcje_we_wszystkich_plikach[i].nazwa_funkcji + "(" + wszystkie_funkcje_we_wszystkich_plikach[i].zlozonosc_string + ")\";\n";
	}

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

				temp += "\"" + wszystkie_funkcje_we_wszystkich_plikach[i].nazwa_funkcji + "(" + wszystkie_funkcje_we_wszystkich_plikach[i].zlozonosc_string + ")\"" + strzalka + "\"" + wszystkie_funkcje_we_wszystkich_plikach[i].polaczenia_miedzy_funkcjami[j].nazwa_polaczonego_elementu + "(" + zlozonosc + ")\"" + "[ label = \"" + sila_polaczenia + "\" ]" + styl_strzalki + ";\n";
			}
		}
	}

	tekst = poczatek + temp + "}";		//zawsze zamykajcie nawiasy klamrowe :D

	//std::cout << tekst; 		//tescik
	return tekst;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

string graf::Graf::zamien_na_string_dla_modulu()
{
	std::string strzalka = "->";
	std::string poczatek = "digraph G {\nbgcolor=\"#66cc99:#009966\"\n";
	std::string node = "node [shape=diamond fillcolor=\"#FFCC66:#FFFF99\" style=\"filled\" gradientangle=120]\n";
	std::string styl_strzalki = "[color=\"#996600\", penwidth = 1.2]";
	std::string temp = "";
	std::string tekst;
	std::string sila_polaczenia = "999";
	std::ostringstream waga_polaczenia;


	temp += node;

	if (przestrzenie_nazw.size() < 1)
		for (unsigned int i = 0; i < przestrzenie_nazw.size(); i++)
		{
			temp += "\"" + przestrzenie_nazw[i].nazwa_przestrzeni + "\";\n";
		}

	for (unsigned int i = 0; i < przestrzenie_nazw.size(); i++)
	{
		if (przestrzenie_nazw[i].polaczenia_miedzy_namespaceami.size() < 1)
		{
			temp += "\"" + przestrzenie_nazw[i].nazwa_przestrzeni + "\"\n";
		}
		for (unsigned int j = 0; j < przestrzenie_nazw[i].polaczenia_miedzy_namespaceami.size(); j++)
		{
			waga_polaczenia << przestrzenie_nazw[i].polaczenia_miedzy_namespaceami[j].waga;
			std::string sila_polaczenia = waga_polaczenia.str();
			waga_polaczenia.str("");
			waga_polaczenia.clear();

			temp += "\"" + przestrzenie_nazw[i].nazwa_przestrzeni + "\"" + strzalka + "\"" + przestrzenie_nazw[i].polaczenia_miedzy_namespaceami[j].nazwa_polaczonego_elementu + "\"" + "[ label = \"" + sila_polaczenia + "\" ]" + styl_strzalki + ";\n";
		}
	}
	tekst = poczatek + temp + "}";
	//std::cout << tekst;
	return (tekst);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

string graf::Graf::string_dla_plikow_i_funkcji(string pierwsza_czesc_stringa, string druga_czesc_stringa)
{
	string poczatek = "digraph G {";
	pierwsza_czesc_stringa.erase(0, 11);
	pierwsza_czesc_stringa.erase(pierwsza_czesc_stringa.length() - 1, pierwsza_czesc_stringa.length());
	druga_czesc_stringa.erase(0, 11);
	druga_czesc_stringa.erase(druga_czesc_stringa.length() - 1, druga_czesc_stringa.length());
	string trzecia_czesc_stringa;
	string temp;
	ostringstream ss;
	std::string styl_strzalki = "[color=\"#871F78\", penwidth = 1.2]";	//¿eby strzalki inny kolor mialy


	for (unsigned int i = 0; i < pliki.size(); i++)
	{
		for (unsigned int j = 0; j < pliki[i].funkcje.size(); j++)
		{
			ss << pliki[i].ilosc_linijek_kodu;
			string ile_linii = ss.str();
			ss.str("");
			ss.clear();
			temp = "\"" + pliki[i].funkcje[j].nazwa_funkcji + "(" + pliki[i].funkcje[j].zlozonosc_string + ")" + "\"->\"" + pliki[i].nazwa_pliku + "(" + ile_linii + ")" + "\"" + styl_strzalki + ";\n";
			//std::cout << temp << endl;";\n";
			trzecia_czesc_stringa = trzecia_czesc_stringa + temp;
		}
	}
	//cout << trzecia_czesc_stringa << endl;

	string scalone = poczatek + pierwsza_czesc_stringa + druga_czesc_stringa + trzecia_czesc_stringa + "\n}";

	return scalone;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

string graf::Graf::string_dla_plikow_i_modulu(string pierwsza_czesc_stringa, string druga_czesc_stringa)
{
	string poczatek = "digraph G {";
	pierwsza_czesc_stringa.erase(0, 11);
	pierwsza_czesc_stringa.erase(pierwsza_czesc_stringa.length() - 1, pierwsza_czesc_stringa.length());
	druga_czesc_stringa.erase(0, 11);
	druga_czesc_stringa.erase(druga_czesc_stringa.length() - 1, druga_czesc_stringa.length());
	string temp;
	ostringstream ss;

	string scalone = poczatek + pierwsza_czesc_stringa + druga_czesc_stringa + "}";
	return scalone;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

string graf::Graf::string_dla_funkcji_i_modulu(string pierwsza_czesc_stringa, string druga_czesc_stringa)
{
	string poczatek = "digraph G {";
	pierwsza_czesc_stringa.erase(0, 11);
	pierwsza_czesc_stringa.erase(pierwsza_czesc_stringa.length() - 1, pierwsza_czesc_stringa.length());
	druga_czesc_stringa.erase(0, 11);
	druga_czesc_stringa.erase(druga_czesc_stringa.length() - 1, druga_czesc_stringa.length());
	string trzecia_czesc_stringa;
	string temp;
	ostringstream ss;
	std::string styl_strzalki = "[color=\"#FF7F00\", penwidth = 1.2]";	//¿eby strzalki inny kolor mialy

	for (unsigned int i = 0; i < przestrzenie_nazw.size(); i++)
	{
		for (unsigned int j = 0; j < przestrzenie_nazw[i].funkcje_modulu.size(); j++)
		{
			temp = "\"" + przestrzenie_nazw[i].funkcje_modulu[j].nazwa_funkcji + "(" + przestrzenie_nazw[i].funkcje_modulu[j].zlozonosc_string + ")" + "\"->\"" + przestrzenie_nazw[i].nazwa_przestrzeni + "\"" + styl_strzalki + ";\n";
			trzecia_czesc_stringa = trzecia_czesc_stringa + temp;
		}

	}
	string scalone = poczatek + pierwsza_czesc_stringa + druga_czesc_stringa + trzecia_czesc_stringa + "}";
	return scalone;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

string graf::Graf::string_dla_funkcji_i_modulu_bez_polaczen(string polaczenia_modulow)
{
	std::string poczatek = "digraph G {\nbgcolor=\"#66cc99:#009966\"\n";
	polaczenia_modulow.erase(0, 11);
	polaczenia_modulow.erase(polaczenia_modulow.length() - 1, polaczenia_modulow.length());
	string trzecia_czesc_stringa;
	string temp;
	ostringstream ss;
	std::string styl_strzalki = "[color=\"#FF7F00\", penwidth = 1.2]";	//¿eby strzalki inny kolor mialy

	std::string node = "node[shape = box fillcolor = \"#FF3366:#CC3366\" style = \"filled\" gradientangle = 120]\n";


	trzecia_czesc_stringa += node;
	for (size_t i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++)
	{
		trzecia_czesc_stringa += "\"" + wszystkie_funkcje_we_wszystkich_plikach[i].nazwa_funkcji + "(" + wszystkie_funkcje_we_wszystkich_plikach[i].zlozonosc_string + ")\";\n";
	}




	for (unsigned int i = 0; i < przestrzenie_nazw.size(); i++)
	{
		for (unsigned int j = 0; j < przestrzenie_nazw[i].funkcje_modulu.size(); j++)
		{
			temp = "\"" + przestrzenie_nazw[i].funkcje_modulu[j].nazwa_funkcji + "(" + przestrzenie_nazw[i].funkcje_modulu[j].zlozonosc_string + ")" + "\"->\"" + przestrzenie_nazw[i].nazwa_przestrzeni + "\"" + styl_strzalki + ";\n";
			trzecia_czesc_stringa = trzecia_czesc_stringa + temp;
		}

	}
	string scalone = poczatek + polaczenia_modulow + trzecia_czesc_stringa + "}";
	return scalone;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

string graf::Graf::string_dla_wszystkiego(string pliki_funkcje, string funkcje_moduly)
{
	string poczatek = "digraph G {";
	pliki_funkcje.erase(0, 11);
	pliki_funkcje.erase(pliki_funkcje.length() - 1, pliki_funkcje.length());
	funkcje_moduly.erase(0, 11);
	funkcje_moduly.erase(funkcje_moduly.length() - 1, funkcje_moduly.length());
	string scalone = poczatek + pliki_funkcje + funkcje_moduly + "}";
	return scalone;
}

string graf::Graf::dodaj_wersje(string gdzie_dodac)
{
	string label = "label = \" version: " + version + "\" fontcolor = \"black\" fontsize = 26";
	gdzie_dodac.erase(gdzie_dodac.length() - 1, gdzie_dodac.length());
	string scalone = gdzie_dodac + label + "}";
	return scalone;
}