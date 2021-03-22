#pragma once
#include "..\Graf.h"

void graf::Graf::wykonaj() {
	
	cout << "Witam rozpoczynam prace..." << endl;
	CreateDirectoryA("..\\temp", NULL);
	
	pobierzWersjeGrafu();
	policz_linijki_kodu_dla_pliku();
	znajdz_polaczenia_pomiedzy_plikami();

	znajdz_definicje_funkcji();
	znajdz_funkcje_i_wagi_pomiedzy_plikami();
	znajdz_polaczenia_miedzy_funkcjami();
	zlozonosc_cyklomatyczna();
	zlozonosc_na_stringa();

	znajdz_przestrzenie_nazw();
	znajdz_elementy_przestrzeni_nazw();
	
	kopiowanie_do_funkcji();

	polaczenia_i_wagi_modulow();

	cout << "Rozpoczynam proces rysowania grafu to moze chwile potrwac..." << endl;

	std::string graf_pliki = zamien_na_string_dla_plikow_do_grafu();
	std::string graf_funkcje = zamien_na_string_dla_funkcji_do_grafu();
	std::string graf_modul = zamien_na_string_dla_modulu();
	std::string graf_bez_polaczen = string_dla_funkcji_i_modulu_bez_polaczen(graf_modul);
	std::string graf_pliki_funkcje = string_dla_plikow_i_funkcji(graf_pliki, graf_funkcje);
	std::string graf_funkcje_moduly = string_dla_funkcji_i_modulu(graf_funkcje, graf_modul);
	std::string graf_pliki_modul = string_dla_plikow_i_modulu(graf_pliki, graf_modul);
	std::string graf_metis_funkcje = przygotujPlikZFunkcjamiDlaMetisa();
	std::string graf_wszystko = string_dla_wszystkiego(graf_pliki_funkcje, graf_funkcje_moduly);

	std::string do_txt_funkcje = przygotuj_txt_dla_funkcji_do_visual_paradigma();
	std::string do_txt_pliki = przygotuj_txt_dla_plikow_do_visual_paradigma();
	std::string do_txt_moduly = przygotuj_txt_dla_modulu_do_visual_paradigma();
	std::string do_txt_pliki_funkcje = przygotuj_txt_dla_plikow_i_funkcji_do_visual_paradigma(do_txt_pliki, do_txt_funkcje);
	std::string do_txt_moduly_funkcje = przygotuj_txt_dla_modulow_i_funkcji_do_visual_paradigma(do_txt_moduly, do_txt_funkcje);
	przygotuj_txt_dla_wszystkiego_do_visual_paradigma(do_txt_pliki_funkcje, do_txt_moduly_funkcje);

	rysuj_graf(dodaj_wersje(graf_pliki), "Graf_plikow");
	cout << "-";
	rysuj_graf(dodaj_wersje(graf_funkcje), "Graf_funkcji");
	cout << "-";
	rysuj_graf(dodaj_wersje(graf_funkcje_moduly), "Graf_funkcje_moduly");
	cout << "-";
	rysuj_graf(dodaj_wersje(graf_bez_polaczen), "Graf_bez_polaczen");
	cout << "-";
	rysuj_graf(dodaj_wersje(graf_modul), "Graf_modulu");
	cout << "-";
	rysuj_graf(dodaj_wersje(graf_pliki_modul), "Graf_pliki_moduly");
	cout << "-";
	rysuj_graf(dodaj_wersje(graf_pliki_funkcje), "Graf_pliki_funkcje");
	cout << "-";
	rysuj_graf(dodaj_wersje(graf_metis_funkcje), "Graf_metis_funkcje");
	cout << "-";
	rysuj_graf(dodaj_wersje(graf_wszystko), "Graf_wszystko");
	cout << "-";
	usun_tempa();
}

void graf::Graf::usun_tempa()
{
	string sciezka_do_pliku;
	//Najpierw usuwamy pliki w folderze
	for (unsigned int i = 0; i < pliki.size(); i++)
	{
		sciezka_do_pliku = "..\\temp\\" + pliki[i].nazwa_pliku;
		remove(sciezka_do_pliku.c_str());
	}
	//Teraz usuwamy katalog
	RemoveDirectoryA("..\\temp");
}