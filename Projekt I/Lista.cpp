#include <iostream>
#include <fstream>
using namespace std;

class Lista
{
	
	struct Element
	{
		int zawartosc;
		Element * nastepny;
		Element * poprzedni;
	};
	
	Element * glowa; 
	Element * ogon; 
	int ilosc;
	
	public:
		
	Lista()
	{
		glowa = NULL;
		ogon = NULL;
		ilosc = 0;
	}
	
	~Lista()
	{
		while(ilosc!=0)
		usun_z_przodu();
		ilosc = 0;
	}
	
	
	bool wczytaj_z_pliku(string nazwa)
	{
			fstream plik;
			plik.open(nazwa.c_str(),ios::in);
			
			if(plik.good() == false)
				return false;
			else
			{
				plik>>ilosc; 
				int liczba;
				for(int i=0;i<ilosc;i++)
				{
					Element * nowy;
					nowy = new Element;
					
					if(glowa == NULL)
					{
						glowa = new Element;
						ogon = new Element;
						glowa = nowy;
						plik>>glowa->zawartosc;
						glowa->nastepny = NULL;
						glowa->poprzedni = NULL;
						ogon = glowa;
					}
					else
					{
						plik>>nowy->zawartosc;
						nowy->nastepny = NULL;
						nowy->poprzedni = ogon;
						ogon->nastepny = nowy;
						ogon = nowy;
					}
				}                
			}
		return true;		
	}
	
	void dodaj_na_poczatek(int liczba) 
	{
		ilosc++;
		
		if(glowa==NULL)
		{
			glowa = new Element;
			glowa->zawartosc = liczba;
			glowa->poprzedni = NULL;
			glowa->nastepny = NULL;
			ogon = glowa;		
		}
		
		else
		{
			Element * nowy;
			nowy = new Element;
			nowy->zawartosc = liczba;
			nowy->nastepny = glowa;
			nowy->poprzedni = NULL;
			glowa->poprzedni = nowy;
			glowa = nowy;	
		}	
	}
	
	void dodaj_na_koniec(int liczba)   
	{
		ilosc++;
		
		if(glowa==NULL)
		{
			glowa = new Element;
			glowa->zawartosc = liczba;
			glowa->poprzedni = NULL;
			glowa->nastepny = NULL;
			ogon = glowa;
		}
		else
		{
			Element * nowy = new Element;
			nowy->zawartosc = liczba;
			nowy->nastepny = NULL;
			nowy->poprzedni = ogon;
			ogon->nastepny = nowy;
			ogon = nowy;
		}	
	}
	
	bool dodaj_na_wybrana_pozycje(int index,int liczba)
	{
		if(index == 0)
		{
			dodaj_na_poczatek(liczba);
			return true;
		}
		else if(index == ilosc)
		{
			dodaj_na_koniec(liczba);
			return true;
		}
		else if(index > 0 && index < ilosc)
		{
			ilosc++;
			Element * nowy;
			Element * pomoc;
			nowy = new Element;
			
			ogon->nastepny = nowy;
			nowy->nastepny = NULL;
			nowy->poprzedni = ogon;
			nowy->zawartosc = ogon->zawartosc;                 
			pomoc = ogon;
			ogon = nowy;
			for(int i = ilosc-1;i>index+1;i--)
			{
				pomoc->zawartosc = pomoc->poprzedni->zawartosc;
				pomoc=pomoc->poprzedni;	
			}	
			pomoc->zawartosc = liczba;
			return true;
		} 
		else if(index>ilosc+1)
			return false;	
	}
	
	bool usun_z_przodu()
	{
		
		if(glowa == NULL)
			return false;
		else if(glowa->nastepny == NULL)
		{
			ilosc--;
			delete glowa;
			glowa = NULL;   
			ogon = NULL;
			return true;	
		}
		else
		{
			ilosc--;
			Element * nowy;
			nowy = glowa->nastepny;
			delete glowa;
			glowa = nowy;
			glowa->poprzedni = NULL;
			return true;		
		}		
	}
	
	bool usun_z_konca()
	{
		
		if(glowa == NULL)
			return false;
		else if(glowa->nastepny == NULL)
		{
			ilosc--;
			delete glowa;
			glowa = NULL;  
			ogon = NULL;
			return true;	
		}
		else
		{
			ilosc--;
			Element * nowy;
			nowy = ogon->poprzedni;
			delete ogon;
			ogon = nowy;
			ogon->nastepny = NULL;
			return true;
		}
	}
	
	bool usun_z_wybranej_pozycji(int index)
	{
		if(glowa == NULL)
			return false;
		else if(index == 0)
		{
			usun_z_przodu();
			return true;
		}
		else if(index == ilosc-1)
		{
			usun_z_konca();
			return true;
		}
		else if(index>0 && index<ilosc)
		{
			ilosc--;
			Element * nowy;
			Element * pomoc;
			nowy = glowa;
			for(int i = 0;i<index;i++)            
				nowy = nowy->nastepny;
			pomoc = nowy->poprzedni;
			pomoc->nastepny = nowy->nastepny;
			pomoc = nowy->nastepny;
			pomoc->poprzedni = nowy->poprzedni;
			delete nowy;
			return true;	
		}
		else
			return false;
		
	}
	
	void wyswietl_liste()
	{
		if(glowa == NULL)
			cout<<"Lista jest pusta"<<endl;
		else
		{
			Element * nowy;
			nowy = new Element;
			nowy = glowa;
			cout<<"Lista: ";
			for(int i = 0;i<ilosc;i++)
			{
				cout<<nowy->zawartosc<<" ";
				nowy = nowy->nastepny;
			}
	
			delete nowy;
			cout<<endl;
		}
	}	
	
	bool wyszukaj_element(int liczba)
	{
		if(glowa == NULL)
			return false;
		else
		{
			Element * nowy;
			nowy = glowa;
			for(int i =0;i<ilosc;i++)
			{
				if(nowy->zawartosc == liczba)
					return true;
				else
					nowy = nowy->nastepny;
			}
			delete nowy;
			return false;	
		}
	}
};
