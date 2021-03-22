#pragma once
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include "..\Graf.h"

void graf::Graf::rysuj_graf(std::string do_rysowania_graphu, std::string nazwa_pliku) {
	
	////tlumaczenie 
	//std::ofstream plik_wyjsciowy;
	//plik_wyjsciowy.open(nazwa_pliku.c_str(), std::ios::out);		//zapis  do pliku
	//plik_wyjsciowy << do_rysowania_graphu;
	//plik_wyjsciowy.close();							//zamykanie pliku



	string sciezka = "..\\graphviz-2.38\\release\\bin\\dot.exe";	//sciezka do pliku
	string tymczasowy = "temp.dot";		//tworzy tymczasowy plik o nazwie temp.dot
	string wyjscie = "..\\output\\" + nazwa_pliku + ".png";			//koncowy plik o rozszerzeniu png
	ofstream out;
	out.open(tymczasowy.c_str(), std::ios::out);	//zapis???
	out << do_rysowania_graphu << std::endl;
	out.close();

	system((sciezka + " " + tymczasowy + " -Tpng -o " + wyjscie).c_str());
	remove("temp.dot");
}



