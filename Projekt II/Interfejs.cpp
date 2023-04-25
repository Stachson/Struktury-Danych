#include "Interfejs.h"



	

		void Interfejs::menu_glowne()
		{
			cout<<"1. Problem MST"<<endl;
			cout<<"2. Problem najkrotszej drogi w grafie"<<endl;	
			cout<<"3. Wyjscie z programu"<<endl;
		}
		
		void Interfejs::menu_struktury()
		{
			cout<<"1. Macierz incydencji"<<endl;
			cout<<"2. Lista sasiedztwa"<<endl;
		}
		
		void Interfejs::menu_MST()
		{
			cout<<"1. Wczytaj dane z pliku"<<endl;
			cout<<"2. Wygeneruj graf losowo"<<endl;
			cout<<"3. Wyswietl graf na ekranie"<<endl;
			cout<<"4. Algorytm Prima z wyswielteniem wynikow"<<endl;
			cout<<"5. Algorytm Kruskala z wyswietleniem wynikow"<<endl;
		}
		
		void Interfejs::menu_NSWG()
		{
			cout<<"1. Wczytaj dane z pliku"<<endl;
			cout<<"2. Wygeneruj graf losowo"<<endl;
			cout<<"3. Wyswietl graf na ekranie"<<endl;
			cout<<"4. Algorytm Dijkstry"<<endl;
			cout<<"5. Algorytm Forda-Bellmana"<<endl;
		}



