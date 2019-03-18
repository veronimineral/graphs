#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include "font.h"
#include <time.h>
using namespace std;

void narysuj()
{	//zczytuje rozmiar macierzy i macierz
	std::fstream plik;
	plik.open("wynik.txt");
	int n;
	plik >> n;
	int **A = new int*[n];
	for (int i = 0; i < n; i++)
		A[i] = new int[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			plik >> A[i][j];

	//tworze okno 
	sf::RenderWindow window(sf::VideoMode(600, 600), "Graf", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;
	//tworze n-kat
	sf::CircleShape main_circle(200, n);
	//ustalam jego pozycje i inne parametry
	main_circle.setPosition(100, 100);
	main_circle.setRadius(200);
	main_circle.setFillColor(sf::Color::Transparent);
	main_circle.setOutlineColor(sf::Color::Transparent);
	main_circle.setOutlineThickness(2.0f);

	//tworze czcionke
	sf::Font font;
	sf::Text **text = new sf::Text*[n];
	font.loadFromMemory(font_data, font_data_size);

	for (int i = 0; i < n; i++)
	{
		text[i] = new sf::Text;
		text[i]->setFont(font);
		text[i]->setCharacterSize(30);
		text[i]->setFillColor(sf::Color::Black);
	}

	int x, y;
	x = 280;
	y = 80;

	//zliczam ile ma byc krawedzi
	int line_counter = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (A[i][j] == 1)
				line_counter++;
		}
	}

	//tworze tablice lini i ustalam jej parametry podstawowe
	sf::VertexArray *lines = new sf::VertexArray[line_counter];

	for (int i = 0; i < line_counter; i++)
	{
		lines[i] = sf::VertexArray(sf::LinesStrip, 2);
		lines[i][0].color = sf::Color::Black;
		lines[i][1].color = sf::Color::Black;
	}

	//tworze tablice okregow, ustalam podstawowe parametry i pozycje
	sf::CircleShape *vertex = new sf::CircleShape[n];
	for (int i = 0; i < n; i++)
	{
		sf::Vector2f tmp;
		tmp = main_circle.getPoint(i);
		tmp.x = tmp.x + 80;
		tmp.y = tmp.y + 80;
		vertex[i].setRadius(20);
		vertex[i].setPosition(tmp);
		vertex[i].setFillColor(sf::Color::White);
		vertex[i].setOutlineColor(sf::Color::Black);
		vertex[i].setOutlineThickness(2.0f);

		//wypisuje tekst 
		std::string b = "0";
		b = std::to_string(i + 1);
		if (i + 1 < 10)
		{
			tmp.x = tmp.x + 12;
			tmp.y = tmp.y;
		}
		else
		{
			tmp.x = tmp.x + 3;
			tmp.y = tmp.y;
		}
		text[i]->setPosition(tmp);
		text[i]->setString(b);
	}

	//pobieram pozycje tekstu zeby wiedziec gdzie zaczepic krawdzi i ustalam ich pozycje
	int c = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (A[i][j] == 1)
			{
				sf::Vector2f temp;
				temp = text[i]->getPosition();
				temp.x = temp.x + 3;
				temp.y = temp.y + 15;
				lines[c][0].position = temp;
				temp = text[j]->getPosition();
				temp.x = temp.x + 3;
				temp.y = temp.y + 15;
				lines[c][1].position = temp;
				c++;
			}
		}
	}

	//wypisuje na ekran 
	while (window.isOpen())
	{
		window.clear(sf::Color::White);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
		}
		window.draw(main_circle);
		for (int i = 0; i < line_counter; i++)
		{
			window.draw(lines[i]);
		}
		for (int i = 0; i < n; i++) {
			window.draw(vertex[i]);
			window.draw(*text[i]);
		}



		window.display();
	}


}
int main()
{
	srand((unsigned)time(NULL));
	//n-liczba wierzcholkow, l-liczba podanych krawedzi(-1 zeby while nie zadzia³a³), max-maksymalna mozliwa liczba krawdzi
	int n,l=-1,max;
	//p-prawdopodobienstwo podane(-1 zeby nie zadzia³a³ for)
	float p=-1;
	//co ktorej metody losowania chce uzyc uzytkownik
	char g;
	
	cout<<"Podaj liczbe wierzcholkow: ";
	cin>>n;
	max=n*(n-1)/2;
	cout<<"Na podstawie czego chcesz wylosowac graf:\na)krawedzi: l\nb)prawdopodobienstwa: p \n";
	cin>>g;
	
	//pobieram litere dopoki nie dostane p lub l
	while(g!='l' && g!='p')
	{
		cout<<"\nNa podstawie czego chcesz wylosowac graf:\na)krawedzi: l\nb)prawdopodobienstwa: p \n";
		cin>>g;
	}

	//w zaleznosci od przypadku pobieram
	switch(g)
	{
		//liczbe krawedzi
		case 'l':
		{
			cout<<"\nPodaj liczbe krawedzi: ";
			cin>>l;
			//jezeli liczba krawedzi jest wieksza niz maksymalna liczba krawedzi jaka moze byc
			while(l<0 || l>max)
			{
				cout<<"\nPodano zla liczbe krawedzi!\nNie mozesz podac wiecej krawedzi niz: "<<max<<endl;
				cout<<"\nPodaj liczbe krawedzi: ";
				cin>>l;
			}
			//wypisuje na podstawie czego buduje graf
			cout<<"\nPodano liczbe wierzcholkow: "<<n<<"\nPodano liczbe krawedzi: "<<l<<"\n";
			break;
		}
		//prawdopodobienstwo
		case 'p':
		{
			cout<<"\nPodaj prawdopodobienstwo: ";
			cin>>p;
			//jezeli prawdopodobienstwo nie jest z przedzia³u <0,1> 
			while(p>1 || p<0)
			{
				cout<<"\nPodano zle prawdopodobienstwo!\n";
				cout<<"\nPodaj prawdopodobienstwo: ";
				cin>>p;
			}
			//wypisuje na podstawe czego buduje graf
			cout<<"\nPodano liczbe wierzcholkow: "<<n<<"\nPodano prawdopodobienstwo: "<<p<<"\n";
			break;
		}
	}
	//macierz sasiedztwa
	int **A = new int *[n];
	int i,j;
	
	for (i = 0; i < n; i++)
		A[i] = new int[n];
	//zmienna do prawdopodobienstwa
	double los;
	
	//wypelniam macierz zerami
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			A[i][j]=0;
			
	//zmienne do krawedzi
	int a,b,l_k=0;
	
	//na podstawie prawdopodobienstwa buduje graf
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			//losuje prawdopodobienstwo
			los=((double)rand() / (RAND_MAX + 1));
			//jezeli mniejsze niz podane uzupelniam macierz i zapewniam ze diagonala jest zerowa
			if(los<p && i!=j)
			{
				//symetryczna
				A[i][j]=1;
				A[j][i]=1;
			}
		}
	}
	
	//na podstawie krawedzi buduje graf
	while(l_k<l)
	{
		//losuje dwa wierzcholki
		a=rand()%n;
		b=rand()%n;
		//jezeli para nie ma krawedzi dodaje ja, zapewniam ze diagonala jest zerowa
		if(A[a][b]==0 && a!=b)
		{
			//symetryczna
			A[a][b]=1;
			A[b][a]=1;
			//krawedz dodana wiec zwiekszam ilosc dodanych juz krawedzi
			l_k++;
		}
	}
	
	cout<<"\nOtrzymana macierz sasiedztwa: \n";
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cout<<A[i][j]<<" ";
		}
		cout<<endl;
	}
	
	//Zapis do pliku
	FILE *fp;
	fp=fopen("wynik.txt","w");
	fprintf(fp,"%d\n",n);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			fprintf(fp,"%d ",A[i][j]);
		fprintf(fp,"\r\n");
	}
	fclose(fp);

	cout << "\nCzy chcesz narysowac otrzymany graf: \na)tak: t\nb)nie: n\n";
	cin >> g;
	if(g=='t')
		narysuj();

	system("PAUSE");
	return 0;
}
