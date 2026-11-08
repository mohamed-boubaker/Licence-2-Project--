#include "winTxt.h"
#include "txtJeu.h"


#include <vector>
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
	termClear();

    

    Partie p("data/niveau_txt/partie.txt");
	vector<int> v1 = {1,1,2,2};
	p.modifjoueur(v1);
    
	txtBoucle(p,4,3,1);
	termClear();

	return 0;
}
