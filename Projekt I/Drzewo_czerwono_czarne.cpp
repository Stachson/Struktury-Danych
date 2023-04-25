#include <iostream>
#include <fstream>
using namespace std;

class Drzewo_czerwono_czarne
{
	
	struct Element
	{
		int zawartosc;
		Element * rodzic;
		Element * lewy_syn;
		Element * prawy_syn;
		char kolor;
	};
	
	int ilosc;
	Element * korzen;
	
	//Przryklad dostawania sie do elementow struktury
	//Element * nowy;
	//nowy = new Element;
	//nowy->zawartosc = liczba;
	
	public:
		
		Drzewo_czerwono_czarne()
		{
			ilosc = 0;
			korzen = NULL;	
		}
		//void rotacja_w_prawo(Element * tymczasowy1)
	//	{
		//	Element * tymczasowy2 = tymczasowy1->lewy_syn;
		//	tymczasowy1->lewy_syn = tymczasowy2->prawy_syn;
		//	tymczasowy2->rodzic = tymczasowy1->rodzic;
		//	tymczasowy2->prawy_syn = tymczasowy1;
		//	tymczasowy1->rodzic = tymczasowy2;		
	//	}
		
	//	void rotacja_w_lewo(Element * tymczasowy1)
		//{
			//Element * tymczasowy
		//	
		//}
		
		bool wczytaj_z_pliku(string nazwa)
		{
			fstream plik;
			plik.open(nazwa.c_str(),ios::in);
			
			if(plik.good() == false)
				return false;
			else
			{
				
				
			}
			return true;	
		}
		
