#include <iostream>
#include <cstdlib>
#include <time.h>
#define MAX 99999
using namespace std;

//tworzenie grafu
void stworz_graf(int **mac, int size, float praw)
{
	int i,j;
	//zmienna do prawdopodobienstwa
	double los;
	
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			//losuje prawdopodobienstwo
			los=((double)rand() / (RAND_MAX + 1));
			//jezeli mniejsze niz podane uzupelniam macierz i zapewniam ze diagonala jest zerowa
			if(los<praw && i!=j)
				mac[i][j]=1;
		}
	}
}
//========================================================
//=================Algorytm Kosaraju======================
//========================================================

//zmienna zapamietujaca ilosc elementow na stosie
int lel=0;

//funkcja dodajaca wierzcholki do stosu
void dodaj_do_stosu(int start, int *visit,int *s,int **mac,int size)
{
	int i;
	//visit-tablica wierzcholkow odwiedzonych
	//oznaczam wierzcholek jako odwiedzony
	visit[start]=1;
	for(i=0;i<size;i++)
	{
		//jezeli ma polaczenie z innym wierzcholkiem
		if(mac[start][i]!=0)
		{
			//i ten wierzcholek nie byl jeszcze odwiedzony
			if(visit[i]==0)
			{	//sprawdzam jego sasiadow
				dodaj_do_stosu(i,visit,s,mac,size);
			}
		}
	}
	//dodaje wierzcholek do stosu
	s[lel]=start; 
	lel++;
}

//funkcja wypisujaca skladowe
void wypisz(int start, int *visit,int **mac,int size)
{
	int i;
	//oznaczam wierzcholek jako odwiedzony
	visit[start]=1;
	//wypiuje wierzcholek
	for(i=0;i<size;i++)
	{
		//jezeli ma polaczenie z innym wierzcholkiem
		if(mac[start][i]!=0)
		{	
			//i ten wierzcholek nie byl jeszcze odwiedzony
			if(visit[i]==0)
			{
				//wypisuje jego sasiadow
				wypisz(i,visit,mac,size);
			}
		}
	}
	cout<<start+1<<" ";
}

//algorytm Kosaraju
void Kosaraju(int size, int **mac,int skladowa)
{
	int i,next;
	//tworze tablice odwiedzonych
	int *vis=new int [size];
	for(i=0;i<size;i++)
		vis[i]=0;
		
	//tworze stos
	int *stos=new int [size];
	for(i=0;i<size;i++)
		stos[i]=0;
	int j;
	//wypelniam stos
	for(i=0;i<size;i++)
	{
		if(vis[i]==0)
			dodaj_do_stosu(i, vis,stos,mac,size);
	}
	
	int tmp;
	//transponuje macierz (odwracam krawedzie)
	for(i=0;i<size;i++)
	{
		for(j=i+1;j<size;j++)
		{
			tmp=mac[i][j];
			mac[i][j]=mac[j][i];
			mac[j][i]=tmp;
		}
	}
	
	cout<<endl;
	//sprawdzam czy macierz transponowana jest prawid³owa
	/*cout<<"Macierz transponowana:\n";
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			cout<<mac[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;*/
	
	//ustawaiam wierzcholki jako nieodwiedzone
	for(i=0;i<size;i++)
		vis[i]=0;
	
	//wypisuje skladowe
	cout<<"\nSilnie spojne skladowe:\n";
	//dopoki stos nie jest pusty
	while(lel>0)
	{
		//pobieram element ze stosu
		next=stos[lel-1];
		//jezeli nie byl odwiedzony
		if(vis[next]==0)
		{
			//wypisuje ktora to skladowa
			cout<<skladowa+1<<": ";
			skladowa++;
			//wypisuje jej wierzcholki
			wypisz(next,vis,mac,size);
			cout<<endl;
		}
		//wyrzucam element ze stosu
		lel--;
	}
}

