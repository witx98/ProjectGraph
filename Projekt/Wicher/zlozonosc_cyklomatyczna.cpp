//cyklometryczna vol 15 chyba? DO NOWEGO

#include"../Graf.h"

// funkcje nalepiej jednak by bylo dodac do clasy Graf tak po przemysleniu sytuacji XD
//oraz dodac do struct Funkcja 	nalezy dodac `int zlozonosc = 1;` bez ciapek
//funckja po kolei sprawdza plik i kazde slowo po czym jesli znajdzie slowo
//zwiekszajace zlozonosc cyklomatyczna to zwieksza zmienna

//ogolnie o zlozonosci:
// 0-10 kod prosty niewielkie ryzyko
//11-20 kod zlozony powodujacy duze ryzyko
//21-50	kod bardzo zlozony zwiazany z wysokim ryzykiem
//50 i wyzej pamietacie nasz program sprzez refactoringu ??? :D chociaz tamten to i tak byl gorszy

void graf::Graf::zlozonosc_cyklomatyczna()
{
	int licznik_klamer = 0;

	std::fstream otwarty_plik;
	std::string linia;

	//iteruje po  kazdym pliku
	for (int plik = 0; plik < pliki.size(); plik++)
	{
		otwarty_plik.open(pliki[plik].nazwa_pliku, std::ios::in);	//otwiera po kolei kazdy plik
		//iteruje po kazdej funkcji
		while (!otwarty_plik.eof())
		{	//dopoki plik sie nie skonczy
			for (int ktora_funkcja = 0; ktora_funkcja < wszystkie_funkcje_we_wszystkich_plikach.size(); ktora_funkcja++)
			{	//licznik klamer sluzacy do znajdywania ciala funcji
				//od razu po read linie jest sprawdzana czy  nie ma klamry zamykajacej lub otwieracjacej
				
				getline(otwarty_plik, linia);

				if (linia.find( "graf::Graf::" + wszystkie_funkcje_we_wszystkich_plikach[ktora_funkcja].nazwa_funkcji + "()") == std::string::npos)
				{
					Wojtas::szukanie_klamer(linia, licznik_klamer);

					if (licznik_klamer != 0)	//gdy znajdzie juz jakas klamre
					{
						getline(otwarty_plik, linia);
						Wojtas::szukanie_klamer(linia, licznik_klamer);

						if (linia.find("if") == std::string::npos)
						{
							wszystkie_funkcje_we_wszystkich_plikach[ktora_funkcja].zlozonosc++;	//zwiekszamy gdy znajdzie slowo klucz
						}
						else if (linia.find("case") != std::string::npos)
						{

							wszystkie_funkcje_we_wszystkich_plikach[ktora_funkcja].zlozonosc++;	//zwiekszamy gdy znajdzie slowo klucz

						}

					}
				}
			}

		}
		otwarty_plik.close();

		//sprawdzajka
		/*
		for (int i = 0; i < wszystkie_funkcje_we_wszystkich_plikach.size(); i++)
		{
			std::cout << wszystkie_funkcje_we_wszystkich_plikach[i].nazwa_funkcji << "ma zlozonosc: " << wszystkie_funkcje_we_wszystkich_plikach[i].zlozonosc << std::endl;
		}
		*/

	}
}