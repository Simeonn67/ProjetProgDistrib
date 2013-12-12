/*
** dataServer.c for geneticPath in /home/mjolnir
** 
** Made by Nicolas Cataldo
** Contact   <cataldo.nico@gmail.com>
** 
** Started on  Thu Dec 12 15:51:27 2013 Nicolas Cataldo
** Last update Thu Dec 12 20:35:10 2013 Nicolas Cataldo
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

  if(distance < radiusSum)
    return 1;

  return 0;
};
