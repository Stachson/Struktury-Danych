#include <iostream>
using namespace std;



class Interfejs
{
	public:
		
	void menu_main()
	{
		cout<<"Ktora strukture chcesz zbadac?"<<endl;
		cout<<"1. Tablica"<<endl;
		cout<<"2. Lista"<<endl;
		cout<<"3. Kopiec binarny"<<endl;
		//cout<<"4. Drzewo czerwono-czarne"<<endl;
		cout<<"5. Wyjdz z programu"<<endl;
	}
	
	void menu_tablica()
	{
		cout<<"Wybierz jaka operacje chcesz przeprowadzic"<<endl;
		cout<<"1. Wczytaj tablice z pliku"<<endl;
		cout<<"2. Dodaj element na poczatek"<<endl;
		cout<<"3. Dodaj element na koniec"<<endl;
		cout<<"4. Dodaj element na podana pozycje"<<endl;
		cout<<"5. Usun pierwszy element z tablicy"<<endl;
		cout<<"6. Usun ostatni element z tablicy"<<endl;
		cout<<"7. Usun element o podanej pozycji z tablicy"<<endl;	
		cout<<"8. Wyswietl tablice"<<endl;	
		cout<<"9. Wyszukaj podany element tablicy"<<endl;
	}
	
	void menu_lista()
	{
		cout<<"Wybierz jaka operacje chcesz przeprowadzic"<<endl;
		cout<<"1. Wczytaj liste z pliku"<<endl;
		cout<<"2. Dodaj element na poczatek listy"<<endl;
		cout<<"3. Dodaj element na koniec listy"<<endl;
		cout<<"4. Dodaj element na podana pozycje"<<endl;
		cout<<"5. Usun element z poczatku listy"<<endl;
		cout<<"6. Usun element z konca listy"<<endl;
		cout<<"7. Usun element z wybranej pozycji listy"<<endl;
		cout<<"8. Wyswietl zawartosc listy"<<endl;
		cout<<"9. Wyszukaj podany element listy"<<endl;
	}
	
	void menu_kopiec()
	{
		cout<<"Wybierz jaka operacje chcesz przeprowadzic"<<endl;
		cout<<"1. Wczytaj kopiec z pliku"<<endl;
		cout<<"2. Dodaj element do kopca binarnego"<<endl;
		cout<<"3. Usun element z kopca binarnego"<<endl;
		cout<<"4. Wyszukaj element w kopcu binarnym"<<endl;
		cout<<"5. Wyswietl kopiec binarny"<<endl;
	}
	
	void menu_drzewo_czerwono_czarne()
	{
		cout<<"Wybierz jaka operacje chcesz przeprowadzic"<<endl;
		cout<<"1. Wczytaj drzewo czerwono czarne z pliku"<<endl;
		cout<<"2. Dodaj element do drzewa czerwono czarnego"<<endl;
		cout<<"3. Usun element z drzewa czerwono czarnego"<<endl;
		cout<<"4. Wyszukaj element w drzewie czerwono czarnym"<<endl;
		cout<<"5. Wyswietl drzewo czerwono czarne"<<endl;
	}
	
	
};

			
