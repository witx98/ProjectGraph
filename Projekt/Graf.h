#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Wojtas\Funkcje_od_stringow.h"


using namespace std;


namespace polaczenie {
	struct Polaczenie {
		std::string nazwa_polaczonego_elementu;
		int waga;   //zalezne od liczby wywolan funkcji
		Polaczenie(std::string a) {
			nazwa_polaczonego_elementu = a;
			waga = 1;
		}
	};
}

namespace funkcja {
	struct Funkcja {
		std::string nazwa_funkcji;
		std::vector<polaczenie::Polaczenie> polaczenia_miedzy_funkcjami;
		int zlozonosc;
		string zlozonosc_string;
		Funkcja(std::string a) {
			nazwa_funkcji = a;
			polaczenia_miedzy_funkcjami = {};
			zlozonosc = 1;
		}
		void znajdz_polaczone_funkcje(Funkcja sprawdzana_fun, std::fstream& otwarty_plik);
	};
}

//struktura z namespaceami - nowa 16.11.2019
namespace modul {
	struct Modul {
		std::string nazwa_przestrzeni;
		std::vector<funkcja::Funkcja> funkcje_modulu;
		std::vector<std::string> elementy_modulu;
		std::vector<polaczenie::Polaczenie> polaczenia_miedzy_namespaceami;
		vector<polaczenie::Polaczenie> polaczenia_z_plikami;
		vector<polaczenie::Polaczenie> polaczenia_z_funkcjami;

		Modul(std::string a) {
			nazwa_przestrzeni = a;
			funkcje_modulu = {};
			elementy_modulu = {};
			polaczenia_miedzy_namespaceami = {};
			polaczenia_z_plikami = {};
			polaczenia_z_funkcjami = {};
		}
		void znajdz_elementy_modulu(std::fstream&);
		void znajdz_funkcje_w_module(std::string slowo);
		void dodaj_niepowtarzajacy_sie_modul(std::string);
	};
}

namespace plik {
	struct Plik {
		std::string nazwa_pliku;
		int ilosc_linijek_kodu;
		std::vector<polaczenie::Polaczenie> polaczenia_miedzy_plikami;
		std::vector<funkcja::Funkcja> funkcje;
		std::vector<modul::Modul> namespacey;
		Plik() {
			nazwa_pliku = "";
			polaczenia_miedzy_plikami = {};
			funkcje = {};
			namespacey = {};
			ilosc_linijek_kodu = 0;
		};
		Plik(std::string a) {
			nazwa_pliku = a;
			polaczenia_miedzy_plikami = {};
			funkcje = {};
			namespacey = {};
			ilosc_linijek_kodu = 0;
		}
		void znajdz_funkcje_w_pliku();
		void znajdz_moduly();
	private:
		void dodaj_niepowtarzajaca_sie_funkcje(std::string nazwa);
		
	};
}

namespace graf {
	class Graf {
	public:
		std::vector<funkcja::Funkcja> wszystkie_funkcje_we_wszystkich_plikach;
		std::vector<plik::Plik> pliki;
		std::vector<modul::Modul> przestrzenie_nazw;
		std::string version;

		//znajduje pliki w folderze : dodaje znalezione do vectora Graf::pliki definiujac nazwe w konstruktorze
		void znajdz_pliki(const string sciezka);     //                                                               || -> Patryk
		//znajduje scierzki do katalogow zeby je pozniej przeszukac
		void poszukaj_katalogow(const string sciezka); //                                                             || -> Patryk
		//sprawdza inputa i decyduje ktora wersja sprawdzania
		bool sprawdz_czy_cos_jest_w_inpucie(); //														              || -> Patryk

		//dodaje liczbe linijek do pola Plik::ilosc_linijek_kodu dla kazdego pliku z vectora
		void policz_linijki_kodu_dla_pliku(); //liczy linijki kodu dla pliku                   || -> Ewelina

		//znajduje includy etc : dla kazdego pliku dodajego do jego pola vector Plik::polaczenia_miedzy_plikami elemty polaczen do vectora (dodaje nazwy)
		void znajdz_polaczenia_pomiedzy_plikami();  //znajduje polaczenia pomiedzy plikami     || -> Patryk

