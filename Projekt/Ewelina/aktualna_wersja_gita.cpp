#pragma once
#include "..\Graf.h"
using namespace std;


void graf::Graf::pobierzWersjeGrafu() {
	if (sprawdz_czy_cos_jest_w_inpucie() == true) {
		system("cd ../input && git log > temp/git_log.txt");
	}
	else
	{
		system("cd .. && git log > temp/git_log.txt");
	}
	
	fstream plik_operacyjny;
	string linia;
	vector<string> slowa_w_linii;
	plik_operacyjny.open("..\\temp\\git_log.txt", std::ios::in);
	getline(plik_operacyjny, linia);
		slowa_w_linii = Wojtas::dzielenie_na_slowa(linia);
		slowa_w_linii[0] = Wojtas::usuwanie_tabulacji(slowa_w_linii[0]);
		version = slowa_w_linii[1];
	plik_operacyjny.close();
	if (slowa_w_linii[0] == "fatal") {
		version = "unknown";
		cout << "wersja: " << version << endl;
	}
	else
	{
		cout << "wersja: " << version << endl;
	}
	remove("../temp/git_log.txt");
}