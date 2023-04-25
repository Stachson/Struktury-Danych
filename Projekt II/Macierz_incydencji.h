#ifndef MACIERZ_INCYDENCJI_H
#define MACIERZ_INCYDENCJI_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;


class Macierz_incydencji
{
	
	int n; // ilosc wierzcholkow
	int m; // ilosc krawedzi
	
	int **A;
	
	
	public:
		
		Macierz_incydencji();
		~Macierz_incydencji();
		bool zbuduj_z_pliku_skierowany(string nazwa);
		bool zbuduj_z_pliku_nieskierowany(string nazwa);
		bool wypisanie();
		void czyszczenie();
		void wygeneruj_losowo_skierowany(int liczba_wierzcholkow, int zageszczenie,int startowy, Macierz_incydencji * macierz);
		void wygeneruj_losowo_nieskierowany(int liczba_wierzcholkow, int zageszczenie,int startowy, Macierz_incydencji * macierz);
		void dijkstry_macierz(Macierz_incydencji * macierz_incydencji, int startowy);
		void prima_macierz(Macierz_incydencji * macierz_incydencji, int startowy);
		bool bellman_ford(Macierz_incydencji * macierz, int startowy);
			
	
};

#endif