		bool dodaj_element(int liczba)
		{
			//cout<<"test1"<<endl;
			
			if(ilosc == 0)
			{
				ilosc++;
				korzen = new Element;
				korzen->zawartosc = liczba;
				korzen->rodzic = NULL;
				korzen->lewy_syn = NULL;
				korzen->prawy_syn = NULL;
				korzen->kolor = 'B'; // B-black
			}
			else
			{
				ilosc++;
				Element * nowy = new Element;
				nowy->zawartosc = liczba;
				
				Element * tymczasowy;
				tymczasowy = korzen;
			
				while(true)
				{
					if(nowy->zawartosc < tymczasowy->zawartosc)
					{
						if(tymczasowy->lewy_syn == NULL)     //jesli brak lewego syna to w jego miejsce wstawiamy nowe element
						{	
							nowy->rodzic = tymczasowy;    //inicjalizacja danych
							nowy->lewy_syn = NULL;
							nowy->prawy_syn = NULL;
							nowy->kolor = 'R';
							
							tymczasowy->lewy_syn = nowy;	//lewy syn staje sie teraz dodanym elementem
							tymczasowy = tymczasowy->lewy_syn;    //przestawienie tymczasowgo na nowy element
							break;
						}
						tymczasowy = tymczasowy->lewy_syn;  //jesli lewy syn nie byl nullem to przechodzimy na niego i zaczynamy algorytm od poczatku	
					}
					else if(nowy->zawartosc >= tymczasowy->zawartosc)
					{
						if(tymczasowy->prawy_syn == NULL)  // jesli brak prawego syna to w jego miejsce wstawiamy nowy element
						{
							nowy->rodzic = tymczasowy;    //inicjaliacja danych
							nowy->lewy_syn = NULL;
							nowy->prawy_syn = NULL;
							nowy->kolor = 'R';
							
							tymczasowy->prawy_syn = nowy;     //prawy syn staje sie teraz nowym elementem
							tymczasowy = tymczasowy->prawy_syn; // przestawienie tymczasowego na nowy element    
							break;
						}
						tymczasowy = tymczasowy->prawy_syn;    //jesli prawy syn nie byl nullem to przechodzimy na niego i zaczynamy algorytm od poczatku
					}
				} // po wstawieniu elementu:
				
				//sprawdzenie czy zastala zachowana struktura drzewa
				if(nowy->rodzic->kolor = 'B')
					return true;  // struktura drzewa nie naruszona, mozna wyjsc z funkcji :)
				else // sprawdzenie 3 przypadkow po dodaniu elementu do drzewa. Sprawdzenie tez ich lustrzanych odbic
				{
					while(true)
					{
						//Przypadek I Wujek C wstawianego wezla jest czerwony. Przypadek z wujkiem po prawej
						if(tymczasowy->rodzic->rodzic->prawy_syn->kolor == 'R')
						{
							tymczasowy->rodzic->kolor = 'B';
							tymczasowy->rodzic->rodzic->prawy_syn->kolor = 'B';
							tymczasowy->rodzic->rodzic->kolor = 'R';
							
							if(tymczasowy->rodzic->rodzic = korzen)
							{
								tymczasowy->rodzic->rodzic->kolor = 'B';
								return true;  // drzewo uporzadkowane, koniec metody
							}
							else
								tymczasowy = tymczasowy->rodzic->rodzic;  //koniec przypadku I, wracamy do poczaku petli while
						}
						else if(tymczasowy->rodzic->rodzic->lewy_syn->kolor == 'R')   // Lustrzane odbicie przypadku I
						{
							tymczasowy->rodzic->kolor = 'B';
							tymczasowy->rodzic->rodzic->lewy_syn->kolor = 'B';
							tymczasowy->rodzic->rodzic->kolor = 'R';
							
							if(tymczasowy->rodzic->rodzic = korzen)
							{
								tymczasowy->rodzic->rodzic->kolor = 'B';
								return true;  // drzewo uporzadkowane, koniec metody
							}
							else
								tymczasowy = tymczasowy->rodzic->rodzic;  //koniec lustrzango odbicia przypadku I, wracamy do poczaku petli while
						}
						else if(tymczasowy->rodzic->rodzic->prawy_syn->kolor == 'B' && tymczasowy == tymczasowy->rodzic->prawy_syn) //Przypadek II wujek C jest czarny, a wezel X jest prawym dzieckiem wezla B
						{
							//rotacja_w_lewo(tymczasowy->rodzic);
							Element * tymczasowy1 = tymczasowy->rodzic->prawy_syn;
							tymczasowy->rodzic->prawy_syn = tymczasowy1->lewy_syn;
							tymczasowy1->rodzic = tymczasowy->rodzic->rodzic;
							tymczasowy1->lewy_syn = tymczasowy->rodzic;
							tymczasowy->rodzic->rodzic = tymczasowy1;
							////
							//if(tymczasowy1->rodzic == NULL)
							//	korzen = tymczasowy1;
									
						}
						else if(tymczasowy->rodzic->rodzic->lewy_syn->kolor == 'B' && tymczasowy == tymczasowy->rodzic->lewy_syn) // lustrzane odbicie przypadku II
						{
							//rotacja_w_prawo(tymczasowy->rodzic);	
							Element * tymczasowy1 = tymczasowy->rodzic->lewy_syn;
							tymczasowy->rodzic->lewy_syn = tymczasowy1->prawy_syn;
							tymczasowy1->rodzic = tymczasowy->rodzic->rodzic;
							tymczasowy1->prawy_syn = tymczasowy->rodzic;
							tymczasowy->rodzic->rodzic = tymczasowy1;	
							////
							//if(tymczasowy1->rodzic == NULL)
							//	korzen = tymczasowy1;
						}
						else if(tymczasowy->rodzic->rodzic->prawy_syn->kolor == 'B' && tymczasowy == tymczasowy->rodzic->lewy_syn) //Przypadek III wujek C jest czarny, a wezel X jest lewym dzieckiem wezla B
						{
							//rotacja_w_prawo(tymczasowy->rodzic->rodzic);
							Element * tymczasowy1 = tymczasowy->rodzic->rodzic->lewy_syn;
							tymczasowy->rodzic->rodzic->lewy_syn = tymczasowy1->prawy_syn;
							tymczasowy1->rodzic = tymczasowy->rodzic->rodzic->rodzic;
							tymczasowy1->prawy_syn = tymczasowy->rodzic->rodzic;
							tymczasowy->rodzic->rodzic->rodzic = tymczasowy1;
							///
						//if(tymczasowy1->rodzic == NULL)
						//		korzen = tymczasowy1;
							//zmiana koloru wezla A
							if(tymczasowy->rodzic->prawy_syn->kolor == 'B')
								tymczasowy->rodzic->prawy_syn->kolor = 'R';
							else if(tymczasowy->rodzic->prawy_syn->kolor == 'R')
								tymczasowy->rodzic->prawy_syn->kolor = 'B';
							//zmiana koloru wezla B
							if(tymczasowy->rodzic->kolor == 'B')
								tymczasowy->rodzic->kolor = 'R';
							else if(tymczasowy->rodzic->kolor == 'R')
								tymczasowy->rodzic->kolor = 'B';
							return true;
						}
						else if(tymczasowy->rodzic->rodzic->lewy_syn->kolor == 'B' && tymczasowy == tymczasowy->rodzic->prawy_syn) // lustrzane odbicie przypadku III
						{
							//rotacja_w_lewo(tymczasowy->rodzic->rodzic);
							Element * tymczasowy1 = tymczasowy->rodzic->rodzic->prawy_syn;
							tymczasowy->rodzic->rodzic->prawy_syn = tymczasowy1->lewy_syn;
							tymczasowy1->rodzic = tymczasowy->rodzic->rodzic->rodzic;
							tymczasowy1->lewy_syn = tymczasowy->rodzic->rodzic;
							tymczasowy->rodzic->rodzic->rodzic = tymczasowy1;
							////
							//if(tymczasowy1->rodzic == NULL)
							//	korzen = tymczasowy1;
							//zmiana koloru wezla B
							if(tymczasowy->rodzic->lewy_syn->lewy_syn->kolor == 'B')
								tymczasowy->rodzic->lewy_syn->lewy_syn->kolor = 'R';
							else if(tymczasowy->rodzic->lewy_syn->lewy_syn->kolor == 'R')
								tymczasowy->rodzic->lewy_syn->lewy_syn->kolor = 'B';
							//zmiana koloru wezla A
							if(tymczasowy->rodzic->lewy_syn->kolor == 'B')
								tymczasowy->rodzic->lewy_syn->kolor = 'R';
							else if(tymczasowy->rodzic->lewy_syn->kolor = 'R')
								tymczasowy->rodzic->lewy_syn->kolor = 'B';
							return true;
						}
					}
				}
			}
			
		}
		
