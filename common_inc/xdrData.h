#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include <stdio.h>
#include <stdlib.h>

#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/rpc.h>
#include <rpc/types.h>

#include <pthread.h>
#include "infoGame.h"

#define PROGNUM 0x20001055 
#define VERSNUM 1
#define PROCNUM 1
#define N 2

enum flagDataType { flagExchange, flagPath, flagObstacleList }; 

typedef struct xarray
{
  int size;
  char* p_array;
  
} xarray;

typedef struct {
  int clientId;
  int dataFlag;
  int dataSize;
  char* dataRaw;
  int  *intRaw;
} dataStruct;

// Définition du filtre XDR pour la structure entiers2
bool_t xdrDataFilter(XDR *xdrs, dataStruct *e);
char* obstacleToRawData(int* dataSizeParam, t_obstacle* tabObs[], int tabSize); 
void* rawDataToObstacle(t_obstacle* tabObs[], int* tabSize, char* data);


#endif // __INCLUDE_H__
