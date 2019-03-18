#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

int main()
{
	srand((unsigned)time(NULL));
	fstream plik;
	plik.open("wynik.txt");
	int n = 0, i = 0, j = 0;
	plik >> n;
	int **A = new int*[n];
	for (i = 0; i < n; i++)
	{
		A[i] = new int[n];
	}
	cout << "Wczytana macierz:\n";
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			plik >> A[i][j];
			cout << A[i][j] << " ";
		}
		cout << std::endl;
	}
	int **wyniki = new int*[n];
	for (i = 0; i < n; i++)
	{
		wyniki[i] = new int[n];
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			wyniki[i][j] = 0;
		}
	}
	int steps = 0;
	double los;
	int los2;
	double d = 0.85;
	int index;
	int wyjscie = 0;
	int wyjscie2 = 0;
	for (int i = 0; i < n; i++)
	{
		index = i;
		steps = 0;
		wyjscie2 = 0;
		for (int k = 0; k < n; k++)
		{
			if (A[index][k] == 1)
				wyjscie2 = 1;
		}
		while (steps < 10000)
		{
			if (wyjscie2 != 1)
				break;
			wyjscie = 0;
			los = ((double)rand() / (RAND_MAX + 1));
			if (los <= d)
			{
				do
				{
					wyjscie = 0;
					los2 = rand() % n;
					for (int j = 0; j < n; j++)
					{
						if (A[los2][j] == 1)
							wyjscie = 1;
					}
				} while (A[index][los2] != 1 || wyjscie == 0);
				index = los2;
				wyniki[i][index]++;
				steps++;
			}
			else
			{
				do
				{
					wyjscie = 0;
					los2 = rand() % n;
					for (int j = 0; j < n; j++)
					{
						if (A[los2][j] == 1)
							wyjscie = 1;
					}
				} while (los2 == index || wyjscie == 0);
				index = los2;
				wyniki[i][index]++;
				steps++;
			}

		}
	}
	double* srednia = new double[n];
	for (int i = 0; i < n; i++)
	{
		srednia[i] = 0;
		for (int j = 0; j < n; j++)
		{
			srednia[i] = srednia[i] + wyniki[j][i];
		}
	}
	double max = -1;
	int indexmax = -1;
	std::cout << "Ranking wierzcholkow: " << std::endl;
	for (int i = 0; i < n; i++)
	{
		max = -1;
		for (int j = 0; j < n; j++)
		{
			if (srednia[j] > max)
			{
				max = srednia[j];
				indexmax = j;
			}
		}
		srednia[indexmax] = -100;
		cout << indexmax+1 << " ";
	}
	cout << endl;

	cout << endl;
	cout << "Metoda wektora obsadzen: " << endl;
	double* pt = new double[n];
	for (int i = 0; i < n; i++)
	{
		pt[i] = 1.0/n;
	}

	double **P = new double*[n];
	for (i = 0; i < n; i++)
	{
		P[i] = new double[n];
	}

	double *dt = new double[n];
	for (int i = 0; i < n; i++)
	{
		dt[i] = 0;
		for (int j = 0; j < n; j++)
		{
			dt[i] = dt[i] + A[i][j];
		}
	}


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			P[i][j] = d * (A[i][j] / dt[i]) + ((1 - d) / n);
		}
	}

	double* ptv2 = new double[n];

	int iter = 10000;
	for (int t = 0; t < iter; t++)
	{
		for (int l = 0; l < n; l++)
		{
			ptv2[l] = pt[l];
		}
		for (int i = 0; i < n; i++)
		{
			double s = 0;
			for (int j = 0; j < n; j++)
			{
				s = s + ptv2[j] * P[j][i];
			}
			pt[i] = s;
		}
	}

	cout << "Wartosci wektora pt po " << iter <<" iteracjach: " << endl;
	for (int i = 0; i < n; i++)
	{
		cout << pt[i] << " ";
	}
	cout << endl;

	indexmax = -1;
	cout<< "Ranking wierzcholkow v2:" << endl;
	for (int i = 0; i < n; i++)
	{
		max = -1;
		for (int j = 0; j < n; j++)
		{
			if (pt[j] > max)
			{
				max = pt[j];
				indexmax = j;
			}
		}
		pt[indexmax] = -100;
		cout << indexmax + 1 << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}