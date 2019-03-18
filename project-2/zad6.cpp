#include<stdio.h>
#include "Funkcje6.h"

int main()
{

	// Z A D A N I E 6 - H A M I L T O N

   // Tworzymy przykladowe grafy
   bool graf1[W][W] = {{0, 1, 1, 1, 1},
                      {0, 0, 1, 0, 1},
                      {1, 0, 0, 0, 1},
                      {1, 1, 1, 0, 1},
                      {0, 1, 0, 1, 0},
                     };
   Hamilton(graf1);

	bool graf2[W][W] = { { 0, 1, 1, 0, 1 },
	{ 0, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 1 },
	{ 0, 1, 1, 0, 1 },
	{ 0, 1, 0, 1, 0 },
	};

    Hamilton(graf2);


/*	bool graf3[W][W] = {{0, 1, 0, 1, 0, 1},
                      {1, 0, 1, 1, 1, 0},
                      {0, 1, 0, 0, 1, 0},
                      {1, 1, 0, 0, 0, 1},
                      {0, 1, 1, 0, 0, 1},
                      {0, 1, 1, 0, 1, 0}
                     };
	Hamilton(graf3); */
    return 0;


}
