/*
** main.c for geneticPath in /home/mjolnir
** 
** Made by Nicolas Cataldo
** Contact   <cataldo.nico@gmail.com>
** 
** Started on  Thu Dec 12 19:28:12 2013 Nicolas Cataldo
** Last update Sat Dec 14 11:07:00 2013 Nicolas Cataldo
*/

#include		<stdio.h>
#include 		<stdlib.h>
#include		<string.h>
#include		<math.h>
#include		<time.h>
#include		<SDL/SDL.h>
#include		<SDL/SDL_image.h>
#include		<SDL/SDL_thread.h>

#include		"dataServer.h"
#include		"xdrData.h"

int			exitMainLoop = 0;
int			nbClient=0;
int			randomNbObs;
t_door			theDoor;
t_obstacle		tabObs[_MAX_OBSTACLE];
SDL_Surface		*screen = NULL;
SDL_Surface		*fond;
SDL_Surface		*flag;
SDL_Rect		posFond;
SDL_Rect		posFlag;
SDL_Event		event;

void			initDoor()
{
  theDoor.doorHeight = 76;
  theDoor.doorWidth = 89;
  theDoor.screen = screen;
  theDoor.doorSource.x = _SCREEN_WIDTH - theDoor.doorWidth;
  theDoor.doorSource.y = (10+(rand () % ( (_SCREEN_HEIGHT-80) -10 + 1)));
  theDoor.doorSurface = IMG_Load("./res/img/door.png");
  theDoor.doorCenter.x = theDoor.doorSource.x + theDoor.doorWidth/2; 
  theDoor.doorCenter.y = theDoor.doorSource.y + theDoor.doorHeight/2; 

  SDL_BlitSurface(theDoor.doorSurface, NULL, screen, &(theDoor.doorSource));
  SDL_Flip(screen);  
};

/* BIEN REPLACER LE SPRITE PAR RAPPORT AU X ET Y */
void			makeItRun(direction *path, int nb)
{
  int			i;
  int			j;
  int			sheetNum;
  t_sprite		sprite;
  int  			tempo;
  
  sprite.spriteSource.x = posFlag.x;
  sprite.spriteSource.y = posFlag.y+60;
  
  tempo = 3;
  sheetNum=0;

  for (i=0; i < nb; ++i)
    {

      if(sheetNum<8)
	sheetNum++;
      else
	sheetNum=1;
      
      SDL_BlitSurface(fond, NULL, screen, &posFond);
      
      SDL_BlitSurface(flag, NULL, screen, &posFlag);
      

      for (j=0;j<randomNbObs;j++)
	{
	  SDL_BlitSurface(tabObs[j].obsSurface, NULL, screen, &(tabObs[j].obsSource));
	}
      

      SDL_BlitSurface(theDoor.doorSurface, NULL, screen, &(theDoor.doorSource));

      if(tempo == 3)
	{
	  sprite.spriteSurface=loadSprite(path[i], sheetNum);
	  tempo = 0;
	}
      tempo++;
      newSpritePos((int*)&(sprite.spriteSource.x), (int*)&(sprite.spriteSource.y), path[i]);
      SDL_BlitSurface(sprite.spriteSurface, NULL, screen, &(sprite.spriteSource));

      SDL_Flip(screen);

      usleep(1500);
    }
};  
void			loadObstacleImg(int pos, int numObs)
{
  switch(numObs)
    {
    case 1 : tabObs[pos].obsSurface = IMG_Load( ("./res/img/obstacle20px.png") );
      tabObs[pos].obsSize = size01;
      break;
    case 2 : tabObs[pos].obsSurface = IMG_Load( ("./res/img/obstacle40px.png") );
      tabObs[pos].obsSize = size02;
      break;
    case 3 : tabObs[pos].obsSurface = IMG_Load( ("./res/img/obstacle60px.png") );
      tabObs[pos].obsSize = size03;
      break;
    case 4 : tabObs[pos].obsSurface = IMG_Load( ("./res/img/obstacle80px.png") );
      tabObs[pos].obsSize = size04;
      break;
    case 5 : tabObs[pos].obsSurface = IMG_Load( ("./res/img/obstacle100px.png") );
      tabObs[pos].obsSize = size05;
      break;
    case 6 : tabObs[pos].obsSurface = IMG_Load( ("./res/img/obstacle120px.png") );
      tabObs[pos].obsSize = size06;
      break;
    case 7 : tabObs[pos].obsSurface = IMG_Load( ("./res/img/obstacle140px.png") );
      tabObs[pos].obsSize = size07;
      break;
    case 8 : tabObs[pos].obsSurface = IMG_Load( ("./res/img/obstacle160px.png") );
      tabObs[pos].obsSize = size08;
      break;
    case 9 : tabObs[pos].obsSurface = IMG_Load( ("./res/img/obstacle180px.png") );
      tabObs[pos].obsSize = size09;
      break;
    case 10 : tabObs[pos].obsSurface = IMG_Load( ("./res/img/obstacle200px.png") );
      tabObs[pos].obsSize = size10;
      break;
    default : break;
    }

  tabObs[pos].obsRadius = tabObs[pos].obsSize/2; 
};


