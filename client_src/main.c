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

}
