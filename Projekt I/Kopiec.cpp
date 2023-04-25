#include <iostream>
#include <fstream>
using namespace std;


class Kopiec
{
	
	int rozmiar;
	int * tablica;
	
	
	public:
		
	Kopiec()
	{
		rozmiar = 0;
	}
	
	~Kopiec()
	{
		delete [] tablica;
		tablica = NULL;
		rozmiar = 0;
	}


		bool wczytaj_kopiec(string nazwa)
		{
			int ilosc;
			int liczba;
			fstream plik;
			plik.open(nazwa.c_str(),ios::in);
			
			if(plik.good() == false)
				return false;
			else
			{
				plik>>ilosc;                  		
				
				for(int i=0;i<ilosc;i++)
				{
					plik>>liczba;
					dodaj_element(liczba);	
				}		
			}
			rozmiar = ilosc;
			return true;
		}
		
		void dodaj_element(int liczba)
		{
			if(rozmiar == 0)
			{
				rozmiar++;
				tablica = new int[rozmiar];
				tablica[0] = liczba;
			}
			else
			{
				rozmiar+=1;						
				int * nowa_tablica;				
				nowa_tablica = new int[rozmiar];	
				nowa_tablica[rozmiar-1] = liczba;
				for(int i = 0;i<rozmiar-1;i++)
				{
					nowa_tablica[i] = tablica[i];		
				}
				
				delete [] tablica;					
				tablica = nowa_tablica;
				
				for(int i = rozmiar-1;i>0;i=(i-1)/2)
				{
					if(tablica[i]>tablica[(i-1)/2]) 
						swap(tablica[i], tablica[(i-1)/2]);	
					else
						break;				
				}
			}	
		}
		
		bool usun_element()
		{
			if(rozmiar == 0)
			{
				return false;
			}
			if(rozmiar == 1)
			{
				rozmiar--;
				delete [] tablica;
				return true;
			}
			else
			{
				rozmiar--;
				int * nowa_tablica;
				nowa_tablica = new int[rozmiar];
				nowa_tablica[0] = tablica[rozmiar];
				for(int i = 1;i<rozmiar;i++)
				{
					nowa_tablica[i] = tablica[i];
				}
				delete [] tablica;					
				tablica = nowa_tablica;
				int i = 0;
				
				while((2*i)+1<rozmiar)
				{
					if((2*i)+2 <rozmiar)
					{
						if(tablica[i] < tablica[2*i+1] && tablica[2*i+1] >= tablica[2*i+2])
						{
							swap(tablica[i], tablica[2*i+1]);
							i = 2*i+1;
						}
						else if(tablica[i] < tablica[2*i+2] && tablica[2*i+2] > tablica[2*i+1])
						{
							swap(tablica[i], tablica[2*i+2]);
							i = 2*i+2;
						}
						else
							break;
					}
					else
					{
						if(tablica[(2*i)+1]>tablica[i])
						{
							swap(tablica[(i*2)+1],tablica[i]);
						}
						i=(2*i)+1;
					}
				}
				return true;
			}	
		}
		
		bool wyszukaj_element(int liczba)
		{
			if(rozmiar == 0)
				return false;
			for(int i = 0;i<rozmiar;i++)
			{
				if(tablica[i] == liczba)
					return true;
			}
			return false;
		}
		
		bool wyswietl()
		{
			if(rozmiar == 0)
				return false;
			else
			{
				int nowa_linijka = 1;
				for(int i = 0;i<rozmiar;i++)
				{
					if(i == nowa_linijka)
					{
						cout<<endl;
						nowa_linijka = i*2+1;
					}
					cout<<tablica[i]<<" ";
				}
				cout<<endl;
				return true;
			}
		}
	
};
