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

/* Main By Coni~~ */

int main(int argc, char **argv)
{

  char 			*host;
  t_game_data		data;
  t_game_data		res;
  enum clnt_stat 	stat;
  int			i,j,worstId,momId,dadId,worstMark,mutateOrNot;
  t_dot2d   posFlag;
  bool found;

  host = argv[1];

  if (argc != 2) 
    { 
      printf("Usage: %s server_address\n",argv[0]);
      exit(0);
    }
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
    }
  else
    {
		  printf("Call Succes dude \n");
		  
		  i = 0;
		  printf(" data size %d \n", res.size);
		  for (i=0; i<res.size; i++)
			{
			  printf("Obs num %d : %d Radius, x_src = %d, y_src = %d \n"
				 ,i
				 ,res.tabObs[i].obsRadius
				 ,res.tabObs[i].obsCenter.x
				 ,res.tabObs[i].obsCenter.y);
			}
		

		/****************************
		 * Initializing village		*
		 * **************************/
		village=malloc(MAX_POP*sizeof(struct s_person*));
		for(i=0;i<MAX_POP;i++) 
		{ 
			village[i]=malloc(sizeof(struct s_person)); 
			village[i]->current=0; 
			village[i]->mark=-1; 
			village[i]->path=malloc(_MAX_PATH_SIZE*sizeof(int));
			for(j=0;j<_MAX_PATH_SIZE;j++)
				village[i]->path[j]=rand()%9;
		 }
		 calculAllMarks(village,res.tabObs,res.door,posFlag,res.size);
		 worstMark=getWorst(village);		//What's the worst result?
		 
		int zzz;
		
		/************************
		 * LOOPING FOR DEBUG	*
		 * **********************/
		 			int u=0;
		for(zzz=0;zzz<5000;zzz++)
		{
			//printf("%d",zzz);
			found=false;
			
			for(i=0;i<MAX_POP && !found;i++)
				if(village[i]->mark==worstMark)
				{
					worstId=i;
					found=true;
				}
			village[worstId]->mark=-1;

			momId=rand()%MAX_POP;	//Let's take a mother
			dadId=rand()%MAX_POP;	//Let's take a father
			village[worstId]->path=crossOver(village[dadId],village[momId]);	//Let them have some sex
			calculMark(village[worstId],res.tabObs, res.door, posFlag,res.size);	//How about the son's results?
			if(village[worstId]==0)		//if this guy is a jackass, we try again
			{
				momId=rand()%MAX_POP;
				dadId=rand()%MAX_POP;
				village[worstId]->path=crossOver(village[dadId],village[momId]);
				calculMark(village[worstId],res.tabObs, res.door, posFlag,res.size);
			}
			mutateOrNot=rand()%100;

			if(mutateOrNot>=_PERCENT_OF_NOMUTATION)
			{
				u=rand()%MAX_POP;
				printf("We mutate! (%d : %d)",u, village[u]->mark);
				mutate(village[u]);
				calculMark(village[u],res.tabObs,res.door,posFlag,res.size);
				
			}
			
		}

    }
    printf("av : %d",village[0]->mark);
	mutate(village[0]);
	calculMark(village[0],res.tabObs,res.door,posFlag,res.size);
	printf(" ap : %d",village[0]->mark);
  return 0;
}
