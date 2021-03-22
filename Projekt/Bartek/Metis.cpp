#pragma once
#include "../Graf.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <metis.h> 
#pragma comment(lib, "metis.lib") //wkleiæ plik metis.lib do D:\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.23.28105\lib\x64 i x86 (2 rozne liby na dwie architektury)
#include<sstream>

using namespace std;


string graf::Graf::przygotujPlikZFunkcjamiDlaMetisa() {

	idx_t nParts = 4; //PARAMETR ZADANY PRZEZ PROWADZ¥CEGO, na ile podgrafow podzielic glowny graf (na uplu od 2 do 6). Trzeba go jakoœ tu przekazywaæ
	


	class cluster { //klasa pomocnicza do kodowania nazw funkcji na kolejne liczby calkowite, obudowuje Funkcjê
	public:
		int number;
		string name;
		funkcja::Funkcja* function;

		cluster(int nr, string na, funkcja::Funkcja *fun) {
			number = nr;
			name = na;
			function = fun;
		};
	};

	std::vector <cluster> slownik; //tu beda przechowywane zakodowane funkcje

	std::vector<idx_t> xadj; //wektor biblioteki metis.h, // Indexes of starting points in adjacent array
	std::vector<idx_t> adjncy; //jw. //Adjacent vertices in consecutive index order
	std::vector<idx_t> adjwgt; //jw. zawiera wagi krawedzi

	//zestaw 3 pomocniczych zmiennych
	std::vector<idx_t> xadjtemp; 
	std::vector<idx_t> adjncytemp; 
	std::vector<idx_t> adjwgttemp; 

	//w tej pêtli iterujemy po wszystkich funkcjach i je kodujemy
	for (int i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++) {
		cluster temp(i, wszystkie_funkcje_we_wszystkich_plikach[i].nazwa_funkcji, &wszystkie_funkcje_we_wszystkich_plikach[i]);
		slownik.push_back(temp);
	}

	//funkcja tworz¹ca niepe³n¹ liste s¹siedztwa
	for (int i = 0; i < slownik.size(); i++) { //dla kazdej funkcji zakodowanej w slowniku...
		//int current_findex = slownik[i].number; //wez nr rozpatrywanej funkcji
		xadjtemp.push_back(adjncytemp.size());

		for (int j = 0; j < slownik[i].function->polaczenia_miedzy_funkcjami.size(); j++) { //a¿ do wyczerpania jej po³¹czeñ
			
			polaczenie::Polaczenie rozwazane_polaczenie = slownik[i].function->polaczenia_miedzy_funkcjami[j];

			//zdekoduj nazwe na int i spushuj do wektora
			int decoded_number;
			for (int m = 0; m < slownik.size(); m++) {
				if (rozwazane_polaczenie.nazwa_polaczonego_elementu == slownik[m].name)
					decoded_number = m;
			}
			adjncytemp.push_back(decoded_number);
			adjwgttemp.push_back(rozwazane_polaczenie.waga);
		}

		if(i+1 == slownik.size())  //musi byæ spuszowane jeszcze raz na samiutkim koñcu
			xadjtemp.push_back(adjncytemp.size());
	}

	//tworzenie niepe³nej macierzy s¹siedztwa na podstawie niepe³nej listy s¹siedztwa 
	int** macierz_sasiedztwa = new int* [wszystkie_funkcje_we_wszystkich_plikach.size()];
	for (int i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++) {
		macierz_sasiedztwa[i] = new int[wszystkie_funkcje_we_wszystkich_plikach.size()];
	}
	
	//wypelnienie macierzy zerami
	for (int i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++) { 
		for (int j = 0; j < wszystkie_funkcje_we_wszystkich_plikach.size(); j++) {
			macierz_sasiedztwa[i][j] = 0;
		}
	}

	//wypelnienie wybranych pól jedynkami
	for (int i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++) {
		int k = i;
		for (int x = xadjtemp[i + 1] - xadjtemp[i]; x >= 0; x--) {
			macierz_sasiedztwa[i][adjncytemp[k]] = 1;
			k++;
		}
	}

	//utworzenie pe³nej macierzy s¹siedztwa
	for (int i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++) { 
		for (int j = 0; j < wszystkie_funkcje_we_wszystkich_plikach.size(); j++) {
			if (macierz_sasiedztwa[i][j] == 1)
				macierz_sasiedztwa[j][i] = 1;				
		}
	}

	//zwiniecie pe³nej macierzy s¹siedztwa do pe³nej listy s¹siedztwa
	for (int i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++) {
		xadj.push_back(adjncy.size());


		for (int j = 0; j < wszystkie_funkcje_we_wszystkich_plikach.size(); j++) {
			if (macierz_sasiedztwa[i][j] == 1)
				adjncy.push_back(j);
		}

		if (i + 1 == wszystkie_funkcje_we_wszystkich_plikach.size())
			xadj.push_back(adjncy.size()); //musi byæ spuszowane jeszcze raz na samiutkim koñcu
	}

	//DEBUG MACIERZY SASIEDZTWA
	/*
	for (int i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++) { 
		for (int j = 0; j < wszystkie_funkcje_we_wszystkich_plikach.size(); j++) {
			cout << macierz_sasiedztwa[i][j] << " ";
		}
		cout << endl;
	}
	*/

	////////////////////////////////////////////////////////////////to samo tylko dla WAG //////////////////////////
	
	//utworzenie macierzy wag
	int** macierz_wag = new int* [wszystkie_funkcje_we_wszystkich_plikach.size()];
	for (int i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++) {
		macierz_wag[i] = new int[wszystkie_funkcje_we_wszystkich_plikach.size()];
	}

	//wypelnienie macierzy wag zerami
	for (int i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++) {
		for (int j = 0; j < wszystkie_funkcje_we_wszystkich_plikach.size(); j++) {
			macierz_wag[i][j] = 0;
		}
	}

	//wypelnienie wybranych pól wagami 
	for (int i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++) {
		int k = i;
		for (int x = xadjtemp[i + 1] - xadjtemp[i]; x >= 0; x--) {
			macierz_wag[i][adjncytemp[k]] = adjwgttemp[k];
			k++;
		}
	}

	//utworzenie pe³nej macierzy wag
	for (int i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++) {
		for (int j = 0; j < wszystkie_funkcje_we_wszystkich_plikach.size(); j++) {
			if (macierz_wag[i][j] != 0)
				macierz_wag[j][i] = macierz_wag[i][j];
		}
	}

	//zwiniecie pe³nej macierzy wag do pe³nej listy wag
	for (int i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++) {
		for (int j = 0; j < wszystkie_funkcje_we_wszystkich_plikach.size(); j++) {
			if (macierz_wag[i][j] != 0)
				adjwgt.push_back(macierz_wag[i][j]);
		}
	}
	
	//DEBUG MACIERZY wag
	/*
	cout << endl << endl << endl;
	for (int i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++) {
		for (int j = 0; j < wszystkie_funkcje_we_wszystkich_plikach.size(); j++) {
			cout << macierz_wag[i][j] << " ";
		}
		cout << endl;
	}
	*/

	///////////////////////////////////////// METIS - zmienne //////////////////////
	idx_t nVertices = wszystkie_funkcje_we_wszystkich_plikach.size(); //liczba wierzcholkow
	idx_t nEdges = adjncy.size()/2;
	idx_t nWeights = 1;
	idx_t objval;
	std::vector<idx_t> part(nVertices);

	
	int ret = METIS_PartGraphKway(&nVertices, &nWeights, xadj.data(), adjncy.data(),
		NULL, NULL, NULL, &nParts, NULL,
		NULL, NULL, &objval, part.data());


	//std::cout << ret << std::endl; //1 lub 0?

	//DEBUG - ktory index funkcji do ktorego grafu
	//cout << "WYNIK OSTATECZNY:" << endl << endl << endl;
	//for (unsigned part_i = 0; part_i < nVertices; part_i++) {
	//	std::cout << part_i << " " << part[part_i] << std::endl;
	//}


	/////////////////////////////////////////////////////////WYPISYWANIE DANYCH DO GRAPHIZA /////////////////////////////	
		string strzalka = "->";
		string poczatek = "digraph G {\nbgcolor=\"#66cc99:#009966\"\n";
		string temp;
		string tekst;
		string tekst2;
		stringstream nr_klastra;
		ostringstream waga_polaczenia;		//definiuje przed bo po co definiowac to samo wiele razy

		string node = "node[shape = box fillcolor = \"#99ffff:lightblue\" style = \"filled\" gradientangle = 120] \n"; //¿eby to ³adniej wygl¹da³o
		//string styl_strzalki = "[color=\"magenta\", penwidth = 2]";	//¿eby strzalki inny kolor mialy

		for (size_t i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++)
		{
			//std::cout << wszystkie_funkcje_we_wszystkich_plikach[i].nazwa_funkcji << endl;
			for (size_t j = 0; j < wszystkie_funkcje_we_wszystkich_plikach[i].polaczenia_miedzy_funkcjami.size(); j++)
			{
				if (wszystkie_funkcje_we_wszystkich_plikach[i].polaczenia_miedzy_funkcjami[j].waga != 0)		//drugi warunek po to zeby nie rysowalo polaczen z waga 0
				{
					//std::cout << wszystkie_funkcje_we_wszystkich_plikach[i].nazwa_funkcji << endl;
					waga_polaczenia << wszystkie_funkcje_we_wszystkich_plikach[i].polaczenia_miedzy_funkcjami[j].waga;
					std::string sila_polaczenia = waga_polaczenia.str();
					waga_polaczenia.str("");
					waga_polaczenia.clear();

					temp += "\"" + wszystkie_funkcje_we_wszystkich_plikach[i].nazwa_funkcji + "\"" + strzalka + "\"" + wszystkie_funkcje_we_wszystkich_plikach[i].polaczenia_miedzy_funkcjami[j].nazwa_polaczonego_elementu + "\"" + "[ xlabel = \"" + sila_polaczenia + "\" ]" + ";\n"; //wywali³em styl strza³ki z koñca

				}
			}
		}

		//tekst2 = "";
		for (int i = 0; i < nParts; i++) {
			nr_klastra.str("");
			nr_klastra.clear();
			nr_klastra << i;
			tekst2 += "subgraph \"cluster_" + nr_klastra.str();
			tekst2 += "\" { ";
			for (int j = 0; j < part.size(); j++) {
				if (part[j] == i) {	//to wtedy j-ta funkcja powinna byc w itym klastrze

					//rozkoduj funkcje o j-tym indeksie
					for (int k = 0; k < slownik.size(); k++) {
						if (slownik[k].number == j)
							tekst2 += "\"" + slownik[j].name + "\"" + "; ";
					}
				}
			}
			tekst2 += " }\n\n";
			
		}

		tekst = poczatek + node + temp + tekst2 + "}";


		//////////////////////////////////// zwalnianie pamiêci //////////////////////////
		
		for (int i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++) {
			delete [] macierz_sasiedztwa[i];
		}
		delete [] macierz_sasiedztwa;

		for (int i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++) {
			delete[] macierz_wag[i];
		}
		delete[] macierz_wag;

		//cout << tekst << endl << endl;
		//cout << tekst;
		//std::cout << tekst; 		//tescik
		return tekst;
	



	//WIELKI DEBUG
/*
	cout << wszystkie_funkcje_we_wszystkich_plikach.size() << endl;
	cout << xadj.size() << endl;
	cout << adjncy.size() << endl;
	cout << adjwgt.size() << endl;
	for (int i = 0; i < xadj.size(); i++) {
		cout << " " << xadj[i];
	}
	cout << endl << endl;
	for (int i = 0; i < adjncy.size(); i++) {
		cout << " " << adjncy[i];
	}
	cout << endl << endl;
	//for (int i = 0; i < adjncy.size(); i++) {
	//	cout << " " << adjwgt[i];
	//}
	cout << endl;
	*/
	
}

/*

codeStringToInt( name1) {
		for (int m = 0; m < slownik.size(); m++) {
			if (slownik[i].name == name1)
				wyprowadz slownik[i].number;
		}
};

 codeIntToString( number1) {
		for (int i = 0; i < slownik.size(); i++) {
			if (slownik[i].number == number1)
				wyprowadz slownik[i].name;
	}
}
	*/