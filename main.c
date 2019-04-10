#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "fnc.h"

int main()
{
    image background,quiz1,quiz2,quiz3,quiz4,win;
    char *phrase,* mot;
    char correctanswer[18][20]= {{"stylo"},{"15"},{"Okkkk"}};
    phrase=calloc(20,sizeof(char));
    mot=calloc(6,sizeof(char));
    int continuer = 1,i=0,True=0,enigmeDone=1,j=0,done=0,winenigme=0;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO); 
    SDL_Surface *ecran =NULL,*zoneSaisie=NULL,*curseur=NULL;
    TTF_Font *police = NULL;
    SDL_Color couleurbleu = {0,0,53};
    TTF_Init();
    police = TTF_OpenFont("font/font.ttf", 22);
    ecran=SDL_SetVideoMode(450, 650, 32, SDL_HWSURFACE); 
    SDL_Rect posbg,posquiz,poscurseur,poszoneSaisie,poswin;
    SDL_WM_SetCaption("Enigme Youssef", NULL); 
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)==-1){printf("%s",Mix_GetError()); }
    Mix_Chunk *correct,*wrong,*soundwin; 
    correct = Mix_LoadWAV("sound/correct.wav");
    wrong = Mix_LoadWAV("sound/wrong.wav");
    soundwin= Mix_LoadWAV("sound/win.wav");
