#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <limits>
using namespace std;

void ustal_wart(int **mac1,int **mac2,int size)
{
	int i,j;
	for (i = 0; i < size; i++)
	{
		for (j = i+1; j < size; j++)
		{
			if(mac1[i][j]==1)
			{
				mac2[i][j]=rand()%10+1;
				mac2[j][i]=mac2[i][j];
			}
		}
	}
}

void dijkstra(int **mac1,int **mac2,int size,int str,int **mac3)
{
	int *d=new int [size];
	int *p=new int [size];
	int *s=new int [size];
	int imax = std::numeric_limits<int>::max();
	int i,k;
	for(i=0;i<size;i++)
		s[i]=0;
	
	int j,ile_got=0,min=10000,indeks;
	
	for(i=0;i<size;i++)
	{
		d[i]=imax;
		p[i]=0;
	}
	d[str-1]=0;
	
	while(ile_got<size)
	{
		min=10000;
		for(i=0;i<size;i++)
		{
			if(d[i]<min && s[i]==0)
			{
				min=d[i];
				indeks=i;
			}
		}
		s[indeks]=1;
		for(i=0;i<size;i++)
		{
			if(s[i]==0 && mac1[i][indeks]!=0)
			{
				if(d[i]>d[indeks]+mac2[i][indeks])
				{
					d[i]=d[indeks]+mac2[i][indeks];
					p[i]=indeks+1;
				}
			}
		}
		ile_got=0;
		for(i=0;i<size;i++)
		{
			if(s[i]!=0)
				ile_got++;
		}
	}
	for(i=str;i<size+1;i++)
	{
		for(j=0;j<size;j++)
			mac3[str-1][j]=d[j];
	}
	int tmp;
	cout<<"\nNajkrotsze sciezki od wierzcholka: "<<str<<endl;
	for(i=0;i<size;i++)
	{
		cout<<i+1<<": ";
		tmp=p[i];
		while(tmp!=0)
		{
			cout<<tmp<<" ";
			tmp=p[tmp-1];
		}
		cout<<" Dl: "<<d[i]<<"\n";
	}
}

int main()
{
	srand((unsigned)time(NULL));
	fstream plik;
	plik.open("wynik.txt");
	int n,i,j;
	plik >> n;
	int **A = new int*[n];
	for (i= 0; i < n; i++)
	{
		A[i] = new int[n];
	}
	cout<<"Wczytana macierz:\n";
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			plik >> A[i][j];
			cout << A[i][j] << " ";
		}
		cout<<std::endl;
	}
	int **B=new int *[n];
	for (i= 0; i < n; i++)
	{
		B[i] = new int[n];
	}
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
				B[i][j]=0;
		}
	}
	
	
	cout<<std::endl;
	ustal_wart(A,B,n);
	
	cout<<"Macierz wag:\n";
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << B[i][j] << " ";
		}
		cout<<std::endl;
	}
	int **D= new int *[n];
	for (i=0;i<n;i++)
		D[i]=new int [n];
		
	for(i=0;i<n;i++)
		dijkstra(A,B,n,i+1,D);
		
	cout<<endl;
	cout<<"\nMacierz odleglosci:\n";
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << D[i][j] << " ";
		}
		cout<<std::endl;
	}
	
	int *centrum=new int [n];
	int suma;
	cout<<std::endl;
	for(i=0;i<n;i++)
	{
		suma=0;
		for(j=0;j<n;j++)
			suma=suma+D[i][j];
		centrum[i]=suma;
		cout<<centrum[i]<<" ";
	}
	
	int min=10000000000;
	int centrum1=0;
	
	for(i=0;i<n;i++)
	{
		if(centrum[i]<min)
		{
			min=centrum[i];
			centrum1=i+1;
		}
	}
	cout << "\nCentrum grafu: "<<centrum1<<endl<<endl;
	
	int *centrumini=new int [n];
	int max;
	
	for(i=0;i<n;i++)
	{
		max=0;
		for(j=0;j<n;j++)
		{
			if(D[i][j]>max&&i!=j)
			{
				max=D[i][j];
			}
		}
		centrumini[i]=max;
		cout<<centrumini[i]<<" ";
	}
	
	min=1000000;
	int centrum2;
	for(i=0;i<n;i++)
	{
		if(centrumini[i]<min)
		{
			min=centrumini[i];
			centrum2=i+1;
		}
	}
	
	cout << "\nCentrum minimax grafu: "<<centrum2<<endl;
	return 0;
}
