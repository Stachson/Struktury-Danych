#include <iostream>
#include "Interfejs.h"
#include "Lista_sasiedztwa.h"
#include "Macierz_incydencji.h"
#include <windows.h>
#include <time.h>
//#include "Lista_sasiedztwa.h"
using namespace std;

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
	LARGE_INTEGER li;
	if(!QueryPerformanceFrequency(&li))
		cout<<"QueryPerformanceFrequency failed!"<<endl;
		
	PCFreq = double(li.QuadPart)/1000000000.0;
	
	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

	//Przyklad mierzenia czasu
		//StartCounter();
    	//Sleep(1000);
    	//cout << GetCounter() <<"\n";
    	//zwraca czas w milisekundach

double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double (li.QuadPart - CounterStart)/PCFreq;
}





int main()
{
	Interfejs * interfejs = new Interfejs;
	int wybor;
	int wyjscie;
	int poprawna;
	int startowy;
	int zageszczenie;
	int ilosc_wierzcholkow;
	string nazwa;
	Macierz_incydencji * macierz_incydencji;
	Lista_sasiedztwa * lista_sasiedztwa;
	
	/*
	macierz_incydencji = new Macierz_incydencji;
	lista_sasiedztwa = new Lista_sasiedztwa;
	long long int suma = 0;
	int gestosc = 25;
	int wierzcholki = 170;
	for(int i = 0; i<50;i++)
	{
		macierz_incydencji->wygeneruj_losowo_skierowany(wierzcholki, gestosc, 0, macierz_incydencji);
		StartCounter();
			macierz_incydencji->bellman_ford(	macierz_incydencji, 0);
		suma = suma + GetCounter();
	}
	cout<<"Sredni czas dla gestosci "<<gestosc<<" = "<<suma/50<<endl;
	
	gestosc = 50;
	
	for(int i = 0; i<50;i++)
	{
		macierz_incydencji->wygeneruj_losowo_skierowany(wierzcholki, gestosc, 0, macierz_incydencji);
		StartCounter();
			macierz_incydencji->bellman_ford(	macierz_incydencji, 0);
		suma = suma + GetCounter();
	}
	cout<<"Sredni czas dla gestosci "<<gestosc<<" = "<<suma/50<<endl;
	
	gestosc = 75;
	
	for(int i = 0; i<50;i++)
	{
		macierz_incydencji->wygeneruj_losowo_skierowany(wierzcholki, gestosc,0, macierz_incydencji);
		StartCounter();
			macierz_incydencji->bellman_ford(	macierz_incydencji, 0);
		suma = suma + GetCounter();
	}
	cout<<"Sredni czas dla gestosci "<<gestosc<<" = "<<suma/50<<endl;
	
	gestosc = 99;
	
	for(int i = 0; i<50;i++)
	{
	macierz_incydencji->wygeneruj_losowo_skierowany(wierzcholki, gestosc,0, macierz_incydencji);
		StartCounter();
		macierz_incydencji->bellman_ford(	macierz_incydencji, 0);
		suma = suma + GetCounter();
	}
	cout<<"Sredni czas dla gestosci "<<gestosc<<" = "<<suma/50<<endl;
	
	*/

	
	
	
	
	
	interfejs ->menu_glowne();
	cin>>wybor;
	switch(wybor)
	{
		case 1: // Po wybraniu MST
			interfejs->menu_struktury();
			cin>>wybor;
			switch(wybor)
			{
				case 1: // Po wybraniu MST i macierzy
					macierz_incydencji = new Macierz_incydencji();
					do
					{
						interfejs->menu_MST();
						cin>>wybor;
						switch(wybor)
						{
							case 1: // MST wczytaj dane z pliku macierz
								cout<<"Podaj nazwe pliku z zakonczeniem .txt"<<endl;
								cin>>nazwa;
								poprawna = macierz_incydencji->zbuduj_z_pliku_nieskierowany(nazwa);
								if(!poprawna)
									cout<<"Niepowodzenie"<<endl;
								break;
							case 2: // MST Wygeneruj graf losowo macierz
								cout<<"Podaj liczbe wierzcholkow"<<endl;
								cin>>ilosc_wierzcholkow;
								cout<<"Podaj gestosc grafu"<<endl;
								cin>>zageszczenie;
								macierz_incydencji->wygeneruj_losowo_nieskierowany(ilosc_wierzcholkow, zageszczenie, 0, macierz_incydencji);
								break;
							case 3: // MST wyswietl graf na ekranie macierz
								poprawna = macierz_incydencji->wypisanie();
								if(!poprawna)
									cout<<"Macierz jest pusta"<<endl;
								break;
							case 4: //MST PRIM macierz
								cout<<"Podaj wierzcholek startowy"<<endl;
								cin>>startowy;
								macierz_incydencji->prima_macierz(macierz_incydencji, startowy);
								break;
							case 5: // MST KRUSKAL macierz
								cout<<"Ten algorytm nie zosta³ zaimplementowany"<<endl;
								break;
							default: 
								cout<<"Nieprawidlowy znak"<<endl;
								break;	
						}
					cout<<"Czy chcesz wykonac jeszcze jakas operacje?(tak = 1/ nie = 0)"<<endl;
					cin>>wyjscie;
					} while(wyjscie != 0);	
					
					//czyszczenie macierzy
					macierz_incydencji->czyszczenie();
					
					break;
				case 2: // Po wybraniu MST i listy
					
					lista_sasiedztwa = new Lista_sasiedztwa();
					
					do
					{
						interfejs->menu_MST();
						cin>>wybor;
						switch(wybor)
						{
							case 1: // MST wczytaj dane z pliku lista
								cout<<"Podaj nazwe pliku tekstowego z koncowka .txt"<<endl;
								cin>>nazwa;
								poprawna = lista_sasiedztwa->zbuduj_z_pliku_nieskierowany(nazwa);
								if(!poprawna)
									cout<<"Niepowodzenie"<<endl;
								break;
							case 2: // MST Wygeneruj graf losowo lista
								cout<<"Podaj liczbe wierzcholkow"<<endl;
								cin>>ilosc_wierzcholkow;
								cout<<"Podaj gestosc grafu"<<endl;
								cin>>zageszczenie;
								lista_sasiedztwa->wygeneruj_losowo_nieskierowany(ilosc_wierzcholkow, zageszczenie, lista_sasiedztwa);
								break;
							case 3: // MST wyswietl graf na ekranie lista
								poprawna = lista_sasiedztwa->wypisanie();
								if(!poprawna)
									cout<<"Lista jest pusta"<<endl;
								break;
							case 4: //MST PRIM lista
								cout<<"Podaj wierzcholek startowy"<<endl;
								cin>>startowy;
								lista_sasiedztwa->prima_lista(lista_sasiedztwa, startowy);
								break;
							case 5: // MST KRUSKAL lista
								cout<<"Ten algorytm nie zosta³ zaimplementowany"<<endl;
								break;
							default: 
								cout<<"Nieprawidlowy znak"<<endl;
								break;	
							}
						cout<<"Czy chcesz wykonac jeszcze jakies operacje?(tak = 1/ nie = 0)"<<endl;
						cin>>wyjscie;
					} while (wyjscie != 0);
					
					lista_sasiedztwa -> czyszczenie();
					
					break;	
				default:
					cout<<"Nieprawidlowy znak"<<endl;
					break;
			}
			break;
		case 2: // Po wybraniu NSWG
			interfejs->menu_struktury();
			cin>>wybor;
			switch(wybor)
			{
				case 1: // Po wybraniu NSWG i macierz
					macierz_incydencji = new Macierz_incydencji();
					do
					{
						interfejs->menu_NSWG();
						cin>>wybor;
						switch(wybor)
						{
							case 1: // NSWG wczytaj dane z pliku macierz
								cout<<"Podaj nazwe pliku tesktowego z koncowka .txt"<<endl;
								cin>>nazwa;
								poprawna = macierz_incydencji->zbuduj_z_pliku_skierowany(nazwa);
								if(!poprawna)
									cout<<"Niepowodzenie"<<endl;
								break;
							case 2: // NSWG wygeneruj graf losowo macierz
								cout<<"Podaj liczbe wierzcholkow"<<endl;
								cin>>ilosc_wierzcholkow;
								cout<<"Podaj gestosc grafu"<<endl;
								cin>>zageszczenie;
								macierz_incydencji->wygeneruj_losowo_skierowany(ilosc_wierzcholkow, zageszczenie, 0, macierz_incydencji);
								break;
							case 3: // NSWG wyswietl graf na ekranie macierz
								poprawna = macierz_incydencji->wypisanie();
								if(!poprawna)
									cout<<"Macierz jest pusta"<<endl;
								break;
							case 4: // NSWG Dijsktry macierz
								cout<<"Podaj wierzchlek startowy"<<endl;
								cin>>startowy;
								macierz_incydencji->dijkstry_macierz(macierz_incydencji, startowy);
								break;
							case 5: // NSWG Bellman Ford macierz
								cout<<"Podaj wierzcholek startowy"<<endl;
								cin>>startowy;
								poprawna = macierz_incydencji->bellman_ford(macierz_incydencji, startowy);
								if(!poprawna)
									cout<<"Wykryto cykl ujmeny"<<endl;
								break;
							default:
								cout<<"Nieprawidlowy znak"<<endl;
								break;	
						}
						cout<<"Czy chcesz wykonac jeszcze jakies operacje? (1 = tak / 0 = nie)"<<endl;
						cin>>wyjscie;
						
					} while(wyjscie != 0);
					macierz_incydencji -> czyszczenie();
					break;
				case 2: // NSWG i lista
					lista_sasiedztwa = new Lista_sasiedztwa();
					do
					{
						interfejs->menu_NSWG();
						cin>>wybor;
						switch(wybor)
						{
							case 1: // NSWG wczytaj dane z pliku lista
								cout<<"Podaj nazwe pliku tesktowego z koncowka .txt"<<endl;
								cin>>nazwa;
								poprawna = lista_sasiedztwa->zbuduj_z_pliku_skierowany(nazwa);
								if(!poprawna)
									cout<<"Niepowodzenie"<<endl;
								break;
							case 2: // NSWG wygeneruj graf losowo lista
								cout<<"Podaj liczbe wierzcholkow"<<endl;
								cin>>ilosc_wierzcholkow;
								cout<<"Podaj gestosc grafu"<<endl;
								cin>>zageszczenie;
								cout<<"Podaj wierzcholek startowy"<<endl;
								cin>>startowy;
								lista_sasiedztwa->wygeneruj_losowo_skierowany(ilosc_wierzcholkow, zageszczenie, 0, lista_sasiedztwa);
								break;
							case 3: // NSWG wyswietl graf na ekranie lista
								poprawna = lista_sasiedztwa->wypisanie();
								if(!poprawna)
									cout<<"Lista jest pusta"<<endl;
								break;
							case 4: // NSWG Dijsktry lista
								cout<<"Podaj wierzcholek poczatkowy"<<endl;
								cin>>startowy;
								lista_sasiedztwa->dijkstry_lista(lista_sasiedztwa, startowy);
								break;
							case 5: // NSWG Bellman Ford lista
								cout<<"Podaj wierzcholek startowy"<<endl;
								cin>>startowy;
								poprawna = lista_sasiedztwa->bellman_ford_lista(lista_sasiedztwa, startowy);
								if(!poprawna)
									cout<<"Wykryto cykl ujemny"<<endl;
								break;
							default:
								cout<<"Nieprawidlowy znak"<<endl;
								break;		
						}
						cout<<"Czy chcesz wykonac jeszcze jakies operacje? (tak = 1 / nie = 0)"<<endl;
						cin>>wyjscie;
						
					} while (wyjscie != 0);
					
					lista_sasiedztwa -> czyszczenie();
					
					break;
				default:
					cout<<"Nieprawidlowy znak"<<endl;
					break;	
			}
			break;
		case 3:
			return 0;
		
		default:
			cout<<"Nieprawidlowy znak"<<endl;
			break;	
	}
	
		
}

