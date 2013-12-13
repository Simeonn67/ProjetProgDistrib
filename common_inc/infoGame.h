/*
** data.h for geneticPath in /home/mjolnir
** 
** Made by Nicolas Cataldo
** Contact   <cataldo.nico@gmail.com>
** 
** Started on  Thu Dec 12 08:06:49 2013 Nicolas Cataldo
** Last update Fri Dec 13 02:23:53 2013 Nicolas Cataldo
*/

#ifndef _INFOGAME_H_
#define _INFOGAME_H_

#include		<stdio.h>
#include 		<stdlib.h>
#include		<string.h>
#include		<math.h>

#include		"dataCommon.h"

#define 		bool int
#define 		true 1
#define 		false 0


typedef struct		s_xdr_door
{
  int   		doorHeight;
  int			doorWidth;
  t_dot2d		doorSource;
  t_dot2d		doorCenter;
}			t_xdr_door;


typedef struct		s_xdr_obstacle
{
  int			obsRadius;
  t_dot2d		obsSource;
  t_dot2d		obsCenter;
}			t_xdr_obstacle;

#endif /* _INFOGAME_H_ */