////////////////////////////////////////////////////
    background=init_image("img/bg.png",0,0);
    quiz1=init_image("img/quiz1.png",0,0);
    quiz2=init_image("img/quiz2.png",0,0);
    quiz3=init_image("img/quiz3.png",0,0);
    quiz4=init_image("img/quiz4.png",0,0);
    win=init_image("img/win.png",135,240);
    curseur=IMG_Load("img/curseur.png");
    poscurseur.x=0;
    poscurseur.y=0;
    poszoneSaisie.x=135;
    poszoneSaisie.y=440;
    //////////////////////////////////
    Music_enigme();
    while (continuer/*&&winenigme!=1*/)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)// win teta9ra l click
            {
            case SDLK_RETURN:
            /////////Verif_Enigme1//////////
            if(enigmeDone==1)
            { if(poscurseur.y==0){sound_correct();printf("win Enigme 1 \n");enigmeDone=2;done=0;} 
              else{sound_wrong();printf("False Enigme 1\n");}
            }
            //////////Verif_Enigme2//////////
            if(enigmeDone==2&&done==2)
            { if(poscurseur.y==50){sound_correct();printf("win Enigme 2 \n");enigmeDone=3;done=0;} 
              else{sound_wrong();printf("False Enigme 2\n");}
            }
            //////////Verif_Enigme3//////////
            if(enigmeDone==3&&done==3)
            {   done=0; 
                if(strcmp(phrase,correctanswer[0])==0)
                {sound_correct();printf("win Enigme 3\n");enigmeDone=4;
                 memset(phrase,0,sizeof(char));phrase=calloc(20,sizeof(char));done=0;}
              else{sound_wrong();memset/*tna7i lghalta*/(phrase,0,sizeof(char));phrase=calloc(20,sizeof(char));printf("False Enigme 3\n");}
            }
            //////////Verif_Enigme4//////////
            if(enigmeDone==4&&done==4)
            {   
                if(strcmp(phrase,correctanswer[1])==0)
                {sound_correct();printf("win Enigme 4 \n");enigmeDone=5;}
              else{sound_wrong();memset(phrase,0,sizeof(char));phrase=calloc(20,sizeof(char));printf("False Enigme 3\n");}
            }
            break;
             //////////FIN_Case_RETURN//////////
             case SDLK_UP: 
             if(enigmeDone!=3 && enigmeDone!=4 && enigmeDone!=5)
             {
             i--;
             if(i<=0){i=3;}
             if(i==4){i=1;}
             if(i==1){poscurseur.y=0; SDL_BlitSurface(curseur,NULL,ecran,&poscurseur);  SDL_Flip(ecran); SDL_Delay(900);} 
             if(i==2){poscurseur.y=50; SDL_BlitSurface(curseur,NULL,ecran,&poscurseur); SDL_Flip(ecran); SDL_Delay(900);} 
             if(i==3){poscurseur.y=105; SDL_BlitSurface(curseur,NULL,ecran,&poscurseur); SDL_Flip(ecran); SDL_Delay(900);}
             }
             break;
             //////////FIN_Case_UP//////////
             case SDLK_DOWN:
             if(enigmeDone!=3 && enigmeDone!=4 && enigmeDone!=5)
             {
             i++;
             if(i==4){i=1;}
             if(i==1){poscurseur.y=0; SDL_BlitSurface(curseur,NULL,ecran,&poscurseur); SDL_Flip(ecran); SDL_Delay(900);}
             if(i==2){poscurseur.y=50; SDL_BlitSurface(curseur,NULL,ecran,&poscurseur); SDL_Flip(ecran); SDL_Delay(900);}
             if(i==3){poscurseur.y=105; SDL_BlitSurface(curseur,NULL,ecran,&poscurseur); SDL_Flip(ecran); SDL_Delay(900);}
             }
             break;
             //////////FIN__DOWN//////////
            case SDLK_BACKSPACE:
                printf("Effacer\n");
                int casee = 0,longeur;
                longeur=strlen(phrase);
                longeur--;
                while(phrase[casee] != '\0')
                {
                    if(casee >=longeur)
                    {
                        phrase[casee] = phrase[casee+1];
                    }
                    casee++;
                }
                break;
            case SDLK_KP0:
                strcpy(mot,"0");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("0\n");}
                break;
            case SDLK_KP1:
                strcpy(mot,"1");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("1\n");}
                break;
            case SDLK_KP2:
                strcpy(mot,"2");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("2\n");}
                break;
            case SDLK_KP3:
                strcpy(mot,"3");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("3\n");}
                break;
            case SDLK_KP4:
                strcpy(mot,"4");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("4\n");}
                break;
            case SDLK_KP5:
                strcpy(mot,"5");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("5\n");}
                break;
            case SDLK_KP6:
                strcpy(mot,"6");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("6\n");}
                break;
            case SDLK_KP7:
                strcpy(mot,"7");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("7\n");}
                break;
            case SDLK_KP8:
                strcpy(mot,"8");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("8\n");}
                break;
            case SDLK_KP9:
                strcpy(mot,"9");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("9\n");}
                break;
                //////////alphabet//////////
            case SDLK_a:
                strcpy(mot,"a");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("a\n");}
                break;
            case SDLK_b:
                strcpy(mot,"b");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("b\n");}
                break;
            case SDLK_c:
                strcpy(mot,"c");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("c\n");}
                break;
            case SDLK_d:
                strcpy(mot,"d");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("d\n");}
                break;
            case SDLK_e:
                strcpy(mot,"e");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("e\n");}
                break;
            case SDLK_f:
                strcpy(mot,"f");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("f\n");}
                break;
            case SDLK_g:
                strcpy(mot,"g");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("g\n");}
                break;
            case SDLK_h:
                strcpy(mot,"h");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("h\n");}
                break;
            case SDLK_i:
                strcpy(mot,"i");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("i\n");}
                break;
		    case SDLK_j:
                strcpy(mot,"j");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("j\n");}
                break;
            case SDLK_k:
                strcpy(mot,"k");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("k\n");}
                break;
            case SDLK_l:
                strcpy(mot,"l");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("l\n");}
                break;
            case SDLK_m:
                strcpy(mot,"m");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("m\n");}
                break;
            case SDLK_n:
                strcpy(mot,"n");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("n\n");}
                break;
            case SDLK_o:
                strcpy(mot,"o");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("o\n");}
                break;
            case SDLK_p:
                strcpy(mot,"p");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("p\n");}
                break;
            case SDLK_q:
                strcpy(mot,"q");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("q\n");}
                break;
            case SDLK_r:
                strcpy(mot,"r");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("r\n");}
                break;
				case SDLK_s:
                strcpy(mot,"s");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("s\n");}
                break;
            case SDLK_t:
                strcpy(mot,"t");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("t\n");}
                break;
            case SDLK_u:
                strcpy(mot,"u");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("u\n");}
                break;
            case SDLK_v:
                strcpy(mot,"v");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("v\n");}
                break;
            case SDLK_w:
                strcpy(mot,"w");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("w\n");}
                break;
            case SDLK_x:
                strcpy(mot,"x");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("x\n");}
                break;
            case SDLK_y:
                strcpy(mot,"y");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("y\n");}
                break;
            case SDLK_z:
                strcpy(mot,"z");
                if(strlen(phrase)<5){strcat(phrase,mot);printf("z\n");}
                break;
         }
     }
            affichage(ecran,background); 
            if(enigmeDone==1){done=0;affichage(ecran,quiz1);}

            if(enigmeDone==2){done=2;affichage(ecran,quiz2);}

            if(enigmeDone==3){done=3;affichage(ecran,quiz3);
            zoneSaisie=TTF_RenderText_Blended(police,phrase,couleurbleu);
            SDL_BlitSurface(zoneSaisie,NULL,ecran,&poszoneSaisie);}

            if(enigmeDone==4)
            {done=4;affichage(ecran,quiz4);
            zoneSaisie=TTF_RenderText_Blended(police,phrase,couleurbleu);
            SDL_BlitSurface(zoneSaisie,NULL,ecran,&poszoneSaisie);}

            if(enigmeDone==5){winenigme=1;Mix_PlayChannel(1,soundwin,0);affichage(ecran,win);}

            SDL_Flip(ecran);
                        
    } //background,quiz1,quiz2,quiz3,quiz4,win
    TTF_CloseFont(police);
    SDL_Quit(); // Arrêt de la SDL
    librer_image(background);
    librer_image(quiz1);//sdl freesur
    librer_image(quiz2);
    librer_image(quiz3);
    librer_image(quiz4);
    librer_image(win);
    SDL_FreeSurface(zoneSaisie);
   
    return winenigme; 
}







