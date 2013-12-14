/*
** xdrData.c for geneticPath in /home/mjolnir
** 
** Made by Nicolas Cataldo
** Contact   <cataldo.nico@gmail.com>
** 
** Started on  Fri Dec 13 00:52:57 2013 Nicolas Cataldo
** Last update Sat Dec 14 06:50:12 2013 Nicolas Cataldo
*/

#include "xdrData.h"

#define SIZETEST 256




bool_t			xdr_dot2d(XDR *xdrs, t_dot2d *t)
{
  if (!xdr_int(xdrs, &t->x)) return 0;
  if (!xdr_int(xdrs, &t->y)) return 0;

  return 1;
};

bool_t			xdr_door(XDR *xdrs, t_xdr_door *t)
{
  if (!xdr_int(xdrs, &t->doorHeight)) return 0;
  if (!xdr_int(xdrs, &t->doorWidth)) return 0;
  if (!xdr_dot2d(xdrs, &t->doorSource)) return 0;
  if (!xdr_dot2d(xdrs, &t->doorCenter)) return 0;
  
  return 1;
};

bool_t			xdr_obstacle(XDR *xdrs, t_xdr_obstacle *t)
{
  if (!xdr_int(xdrs, &t->obsRadius)) return 0;
  if (!xdr_dot2d(xdrs, &t->obsSource)) return 0;
  if (!xdr_dot2d(xdrs, &t->obsCenter)) return 0;

  return 1;
};

bool_t			xdr_person(XDR *xdrs, t_person *t)
{
  if (!xdr_int(xdrs, &t->current)) return 0;
  if (!xdr_int(xdrs, &t->mark)) return 0;

  t->path = malloc(t->current*sizeof(int));
  
  if (!xdr_array(xdrs
		 ,(char**)&t->path
		 ,&t->current
		 ,_MAX_PATH_SIZE
		 ,sizeof (int)
		 ,(xdrproc_t)xdr_int))
    return 0;

  return 1;
};

/*
** flag = 0 : new client   // server send info to init the world
** flag = 1 : new client   // client  get info and decode
** flag = 2 : known client // client send his best path
** flag = 3 : known client // client send ~10 person for exchange
** flag = 4 : known client // client get ~10 person in exchange
*/
bool_t			xdr_game_data(XDR *xdrs, t_game_data *t)
{
  if (!xdr_int(xdrs, &t->flag)) return 0;
  if (!xdr_int(xdrs, &t->idClient)) return 0;
  if (!xdr_int(xdrs, &t->size)) return 0;
  
  if (t->flag == 0)
    {
      return 1;
    }
  else if (t->flag == 1)
    {
      if(!xdr_door(xdrs, &t->door)) return 0;
      
      if(t->tabObs == NULL)
	t->tabObs = malloc(t->size*(sizeof (struct s_xdr_obstacle)));

      if (!xdr_array(xdrs
		     ,(char**)&t->tabObs
		     ,&t->size
		     ,_MAX_OBSTACLE
		     ,sizeof (struct s_xdr_obstacle)
		     ,(xdrproc_t)xdr_obstacle))
	return 0;
    }
  else if(t->flag==2 || t->flag==3)
    {
      if(!xdr_person(xdrs,  &t->person)) return 0;
    }

  return 1;

};
