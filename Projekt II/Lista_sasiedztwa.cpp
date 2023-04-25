#include "Lista_sasiedztwa.h"


	// w pliku: liczba krawedzi, liczba wierzcholkow
	// w kolejnych liniach opis krawedzi (wierzcholek poczatkowy, wierzcholek, koncowy, waga)
		
		Lista_sasiedztwa::Lista_sasiedztwa()
		{
			m = 0;
			n = 0;
		}
		
		Lista_sasiedztwa::~Lista_sasiedztwa()
		{
			czyszczenie();
			A = NULL;
		}
		
		
		bool Lista_sasiedztwa:: zbuduj_z_pliku_skierowany(string nazwa)
		{
			int poczatkowy, koncowy, waga;
			fstream plik;
			plik.open(nazwa.c_str(),ios::in);
			
			if(plik.good() == false)
				return false;
			else
			{
				plik>>m;
				plik>>n;
				
				A = new Element * [n]; // tworzenie tablicy list sasiedztwa
				
				
				for(int i = 0;i<n;i++)
					A[i] = NULL;
					
					
				for(int i = 0;i<m;i++)
				{
					plik>>poczatkowy>>koncowy>>waga;
					Element * nowy;
					nowy = new Element;
					nowy->wierzcholek = koncowy;
					nowy->waga_nastepna = waga;
					nowy->nastepny = A[poczatkowy];
					A[poczatkowy] = nowy;	
				}
			}
			return true;
		}
		
		
		bool Lista_sasiedztwa::zbuduj_z_pliku_nieskierowany(string nazwa)
		{
			int poczatkowy, koncowy, waga;
			fstream plik;
			plik.open(nazwa.c_str(),ios::in);
			
			if(plik.good() == false)
				return false;
			else
			{
				plik>>m;
				plik>>n;
				
				A = new Element * [n]; // tworzenie tablicy list sasiedztwa
				
				
				for(int i = 0;i<n;i++)
					A[i] = NULL;
					
					
				for(int i = 0;i<m;i++)
				{
					plik>>poczatkowy>>koncowy>>waga;
					Element * nowy1;
					nowy1 = new Element;
					nowy1->wierzcholek = koncowy;
					nowy1->waga_nastepna = waga;
					nowy1->nastepny = A[poczatkowy];
					A[poczatkowy] = nowy1;
					
					Element * nowy2;
					nowy2 = new Element;
					nowy2->wierzcholek = poczatkowy;
					nowy2->waga_nastepna = waga;
					nowy2->nastepny = A[koncowy];
					A[koncowy] = nowy2;	
				}
			}
			return true;
		}
		
		
		bool Lista_sasiedztwa::wypisanie()
		{
			if(m==0 || n==0)
				return false;
				
			Element * nowy;
			for(int i = 0;i<n;i++)
			{
				cout<<"A ["<<i<<"] = ";
				nowy = A[i];
				while(nowy)
				{
					cout<<nowy->wierzcholek<<":";
					cout<<nowy->waga_nastepna<<" ";
					nowy = nowy -> nastepny;
				}
				cout<<endl;
			}
			return true;
		}
		
		
	void Lista_sasiedztwa::czyszczenie()
	{
		Element *p,*r;
		for(int i = 0;i<n;i++)
		{
			p = A[i];
			while(p)
			{
				r=p;
				p = p->nastepny;
				delete r;
			}
		}
		if(n != 0)
			delete [] A;
		m=0;
		n=0;
	}
	
	void Lista_sasiedztwa::wygeneruj_losowo_skierowany(int liczba_wierzcholkow, int zageszczenie, int startowy, Lista_sasiedztwa * lista_sasiedztwa)
	{
		int waga, poczatkowy, koncowy,pomin;
		lista_sasiedztwa->czyszczenie();
		n = liczba_wierzcholkow;
		m = (zageszczenie*(liczba_wierzcholkow * (liczba_wierzcholkow - 1))/2)/100;  // obliczamy ilosc krawedzi do dodania
		
		srand(time(NULL));
		
		A = new Element * [n]; // tworzenie tablicy list sasiedztwa
					
		for(int i = 0;i<n;i++)
			A[i] = NULL;
			
		for(int i = 0;i<n;i++)   // utworzenie polaczen miedzy wierzcholkiem startowym, a kazdym innym wierzcholkiem, tak by zapewnic spojnosc grafu
		{
			if(i != startowy)    // jako wierzcholek koncowy bedziemy traktowac iterator i. Nie mo¿e byæ równy wierzcholkowi startowemu, tak by nie powstaly petle
			{
				poczatkowy = startowy;   // poczatkowym wierzcholkiem generowanej krawedzi bedzie nasz wierzcholek startowy
				koncowy = i;   // koncowym wierzcholiem bedzie wartosc iteratora i
				waga = rand() % 100 + 1; // waga krawedzi losowana z zakresu 1 do 100
				
				Element * nowy;				// utworzenie nowego elementu listy i nadanie mu odpowiednich wartoœci
				nowy = new Element;				// algorytm zgodny z tym, ktory tworzy liste z pliku
				nowy->wierzcholek = koncowy;
				nowy->waga_nastepna = waga;
				nowy->nastepny = A[poczatkowy];
				A[poczatkowy] = nowy;	
			}
		}
		
		
		int liczba_krawedzi_do_dodania = m - (n-1);   // obliczenie ilosci krawedzi, ktore zostaly nam do wygenerowania po generacji krawedzi zapewniaj¹cych spójnoœæ grafu
			
		for(int i = 0;i<liczba_krawedzi_do_dodania;i++) // generowanie tylu krawêdzi ile brakuje
		{
			poczatkowy = rand() % (n-1);                  // losowanie wierzcholka poczatkowego
			koncowy = rand() % (n-1);						// losowanie wierzcholka koncowego
			if(poczatkowy == koncowy || poczatkowy == startowy)  // jezeli wylosowano te samo wierzcholki lub wierzcholek poczatkowy jest wierzcholkiem startowym to powtarzamy losowanie
			{
				i--;												// robimy tak, poniewaz nie chcemy robic petli ani tworzyc kilku krawedzi miedzy tymi samymi wierzcholkami
				continue;
			}
			Element * spr;
			spr = A[poczatkowy];						// ustrawienei wskaznika na pierwszego sasiada wylosowanego wierzcholka poczatkowego
			while(spr)
			{
				if(spr->wierzcholek == koncowy)			// sprawdzenie czy podana krawedz juz istnieje, jezeli tak, to bedziemy powtarzac losowanie
				{										// bedzie nas o tym informowac wartosc zmiennej "pomin"
					pomin = 1;
					break;
				}
				spr = spr->nastepny;					// przechodzimy przez wszystkich sasiadow naszego wierzcholka poczatkowego
				pomin = 0;
			}
			if(pomin == 1)
			{
				i--;
				continue;								// powtorzenie losowania jezeli krawedz miedzy wylosowanymi wierzcholkami juz istnieje
			}
			waga = rand() % 100 + 1;					// wylosowanie wagi nowej krawedzi
			
			Element * nowy;
				nowy = new Element;						// dodanie nowej krawedzi do struktury
				nowy->wierzcholek = koncowy;			// algorytm taki sam jak przy generowaniu struktury z pliku
				nowy->waga_nastepna = waga;
				nowy->nastepny = A[poczatkowy];
				A[poczatkowy] = nowy;	
		}	
	}
	
	void Lista_sasiedztwa::wygeneruj_losowo_nieskierowany(int liczba_wierzcholkow, int zageszczenie, Lista_sasiedztwa * lista)
	{
		int waga, poczatkowy, koncowy,pomin;
		lista->czyszczenie();
		n = liczba_wierzcholkow;
		m = (zageszczenie*(liczba_wierzcholkow * (liczba_wierzcholkow - 1))/2)/100;  // obliczamy ilosc krawedzi do dodania
		
		srand(time(NULL));
		
		A = new Element * [n]; // tworzenie tablicy list sasiedztwa
					
		for(int i = 0;i<n;i++)
			A[i] = NULL;
		
		
		for(int i = 1;i<n;i++)   // utworzenie polaczen miedzy wierzcholkiem startowym, a kazdym innym wierzcholkiem, tak by zapewnic spojnosc grafu
			{
				poczatkowy = 0;
				koncowy = i;
				waga = rand() % 100 + 1;
				
				Element * nowy;
				nowy = new Element;
				nowy->wierzcholek = koncowy;
				nowy->waga_nastepna = waga;
				nowy->nastepny = A[poczatkowy];
				A[poczatkowy] = nowy;	
				
				Element * nowy2;
                nowy2 = new Element;
                nowy2->wierzcholek = poczatkowy;
                nowy2->waga_nastepna = waga;
                nowy2->nastepny = A[koncowy];
                A[koncowy] = nowy2;		
			}
			
		int liczba_krawedzi_do_dodania = m - (n-1);  // obliczamy liczbe pozostalych krawedzi do dodania
		
		for(int i = 0;i<liczba_krawedzi_do_dodania;i++)
		{
			poczatkowy = rand() % (n-1) + 1; //losujemy wierzcholek poczatkowy
			koncowy = rand() % (n-1) + 1;	// losujemy wierzcholek koncowy
			if(poczatkowy == koncowy)
			{
				i--;			// nie chcemy dodac petli
				continue;
			}
			Element * spr;
			spr = A[poczatkowy];  // wskaznik ustawiamy na pierwszego sasiada poczatkowego
			while(spr)				// sprawdzamy czy wylosowana krawedz juz istnieje
			{
				if(spr->wierzcholek == koncowy)
				{
					pomin = 1;
					break;
				}
				spr = spr->nastepny;
				pomin = 0;
			}
			if(pomin == 1)   // jesli tak to powtarzamy losowanie
			{
				i--;
				continue;
			}
			waga = rand() % 100 + 1;  // losujemy wage 
			
			Element * nowy;				// dodajemy nowa krwaedz do struktury
				nowy = new Element;
				nowy->wierzcholek = koncowy;
				nowy->waga_nastepna = waga;
				nowy->nastepny = A[poczatkowy];
				A[poczatkowy] = nowy;	
				
				Element * nowy2;
                nowy2 = new Element;
                nowy2->wierzcholek = poczatkowy;
                nowy2->waga_nastepna = waga;
                nowy2->nastepny = A[koncowy];
                A[koncowy] = nowy2;	
		}
	}
		
		
	void Lista_sasiedztwa::dijkstry_lista(Lista_sasiedztwa * lista_sasiedztwa,int startowy)
	{
		int s = startowy; // ustawienie wierzcholka poczatkowego
		int min;
		int * d = new int [n]; // przechowuje odleglosci od wierzcholka startowego
		int * p = new int [n]; // zbiór poprzedników
		int * Q = new int [n]; // zbior wierzcholkow nieprzebadanych
		Element * nowy;
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
			
			nowy = A[najmniejszy];
					
				while(nowy)
				{
					if(d[nowy->wierzcholek] > d[najmniejszy] + nowy->waga_nastepna)
					{
						d[nowy->wierzcholek] = d[najmniejszy] + nowy->waga_nastepna;
						p[nowy->wierzcholek] = najmniejszy;
					}
					nowy = nowy->nastepny;
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
	
	
	void Lista_sasiedztwa::prima_lista(Lista_sasiedztwa * lista_sasiedztwa, int startowy)
	{
		int s = startowy;
		int * p = new int [n]; // zbiór poprzedników
		int * Q = new int [n]; // zbior wierzcholkow nieprzebadanych
		int * key = new int[n]; // wagi najmniejszych 
		Element * nowy;
		int indeks_do_usuwania;
		int ilosc_nieprzebadanych = n;
		int min;
		int najmniejszy;
		
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
			nowy = A[najmniejszy];
			
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
			
			while(nowy)
			{
				for(int i = 0;i<ilosc_nieprzebadanych;i++)
				{
					if(nowy->waga_nastepna < key[nowy->wierzcholek] && nowy->wierzcholek == Q[i])
					{
						key[nowy->wierzcholek] = nowy->waga_nastepna;
						p[nowy->wierzcholek] = najmniejszy;
					}
				}
				nowy = nowy->nastepny;
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
	
	
	bool Lista_sasiedztwa::bellman_ford_lista(Lista_sasiedztwa * lista, int startowy)
	{
		int s = startowy;
		bool test;
		Element * nowy;
		int * d = new int [n]; // tablica aktualnych odleglosci od wierzcholka startowego
		int * p = new int [n]; // tablica poprzedzaj¹cych wierzcho³ków w najkrótszej drodze
		
		for(int i = 0;i<n;i++)
		{
			d[i] = 2147483647; // traktujemy jako nieskonczonosc
			p[i] = -1; // -1 = N brak poprzednikow
		}
		
		d[s] = 0;
		
		for(int i = 1;i<n;i++) // n-1 obiegow zeby zrelaksowac n-1 pozosta³ych nam wierzcholkow, bo poczatkowy juz jest zrelaksowany
		{
			test = true;
			for(int j = 0;j<n;j++)  // j oznacza wierzcholek poczatkowy
			{
				nowy = A[j];	
				while(nowy)		// przegladamy wszystkich sasiadow poczatkowego
				{
					if(d[nowy->wierzcholek] > d[j] + nowy->waga_nastepna && d[j] != 2147483647 ) // relaskacja wierzcholkow sasiadujacych 
					{
						test = false;	
						d[nowy->wierzcholek] = d[j] + nowy->waga_nastepna;  
						p[nowy->wierzcholek] = j;
						
					}
					nowy = nowy->nastepny; // przejscie na kolejengo sasiada
				}
			//	if(test)
			//		return true;    //to utuchomic na potrzeby testow dopiero ///////////////////////////// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
			}	
		}
		
		//sprawdzenie czy nie ma cyklu ujemnego
		for(int i = 0;i<n;i++)
		{
			nowy = A[i];
			while(nowy)
			{
				if(d[nowy->wierzcholek] > d[i] + nowy->waga_nastepna)
					return false;
				nowy=nowy->nastepny; 
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
	


	

