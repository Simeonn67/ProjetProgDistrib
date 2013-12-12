/*
** main.c for geneticPath in /home/mjolnir
** 
** Made by Nicolas Cataldo
** Contact   <cataldo.nico@gmail.com>
** 
** Started on  Thu Dec 12 19:28:12 2013 Nicolas Cataldo
** Last update Thu Dec 12 21:23:13 2013 Nicolas Cataldo
*/

#include		<stdio.h>
#include 		<stdlib.h>
#include		<string.h>
#include		<math.h>
#include		<SDL/SDL.h>
#include		<SDL/SDL_image.h>
#include		<SDL/SDL_thread.h>


#include		"dataServer.h"

#define			_SCREEN_HEIGHT 720
#define			_SCREEN_WIDTH 1280
#define			_MAX_OBSTACLE 10

SDL_Surface		*screen = NULL;
SDL_Event		event;
int			exitMainLoop = 0;
t_door			theDoor;
t_obstacle		tabObs[_MAX_OBSTACLE];


void			initDoor()
{
  theDoor.doorHeight = 76;
  theDoor.doorWidth = 89;
  theDoor.screen = screen;
  theDoor.doorSource.x = _SCREEN_WIDTH - theDoor.doorWidth;
  theDoor.doorSource.y = (_SCREEN_HEIGHT/2) - (theDoor.doorHeight/2);
  theDoor.obsSurface = IMG_Load("./res/img/door.png");
  theDoor.doorCenter.x = _SCREEN_WIDTH - theDoor.doorWidth/2;
  theDoor.doorCenter.y = _SCREEN_HEIGHT/2;
}

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
};


void			setObstaclePos(int pos, int x, int y)
{
  tabObs[pos].obsSource.x = x;
  tabObs[pos].obsSource.y = y;

  tabObs[pos].obsCenter.x = tabObs[pos].obsSource.x + tabObs[pos].obsRadius;
  tabObs[pos].obsCenter.y = tabObs[pos].obsSource.y + tabObs[pos].obsRadius;
};

void			generateWorld()
{
  SDL_Surface		*fond;
  SDL_Rect		posFond;
  SDL_Surface		*flag;
  SDL_Rect		posFlag;
  int			newObsSize;
  int			newObsPosX;
  int			newObsPosY;
  int			nbObs;
  bool			posAvailable;
  Obstacle		*newObstacle;

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

  for (int i=0;i<_MAX_OBSTACLE;i++)
    {
      newObsSize = rand() % 10 + 1;
      loadObstacleImg(i, newObsSize);
      posAvailable = false;

      while (posAvailable == false)
        {
          posAvailable = true;

          newObsPosX = rand() % ((3*_SCREEN_WIDTH)/4) + (_SCREEN_WIDTH/4) ;
          newObsPosY = rand() % _SCREEN_HEIGHT;
	  setObstaclePos(i, newObsPosX, newObsPosY);
          
          for (int y=0;y<nbObs;y++)
            {
              if (isObstacleInCollision(tabObs[i], tabObs[y]))
                {
                  posAvailable = false;
                  break;
		}
            }
        }
      nbObs++;

      SDL_BlitSurface(tabObs[i].obsSurface, NULL, screen, &(tabObs[i].obsSource));
      SDL_Flip(screen);
    }

};



int main(void)
{
    
  return 0;
}
