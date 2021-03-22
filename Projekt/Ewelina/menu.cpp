#include "menu.h"

using namespace std;


void menu() {
	char wybor;
	for (;;)
	{
		cout << "MENU GLOWNE" << endl;
		cout << "-----------------" << endl;
		cout << "1. Historyjka 1: Wyswietl graf plikow" << endl;
		cout << "2. Historyjka 2: Wyswietl graf funkcji" << endl;
		cout << "3. Historyjka 3: Wyswietl graf funkcji i modulow" << endl;
		cout << "4. Historyjka 3: Wyswietl graf funkcji i modulow (bez polaczen miedzy funkcjami)" << endl;
		cout << "5. Wyswietl graf samych modulow" << endl;
		cout << "6. Wyswietl graf plikow i modulow" << endl;
		cout << "7. Historyjka 6: Wyswietl graf plikow i funkcji" << endl;
		cout << "8. Historyjka 7: Wyswietl graf funkcji z podzialem na optymalne klastry" << endl;
		cout << "9. WIELKI GRAF WSZYSTKIEGO!!!" << endl;
		cout << "0. Koniec programu" << endl;
		
		cout << endl;


		cout << "Wybor: ";
		cin >> wybor;

		switch (wybor)
		{
		case '1':
			cout << "Historyjka 1: Graf plikow";
			system("start ..\\output\\Graf_plikow.png");
			break;
		case '2':
			cout << "Historyjka 2: Graf funkcji";
			system("start ..\\output\\Graf_funkcji.png");
			break;
		case '3':
			cout << "Historyjka 3: Graf modulow i funkcji";
			system("start ..\\output\\Graf_funkcje_moduly.png");
			break;
		case '4':
			cout << "Historyjka 3: Graf modulow i funkcji (bez polaczen miedzy funkcjami)";
			system("start ..\\output\\Graf_bez_polaczen.png");
			break;
		case '5':
			cout << "Graf modulow";
			system("start ..\\output\\Graf_modulu.png");
			break;
			break;
		case '6':
			cout << "Graf plikow i modulow\n";
			system("start ..\\output\\Graf_pliki_moduly.png");
			break;;
		case '7':
			cout << "Historyjka 6: Graf funkcji i plikow";
			system("start ..\\output\\Graf_pliki_funkcje.png");
			break;
		case '8':
			cout << "Graf funkcji z podzialem na optymalne klastry";
			system("start ..\\output\\Graf_metis_funkcje.png");
			break;
		case '9':
			cout << "Graf wszystkiego";
			system("start ..\\output\\Graf_wszystko.png");
			break;
		case '0':
			exit(0);
			break;		

		default: cout << "Nie ma takiej opcji w menu!";
		}
		getchar();
		system("cls");
	}
}