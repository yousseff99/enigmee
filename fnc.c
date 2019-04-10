#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "fnc.h"

image init_image(char nameofpicture[100],int x,int y)
{
image image;
image.back=IMG_Load(nameofpicture);//load image
image.posPicture.x=x;//position x de bg
image.posPicture.y=y;//position y de bg
return image;
}




void affichage(SDL_Surface *ecran,image image)
{
SDL_BlitSurface(image.back,NULL,ecran,&image.posPicture);
}







void librer_image(image image)
{
 SDL_FreeSurface(image.back);//Liberer memoire
}





void Music_enigme()
{
    Mix_Music *music_enigme;
    music_enigme = Mix_LoadMUS("sound/klay.mp3");//chargement de la musique
    Mix_VolumeMusic(MIX_MAX_VOLUME / 1);
    Mix_PlayMusic(music_enigme,-1);//boucle infini

}




void sound_wrong()//false rep
{
Mix_Chunk *wrong; 
    
    wrong = Mix_LoadWAV("sound/wrong.wav");
Mix_PlayChannel(1,wrong,0);
    
}

void sound_correct()
{
Mix_Chunk *correct;
correct = Mix_LoadWAV("sound/correct.wav"); 
Mix_PlayChannel(1,correct,0);
}

void sound_win()
{
Mix_Chunk *soundwin; 
soundwin= Mix_LoadWAV("sound/win.wav");
Mix_PlayChannel(1,soundwin,0);

}


