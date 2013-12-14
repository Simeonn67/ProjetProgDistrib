/*
** dataServer.h for geneticPath in /home/mjolnir
** 
** Made by Nicolas Cataldo
** Contact   <cataldo.nico@gmail.com>
** 
** Started on  Thu Dec 12 15:53:11 2013 Nicolas Cataldo
** Last update Sat Dec 14 05:11:22 2013 Nicolas Cataldo
*/

#ifndef			_DATA_H_
#define 		_DATA_H_

#include		<stdio.h>
#include 		<stdlib.h>
#include		<string.h>
#include		<math.h>
#include		<SDL/SDL.h>
#include		<SDL/SDL_image.h>
#include		<SDL/SDL_thread.h>

#include		"dataCommon.h"
#include		"person.h"

enum e_obs_size{size01 = 20, size02 = 40, 
		size03 = 60, size04 = 80,
		size05 = 100, size06 = 120, 
		size07 = 140, size08 = 160,
		size09 = 180, size10 = 200};

typedef enum e_obs_size t_obs_size;
typedef enum e_direction_sprite t_direction_sprite;

typedef struct		s_door
{
  unsigned short int   	doorHeight;
  unsigned short int	doorWidth;
  SDL_Rect		doorSource;
  t_dot2d		doorCenter;
  SDL_Surface		*doorSurface;
  SDL_Surface		*screen;
}			t_door;

typedef struct		s_obstacle
{
  t_obs_size		obsSize;
  int			obsRadius;
  SDL_Rect		obsSource;
  t_dot2d		obsCenter;
  SDL_Surface		*obsSurface;
  SDL_Surface		*screen;
}			t_obstacle;

typedef struct		s_sprite
{
  SDL_Rect		spriteSource;
  SDL_Surface		*spriteSurface;
}			t_sprite;

int			isObstacleInCollision(t_obstacle newObstacle, t_obstacle testedObstacle);
SDL_Surface		*loadSprite(direction direc, int which);
void                    newSpritePos(int *x, int *y,direction direct);
#endif /* _DATA_H_ */
