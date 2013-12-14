#include 		"xdrData.h"
#include 		"person.h"
#include		"dataCommon.h"

#include 		<rpc/types.h>
#include 		<rpc/xdr.h>
#include 		<rpc/rpc.h>

t_xdr_door* theDoor;
t_dot2d theFlag;
t_xdr_obstacle* tabObs[_MAX_OBSTACLE];
t_person** village;

void displayVillage()
{
  int i,j;
  for(i=0;i<MAX_POP;i++)
    {
      printf("%d[",i);
      for(j=0;j<_MAX_PATH_SIZE;j++)
	printf("%d",village[i]->path[j]);
      printf("]\n\n\n");
    }
};


void		initVillage()
{
  int		i;
  int		j;

  village=malloc(MAX_POP * sizeof(struct s_person*));

  for(i=0;i<MAX_POP;i++) 
    { 
      village[i]=malloc(sizeof(struct s_person)); 
      village[i]->current=0; 
      village[i]->mark=-1; 
      village[i]->path=malloc(_MAX_PATH_SIZE*sizeof(int));

      for(j=0;j<_MAX_PATH_SIZE;j++)
	village[i]->path[j]=rand()%9;
    }
};

/* New main by (still) Coni */
int main(int argc, char **argv)
{

  char 			*host;
  t_game_data		data;
  t_game_data		res;
  t_dot2d   		posFlag;
  int			i;
  enum clnt_stat 	stat;

  host = argv[1];

  if (argc != 2)
    {
      printf("Usage: %s server_address\n",argv[0]);
      exit(0);
    }

  jesuisdegue = 0;

  posFlag.x = 100+(86/2);
  posFlag.y = (_SCREEN_HEIGHT/2) - 138/2+138;

  srand(time(NULL));

  data.flag = 0;
  data.idClient = 0;
  data.size = 0;
  data.tabObs=NULL;
  
  res.tabObs=NULL;

  stat = callrpc(host
  		 ,PROGNUM
  		 ,VERSNUM
  		 ,PROCNUM
  		 ,(xdrproc_t) xdr_game_data
  		 ,(char*)&data
  		 ,(xdrproc_t) xdr_game_data
  		 ,(char*)&res
  		 );

  if (stat != RPC_SUCCESS)
    {
      fprintf(stderr, "Echec de l'appel distant\n");
      clnt_perrno(stat);
      fprintf(stderr, "\n");
      exit(0);
    }
  else
    {
      printf("Call Succes dude \n");
    }

  
  initVillage();

  calculAllMarks(village,res.tabObs,res.door,posFlag,res.size);

  giveMeTheBests(village, 0);
  

  //2nd call

  res.tabObs=NULL;
 
  data.tabObs=NULL;
  data.flag = 2;
  data.idClient = 0;
  data.size = 1;

  data.person.current =1000;
  data.person.mark = 10;
  data.person.path = malloc(1000*sizeof(int));

  //printf("\nPATH :");

  for(i=0;i<1000;i++)
    {
      data.person.path[i] = rand()%8;
      printf("[%d]", data.person.path[i]);
    }
  //printf(" \nEND \n");


  stat = callrpc(host
		 ,PROGNUM
		 ,VERSNUM
		 ,PROCNUM
		 ,(xdrproc_t) xdr_game_data
		 ,(char*)&data
		 ,(xdrproc_t) xdr_game_data
		 ,(char*)&res
		 );

  if (stat != RPC_SUCCESS)
    {
      fprintf(stderr, "Echec de l'appel distant\n");
      clnt_perrno(stat);
      fprintf(stderr, "\n");
    }
  else
    {
      printf("Call 2 Success dude \n");
    }
}
  
