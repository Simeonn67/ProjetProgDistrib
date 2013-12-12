/*
** data.h for geneticPath in /home/mjolnir
** 
** Made by Nicolas Cataldo
** Contact   <cataldo.nico@gmail.com>
** 
** Started on  Thu Dec 12 08:06:49 2013 Nicolas Cataldo
** Last update Thu Dec 12 15:41:27 2013 Nicolas Cataldo
*/

#ifndef			_DATA_H_
#define 		_DATA_H_

#include		<stdio.h>
#include 		<stdlib.h>
#include		<string.h>
#include		<math.h>
 
enum e_obs_size{size01 = 020, size02 = 040, 
		size03 = 060, size04 = 080,
		size05 = 100, size06 = 120, 
		size07 = 140, size08 = 160,
		size09 = 180, size10 = 200};

typedef struct          s_dot2d
{
  int 			x;
  int			y;
}                       t_dot2d;

double			distance(int x1, int y1, int x2, int y2);


typedef struct		s_door
{
  unsigned short int   	doorHeight;
  unsigned short int	doorWidth;
  t_dot2d		doorSource;
  t_dot2d		doorCenter;
}			t_door;



typedef struct		s_obstacle
{
  e_obs_size		obsSize;
  int			obsRadius;
  t_dot2d		obsSource;
  t_dot2d		obsCenter;
}			t_obstacle;


#endif /* _DATA_H_ */
