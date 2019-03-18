#include<iostream>
#include <list>
#include <ctime>

using namespace std;
 
// reprezentacja grafu za pomoc¹ listy s¹siedztwa
class Graf
{
	private:
		// liczba wierzcholkow V
    	int W;   
    	// wskaznik na tablice z lista sasiedztwa
 		list<int> *lista; 
 		//funkcja przeszukujaca graf w glab
    	void DFS(int w, bool done[]); 
    	
	public:
   		Graf(int W);   // konstruktor
    	void dodaj_kr(int w1, int w2); //w=v k=w
    	void spojne();
    	Graf &regular_graf(const int k);
    
    

};



Graf::Graf(int W)
{
    this->W = W;
    lista = new list<int>[W];
}

void Graf::DFS(int w, bool done[])
{

    // oznaczamy aktualny wierzcholek jako odwiedzony i wypisujemy
    done[w] = true;
    cout << w << " ";
   
   
	 
    // rekurencja dla wszystkich sasiadow w, funkcje z <list>
    list<int>::iterator i;
    for(i = lista[w].begin(); i != lista[w].end(); ++i)
        if(!done[*i])
            DFS(*i, done);
              
            
   }

 
// wypisywanie spojnych skladowych
void Graf::spojne()
{
	int temp = 0;
    //oznaczamy wszystkie wierzcholki jako nieoznaczone
    bool *done = new bool[W];
    for(int w = 0; w < W; w++)
        done[w] = false;
 
    for(int w = 0; w < W; w++)
    {
        if (done[w] == false)
        {
            DFS(w, done);
            if(temp == 0){
            		cout << "\nPozostale spojne skladowe: \n";	
			}
			temp++;
			cout << endl;
            
           
        }
    
    }
   
}
 

// dodawanie krawedzi
void Graf::dodaj_kr(int w1, int w2)
{
	//funkcja push_back dodaje na koñcu listy kopiê przekazanego argumentu
    lista[w1].push_back(w2);
    lista[w2].push_back(w1);
}
 
