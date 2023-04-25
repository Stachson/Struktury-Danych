#include <iostream>
#include <fstream>
using namespace std;


class Tablica
{
	int rozmiar;
	int *tablica;
		
	public:
		
		Tablica() 
		{
			rozmiar = 0;
		}
	
		~Tablica()
		{
			delete [] tablica;
			tablica = NULL;
			rozmiar = 0;
		}
		
		bool wczytaj_tablice(string nazwa)
		{
			fstream plik;
			plik.open(nazwa.c_str(),ios::in);
			
			if(plik.good() == false)
				return false;
			else
			{
				plik>>rozmiar;                  //wczytanie pierwszej danej z pliku tekstowego, dana ta reprezentuje rozmiar
				tablica = new int[rozmiar];		// zaalokowanie tablicy o rozmiarze wczytanym z pliku tekstowego
				
				for(int i=0;i<rozmiar;i++)
				{
					plik>>*tablica;				// wypelnienie tablicy kolejnymi danymi z pliku tekstowego
					tablica++;	
				}
				tablica = tablica-rozmiar;		// ustawienie wskaznika z powrotem na pierwszy element
			}
			return true;
		}
		
		void wyswietl_tablice()
		{
			if(rozmiar == 0)								// jezeli rozmiar tablicy b�dzie r�wny 0, to tablica si� nie wy�wietli, poniewa� nie istnieje
				cout<<"Tablica nie istnieje"<<endl;
			else
			{	cout<<"Tablica: ";
				for(int i=0;i<rozmiar;i++)
				{
					cout<<*tablica<<" ";				// wy�wietlanie kolejnych element�w tablicy
					tablica++;
				}
				cout<<endl;
				tablica = tablica-rozmiar;				// ustawienie wskaznika z powrotem na pierwszy element
			}		
		}
		
		void dodaj_na_pierwsza_pozycje(int liczba)
		{	
			if(rozmiar==0)					//je�eli rozmiar == 0 , czyli tablica nie istnieje
			{								// to utworzy si� nowa tablica o rozmiarze 1, wypelniona podan� wcze�niej przez u�ytkownika liczb�								
				rozmiar = 1;
				tablica = new int[1];		// alokacja tablicy 1 - elementowej
				tablica[0] = liczba;
			}
			
			else
			{
				rozmiar+=1;						// zzwiekszenie rozmiaru tablicy
				int * nowa_tablica;				// utworzenie wska�nika, kt�ry b�dzie wskazywa� na poczatek nowej tablicy
				nowa_tablica = new int[rozmiar];	//alokacja nowej tablicy z rozmiarem wi�kszym o 1 wzgl�dem wcze�niej istniej�cej tablicy
				nowa_tablica[0] = liczba;			// wypelnienie pierwszego elementu tablicy liczb� podan� wcze�niej przez u�ytkownika
				
				for(int i=1;i<rozmiar;i++)
				{
					nowa_tablica[i] = tablica[i-1];		//kopiowanie element�w ze starej tablicy do nowej
				}										// elementy ze starej tablicy s� kopiowane do nowej tablicy na pozycje o indeksie wi�kszym o 1, poniewa� z racji pojawienia si� nowego elementu na pocz�tku, pozosta�e dane trzeba przesun�� o 1 dalej
				delete [] tablica;						// usuniecie zawartosci starej tablicy
				tablica = nowa_tablica;	
				//nowa_tablica = NULL;				// wska�nik wskazuj�cy na star� tablic� wskazuje teraz na nowy obszar pami�ci, w kt�rej znajduj� si� elementy nowej tablicy
			}
		}
		
		void dodaj_na_ostatnia_pozycje(int liczba)
		{															
			if(rozmiar==0)											
			{
				rozmiar = 1;														// jezeli tablica nie istnieje, to alokacja nowej 1 elementowej tablicy
				tablica = new int[1];
				tablica[0] = liczba;												// przypisanie jedynemu elementowi tablicy wprowadzonej liczby
			}
			else
			{													
				rozmiar+=1;
				int * nowa_tablica;
				nowa_tablica = new int[rozmiar];									// alokacja nowej tablicy o rozmiarze o 1 wiekszym wzgledem starej tablicy
				nowa_tablica[rozmiar-1] = liczba;									// wstawienie podanej liczby na koniec tablicy
				
				for(int i=0;i<rozmiar-1;i++)
				{
					nowa_tablica[i] = tablica[i];									// kopiowanie elemntow ze starej do nowej tablicy, z wylaczeniem ostatniej pozycji nowej tablicy
				}
				delete [] tablica;													// zwolnienie obszaru w pamieci, gdzie zapisane byly elementy starej tablicy
				tablica = nowa_tablica;	
				nowa_tablica = NULL;											// stary wskaznik tablica wskazuje teraz na nowy obszar, w ktorym znajduja sie elementy nowej tablicy
			}
		}
	
