#include <iostream>
#include <fstream>
#include "Tablica.cpp"
#include "Lista.cpp"
#include "Interfejs.cpp"
#include "Kopiec.cpp"
#include "Drzewo_czerwono_czarne.cpp"
#include <windows.h>
#include <time.h>
#include <cstdlib>
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

double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double (li.QuadPart - CounterStart)/PCFreq;
}

		//Przyklad mierzenia czasu
		//StartCounter();
    	//Sleep(1000);
    	//cout << GetCounter() <<"\n";
    	//zwraca czas w milisekundach

int main() 
{	
	int tablicatest[20000];
	srand(time(NULL));
	long double czas = 0.0;

	
	int wybor;
	int index;
	int liczba;
	bool wyjscie = true; 
	bool poprawna = false;
	Tablica * tablica;
	Lista * lista;
	Kopiec * kopiec;
	Drzewo_czerwono_czarne * drzewo_czerwono_czarne;
	Interfejs * interfejs;
	interfejs = new Interfejs();
	string nazwa;
		
	interfejs->menu_main();
	cin>>wybor;
	
	switch(wybor)
	{
		case 1:
			tablica = new Tablica();
			do
			{
				interfejs->menu_tablica();
				cin>>wybor;
				
				switch(wybor)
				{
					case 1:
						cout<<"Podaj nazwe pliku z rozszerzeniem txt (nazwa.txt), ktory chcesz wczytac"<<endl;
						cin>>nazwa;
						poprawna = tablica->wczytaj_tablice(nazwa);
						if(!poprawna)
							cout<<"Wczytywanie pliku nie powiodlo sie, prawdopodobnie podano zla nazwe pliku"<<endl;
						break;
					case 2:
						cout<<"Podaj liczbe, ktora chcesz dodac na poczatek tablicy"<<endl;		
						cin>>liczba;
						tablica->dodaj_na_pierwsza_pozycje(liczba);
						break;
					case 3:
						cout<<"Podaj liczbe, ktora chcesz dodac na koniec tablicy"<<endl;		
						cin>>liczba;
						tablica->dodaj_na_ostatnia_pozycje(liczba);
						break;
					case 4:
						cout<<"Podaj index pozycji, na ktory chcesz dodac liczbe"<<endl;
						cin>>index;
						cout<<"Wprowadz liczbe, ktora chcesz dodac na indeks numer "<<index<<endl;
						cin>>liczba;
						poprawna = tablica->dodaj_na_wybrana_pozycje(index,liczba);
						if(!poprawna)
							cout<<"Dodanie elementu na ta pozycje nie powiodlo sie"<<endl;
						break;
					case 5:
						poprawna = tablica->usun_z_pierwszej_pozycji();
						if(!poprawna)
							cout<<"Usuniecie elementu z poczatku nie powiodlo sie"<<endl;
						break;
					case 6:
						poprawna = tablica->usun_z_ostatniej_pozycji();
						if(!poprawna)
							cout<<"Usuniecie elementu z konca nie powiodlo sie"<<endl;
						break;
					case 7:
						cout<<"Podaj index pozycji, z ktorego chcesz usunac liczbe"<<endl;
						cin>>index;
						poprawna = tablica->usun_z_wybranej_pozycji(index);
						if(!poprawna)
							cout<<"Usuniecie elementu z wybranej pozycji nie powiodlo sie"<<endl;
						break;
					case 8:
						tablica->wyswietl_tablice();
						break;
					case 9:
						cout<<"Podaj liczbe, ktora chcesz wyszukac w tablicy"<<endl;
						cin>>liczba;
						poprawna = tablica->wyszukaj_element(liczba);
						
						if(poprawna)
							cout<<"Szukany element znajduje sie w tablicy"<<endl;
						else
							cout<<"W tablicy nie ma szukanego elementu"<<endl;
						break;
							
					default:
						cout<<"Niepoprwany znak"<<endl;
						break;
				} 
			cout<<"Czy chcesz wykonac jeszcze jakies operacje na tablicy?(tak = 1, nie = 0)"<<endl;
			cin>>wyjscie;	
				
			} while(wyjscie!=0);
			break;
		case 2:
			lista = new Lista();
			do
			{
				interfejs->menu_lista();
				cin>>wybor;
				
				switch(wybor)
				{
					case 1:
						cout<<"Podaj nazwe pliku z rozszerzeniem txt (nazwa.txt), ktory chcesz wczytac"<<endl;
						cin>>nazwa;
						poprawna = lista->wczytaj_z_pliku(nazwa);
						if(!poprawna)
							cout<<"Wczytanie pliku nie powiodlo sie, prawdopodobnie podano zla nazwe pliku"<<endl;
						break;
					case 2:
						cout<<"Podaj liczbe, ktora chcesz dodac na poczatek listy"<<endl;
						cin>>liczba;
						lista->dodaj_na_poczatek(liczba);
						break;
					case 3:
						cout<<"Podaj liczbe jaka chcesz dodac na koniec listy"<<endl;
						cin>>liczba;
						lista->dodaj_na_koniec(liczba);
						break;
					case 4:
						cout<<"Podaj liczbe jaka chcesz dodac"<<endl;
						cin>>liczba;
						cout<<"Podaj index pozycji(indeksujemy elementy od 0) na ktory chcesz dodac liczbe"<<endl;
						cin>>index;
						
						poprawna = lista->dodaj_na_wybrana_pozycje(index,liczba);
						if(!poprawna)
							cout<<"Dodawanie na podana pozycje nie powiodlo sie"<<endl;
						break;
					case 5:
						poprawna = lista->usun_z_przodu();
						if(!poprawna)
							cout<<"Usuwanie z przodu nie powiodlo sie"<<endl;
						break;
					case 6:
						poprawna = lista->usun_z_konca();
						if(!poprawna)
							cout<<"Usuwanie z konca nie powiodlo sie"<<endl;
						break;
					case 7:
						cout<<"Podaj index pozycji(indeksujemy elementy od 0), z ktorego chcesz usunac liczbe"<<endl;
						cin>>index;
					
						poprawna = lista->usun_z_wybranej_pozycji(index);
						if(!poprawna)
							cout<<"Usuwanie liczby z podanej pozycji nie powiodlo sie"<<endl;
						break;
					case 8:
						lista->wyswietl_liste();
						break;
					case 9:
						cout<<"Podaj liczbe, ktora chcesz wyszukac"<<endl;
						cin>>liczba;
						poprawna = lista->wyszukaj_element(liczba);
	
						if(poprawna)
							cout<<"Podany element znajduje sie w liscie"<<endl;
						else
							cout<<"Podany element nie znajduje sie w liscie"<<endl;
						break;
					default:
						cout<<"Niepoprawny znak"<<endl;
						break;	
				}	
				cout<<"Czy chcesz wykonac jeszcze jakies operacje na liscie?(tak = 1, nie = 0)"<<endl;
				cin>>wyjscie;
				
			} while (wyjscie!=0);
		
			break;
			
			case 3:
				kopiec = new Kopiec();	
				do
				{
					interfejs->menu_kopiec();
					cin>>wybor;
					switch(wybor)
					{
						case 1:
							cout<<"Podaj nazwe pliku z rozszerzeniem txt (nazwa.txt), ktory chcesz wczytac"<<endl;
							cin>>nazwa;
							poprawna = kopiec->wczytaj_kopiec(nazwa);
							if(!poprawna)
								cout<<"Wczytanie pliku nie powiodlo sie, prawdopodobnie podano zla nazwe pliku"<<endl;
							break;
						case 2:
							cout<<"Podaj liczbe, ktora chcesz dodac do kopca"<<endl;
							cin>>liczba;
							kopiec->dodaj_element(liczba);
							break;
						case 3:
							poprawna = kopiec->usun_element();
							if(!poprawna)
								cout<<"Usuwanie nie powiodlo sie"<<endl;
							break;
						case 4:
							cout<<"Podaj element, ktory chcesz wyszukac"<<endl;
							cin>>liczba;
							poprawna = kopiec->wyszukaj_element(liczba);
							if(!poprawna)
								cout<<"W kopcu nie wystepuje szukany element"<<endl;
							else
								cout<<"Szukany element znajduje sie w kopcu"<<endl;
							break;
						case 5:
							poprawna = kopiec->wyswietl();
							if(!poprawna)
								cout<<"Kopiec jest pusty"<<endl;
							break;		
						default:
							cout<<"Wprowadzono niew³aœciwy znak"<<endl;
							break;
					}
					cout<<"Czy chcesz wykonac jeszcze jakies operacje na kopcu?(tak = 1, nie = 0)"<<endl;
					cin>>wyjscie;
				} while(wyjscie!=0);
				break;
			case 4:
				drzewo_czerwono_czarne = new Drzewo_czerwono_czarne();
				do
				{
					interfejs->menu_drzewo_czerwono_czarne();
					cin>>wybor;
					switch(wybor)
					{
						case 1:
							cout<<"Podaj nazwe pliku z rozszerzeniem txt (nazwa.txt), ktory chcesz wczytac"<<endl;
							cin>>nazwa;
							poprawna = drzewo_czerwono_czarne->wczytaj_z_pliku(nazwa);
							if(!poprawna)
								cout<<"Wczytanie pliku nie powiodlo sie, prawdopodobnie podano zla nazwe pliku"<<endl;
							break;
						case 2:
							cout<<"Podaj liczbe, ktora chcesz dodac do drzewa czerwono czarnego"<<endl;
							cin>>liczba;
							poprawna = drzewo_czerwono_czarne->dodaj_element(liczba);
							break;
						case 3:
							poprawna = drzewo_czerwono_czarne->usun_element();
							if(!poprawna)
								cout<<"Usuwanie nie powiodlo sie"<<endl;
							break;
						case 4:
							cout<<"Podaj element, ktory chcesz wyszukac"<<endl;
							cin>>liczba;
							poprawna = drzewo_czerwono_czarne->wyszukaj_element(liczba);
							if(!poprawna)
								cout<<"W drzewie czerwono czarnym nie wystepuje szukany element"<<endl;
							else
								cout<<"Szukany element znajduje sie w drzewie czerwono_czarnym"<<endl;
							break;
						case 5:
							poprawna = drzewo_czerwono_czarne->wyswietl();
							if(!poprawna)
								cout<<"Drzewo czerwono czarne jest puste"<<endl;
							break;
				
						default:
								cout<<"Wprowadzono niew³aœciwy znak"<<endl;
								break;
						}
					cout<<"Czy chcesz wykonac jeszcze jakies operacje na drzewie czerwono czarnym?(tak = 1, nie = 0)"<<endl;
					cin>>wyjscie;
				} while(wyjscie!=0);
		case 5:	
			break;
		default:
			cout<<"Niepoprawny znak"<<endl;
			break;
	}
	
	
	
}
