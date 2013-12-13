/*
** dataCommon.h for geneticPath in /home/mjolnir
** 
** Made by Nicolas Cataldo
** Contact   <cataldo.nico@gmail.com>
** 
** Started on  Thu Dec 12 16:18:19 2013 Nicolas Cataldo
** Last update Fri Dec 13 01:40:16 2013 Nicolas Cataldo
*/

#ifndef _DATACOMMON_H_
#define _DATACOMMON_H_

#include		<stdio.h>
#include 		<stdlib.h>
#include		<string.h>
#include		<math.h>

#define 		_MAX_OBSTACLE	15
#define 		_SCREEN_HEIGHT 720
#define 		_SCREEN_WIDTH 1280

typedef struct          s_dot2d
{
  int 			x;
  int			y;
}                       t_dot2d;

double			distance(int x1, int y1, int x2, int y2);

#endif /* _DATACOMMON_H_ */
