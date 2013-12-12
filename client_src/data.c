/*
** data.c for geneticPath in /home/mjolnir
** 
** Made by Nicolas Cataldo
** Contact   <cataldo.nico@gmail.com>
** 
** Started on  Thu Dec 12 08:19:32 2013 Nicolas Cataldo
** Last update Thu Dec 12 08:21:57 2013 Nicolas Cataldo
*/

#include 		"data.h"

/*
 ** Return the distance between two dot
 */
double 			distance(int x1, int y1, int x2, int y2)
{
  return sqrt( pow( x2 - x1, 2 ) + pow( y2 - y1, 2 ) );
};
