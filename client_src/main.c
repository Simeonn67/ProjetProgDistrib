#include 		"xdrData.h"
#include 		"person.h"

#include 		<rpc/types.h>
#include 		<rpc/xdr.h>
#include 		<rpc/rpc.h>

#define MAX_POP 60


t_xdr_door* theDoor;
t_dot2d theFlag;
t_xdr_obstacle* tabObs[_MAX_OBSTACLE];
t_person* village[MAX_POP];

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
  int			i;

  host = argv[1];

  if (argc != 2) 
    { 
      printf("Usage: %s server_address\n",argv[0]);
      exit(0);
    }

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
      	     ,res.tabObs[i].obsSource.x
      	     ,res.tabObs[i].obsSource.y);
      	}

      

    }

  return 0;
}


/* int main(int argc, char *argv[]) */
/* { */
/* 	srand(time(NULL)); */
/* 	int i,j,randomInteger; */
/*   for(i=0;i<MAX_POP;i++) */
/*     { */
/* /\*		  direction randomDirection; */
/*   int randomInteger; */

/*   current = 0; */
/*   mark = -1; */

/* //  srand (time(NULL)); */

/*   for(int i=0;i<_MAX_PATH_SIZE;i++) */
/*     { */
/*       randomInteger = rand() % 8 + 1; */
/*       randomDirection = static_cast<direction>(randomInteger); */
/*       path[i] = randomDirection; */
/*     } */
/* *\/ */
/* 		village[i]=malloc(sizeof(village)); */
/* 		village[i]->current=0; */
/* 		village[i]->mark=-1; */
/* 		for(j=0;j<_MAX_PATH_SIZE;j++) */
/* 		{ */
/* 			randomInteger=rand()%8+1; */
/* 			village[i]->path[j]=randomInteger; */
/* 		} */
/*       //village[i] = new Person(); */
/*     } */
/*   /\*int newObsSize = 0; */
/*   int newObsPosX = 0; */
/*   int newObsPosY = 0;  */
/*   t_obstacle* newObstacle; */
/*   bool newObsInCollision = false; */
/*   int nbObs=0; //number of obstacle */
/*   bool posAvailable; */
/* 	//SDL_Surface* screen; */
/* 	//theDoor = new Door(screen, _SCREEN_WIDTH, _SCREEN_HEIGHT); */

/*   theFlag.x=100; */
/*   theFlag.y=(_SCREEN_HEIGHT/2) - 138/2; */

/*   srand (time(NULL)); */

/* 	for(i=0;i<_MAX_OBSTACLE;i++) */
/*     { */
/*       newObsSize = rand() % 10 + 1; */
/*       newObstacle = new Obstacle(screen, newObsSize); */

/*       posAvailable = false; */

/*       cout << " \n Obs size is : " << newObsSize*20 << "\n" ; */

/*       while(posAvailable == false) */
/* 	{ */
/* 	  posAvailable = true; */
/* 	  newObsPosX = rand() % ((3*_SCREEN_WIDTH)/4) + (_SCREEN_WIDTH/4) ; */
/* 	  newObsPosY = rand() % _SCREEN_HEIGHT; */
/* 	  newObstacle->setPosition(newObsPosX,newObsPosY); */

/* 	  for(int y=0;y<nbObs;y++) */
/* 	    { */
/* 	      if(newObstacle->isInCollision(tabObs[y]) || theDoor->isInCollision(newObstacle) ) */
/* 		{ */
/* 		  posAvailable = false; */
/* 		  break; */
/* 		} */
/* 	    } */
/* 	} */
      
/*       nbObs++; */
/*       tabObs[i] = new Obstacle(screen, newObsSize); */
/*       tabObs[i]->setPosition(newObsPosX,newObsPosY); */
/*       delete newObstacle; */
/*     }*\/ */
/*     //printf("%d",village[1]->getMark()); */
/* 	//village[1]->calculMark(tabObs,*theDoor,theFlag); */
	
/* //	displayVillage(); */
/* /\*	for(i=0;i<MAX_POP;i++) */
/* 	{ */
/* 		calculMark(village[i],tabObs,*theDoor,theFlag); */
		
/* 		printf("%d\n",village[i]->mark); */
/* 	}*\/ */
/* 	//printf("%d",village[1]->getMark()); */
/* 		//displayVillage(); */
/* if(argc<2) */
/* { */
/* 	printf("No enough params!\n"); */
/* 	exit(1); */
/* } */
/*   char *host = argv[1]; */
/*   enum clnt_stat stat; */
/* 	/\*deuxmatricesopeplus aEnvoyer = {mat1,mat2,1,taille}; */
/* 	if(atoi(argv[2])==1) */
/* 	{ */
/* 		printf("1\n"); */
/* 		aEnvoyer.ope=1; */
/* 	} */
/* 	else */
/* 	{ */
/* 		printf("2\n"); */
/* 		aEnvoyer.ope=2; */
/* 	}*\/ */
/* 	dataStruct test; */
/* 	test.clientId=0; */
/* 	test.dataFlag=0; */
/* 	test.dataSize=0; */
/* 	test.dataRaw=NULL; */
/* 	test.intRaw=malloc(100*sizeof(int)); */
/* 	int a; */
/* 	for(a=0;a<100;a++) */
/* 		test.intRaw[a]=a; */
	
/*   stat = callrpc(host,PROGNUM,VERSNUM,PROCNUM,(xdrproc_t)xdrDataFilter,(char*)&test,(xdrproc_t)xdrDataFilter,(char*)&test);  */
/*   if (stat != RPC_SUCCESS) {  */
/*     fprintf(stderr, "Echec de l'appel distant\n"); */
/*     clnt_perrno(stat); */
/*     fprintf(stderr, "\n"); */
/*   } else { */
/* 	  printf("Return!\n"); */
/*   } */
/*   return(0); */

	

/* 	for(j=0;j<MAX_POP;j++) */
/*     { */
/*       free(village[j]); */
/*     } */
/* 	return 0; */
/* } */

