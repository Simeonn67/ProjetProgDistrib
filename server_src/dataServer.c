/*
** dataServer.c for geneticPath in /home/mjolnir
** 
** Made by Nicolas Cataldo
** Contact   <cataldo.nico@gmail.com>
** 
** Started on  Thu Dec 12 15:51:27 2013 Nicolas Cataldo
** Last update Sat Dec 14 03:35:11 2013 Nicolas Cataldo
*/

#include 		"dataServer.h"

int			isObstacleInCollision(t_obstacle newObstacle, t_obstacle testedObstacle)
{
  double                dist;
  double                radiusSum;

  dist = distance(newObstacle.obsCenter.x
		   ,newObstacle.obsCenter.y
		   ,testedObstacle.obsCenter.x
		   ,testedObstacle.obsCenter.y 
		   );

  radiusSum = newObstacle.obsRadius + testedObstacle.obsRadius;

  if(dist < radiusSum)
    return 1;

  return 0;
};

SDL_Surface		*loadSprite(direction direc, int which)
{
  char 			fullLink[42]="";
  char			*numSheet;

  numSheet = malloc(sizeof(char));

  strcat(fullLink, "./res/img/humanSprite/");
  
  if (direc == Left || direc == UpLeft || direc == DownLeft)
    strcat(fullLink, "lefty/");
  else
    strcat(fullLink, "right/");

  strcat(fullLink, "spriteMov");

  sprintf(numSheet, "%d", which);

  strcat(fullLink, numSheet);

  strcat(fullLink, ".png");

  printf("%s \n", fullLink);

  return IMG_Load( fullLink);
};

void			newSpritePos(int *x, int *y,direction direct)
{
  if( direct == Left || direct == UpLeft || direct == DownLeft)
    *x = *x - _STEP ;
  if(direct == Right || direct == UpRight || direct == DownRight)
    *x = *x + _STEP ;
  if( direct == Up || direct == UpRight || direct == UpLeft)
    *y = *y - _STEP ;
  if (direct == Down || direct == DownLeft || direct == DownRight)
    *y = *y + _STEP ;
};
      

