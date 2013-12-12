#include "xdrData.h"
#include "person.h"
#define SIZETEST 256

// Filtre xdr pour la structure entiers2
bool_t xdrDataFilter(XDR *xdrs, dataStruct *e)
{
  //XDR xdr_encode, xdr_decode;
  //char tab[SIZETEST];
  //bool_t toto = true;

  //xdrmem_create(&xdr_encode, tab, SIZETEST, XDR_ENCODE);
  //xdrmem_create(&xdr_decode, tab, SIZETEST, XDR_DECODE);
  
  //Encoding xdr
  /*if( !xdr_int( &xdr_encode,&e->clientId) ) return toto;
  fprintf(stdout,"Error when encoding clientId \n");

  if(!xdr_int(&xdr_encode,&e->dataFlag)) return toto;
  fprintf(stdout,"Error when encoding clientId \n");

  if(!xdr_int(&xdr_encode,&e->dataSize)) return toto;
  fprintf(stdout,"Error when encoding clientId \n");

  if(!xdr_bytes(&xdr_encode,&(e->dataRaw),(uint*)&(e->dataSize),9999999)) return toto;
  fprintf(stdout,"Error when encoding clientId \n");*/

  //Decoding xdr
/*
  if(!xdr_int(&xdr_decode,&e->clientId)) return toto;
  fprintf(stdout,"Error when decoding clientId \n");

  if(!xdr_int(&xdr_decode,&e->dataFlag)) return toto;
  fprintf(stdout,"Error when decoding clientId \n");

  if(!xdr_int(&xdr_decode,&e->dataSize)) return toto;
  fprintf(stdout,"Error when decoding clientId \n");

  e->dataRaw = (char*)malloc(e->dataSize);

  if(!xdr_bytes(&xdr_decode,&(e->dataRaw),(uint*)&(e->dataSize),e->dataSize)) return toto;
  fprintf(stdout,"Error when decoding clientId \n");
  
  return toto;*/
  u_int test=_MAX_PATH_SIZE;
  //return xdr_int(xdrs,&(e->clientId))&&xdr_int(xdrs,&(e->dataFlag))&&xdr_int(xdrs,&(e->dataSize))&&xdr_array(xdrs,&(e->dataRaw),&test,test,sizeof(char),(xdrproc_t)xdr_char);
  return xdr_int(xdrs,&(e->clientId))&&xdr_int(xdrs,&(e->dataFlag))&&xdr_int(xdrs,&(e->dataSize))&&xdr_array(xdrs,&(e->dataRaw),&test,test,sizeof(char),(xdrproc_t)xdr_char)&&xdr_array(xdrs,(char**)&e->intRaw,&test,test,sizeof(int),(xdrproc_t)xdr_int);
}

/*char* obstacleToRawData(int* dataSizeParam, t_obstacle* tabObs[], int tabSize)
{
  char* data;
  int dataSize = 0;
  int offset = 0;
  flagDataType flag = flagObstacleList; 

  //Add the number of obstacle
  dataSize += sizeof(int);

  //The number of obstacle *(ObsSize+theObsRadius(int)+the center's posX(int)+the center's posY(int))
  dataSize += tabSize*(sizeof(obsSize) + sizeof(int) + sizeof(int) + sizeof(int));

  *dataSizeParam = dataSize;
  data = (char*)malloc(dataSize);
  
  //set data to 0
  memset(data,0,dataSize);

  //Number of obstacle
  memcpy(data+offset, &tabSize, sizeof(int));
  offset+=sizeof(int);

  obsSize tempObsSize;
  int tempObsRadius=0;
  int tempPosX=0;
  int tempPosY=0;

  for(int i =0;i<tabSize;i++)
    {
      tempObsSize = tabObs[i]->getObsSize();
      tempObsRadius = tabObs[i]->getRadius();
      tempPosX = tabObs[i]->getCenter()->getX();
      tempPosY = tabObs[i]->getCenter()->getY();

      memcpy(data+offset, &tempObsSize, sizeof(obsSize));
      offset+=sizeof(obsSize);

      memcpy(data+offset, &tempObsRadius, sizeof(int));
      offset+=sizeof(int);
      
      memcpy(data+offset, &tempPosX, sizeof(int));
      offset+=sizeof(int);

      memcpy(data+offset, &tempPosY, sizeof(int));
      offset+=sizeof(int);
    }
};

void* rawDataToObstacle(t_obstacle* tabObs[], int* tabSize, char* data)
{
  int offset = 0;

  memcpy(tabSize, data+offset, sizeof(int));
  offset+=sizeof(int);
  
  tabObs = (Obstacle**)malloc((*tabSize)*sizeof(Obstacle));

  obsSize tempObsSize;
  int tempObsRadius=0;
  int tempPosX=0;
  int tempPosY=0;

  for(int i = 0; i<*tabSize;i++)
    {
      memcpy(&tempObsSize, data+offset, sizeof(obsSize));
      offset+=sizeof(obsSize);
      memcpy(&tempObsRadius, data+offset, sizeof(int));
      offset+=sizeof(int);
      memcpy(&tempPosX, data+offset, sizeof(int));
      offset+=sizeof(int);
      memcpy(&tempPosY, data+offset, sizeof(int));
      offset+=sizeof(int);
      
      tabObs[i] = new Obstacle(tempObsSize, tempObsRadius, tempPosX, tempPosY);
    }
}*/
  