		//dodaje definicje do pola Graf::wszystkie_funkcje... oraz dla kazdego pliku do pola Plik::funkcje jego pliki
		void znajdz_definicje_funkcji();			//										   || -> Wojtek

		//dla kazdego Pliku dodaje do polaczeniamiedzyplikami[].waga ich wage szuka funkcji dla pliku ktore sa w Graf::wsystkie.. a nie ma w Plik::funkcje
		void znajdz_funkcje_i_wagi_pomiedzy_plikami();//                                       || -> Bartek

		//dla kazdej Funkcji dodaje polaczenia do vecota Funkcja::polaczenia_miedzy_funkcjami (nazwy polaczonych funkcji)
		void znajdz_polaczenia_miedzy_funkcjami();                 //                          || -> Matuesz Witkowski i Wojtek

		//znajduje przestrzenie 
		void znajdz_przestrzenie_nazw();									//                 || -> Wojtek
					   
		//znajduje pola dla  przestrzeni zdefiniowanych przez uzytkownika i napisuje (narazie czesc, wiec jak potzreba to dopisac)
		//dla domyslnych jak std
		void znajdz_elementy_przestrzeni_nazw();							//                 || -> Wojtek

		void polaczenie_modulu_z_plikiem();//												   || -> Mateusz Wicherski

		void zlozonosc_cyklomatyczna();//													   || -> Mateusz Wicherski

		void zlozonosc_na_stringa();//														   || -> Patryk B這niarz
		void kopiowanie_do_funkcji();//														   || -> Patryk B這niarz
		void polaczenia_i_wagi_modulow();//													   || -> Patryk B這niarz

		//Zajmuja sie edycja danych by pasowaly one do visual paradigma
		void przygotuj_txt_dla_wszystkiego_do_visual_paradigma(string,string);//		           || -> Patryk B這niarz
		std::string przygotuj_txt_dla_plikow_do_visual_paradigma();//							   || -> Patryk B這niarz
		std::string przygotuj_txt_dla_funkcji_do_visual_paradigma();//							   || -> Patryk B這niarz
		std::string przygotuj_txt_dla_modulow_i_funkcji_do_visual_paradigma(string, string);//	   || -> Patryk B這niarz
		std::string przygotuj_txt_dla_modulu_do_visual_paradigma();//							   || -> Patryk B這niarz
		std::string przygotuj_txt_dla_plikow_i_funkcji_do_visual_paradigma(string, string);//	   || -> Patryk B這niarz

		std::string string_dla_funkcji_i_modulu_bez_polaczen(string);//							   || -> Patryk B這niarz	
		std::string string_dla_wszystkiego(string, string);	//									   || -> Patryk B這niarz	
		std::string zamien_na_string_dla_modulu();				//							   || -> Patryk B這niarz				
		std::string zamien_na_string_dla_plikow_do_grafu();  //                                || -> Matuesz Wicherski // Mateusz Witkowski ==> zmiany Patryk
		std::string zamien_na_string_dla_funkcji_do_grafu(); //do skopiowania i prxerobienia   || -> Matuesz Wicherski // Mateusz Witkowski ==> zmiany Patryk
		std::string string_dla_plikow_i_funkcji(string, string);//							   || -> Patryk B這niarz	
		std::string string_dla_plikow_i_modulu(string, string);//							   || -> Patryk B這niarz
		std::string string_dla_funkcji_i_modulu(string, string);//							   || -> Patryk B這niarz

		std::string przygotujPlikZFunkcjamiDlaMetisa();//									   || -> Bartlomiej Zieja

		std::string dodaj_wersje(string);//													   || -> Patryk B這niarz	

		void pobierzWersjeGrafu();//			                                             

		void rysuj_graf(std::string do_rysowania_grafu, std::string nazwa_pliku);//GOTOWE      || -> Matuesz Wich i Wojtek // Mateusz Witkowski

		void usun_tempa(); // pomocnicza to usuwania katalogu temp (definicja w pliku wykonaj) || -> Patryk B這niarz

		void wykonaj();//																	   

	};
}