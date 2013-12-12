/*
** data.h for geneticPath in /home/mjolnir
** 
** Made by Nicolas Cataldo
** Contact   <cataldo.nico@gmail.com>
** 
** Started on  Thu Dec 12 08:06:49 2013 Nicolas Cataldo
** Last update Thu Dec 12 16:22:38 2013 Nicolas Cataldo
*/

#ifndef			_DATA_H_
#define 		_DATA_H_

#include		<stdio.h>
#include 		<stdlib.h>
#include		<string.h>
#include		<math.h>

#include		"dataCommon.h"


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