void			setObstaclePos(int pos, int x, int y)
{
  tabObs[pos].obsSource.x = x;
  tabObs[pos].obsSource.y = y;

  tabObs[pos].obsCenter.y = tabObs[pos].obsSource.y + tabObs[pos].obsRadius;
  tabObs[pos].obsCenter.x = tabObs[pos].obsSource.x + tabObs[pos].obsRadius;
};

void			generateWorld()
{
  int			newObsSize;
  int			newObsPosX;
  int			newObsPosY;
  int			nbObs;
  int			posAvailable;
  int			i;
  int 			y;
  t_obstacle		avoidDoor;

  newObsSize=0;
  newObsPosX=0;
  newObsPosY=0;
  nbObs=0;
  
  srand (time(NULL));

  fond = IMG_Load( ("./res/img/fond.png") );
  posFond.x = 0;
  posFond.y = 0;
  SDL_BlitSurface(fond, NULL, screen, &posFond);
  flag = IMG_Load( ("./res/img/flag.png") );
  posFlag.x = 100;
  posFlag.y = (_SCREEN_HEIGHT/2) - 138/2;
  
  SDL_BlitSurface(flag, NULL, screen, &posFlag);
  SDL_Flip(screen);

  initDoor();

  avoidDoor.obsSize =  size05;
  avoidDoor.obsRadius = avoidDoor.obsSize/2;
  avoidDoor.obsSource.x = theDoor.doorSource.x;
  avoidDoor.obsSource.y = theDoor.doorSource.y;
  avoidDoor.obsCenter.x = theDoor.doorCenter.x;
  avoidDoor.obsCenter.y = theDoor.doorCenter.y;


  randomNbObs = (10+(rand () % (_MAX_OBSTACLE-10+1))); 

  for (i=0;i<randomNbObs;i++)
    {
      newObsSize = rand() % 10 + 1;
      loadObstacleImg(i, newObsSize);
      posAvailable = 0;

      while (posAvailable == 0)
        {
          posAvailable = 1;

          newObsPosX = rand() % ((3*_SCREEN_WIDTH)/4) + (_SCREEN_WIDTH/4) ;
          newObsPosY = rand() % _SCREEN_HEIGHT;
	  setObstaclePos(i, newObsPosX, newObsPosY);
          
          for (y=0;y<nbObs;y++)
            {
              if (isObstacleInCollision(tabObs[i], tabObs[y]))
                {
                  posAvailable = 0;
                  break;
		}
            }

	  if (isObstacleInCollision(tabObs[i], avoidDoor))
	    posAvailable = 0;
        }
      nbObs++;

      SDL_BlitSurface(tabObs[i].obsSurface, NULL, screen, &(tabObs[i].obsSource));
      SDL_Flip(screen);
    }

};

t_game_data		initGameDataStruct()
{
  t_game_data		data;
  int			i;

  data.flag = 1;
  data.idClient = nbClient;
  data.size = randomNbObs;
  data.door.doorHeight = theDoor.doorHeight;
  data.door.doorWidth = theDoor.doorWidth;
  data.door.doorSource.x = theDoor.doorSource.x;
  data.door.doorSource.y = theDoor.doorSource.y;
  data.door.doorCenter.x = theDoor.doorCenter.x;
  data.door.doorCenter.y = theDoor.doorCenter.y;

  data.tabObs = malloc(randomNbObs*sizeof(t_xdr_obstacle));
  
  for (i=0; i<randomNbObs; i++)
    {
      data.tabObs[i].obsRadius = tabObs[i].obsRadius;
      data.tabObs[i].obsSource.x = tabObs[i].obsSource.x;
      data.tabObs[i].obsSource.y = tabObs[i].obsSource.y;
      data.tabObs[i].obsCenter.x = tabObs[i].obsCenter.x;
      data.tabObs[i].obsCenter.y = tabObs[i].obsCenter.y;

    }

  return data;
};

t_game_data 		*proc_dist(t_game_data *t)
{
  static t_game_data 	resend;
  int			i;

  printf("proc dist  \n");

  if (t->flag == 0)
    {
      resend = initGameDataStruct();
      resend.tabObs = NULL;
    }
  else if (t->flag == 2)
    {
      for(i=0;i<t->person.current;i++)
	printf("[%d]", t->person.path[i]);

      makeItRun(t->person.path, t->person.current);
      
      resend.flag = 0;
      resend.idClient =0;
      resend.size=0;
      
    }

  printf("Je repond \n");

  return &resend;
};

int main(void)
{
  bool_t 		stat;


  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(_SCREEN_WIDTH, _SCREEN_HEIGHT, 32, SDL_HWSURFACE);
  generateWorld();
  while( exitMainLoop == 0 ){
    SDL_WaitEvent(&event);
    if (event.type == SDL_QUIT)
      exitMainLoop = 1;
    else if (event.type == SDL_KEYDOWN)
      {
	if (event.key.keysym.sym == SDLK_g)
	  generateWorld();
	else if (event.key.keysym.sym == SDLK_q)
	  {
	    exitMainLoop = 1;
	  }
      }
  }


  jesuisdegue = 1;
  
  stat = registerrpc(PROGNUM
  		     ,VERSNUM
  		     ,PROCNUM
  		     ,proc_dist
  		     ,(xdrproc_t)xdr_game_data
  		     ,(xdrproc_t)xdr_game_data
  		     );

  if (stat != 0)
    {
      fprintf(stderr,"Echec de l'enregistrement\n");
      exit(1);
    }

  svc_run();

  return 0;
}