		bool dodaj_na_wybrana_pozycje(int index,int liczba)
		{
			if(rozmiar==0 && index>0)
				return false;																						
			else if(index == 0)
			{
				dodaj_na_pierwsza_pozycje(liczba);
				return true;	
			}										
			else if(index == rozmiar)
			{
				dodaj_na_ostatnia_pozycje(liczba);	
				return true;
			}										
			else if(index > 0 && index <rozmiar)							
			{																			// jezeli indeks miesci sie w przedziale tablicy(z wylaczeniem pierwszego elementu), to wykona sie operacja wstawiania na ten indeks liczby															// wprowadzenie liczby, ktora chce sie wstawic
				rozmiar+=1;
				int * nowa_tablica;									
				nowa_tablica = new int[rozmiar];										// alokacja nowej tablicy o rozmairze o 1 wiekszym wzgledem juz istniejacej
				for(int i = 0;i<index;i++)
					nowa_tablica[i] = tablica[i];										// dla indeksow mniejszych niz indeks, na ktory chcemy wstawic element, wykona sie kopiowanie elementow
					
				nowa_tablica[index] = liczba;											// na indeks podany przez uzytkownika wstawiona zostanie liczba podana przez uzytkownika
				
				for(int i =index+1;i<rozmiar;i++)
					nowa_tablica[i] = tablica[i-1];										// wstawienie kolejnych elementow starej tablicy do nowej tablicy, tym razem indeks w nowej tablicy bedzie o 1 wikszy niz w starej tablicy, gdyz zostal dodany nowy element
				
				delete [] tablica;														// zwolnienie obszaru pamieci wskazywanego przez stara tablice
				tablica = nowa_tablica;	
				nowa_tablica = NULL;
				return true;										// stary wskaznik tablica wskazuje teraz na nowy obszar, gdzie znajduje sie nowa tablica
			}
			else
				return false;				// jezeli indeks przekracza rozmiar tablicy, to zadna operacja sie nie wykona
		}
		
		bool usun_z_pierwszej_pozycji()
		{
			if(rozmiar == 0)
				return false;		// jezeli tablica nie istnieje, to operacja sie nie wykona gdyz nie mozemy usunac czegos czego nie ma 
			else
			{
				rozmiar-=1;					
				int * nowa_tablica;
				nowa_tablica = new int[rozmiar];										// alokacja obszaru na nowa tablice, mniejszego o 1 wzgledem istniejacej tablicy
				
				for(int i = 0;i<rozmiar;i++)
					nowa_tablica[i] = tablica[i+1];										// kopiowanie wszystkich elementow starej tablicy z wylaczeniem pierwszego
				
				delete [] tablica;														// zwolnienie obszaru zajmowanego przez stara tablice
				tablica = nowa_tablica;	
				nowa_tablica = NULL;
				return true;												// wskaznik wskazuje teraz na obszar, gdzie znajduje sie nowa tablica
			}	
		}
		
		bool usun_z_ostatniej_pozycji()  
		{
			if(rozmiar == 0)
				return false;		// jezeli tablica nie istnieje, to operacja sie nie wykona gdyz nie mozemy usunac czegos czego nie ma
			else
			{
				rozmiar-=1;
				int * nowa_tablica;														// alokacja nowego obszaru, mneijszego o 1 (4 bajty) wzgledem obszaru uzywanego dla juz istniejacej tablicy
				nowa_tablica = new int[rozmiar];										
																					
				for(int i = 0;i<rozmiar;i++)
					nowa_tablica[i] = tablica[i];										// skopiowanie wszystkich elementow ze starej tablicy z wylaczeniem ostatniego
				
				delete [] tablica;														// zwolnienie obszaru zajetego przez stara tablice
				tablica = nowa_tablica;	
				nowa_tablica = NULL;
				return true;												// wskaznik wskazuje teraz na obszar, gdzie znajduje sie nowa tablica
			}
		}
		
		bool usun_z_wybranej_pozycji(int index)
		{
			if(rozmiar==0)
				return false;															// jezeli tablica nie istnieje to operacja sie nie wykona, poniewaz nie da sie usunac czegos czego nie ma
			else if(index == 0)
			{
				usun_z_pierwszej_pozycji();
				return true;	
			}																			// jezeli uzytkownik chce usunac pierwszy element to wywola sie funkcja do tego przeznaczona
			else if(index == rozmiar-1)
			{
				usun_z_ostatniej_pozycji();	
				return true;
			}											// jezeli uzytkownik chce usunac ostatni element to wywola sie funkcja do tego przeznaczona
			else if(index > 0 && index <rozmiar)
			{																			// jezeli indeks znajduje sie w tablicy, z wylaczeniem pierwszego elementu to wywola sie operacja usuniecia elemntu na tym indeksie
				rozmiar-=1;
				int * nowa_tablica;
				nowa_tablica = new int[rozmiar];										// alokacja obszaru na tablice o 1 wieksza wzgledem poprzedniej
				
				for(int i = 0;i<index;i++)
					nowa_tablica[i] = tablica[i];										// kopiowanie elelentow z indeksow mniejszych niz ten podany przez uzytkownika
					
				for(int i = index;i<rozmiar;i++)
					nowa_tablica[i] = tablica[i+1];										// kopiowanie elementow z indeksow wiekszych niz ten podany przez uzytkownika
					
				delete [] tablica;														// zwolnienie obszaru zajmowanego przez elementy starej tablicy
				tablica = nowa_tablica;	
				nowa_tablica = NULL;
				return true;												// wskaznik tablica wskazuje teraz na nowy obszar, gdzie znajduja sie elementy nowej tablicy
			}
			else
				return false;		
		}
		
		bool wyszukaj_element(int liczba)
		{
			if(rozmiar == 0)
				return false;
			for(int i = 0;i<rozmiar;i++)
			{
				if(tablica[i]==liczba)
					return true;
			}
			return false;				
		}			
};

