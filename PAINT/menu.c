#include "menu.h"


////////////////////////////////////////////
//Menu de sélection
////////////////////////////////////////////
void menu()
{
  
  char image[200];
  int i =1;
  Point coin = {0,0};
  ouvrir_fenetre(815,600, 0,0,0,0);
  afficher_image("image/menu.bmp",coin);
  actualiser();

  while(i)
  {
    Point clic = attendre_clic();
    if(clic.x > 300 && clic.x < 500 && clic.y > 350 && clic.y < 400)
    {
      printf("rentrez le nom de l'image\n");
      scanf("%s",image);
      fermer_menu();
      plateau_img(image);
      i = 0;
    }
    else if(clic.x > 300 && clic.x < 500 && clic.y > 250 && clic.y < 300)
    {
    fermer_menu();
    plateau();
    i=0;
    }
  }
}