int Relax(int u, int v, int* d, int** p, int** G, int size)
{
	if (d[v] > (d[u] + G[u][v]))
	{
		//std::cout << u << " " << v << std::endl;
		//std::cout << d[u] << " " << d[v] << " " << G[u][v] << std::endl;
		d[v] = d[u] + G[u][v];
		//std::cout << d[v] << std::endl;
		for (int i = 0; i < size; i++)
		{
			if (p[v][i] == -1)
			{
				p[v][i] = u;
				break;
			}
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

int Check(int* d, int**p, int** G, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (G[i][j] != 0)
			{
				if (Relax(i,j,d,p,G,size) == 1)
				{
					cout << "Istnieje cykl wag ujemnych" << endl;
					return 1;
				}
			}

		}
	}
	return 0;
}

int Bellman_Ford(int** G, int sr, int size, int* d, int** p, int & cf)
{
	int i, j, k, test;
	cf = 0;
	for (i = 0; i<size; i++)
	{
		d[i] = MAX;
		for (j = 0; j < size; j++)
		{
			p[i][j] = -1;
		}
	}
	d[sr - 1] = 0;

	for (i = 1; i <=size+1; i++)
	{
		test = 1; 
		for (j = 0; j < size; j++)
		{
			for (k = 0; k < size; k++)
			{
				if (G[j][k] != 0)
				{
					Relax(j, k, d, p, G,size);
				}
				
			}
		}
	}
	//std::cout << "PO RELAKSACJACH" << std::endl;
	if (Check(d, p, G, size) == 1)
	{
		cf = 1;
		return 0;
	}
	else
	{
		std::cout << "Najkrotsze sciezki:" << std::endl;
		return 1;
	}
}

void dijkstra(int **mac1, int **mac2, int size, int str, int* d)
{
	int *p = new int[size];
	int *s = new int[size];
	int imax = std::numeric_limits<int>::max();
	int i, k;
	for (i = 0; i<size; i++)
		s[i] = 0;

	int j, ile_got = 0, min = 10000, indeks = -1;

	for (i = 0; i<size; i++)
	{
		d[i] = imax;
		p[i] = 0;
	}
	d[str - 1] = 0;

	while (ile_got < size)
	{
		min = 10000;
		for (i = 0; i < size; i++)
		{
			if (d[i] < min && s[i] == 0)
			{
				min = d[i];
				indeks = i;
			}
		}
		s[indeks] = 1;
		for (i = 0; i < size; i++)
		{
			if (s[i] == 0 && mac1[i][indeks] != 0)
			{
				if (d[i] > d[indeks] + mac2[i][indeks])
				{
					d[i] = d[indeks] + mac2[i][indeks];
					p[i] = indeks + 1;
				}
			}
		}
		ile_got = 0;
		for (i = 0; i < size; i++)
		{
			if (s[i] != 0)
				ile_got++;
		}
	}
}

int** Johnson(int** Gs, int** G, int n)
{
	int** G2 = new int*[n + 1];
	for (int i = 0; i<n+1; i++)
		G2[i] = new int[n+1];
	int** Gs2 = new int*[n + 1];
	for (int i = 0; i<n + 1; i++)
		Gs2[i] = new int[n + 1];
	int** ww = new int*[n + 1];
	for (int i = 0; i<n + 1; i++)
		ww[i] = new int[n + 1];
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			G2[i][j] = 0;
			if (i == n)
			{
				Gs2[i][j] = 1;
			}
		}
	}
	Gs2[n][n] = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (G[i][j] != 0)
			{
				G2[i][j] = G[i][j];
				Gs2[i][j] = 1;
			}
		}
	}

	int *d = new int[n+1];
	int **p = new int*[n+1];
	for (int i = 0; i<n + 1; i++)
		p[i] = new int[n + 1];
	int *h = new int[n + 1];
	int cycle_flag = 0;

	if (Bellman_Ford(G2, n, n+1,d,p,cycle_flag) == 0)
	{
		std::cout << "Znaleziono ujemny cykl" << std::endl;
		return 0;
	}
	else
	{
		for (int i = 0; i < n + 1; i++)
		{
			h[i] = d[i];
		}
		for (int i = 0; i < n + 1; i++)
		{
			for (int j = 0; j < n + 1; j++)
			{
				if (G2[i][j] != 0)
				{
					G2[i][j] = G2[i][j] + h[i] - h[j];
				}
			}
		}
		int** D = new int*[n];
		for (int i = 0; i<n; i++)
			D[i] = new int[n];
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				D[i][j] = 0;
			}
		}
		int* dprim = new int[n];
		for (int i = 0; i < n; i++)
		{
			dprim[i] = 0;
		}
		for (int i = 0; i < n; i++)
		{
			dijkstra(Gs, G2, n, i+1, dprim);
			for (int j = 0; j < n; j++)
			{
				D[i][j] = dprim[j] - h[i] + h[j];
			}

		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				std::cout << D[i][j] << " ";
			}
			std::cout << std::endl;
		}
		return D;
	}
}

