#pragma once
#include "..\Graf.h"

void graf::Graf::polaczenie_modulu_z_plikiem()
{	
	std::fstream otwarty_plik;
	string linia;

	for (int plik = 0; plik < pliki.size(); plik++)
	{
		otwarty_plik.open("..\\temp\\" + pliki[plik].nazwa_pliku, std::ios::in);

		for (int ktora_przestrzen = 0; ktora_przestrzen < przestrzenie_nazw.size(); ktora_przestrzen++)
		{
			while (getline(otwarty_plik, linia))
			{
				std::vector<std::string> slowa_w_linii = Wojtas::dzielenie_na_slowa(linia);
				for (int nr_slowa = 0; nr_slowa < slowa_w_linii.size(); nr_slowa++)
				{
					for (int ktory_element = 0; ktory_element < przestrzenie_nazw[ktora_przestrzen].elementy_modulu.size(); ktory_element++)
					{
						if (slowa_w_linii[nr_slowa] == przestrzenie_nazw[ktora_przestrzen].elementy_modulu[ktory_element])
						{
							polaczenie::Polaczenie temp(przestrzenie_nazw[ktora_przestrzen].nazwa_przestrzeni);
							pliki[plik].namespacey[ktora_przestrzen].polaczenia_miedzy_namespaceami.push_back(temp);
						}
					}
				}
			}
		} otwarty_plik.close();
	}
	//Sprawdzenie
	/*for (int i = 0; i < pliki.size(); i++)
	{
		for (int j = 0; j < pliki[i].namespacey.size(); j++)
		{
			for (int k = 0; k < pliki[i].namespacey[j].polaczenia_miedzy_namespaceami.size(); k++)
			{
				std::cout << pliki[i].namespacey[j].polaczenia_miedzy_namespaceami[k].nazwa_polaczonego_elementu << std::endl;
			}
		}
	}*/
}