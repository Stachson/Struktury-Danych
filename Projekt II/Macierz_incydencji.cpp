#include "Macierz_incydencji.h"


// Dla grafów nieskierowanych krawêdzie bêd¹ przy dwóch wierzcho³kach opisane
// Zapewniæ aby generowane losowo grafy by³y spójne
// Dla macierzy incydencji wagi mo¿na wpisaæ dodatnio i ujemnie, tak samo jak za³o¿y³em wczeœniej 
// s¹ rózne sposoby zapewnienia sobie tej spojnosci 
// lista sasiedztwa jest dobrze zaimplementowana

	

		
		Macierz_incydencji::Macierz_incydencji()
		{
			n = 0;
			m = 0;
		}
		Macierz_incydencji::~Macierz_incydencji()
		{
			czyszczenie();
			A = NULL;
		}
		
		bool Macierz_incydencji:: zbuduj_z_pliku_skierowany(string nazwa)
		{
			int poczatkowy, koncowy, waga;
			fstream plik;
			plik.open(nazwa.c_str(),ios::in);
			
			
			if(plik.good() == false)
				return false;
			else
			{
				//[i][j] to bedzie tez [j][i] w nieskierowanym
				plik>>m;
				plik>>n;
				
				A = new int * [n];
				
				for(int i = 0;i<n;i++)
				{
					A[i] = new int [m];
				}
				
				for(int i = 0;i<n;i++)
				{
					for(int j = 0;j<m;j++)
						A[i][j] = 0;
				}
				
				for(int i = 0;i<m;i++)
				{
					plik>>poczatkowy>>koncowy>>waga;
					A[poczatkowy][i] = waga;
					A[koncowy][i] = waga * (-1);
				}	
			}
			return true;
		}
		
		bool Macierz_incydencji::zbuduj_z_pliku_nieskierowany(string nazwa)
		{
			int poczatkowy, koncowy, waga;
			fstream plik;
			plik.open(nazwa.c_str(),ios::in);
			
			
			if(plik.good() == false)
				return false;
			else
			{
				//[i][j] to bedzie tez [j][i] w nieskierowanym
				plik>>m;
				plik>>n;
				
				A = new int * [n];
				
				for(int i = 0;i<n;i++)
				{
					A[i] = new int [m];
				}
				
				for(int i = 0;i<n;i++)
				{
					for(int j = 0;j<m;j++)
						A[i][j] = 0;
				}
				
				for(int i = 0;i<m;i++)
				{
					plik>>poczatkowy>>koncowy>>waga;
					A[poczatkowy][i] = waga;
					A[koncowy][i] = waga;
				}	
			}
			return true;
		}
		
		bool Macierz_incydencji::wypisanie()
		{
			if(m==0 || n==0)
				return false;
				
			cout<<"     ";
			for(int i = 0; i<m;i++)
				printf("%5d", i);
				//cout<<i<<" ";
			cout<<endl;
			
			for(int i = 0;i<n;i++)
			{
				printf("%5d", i);
				//cout<<i<<"   ";
				for(int j = 0;j<m;j++)
				printf("%5d", A[i][j]);
				//	cout<<A[i][j]<<" ";
				cout<<endl;
			}
			return true;
		}
		
		void Macierz_incydencji::czyszczenie()
		{
			if( n!= 0)
			{	
				for(int i = 0;i<n;i++)
				{
					delete [] A[i];
				}
				delete [] A;	
			}
			m=0;
			n=0;
		}
		
	void Macierz_incydencji::wygeneruj_losowo_skierowany(int liczba_wierzcholkow, int zageszczenie,int startowy, Macierz_incydencji * macierz)
	{
		int waga, poczatkowy, koncowy, pomin;
		macierz->czyszczenie();  //czyszczenie poprzedniej struktury
		n = liczba_wierzcholkow;
		m = (zageszczenie*(liczba_wierzcholkow * (liczba_wierzcholkow - 1))/2)/100;  // obliczenie liczby krawedzi do wylosowania
		
	//	cout<<"Ilosc do wygenerowania"<<m<<endl;
		
		srand(time(NULL));
		
		A = new int * [n];   // alokacja kolumn macierzy
			
		//tworzenie tablicy dwuwymiarowej
		for(int i = 0;i<n;i++)
			A[i] = new int [m];	//alokacja wierszy macierzy
		
		//wypelnianie tablicy zerami	
		for(int i = 0;i<n;i++)
		{
			for(int j = 0;j<m;j++)
				A[i][j]=0;
		}	
		
		int j = 0;
		for(int i = 0; i < n; i++)		// zapewnienie spojnosci grafu poprzez polaczenie wierzcholka startowego z kazdym innym wierzcholkiem
		{
			waga = rand() % 100 + 1;
			//startowy
			if(i!= startowy)
			{
				A[startowy][j] = waga;
				A[i][j] = waga * (-1);
				j++;
			}
		}
		
	//	wypisanie();
		
	//	int liczba_krawedzi_do_dodania = m - (n-1);   // obliczenie ilosci pozostalych krawedzi do dodania
		
			for(int j = n-1; j < m; j++)
			{
				poczatkowy = rand() % (n-1) + 1;			// losowanie wierzcholka poczatkowego
				koncowy = rand() % (n-1) + 1;
				if(poczatkowy == startowy || koncowy == startowy)
					{
						j--;
						continue;
					}
				//poczatkowy = poczatkowy - (rand() % (n-1) + 0);				// losowanie wierzcholka koncowego
				//koncowy = koncowy - (rand() % (n-1) + 0);	
				
				if(poczatkowy == koncowy)					// jesli wylosowana krawedz jest petla, to powtarzamy
				{
					j--;
					continue;
				}
				
				waga = rand() % 100 + 1;			// losowanie wagi
				
				pomin = 0;
				
				for(int krawedz = 0; krawedz < m; krawedz++)
				{
					if(A[poczatkowy][krawedz] != 0 && A[koncowy][krawedz] != 0)
					{
						pomin = 1;
						//cout<<"wylosowany poczatek "<<poczatkowy<<" wylosowany koniec "<<koncowy<<endl;
						//wypisanie();
					//	cout<<endl;
					//	cout<<endl;
					}
				}
				
				if(pomin == 0 )
				{
					A[poczatkowy][j] = waga;
					A[koncowy][j] = waga * (-1);
				//	cout<<"dodanie krawedzi"<<endl;
				//	wypisanie();
				//	cout<<endl;
				//	cout<<j<<endl;
					
				}
				else						// w przeciwnym razie powtarzamy losowanie
				{
					j--;
					continue;	
				}
			}	
		
	}
	
	void Macierz_incydencji::wygeneruj_losowo_nieskierowany(int liczba_wierzcholkow, int zageszczenie,int startowy, Macierz_incydencji * macierz)
	{
		int waga, poczatkowy, koncowy, pomin;
		macierz->czyszczenie();  //czyszczenie poprzedniej struktury
		n = liczba_wierzcholkow;
		m = (zageszczenie*(liczba_wierzcholkow * (liczba_wierzcholkow - 1))/2)/100;  // obliczenie liczby krawedzi do wylosowania
		
	//	cout<<"Ilosc do wygenerowania"<<m<<endl;
		
		srand(time(NULL));
		
		A = new int * [n];   // alokacja kolumn macierzy
			
		//tworzenie tablicy dwuwymiarowej
		for(int i = 0;i<n;i++)
			A[i] = new int [m];	//alokacja wierszy macierzy
		
		//wypelnianie tablicy zerami	
		for(int i = 0;i<n;i++)
		{
			for(int j = 0;j<m;j++)
				A[i][j]=0;
		}	
		
		int j = 0;
		for(int i = 0; i < n; i++)		// zapewnienie spojnosci grafu poprzez polaczenie wierzcholka startowego z kazdym innym wierzcholkiem
		{
			waga = rand() % 100 + 1;
			//startowy
			if(i!= startowy)
			{
				A[startowy][j] = waga;
				A[i][j] = waga;
				j++;
			}
		}
		
	//	wypisanie();
		
	//	int liczba_krawedzi_do_dodania = m - (n-1);   // obliczenie ilosci pozostalych krawedzi do dodania
		
			for(int j = n-1; j < m; j++)
			{
				poczatkowy = rand() % (n-1) + 1;			// losowanie wierzcholka poczatkowego
				koncowy = rand() % (n-1) + 1;
				if(poczatkowy == startowy || koncowy == startowy)
					{
						j--;
						continue;
					}
				//poczatkowy = poczatkowy - (rand() % (n-1) + 0);				// losowanie wierzcholka koncowego
				//koncowy = koncowy - (rand() % (n-1) + 0);	
				
				if(poczatkowy == koncowy)					// jesli wylosowana krawedz jest petla, to powtarzamy
				{
					j--;
					continue;
				}
				
				waga = rand() % 100 + 1;			// losowanie wagi
				
				pomin = 0;
				
				for(int krawedz = 0; krawedz < m; krawedz++)
				{
					if(A[poczatkowy][krawedz] != 0 && A[koncowy][krawedz] != 0)
					{
						pomin = 1;
						//cout<<"wylosowany poczatek "<<poczatkowy<<" wylosowany koniec "<<koncowy<<endl;
						//wypisanie();
					//	cout<<endl;
					//	cout<<endl;
					}
				}
				
				if(pomin == 0 )
				{
					A[poczatkowy][j] = waga;
					A[koncowy][j] = waga;
				//	cout<<"dodanie krawedzi"<<endl;
				//	wypisanie();
				//	cout<<endl;
				//	cout<<j<<endl;
					
				}
				else						// w przeciwnym razie powtarzamy losowanie
				{
					j--;
					continue;	
				}
			}	
		
	}
	
	void Macierz_incydencji::dijkstry_macierz(Macierz_incydencji * macierz_incydencji, int startowy)
	{
		
		int s = startowy; // ustawienie wierzcholka poczatkowego
		int min;
		int * d = new int [n]; // przechowuje odleglosci od wierzcholka startowego
		int * p = new int [n]; // zbiór poprzedników
		int * Q = new int [n]; // zbior wierzcholkow nieprzebadanych
		int indeks_do_usuwania;
		
		for(int i = 0;i<n;i++)
		{
			d[i] = 	2147483647; // traktujemy jako nieskonczonosc
			p[i] = -1; // wierzcholek poczatkowy Nieokreslony
			Q[i] = i; 
		}
		d[s] = 0; // ustawienie odleglosci od startowego na 0 w wierzcholku startowym
		
		int ilosc_nieprzebadanych = n;
		int najmniejszy;
		
		while(ilosc_nieprzebadanych != 0)
		{
			int krawedz;
			int waga;
			int koncowy;
			
			min = 2147483647;
			
			for(int i = 0;i<ilosc_nieprzebadanych;i++)
			{
				if(d[Q[i]]<=min)
				{
					min = d[Q[i]];
					najmniejszy = Q[i];	// i z nieprzebadanych, numerem wierzcholka bêdzie Q[i]
					indeks_do_usuwania = i;
				}
			}
			if(min == 2147483647)
			{
				cout<<"Brak rozwi¹zania";
					break;
			}
		
			
			for(int i = 0; i<m; i++)
			{
				if(A[najmniejszy][i]>0)
				{
					krawedz = i;
					waga=A[najmniejszy][i];
					
					for(int j = 0; j<n; j++)
					{
						if(A[j][krawedz]<0)
						{
							koncowy = j;
						}
					}
					
					if(d[koncowy] > d[najmniejszy] + waga)
					{
						d[koncowy] = d[najmniejszy] + waga;
						p[koncowy] = najmniejszy;
					}	
				}			
			}
				ilosc_nieprzebadanych-=1;
				int * nowa_tablica;
				nowa_tablica = new int[ilosc_nieprzebadanych];
				
				
				for(int i = 0;i<indeks_do_usuwania;i++)
						nowa_tablica[i] = Q[i];										
					
				
				for(int i = indeks_do_usuwania; i<ilosc_nieprzebadanych;i++)
						nowa_tablica[i] = Q[i+1];
				
				delete [] Q;
				
				Q = nowa_tablica;	
				nowa_tablica = NULL;
				
				
				
		}	
		cout<<endl;
		cout<<endl<<" Startowy = "<< startowy <<endl;
    	cout<< "  Wierzcholek   Dlugosc sciezki   Sciezka"<<endl;
    	d[startowy] = 0;

    	for(int i = 0 ; i < n ; i++)
		{
        	if(d[i] != 2147483647)
			{
            	printf(" %4d | %4d | ", i, d[i]);
           	int temp = i;

            while(d[temp] != 2147483647 && temp != startowy)
			{
            	cout<< " " << temp;
            	temp = p[temp];
			}
            cout<<" "<<startowy;
        	}
		else 
			printf(" %4d |  inf | ", i);
        cout<<endl;
		}
	}
	
	
	void Macierz_incydencji::prima_macierz(Macierz_incydencji * macierz_incydencji, int startowy)
	{
		int s = startowy;
		int * p = new int [n]; // zbiór poprzedników
		int * Q = new int [n]; // zbior wierzcholkow nieprzebadanych
		int * key = new int[n]; // wagi najmniejszych 
		int indeks_do_usuwania;
		int ilosc_nieprzebadanych = n;
		int min;
		int najmniejszy;
		int krawedz;
		int waga;
		int koncowy;
		
		for(int i = 0;i<n;i++)
		{
			key[i] = 2147483647;
			p[i] = -1;
			Q[i] = i;
		}	
		key[s] = 0;
		p[s] = -1;
			
		while(ilosc_nieprzebadanych != 0)
		{
			min = 2147483647;
			
			for(int i = 0;i<ilosc_nieprzebadanych;i++)
			{
				if(key[Q[i]]<=min)
				{
					min = key[Q[i]];
					najmniejszy = Q[i];	// i z nieprzebadanych, numerem wierzcholka bêdzie Q[i]
					indeks_do_usuwania = i;
				}
			}	
			
			ilosc_nieprzebadanych-=1;
			int * nowa_tablica;
			nowa_tablica = new int[ilosc_nieprzebadanych];
			
			for(int i = 0;i<indeks_do_usuwania;i++)
				nowa_tablica[i] = Q[i];										
						
			for(int i = indeks_do_usuwania; i<ilosc_nieprzebadanych;i++)
				nowa_tablica[i] = Q[i+1];
				
			delete [] Q;
				
			Q = nowa_tablica;	
			nowa_tablica = NULL;
			
		
		for(int i = 0; i<m; i++)
			{
				if(A[najmniejszy][i] != 0)
				{
					krawedz = i;
					waga=A[najmniejszy][i];
					
					for(int j = 0; j<n; j++)
					{
						if(A[j][krawedz] != 0 && j != krawedz)
						{
							koncowy = j;
						}
					}
					for(int i = 0; i<ilosc_nieprzebadanych;i++)
					{
					
						if(waga < key[koncowy] && koncowy == Q[i])
						{
							key[koncowy] = waga;
							p[koncowy] = najmniejszy;
						}
					}
				}			
			}
		}
		
		int suma_MST = 0;
		for(int i = 0; i<n; i++)
		{
			if(key[i] != 2147483647)
				suma_MST += key[i];
		}
		cout<<endl;
		cout<<"Suma MST: "<<suma_MST<<endl;
		cout<<"Drzewo rozpinaj¹ce: "<<endl;
		for(int i = 0;i<n;i++)
		{
			if(key[i]!=2147483647 && p[i]!=-1)
			{
				cout<<"Wierzcholek: "<<i<<". poprzednik: "<<p[i]<<", waga krawedzi: "<<key[i]<<endl;
			}	
		}		
	}
	
	bool Macierz_incydencji::bellman_ford(Macierz_incydencji * macierz, int startowy)
	{
		int s = startowy;
		int min;
		int * d = new int [n]; // tablica aktualnych odleglosci od wierzcholka startowego
		int * p = new int [n]; // tablica poprzedzaj¹cych wierzcho³ków w najkrótszej drodze
		bool test;
		int poczatkowy;
		int koncowy;
		int waga;
		int krawedz;
		
		for(int i = 0;i<n;i++) // ustawiamy wszystkie komorki tablicy d na nieskonczonosc, a tablicy p na brak poprzednika
		{
			d[i] = 2147483000; // traktujemy jako nieskonczonosc
			p[i] = -1; // -1 = N czyli brak poprzednika
		}
		d[s] = 0; // ustawienie odleglosci od startowego na 0 w wierzcholku startowym
		
		
		for(int i = 1;i<n;i++)  // n -1 obiegow petli, poniwaz mamy juz droge dla kazdego wierzcholka, wiec musimy ustalic koszt dojscia do n-1 wierzcholkow
		{
			test = true;
			for(int x = 0;x < n;x++)  // przegladamy po kolei wszystkie wierzcholki grafu
			{
				
				for(int  y = 0; y<m; y++) // sprawdzenie wszystkich sasiadow wierzcholka j, sasiadow oznaczamy jako y
				{
					if(A[x][y] > 0)
					{
						waga = A[x][y];
						poczatkowy = x;
						krawedz = y;
						for(int j = 0; j<n; j++)
						{
							if(A[j][krawedz] == waga * (-1))
							{
								koncowy = j;
								break;
							}
						}
					
						if(d[koncowy] > d[poczatkowy] + waga )   // sprawdzenie warunku relaksacji zgodnie ze wzorem, dwa ostatnie warunki sprawdzaja czy krawedz istnieje
						{		
							test = false;													
							d[koncowy] = d[poczatkowy] + waga;	// relaksacja krawedzi
							p[koncowy] = poczatkowy;
						}
						
						
					} 
				}
				//if(test)
				//return true;    
			}	
		}
		
		
		// sprawdzenie czy nie wyszedl cykl ujemny
		for(int i = 0; i<n ; i++)
		{
			for(int j = 0; j<m; j++)
			{
				if(A[i][j] > 0)
				{
					poczatkowy = i;
					krawedz = j;
					waga = A[i][j];
					for(int k = 0; k<n; k++)
					{
						if(waga == A[k][j] * (-1))
						{
							koncowy = k;
							break;
						}
					}
					if(d[koncowy] > d[poczatkowy] + waga)
						return false;
				}
				
			}
		}
		
		
		
	cout<<endl<<" Startowy = "<< startowy <<endl;
    	cout<< "  Wierzcholek   Dlugosc sciezki   Sciezka"<<endl;
    	d[startowy] = 0;

    	for(int i = 0 ; i < n ; i++)
		{
        	if(d[i] != 2147483647)
			{
            	printf(" %4d | %4d | ", i, d[i]);
           	int temp = i;

            while(d[temp] != 2147483647 && temp != startowy)
			{
            	cout<< " " << temp;
            	temp = p[temp];
			}
            cout<<" "<<startowy;
        	}
		else 
			printf(" %4d |  inf | ", i);
        cout<<endl;
		}
		return true;	
	}
	
	
