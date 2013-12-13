/*
** xdrData.h for geneticPath in /home/mjolnir
** 
** Made by Nicolas Cataldo
** Contact   <cataldo.nico@gmail.com>
** 
** Started on  Fri Dec 13 00:52:33 2013 Nicolas Cataldo
** Last update Fri Dec 13 03:02:38 2013 Nicolas Cataldo
*/


#ifndef 		_XDRDATA_H_
#define 		_XDRDATA_H_

#include 		<stdio.h>
#include 		<stdlib.h>
#include 		<rpc/types.h>
#include 		<rpc/xdr.h>
#include 		<rpc/rpc.h>
#include 		<rpc/types.h>
#include 		<pthread.h>

#include 		"infoGame.h"
#include		"person.h"

#define 		PROGNUM 0x20001055 
#define 		VERSNUM 1
#define 		PROCNUM 1
#define 		N 2

typedef struct s_game_data
{
  int			flag;
  int			idClient;
  u_int			size;
  t_xdr_door		door;
  t_xdr_obstacle	*tabObs;
  t_person		*tabPerson;
}			t_game_data;

bool_t			xdr_dot2d(XDR *xdrs, t_dot2d *t);
bool_t			xdr_door(XDR *xdrs, t_xdr_door *t);
bool_t			xdr_obstacle(XDR *xdrs, t_xdr_obstacle *t);
bool_t			xdr_person(XDR *xdrs, t_person *t);
bool_t			xdr_game_data(XDR *xdrs, t_game_data *t);



#endif /* _XDRDATA_H_ */
