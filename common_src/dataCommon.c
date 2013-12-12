/*
** dataCommon.c for geneticPath in /home/mjolnir
** 
** Made by Nicolas Cataldo
** Contact   <cataldo.nico@gmail.com>
** 
** Started on  Thu Dec 12 16:20:27 2013 Nicolas Cataldo
** Last update Thu Dec 12 16:21:03 2013 Nicolas Cataldo
*/

#include		"dataCommon.h"

/*
 ** Return the distance between two dot
 */
double 			distance(int x1, int y1, int x2, int y2)
{
  return sqrt( pow( x2 - x1, 2 ) + pow( y2 - y1, 2 ) );
};
