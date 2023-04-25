#ifndef LISTA_SASIEDZTWA_H
#define LISTA_SASIEDZTWA_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Lista_sasiedztwa
{
	
	int n; // ilosc wierzcholkow
	int m; // ilosc krawedzi
		
	struct Element
	{
		Element * nastepny;
		int wierzcholek;
		int waga_nastepna;
	};
	
	Element **A;
	
	public:
	
	Lista_sasiedztwa();
	~Lista_sasiedztwa();
	bool zbuduj_z_pliku_skierowany(string nazwa);
	bool zbuduj_z_pliku_nieskierowany(string nazwa);
	bool wypisanie();
	void czyszczenie();
	void wygeneruj_losowo_skierowany(int liczba_wierzcholkow, int zageszczenie, int startowy, Lista_sasiedztwa * lista_sasiedztwa);
	void wygeneruj_losowo_nieskierowany(int liczba_wierzcholkow, int zageszczenie, Lista_sasiedztwa * lista);
	void dijkstry_lista(Lista_sasiedztwa * lista_sasiedztwa,int startowy);
	void prima_lista(Lista_sasiedztwa * lista_sasiedztwa, int startowy);
	bool bellman_ford_lista(Lista_sasiedztwa * lista, int startowy);
	
	
	
};

#endif