		bool usun_element()
		{
			
			
		}
		
		bool wyszukaj_element(int liczba)
		{
			
			
		}
	
		bool wyswietl()
		{
			if(korzen == NULL)
				return false;
			else
			{
				Element * nowy;
				nowy = korzen;
				cout<<nowy->zawartosc<<nowy->kolor<<" ";
				if(nowy->lewy_syn == NULL)
					cout<<"null"<<" ";
				else
					cout<<nowy->lewy_syn->zawartosc<<nowy->lewy_syn->kolor<<" ";
				if(nowy->prawy_syn == NULL)
					cout<<"null"<<" ";
				else
					cout<<nowy->prawy_syn->zawartosc<<nowy->prawy_syn->kolor<<" ";
					
				///
				if(nowy->lewy_syn->lewy_syn == NULL)
					cout<<"null"<<" ";
				else
					cout<<nowy->lewy_syn->lewy_syn->zawartosc<<nowy->lewy_syn->lewy_syn->kolor<<" ";
				if(nowy->lewy_syn->prawy_syn == NULL)
					cout<<"null"<<" ";
				else
					cout<<nowy->lewy_syn->prawy_syn->zawartosc<<nowy->lewy_syn->prawy_syn->kolor<<" ";
					
					
				if(nowy->prawy_syn->lewy_syn == NULL)
					cout<<"null"<<" ";
				else
					cout<<nowy->prawy_syn->lewy_syn->zawartosc<<nowy->prawy_syn->lewy_syn->kolor<<" ";
				if(nowy->prawy_syn->prawy_syn == NULL)
					cout<<"null"<<" ";
				else
					cout<<nowy->prawy_syn->prawy_syn->zawartosc<<nowy->prawy_syn->prawy_syn->kolor<<" ";
				return true;
			}
			
		}
};
