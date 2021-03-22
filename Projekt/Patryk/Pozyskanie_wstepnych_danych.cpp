#pragma once
#include <Windows.h>
#include <iostream>
#include <io.h>
#include <vector>
#include "..\Graf.h"
#include <dirent.h>

using namespace std;

void graf::Graf::poszukaj_katalogow(const string sciezka)
{
	struct dirent* plik;
	DIR* przeszukiwana_sciezka;
	if (przeszukiwana_sciezka = opendir(sciezka.c_str())) 
	{
		while ((plik = readdir(przeszukiwana_sciezka)))
		{
			string nazwa = plik->d_name;
			int typ = plik->d_type;
			if ((typ == 16384) && (nazwa != ".") && (nazwa != "..") && (nazwa != "Release") && (nazwa != "Debug"))
			{
				string nowa_sciezka = sciezka + nazwa + "\\";
				znajdz_pliki(nowa_sciezka.c_str());
			}

		}
		closedir(przeszukiwana_sciezka);
	}
}

bool graf::Graf::sprawdz_czy_cos_jest_w_inpucie()
{
	bool sprawdzam = FALSE;
	struct dirent* plik;
	DIR* sciezka;
	sciezka = opendir("..\\input\\");
	while (plik = readdir(sciezka))
	{
		string nazwa = plik->d_name;
		if ((nazwa != ".") && (nazwa != ".."))
		{
			sprawdzam = TRUE;
		}
	}
	closedir(sciezka);
	if (sprawdzam)
	{
		cout << "Wykonuje zadanie dla plikow w folderze input" << endl;
		znajdz_pliki("..\\input\\");
		return 1;
	}
	else
	{
		cout << "Wykonuje zadanie dla plikow programu" << endl;
		znajdz_pliki(".\\");
		return 0;
	}
}

void graf::Graf::znajdz_pliki(const string sciezka)
{
	//struktura _findata przechowuje informacje o znalezionym pliku
	_finddata_t danePliku;
	
	string sciezka_pomocnicza = sciezka + "*.cpp";
	long uchwyt = _findfirst(sciezka_pomocnicza.c_str() , &danePliku);

	//jeli uchywyt == -1 to znaczy ze nic nie znalazl
	if (uchwyt != -1)
	{
		//przypisujemy do naszego wektora nazwe pierwszej pobranej strukuty za pomoca _findfirst w tym celu tworzymy obiekt Plik
		plik::Plik obiekt(danePliku.name);
		pliki.push_back(obiekt);
		//Kopiujemy do foderu temp <to z niego bedziemy czytac pliki>
		string nazwa = danePliku.name;
		string sciezka_do_pliku = sciezka + nazwa;
		string nowa_sciezka = "..\\temp\\" + nazwa;
		CopyFileA(sciezka_do_pliku.c_str(), nowa_sciezka.c_str(), FALSE);


		//jeli _findnext niczego nie znajduje to zwraca -1 dla tego ten warunek
		while (_findnext(uchwyt, &danePliku) != -1)
		{
			//przypisujemy do naszego wektora nazwe kolejnej pobranej strukuty za pomoc¹ _findnext w tym celu tworzymy obiekt Plik
			plik::Plik obiekt(danePliku.name);
			pliki.push_back(obiekt);
			nazwa = danePliku.name;
			sciezka_do_pliku = sciezka + nazwa;
			nowa_sciezka = "..\\temp\\" + nazwa;
			CopyFileA(sciezka_do_pliku.c_str(), nowa_sciezka.c_str(), FALSE);
		}
	}
	//odczepiamy uchwyt
	_findclose(uchwyt);

	//======================================================Wykonujemy to samo w poszukiwaniu plików .h

	sciezka_pomocnicza = sciezka + "*.h";
	uchwyt = _findfirst(sciezka_pomocnicza.c_str(), &danePliku);

	if (uchwyt != -1)
	{

		plik::Plik obiekt(danePliku.name);
		pliki.push_back(obiekt);
		string nazwa = danePliku.name;
		string sciezka_do_pliku = sciezka + nazwa;
		string nowa_sciezka = "..\\temp\\" + nazwa;
		CopyFileA(sciezka_do_pliku.c_str(), nowa_sciezka.c_str(), FALSE);

		while (_findnext(uchwyt, &danePliku) != -1)
		{
			plik::Plik obiekt(danePliku.name);
			pliki.push_back(obiekt);
			nazwa = danePliku.name;
			sciezka_do_pliku = sciezka + nazwa;
			nowa_sciezka = "..\\temp\\" + nazwa;
			CopyFileA(sciezka_do_pliku.c_str(), nowa_sciezka.c_str(), FALSE);
		}
	}

	//odczepiamy uchwyt
	_findclose(uchwyt);	

	//sprawdzanie(wypisanie)
	/*
	for (int i = 0; i < pliki.size(); i++)
	{
		cout << pliki[i].nazwa_pliku << endl;

	}
	*/
	poszukaj_katalogow(sciezka);
}