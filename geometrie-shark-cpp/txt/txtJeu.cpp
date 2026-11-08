#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32
#include "winTxt.h"

#include "Partie.h"
#include <cassert>
using namespace std;

void txtAff(WinTXT &win,Partie &p,int nb_surface,int nb_obs,int nb_portail)
{

  
	
    assert(p.getnb_sautauto() == 0 && p.getnb_sautclick() == 0);
	/// sautauto et sautclick sont pas inclu dans txt
	win.clear();

	/// Affichage des murs et des pastilles
    
for(int i = 0;i < nb_portail;i++){
	win.print(p.getPortail()[i].getv1()[0],9-p.getPortail()[i].getv1()[1], 'P');
	win.print(p.getPortail()[i].getv1()[0],9-(p.getPortail()[i].getv1()[1]+1), 'P');
}

for(int i = 0;i < nb_obs;i++){
	win.print(p.getObstacle()[i].getv1()[0],9-p.getObstacle()[i].getv1()[1], 'I');
}



	for (int x = 0; x < nb_surface; x++){
		for (int y = p.getSurface()[x].getV1()[1]; y < p.getSurface()[x].getV1()[3]; ++y){
            for (int z = p.getSurface()[x].getV1()[0]; z < p.getSurface()[x].getV1()[2]; ++z){
			    if(z<=70 && z>=0 && y>=0 && y<= 10)
				win.print(z, 9-y, 'S');
			}}}
	/// Affichage de Joueur
       win.print(p.getV1J()[0],9-p.getV1J()[1],'o');
	win.draw();
}

void txtBoucle(Partie &partie,int nb_surface,int nb_obs,int nb_portail)
{
	/// Creation d'une nouvelle fenetre en mode texte
	// => fenetre de dimension et position (WIDTH,HEIGHT,STARTX,STARTY)
	WinTXT win(70, 10);  //x,y

	bool ok = true;
	int c;

	do
	{
		txtAff(win, partie,nb_surface,nb_obs,nb_portail);

#ifdef _WIN32
		Sleep(1000);
#else
		usleep(100000);
#endif // WIN32




		partie.action_automatique_txt();
		partie.colision_txt();

		if(partie.aPerdu()){
			partie.initilisaliser();
		}

		if(partie.gagner()){
			ok=false;
			cout<<"vous avez gagner";
		}

		c = win.getCh();
		if (c=='p')
		{
			ok = false;
		}
		
		partie.action_clavier_txt(c);

	} while (ok);
}
