/*
** xdrData.c for geneticPath in /home/mjolnir
** 
** Made by Nicolas Cataldo
** Contact   <cataldo.nico@gmail.com>
** 
** Started on  Fri Dec 13 00:52:57 2013 Nicolas Cataldo
** Last update Fri Dec 13 05:30:59 2013 Nicolas Cataldo
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
  printf("\n FINE \n");

  return 1;
};

bool_t			xdr_person(XDR *xdrs, t_person *t)
{
	printf("XDR_PERSON\n");
	u_int toto=_MAX_PATH_SIZE;
  if (!xdr_int(xdrs, &t->current)) return 0;
  if (!xdr_int(xdrs, &t->mark)) return 0;
  if (!xdr_array(xdrs
		,(char**)&t->path
		 ,(u_int*)&t->current // TAILLE DU TABLEAU DANS CURRENT ?
		 //,&toto
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
	printf("XDR_GAME_DATA\n");
	if (!xdr_int(xdrs, &t->flag)) return 0;
	if (!xdr_int(xdrs, &t->idClient)) return 0;
	if (!xdr_int(xdrs, &t->size)) return 0;

	if (t->flag == 0)
		return 1;
	else if (t->flag == 1)
	{
		if(!xdr_door(xdrs, &t->door)) return 0;

			printf("%d SIZE \n", t->size);

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
	else if(t->flag==2)	//client send his best path
	{
		if(t->tabPerson == NULL)
			t->tabPerson = malloc(t->size*sizeof(struct s_person));
		
		if(!xdr_array(xdrs,
			(char**)&t->tabPerson,
			&t->size,
			1,
			sizeof(struct s_person),
			(xdrproc_t)xdr_person))
			return 0;
	}
	return 1;
};

  /*int			flag;
  int			idClient;
  int			size;
  t_xdr_door		door;
  t_xdr_obstacle	*tabObs;
  t_person		*tabPerson;*/
      	  
	  
