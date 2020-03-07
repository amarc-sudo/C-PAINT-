#include "lettre.h"


//Fonction void qui permet d'afficher du texte
//demande d'appuyer sur les lettres pour écrire
void lettre(Point lettre, int police)
{
  int i, base = lettre.x, securite = 10,temps = 0;
  while(i != SDLK_LCTRL) // condition qui permet d'arrêter la fonction quand on appuye sur "ctrl"
  {
    i = attendre_touche();

    if (securite != i && temps < 100)
    {
      switch (i) { // on utilise un switch pour éviter de mettre une structure if else répétitive
        case SDLK_SPACE: // on donne se qui se passe avec chaque cas, ici en appuyant sur espace
          afficher_texte(" ", police, lettre, couleurchoisi);//puis on donne se que ça fait, ici ça donne un blanc 
          
          lettre.x += police/2;

          break;
        case SDLK_a: //cas avec en appuyant sur la lettre "a"
          afficher_texte("a", police, lettre, couleurchoisi); // en appuyant sur "a" ça donne la lettre "a" 
          lettre.x += police/2;
          break;
        case SDLK_b: // Fonctionne pareil pour tous les autres caractères que avec la lettre "a" et espace 
          afficher_texte("b", police, lettre, couleurchoisi);
          lettre.x += police/2;
        break;
        case SDLK_c:
          afficher_texte("c", police, lettre, couleurchoisi);
          lettre.x += police/2;
        break;
        case SDLK_d:
          afficher_texte("d", police, lettre, couleurchoisi);
          lettre.x += police/2;
        break;
        case SDLK_e:
          afficher_texte("e", police, lettre, couleurchoisi);
          lettre.x += police/2;
        break;
        case SDLK_f:
          afficher_texte("f", police, lettre, couleurchoisi);
          lettre.x += police/3;
        break;
        case SDLK_g:
          afficher_texte("g", police, lettre, couleurchoisi);
          lettre.x += police/2;
        break;
        case SDLK_h:
          afficher_texte("h", police, lettre, couleurchoisi);
          lettre.x += police/2;
        break;

        case SDLK_i:
          afficher_texte("i", police, lettre, couleurchoisi);
          lettre.x += police/4;
        break;

        case SDLK_j:
          afficher_texte("j", police, lettre, couleurchoisi);
          lettre.x += police/4;
        break;

        case SDLK_k:
          afficher_texte("k", police, lettre, couleurchoisi);
          lettre.x += police/2;
        break;

        case SDLK_l:
          afficher_texte("l", police, lettre, couleurchoisi);
          lettre.x += police/4;
        break;

        case SDLK_m:
          afficher_texte("m", police, lettre, couleurchoisi);
          lettre.x += police-3;
        break;

        case SDLK_n:
          afficher_texte("n", police, lettre, couleurchoisi);
          lettre.x += police/2;
        break;

        case SDLK_o:
          afficher_texte("o", police, lettre, couleurchoisi);
          lettre.x += police/2;
        break;

        case SDLK_p:
          afficher_texte("p", police, lettre, couleurchoisi);
          lettre.x += police/2;
        break;

        case SDLK_q:
          afficher_texte("q", police, lettre, couleurchoisi);
          lettre.x += police/2;
        break;

        case SDLK_r:
          afficher_texte("r", police, lettre, couleurchoisi);
          lettre.x += police/3;
        break;

        case SDLK_s:
          afficher_texte("s", police, lettre, couleurchoisi);
          lettre.x += police/2;
        break;

        case SDLK_t:
          afficher_texte("t", police, lettre, couleurchoisi);
          lettre.x += police/2;
        break;

        case SDLK_u:
          afficher_texte("u", police, lettre, couleurchoisi);
          lettre.x += police/2;
        break;

        case SDLK_v:
          afficher_texte("v", police, lettre, couleurchoisi);
          lettre.x += police/2;
        break;

        case SDLK_w:
          afficher_texte("w", police, lettre, couleurchoisi);
          lettre.x += police-3;
        break;

        case SDLK_x:
          afficher_texte("x", police, lettre, couleurchoisi);
          lettre.x += police/2;
        break;

        case SDLK_y:
          afficher_texte("y", police, lettre, couleurchoisi);
          lettre.x += police/2;
        break;

        case SDLK_z:
          afficher_texte("z", police, lettre, couleurchoisi);
          lettre.x += police/2;
        break;
        case SDLK_EXCLAIM:
          afficher_texte("!", police, lettre, couleurchoisi);
          lettre.x += police/2;
        break;  
        case SDLK_QUESTION:
          afficher_texte("?", police, lettre, couleurchoisi);
          lettre.x += police/2;
        break;  
        case SDLK_RETURN:
          lettre.y += police;
          lettre.x = base;
        break;
      }
      actualiser();
      securite = i;
      }
      else
      {
        attente(150);
        securite = 0;
      }
  }
}
