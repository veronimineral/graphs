#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;

struct kruskal_cont{
	int v1, v2, w;
};

void swap(kruskal_cont & a, kruskal_cont & b)
{
	kruskal_cont tmp = a;
	a = b;
	b = tmp;
}

void ustal_wart(int **mac1, int **mac2, int size)
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = i + 1; j < size; j++)
		{
			if (mac1[i][j] == 1)
			{
				mac2[i][j] = rand() % 10 + 1;
				mac2[j][i] = mac2[i][j];
			}
		}
	}
}

void tree_merge(int **checklist, int index1, int index2, int n)
{
	int **tmp = new int*[1];
	tmp[0] = new int[n];
	for (int i = 0; i < n; i++)
	{
		tmp[0][i] = 0;
	}
	for (int i = 0; i < n; i++)
	{
		tmp[0][i] = checklist[index2][i];
	}
	delete checklist[index2];
	for (int i = 0; i < n; i++)
	{
		if(tmp[0][i] == 1)
		checklist[index1][i] = tmp[0][i];
	}

}

int main()
{
	srand(time(0));
	fstream plik;
	plik.open("wynik.txt");
	int n, i, j;
	plik >> n;
	int **A = new int*[n];
	for (i = 0; i < n; i++)
	{
		A[i] = new int[n];
	}

	std::cout << "Macierz sasiedztwa: \n";
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			plik >> A[i][j];
			cout << A[i][j] << " ";
		}
		cout << std::endl;
	}
	int **B = new int *[n];
	for (i = 0; i < n; i++)
	{
		B[i] = new int[n];
	}
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			B[i][j] = 0;
	cout << std::endl;
	ustal_wart(A, B, n);
	std::cout << "Wagi krawedzi w macierzy: \n";
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << B[i][j] << " ";
		}
		cout << std::endl;
	}

	int lc = 0;

	for (i = 0; i < n; i++)
	{
		for (j = i+1; j < n; j++)
		{
			if (A[i][j] != 0)
				lc++;
		}
		cout << std::endl;
	}

	kruskal_cont *set = new kruskal_cont[lc];
	int x = 0;
	for (int i = 0; i < n;i++)
	{
		for (int j = i+1;j < n;j++)
		{
			if (A[i][j] != 0)
			{
				set[x].v1 = i;
				set[x].v2 = j;
				set[x].w = B[i][j];
				std::cout << set[x].w<<" ";
				x++;
			} 
		}
	}
	std::cout << std::endl;

	for (int i = 0; i < lc; i++)
	{
		for (int j = lc; j >=i+1; j--)
		{
			if (set[j - 1].w > set[j].w)
				swap(set[j - 1], set[j]);
		}
	}

	std::cout << "Lista posortowanych krawedzi: \n";

	for (int i = 0; i < lc; i++)
	{
		std::cout << set[i].w << " "<<set[i].v1<<" "<<set[i].v2<<endl;
	}
	cout << endl;

	kruskal_cont *MST = new kruskal_cont[lc];
	int full = 0, numberot = 1, s=1; 
	x = 1;
	MST[0] = set[0];
	int **Vchecklist = new int*[1];
	Vchecklist[0] = new int[n];
	for (int i = 0; i < n; i++)
	{
		Vchecklist[0][i] = 0;
	}
	Vchecklist[0][set[0].v1] = 1;
	Vchecklist[0][set[0].v2] = 1;
	while (full == 0 && x<lc)
	{
		//cout << x << endl;
		int index1 = -1, index2 = -1;
		for (int i = 0; i < numberot; i++)
		{
			if (Vchecklist[i][set[x].v1] == 1 && Vchecklist[i][set[x].v2] == 1)
			{
				index1 = -2;
				break;
			}
				
			if (Vchecklist[i][set[x].v1] == 1)
				index1 = i;
			if (Vchecklist[i][set[x].v2] == 1)
				index2 = i;
		}
		//cout << index1 << " " << index2 << endl;
		if (index1 == -2)
		{
			//cout << "pomijam"<<endl;
		}
		else if (index1 == -1 && index2 == -1)
		{
			//cout << "tworzê"<<endl;
			int **tmp = new int*[numberot];
			for (int i = 0; i < numberot; i++)
			{
				tmp[i] = new int[n];
			}
			for (int i = 0; i < numberot; i++)
			{
				for (int j = 0; j < n; j++)
				{
					tmp[i][j] = Vchecklist[i][j];
				}
			}
			
			for (int i = 0; i < numberot-1; i++)
			{
				delete [] Vchecklist[i];
			}
			delete [] Vchecklist;
			//cout << numberot << endl;
			numberot++;
			Vchecklist = new int*[numberot];
			for (int i = 0; i < numberot; i++)
			{
				Vchecklist[i] = new int[n];
			}
			for (int i = 0; i < numberot - 1; i++)
			{
				for (int j = 0; j < n; j++)
				{
					Vchecklist[i][j] = tmp[i][j];
				}
			}
			Vchecklist[numberot - 1][set[x].v1] = 1;
			Vchecklist[numberot - 1][set[x].v2] = 1;
			MST[s] = set[x];
			s++;
			for (int i = 0; i < numberot - 1; i++)
			{
				delete tmp[i];
			}
			delete tmp;
		}
		else if (index1 > -1 && index2 > -1)
		{
			MST[s] = set[x];
			s++;
			tree_merge(Vchecklist, index1, index2, n);
			for (int i = 0; i < n; i++)
			{
				//std::cout << Vchecklist[index1][i]<<" "<<std::endl;
			}
		}
		else if (index2 == -1)
		{
			MST[s] = set[x];
			s++;
			Vchecklist[index1][set[x].v2] = 1;
		}
		else if (index1 == -1)
		{
			MST[s] = set[x];
			s++;
			Vchecklist[index2][set[x].v1] = 1;
		}
		//cout << Vchecklist << endl;
		for (int i = 0; i < lc; i++)
		{
			//std::cout << "Wpyelnienie: \n";
			//std::cout << Vchecklist[0][1] << " ";
			if (Vchecklist[0][i] != 1)
			{
				full = 0;
				break;
			}
			else
				full = 1;
		}
		//std::cout << std::endl;
		x++;
	}

	std::cout << std::endl;
	std::cout << "Krawedzie tworzace MST z wagami: \n";
	for (int i = 0; i < s; i++)
	{
		std::cout << MST[i].w << " "<<MST[i].v1+1<<" "<<MST[i].v2+1<<endl;
	}
	system("pause");
	return 0;
}