int main()
{
	srand((unsigned)time(NULL));
	//liczba wierzcholkow
	int n;
	//prawdopodobienstwo
	float p=-1;
	
	cout<<"Podaj liczbe wierzcholkow: ";
	cin>>n;
	cout<<"\nPodaj prawdopodobienstwo: ";
	cin>>p;
	while(p>1 || p<0)
	{
				cout<<"\nPodano zle prawdopodobienstwo!\n";
				cout<<"\nPodaj prawdopodobienstwo: ";
				cin>>p;
	}
	//wypisuje na podstawe czego buduje graf
	cout<<"\nPodano liczbe wierzcholkow: "<<n<<"\nPodano prawdopodobienstwo: "<<p<<"\n";
	
	//macierz sasiedztwa
	int **A=new int *[n];
	int i,j;
	
	for(i=0;i<n;i++)
		A[i]=new int [n];
		
	//wypelniam macierz zerami
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			A[i][j]=0;
	
	//tworze graf
	stworz_graf(A,n,p);
	
	cout<<"\nOtrzymany graf:\n";
	//wypisuje graf
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			cout<<A[i][j]<<" ";
		cout<<endl;
	}
	//wypisuje silne sk³adowe
	int silne_skladowe=0;
	Kosaraju(n,A,silne_skladowe);
	
	//===========================================================
	//===============Wygeberowany silnie spojny graf=============
	//===========================================================
	
	//ustawiam na sztywno prawdopodobienstwo i rozmiar
	p=0.3;
	n=5;
	silne_skladowe=0;
	cout<<"\n=============Generowanie grafu silnie spojnego===========\n";
	do
	{
		stworz_graf(A,n,p);
		Kosaraju(n,A,silne_skladowe);
	}while(silne_skladowe>1);
	
	
	cout<<"\nWygenerowany graf:\n";
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			cout<<A[i][j]<<" ";
		cout<<endl;
	}
	
	/////////////////////////////3/////////////////////
	int **B = new int *[n];

	for (i = 0; i<n; i++)
		B[i] = new int[n];


	for (i = 0; i<n; i++)
		for (j = 0; j<n; j++)
			B[i][j] = 0;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (A[i][j] == 1)
				B[i][j] = (rand() % 16) + (-5);
			if (B[i][j] == 0 && A[i][j] == 1)
				B[i][j] = 1;
		}
	}

	cout << endl;

	cout << "   Bellman-Ford     " << endl;
	int *dist = new int[n];
	int **path = new int*[n];
	for (int i = 0; i<n; i++)
		path[i] = new int[n];
	int cycle_flag = 0;

	do
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (A[i][j] == 1)
					B[i][j] = (rand() % 16) + (-5);
				if (B[i][j] == 0 && A[i][j] == 1)
					B[i][j] = 1;
			}
		}
		Bellman_Ford(B, 1, n, dist, path, cycle_flag);
	} while (cycle_flag == 1);

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			cout << B[i][j] << " ";
		cout << endl;
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			cout << path[i][j] << " ";
		cout << endl;
	}
	std::cout << std::endl;

	for (int j = 0; j < n; j++)
	{
		std::cout << "Z wierzcholka " << 1 << " do  " << j + 1 << " odleglosc: " << dist[j] << std::endl;
		std::cout << "Sciezka: " << std::endl;
		for (int k = 0; k < n; k++)
		{
			if (path[j][k] == -1)continue;
			std::cout << path[j][k] + 1 << " ";
		}
		std::cout << std::endl;
	}
	/////////////////////////4////////////////////////////
	std::cout << "Johnson" << std::endl;

	do
	{
		stworz_graf(A, n, p);
		Kosaraju(n, A, silne_skladowe);
	} while (silne_skladowe>1);


	cout << "\nWygenerowany graf:\n";
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<n; j++)
			cout << A[i][j] << " ";
		cout << endl;
	}

	do
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (A[i][j] == 1)
					B[i][j] = (rand() % 16) + (-5);
				if (B[i][j] == 0 && A[i][j] == 1)
					B[i][j] = 1;
			}
		}
		Bellman_Ford(B, 1, n, dist, path, cycle_flag);
	} while (cycle_flag == 1);

	for (i = 0; i<n; i++)
	{
		for (j = 0; j<n; j++)
			cout << B[i][j] << " ";
		cout << endl;
	}

	int** D = new int*[n];
	for (int i = 0; i<n; i++)
		D[i] = new int[n];

	D = Johnson(A, B, n);

	system("pause");
	return 0;
}

