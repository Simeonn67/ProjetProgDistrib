#include "person.h"

void calculMark(t_person* pers, t_xdr_obstacle *tabObs, t_xdr_door theDoor, t_dot2d theFlag, int size)
{
  int MaxMark=_MAX_MARK;
  t_dot2d currentPos;
  currentPos.x=theFlag.x;
  currentPos.y=theFlag.y;
  int contact=false;
  int i=0;
  for(i=0;i<_MAX_PATH_SIZE && !contact;i++)
    {
      if(isInTheDoor(currentPos,theDoor))
	{
	  printf("END!");
	  pers->current=i;
	  contact=true;
	}
      if(Conflict(currentPos,tabObs, size))
	{
	  MaxMark=_MAX_MARK/2;
	  printf("CONTACT!");
	  contact=true;
	}
      
      //MaxXXi code compressor
      if(pers->path[i] == Left || pers->path[i] == UpLeft || pers->path[i] == DownLeft)
	currentPos.x=currentPos.x-_STEP;
      if(pers->path[i] == Right || pers->path[i] == UpRight || pers->path[i] == DownRight)
	currentPos.x=currentPos.x+_STEP;
      if(pers->path[i] == Up || pers->path[i] == UpRight || pers->path[i] == UpLeft)
	currentPos.y=currentPos.y-_STEP;
      if(pers->path[i] == Down || pers->path[i] == DownLeft || pers->path[i] == DownRight)
	currentPos.y=currentPos.y+_STEP;

      /* switch(pers->path[i]) */
      /* 	{ */
      /* 	case DownRight: */
      /* 	  currentPos.x=currentPos.x+_STEP; */
      /* 	  currentPos.y=currentPos.y+_STEP; */
      /* 	  //printf("'\\ "); */
      /* 	  break; */
      /* 	case Right: */
      /* 	  currentPos.x=currentPos.x+_STEP; */
      /* 	  //printf("-> "); */
      /* 	  break; */
      /* 	case UpRight: */
      /* 	  currentPos.x=currentPos.x+_STEP; */
      /* 	  currentPos.y=currentPos.y-_STEP; */
      /* 	  //printf("./ "); */
      /* 	  break; */
      /* 	case Down: */
      /* 	  currentPos.y=currentPos.y+_STEP; */
      /* 	  //printf("'| "); */
      /* 	  break; */
      /* 	case UpLeft: */
      /* 	  currentPos.x=currentPos.x-_STEP; */
      /* 	  currentPos.y=currentPos.y-_STEP; */
      /* 	  //printf("\\. "); */
      /* 	  break; */
      /* 	case Left: */
      /* 	  currentPos.x=currentPos.x-_STEP; */
      /* 	  //printf("<- "); */
      /* 	  break; */
      /* 	case DownLeft: */
      /* 	  currentPos.x=currentPos.x-_STEP; */
      /* 	  currentPos.y=currentPos.y+_STEP; */
      /* 	  //printf("/' "); */
      /* 	  break; */
      /* 	case Up: */
      /* 	  currentPos.y=currentPos.y-_STEP; */
      /* 	  //printf(".| "); */
      /* 	  break; */
      /* 	} */
    }
  if(distanceLeft(currentPos, theDoor)>distanceBetweenStartStop(theDoor,theFlag))
    {
      pers->mark=0;
    }
  else
    {
      pers->mark=MaxMark-(distanceLeft(currentPos, theDoor)*_MAX_MARK/2)/(distanceBetweenStartStop(theDoor, theFlag));
    }
  printf(" : %d\n",pers->mark);
};

int* crossOver(t_person* Daddy, t_person* Mummy)
{
  int randomForSide, randomForSize;
  direction *son=malloc(_MAX_PATH_SIZE*sizeof(int));
  randomForSide=rand() % 2;
  randomForSize=rand() % _MAX_PATH_SIZE;
  while((_PERCENT_ALLOWED*min(Mummy->current,Daddy->current))/100>=randomForSize)
    randomForSize=rand()%_MAX_PATH_SIZE;
  int i;
  switch(randomForSide)
    {
    case LeftSide:
      for(i=0;i<randomForSize;i++)
	son[i]=Mummy->path[i];
      for(i=randomForSize;i<_MAX_PATH_SIZE;i++)
	son[i]=Daddy->path[i];
      break;

    case RightSide:
      for(i=0;i<randomForSize;i++)
	son[i]=Daddy->path[i];
      for(i=randomForSize;i<_MAX_PATH_SIZE;i++)
	son[i]=Mummy->path[i];
      break;
    }
  return (int*)son;
};

int Conflict(t_dot2d currentPos, t_xdr_obstacle *tabObs, int size)
{
  int i;
	
  for(i=0;i<size;i++)
    {
      if(distance(currentPos.x,currentPos.y,tabObs[i].obsCenter.x,tabObs[i].obsCenter.y)<=tabObs[i].obsRadius)
	return true;
    }
  return false;
}

float distanceLeft(t_dot2d currentPos, t_xdr_door theDoor)
{
  return distance(currentPos.x,currentPos.y,theDoor.doorCenter.x,theDoor.doorCenter.y);
}

int isInTheDoor(t_dot2d currentPos, t_xdr_door theDoor)
{
  return (currentPos.x>=theDoor.doorCenter.x && currentPos.x<=(theDoor.doorCenter.x+theDoor.doorWidth) && currentPos.y>=theDoor.doorCenter.y && currentPos.y<=(theDoor.doorCenter.y+theDoor.doorHeight));
}
int min(int i, int j)
{
  if(i<j)
    return i;
  return j;
}

float distanceBetweenStartStop(t_xdr_door theDoor, t_dot2d PosFlag)
{
  return distance(PosFlag.x,PosFlag.y,theDoor.doorCenter.x,theDoor.doorCenter.y);
}

void order(int* tab)
{
  bool done=false;
  int i,temp;
  do
    {
      done=false;
      for(i=0;i<MAX_POP-1;i++)
	{
	  if(tab[i]>tab[i+1])
	    {
	      temp=tab[i];
	      tab[i]=tab[i+1];
	      tab[i+1]=temp;
	      done=true;
	    }
	}
    }while(done);
}

void getBests(t_person** tab, int n)
{
  int marks[MAX_POP],i;
  for(i=0;i<MAX_POP;i++)
    {
      marks[i]=tab[i]->mark;
    }
  order(marks);
  for(i=MAX_POP-1;i>MAX_POP-(n+1);i--)
    printf("%d : %d\n",i,marks[i]);
}

int getWorst(t_person** tab)
{
  int marks[MAX_POP],i;
  for(i=0;i<MAX_POP;i++)
    {
      marks[i]=tab[i]->mark;
    }
  order(marks);
  return marks[0];
}

void calculAllMarks(t_person** pers, t_xdr_obstacle* tabObs, t_xdr_door theDoor, t_dot2d flag, int size)
{
  int i;
  for(i=0;i<MAX_POP;i++)
    if(pers[i]->mark==-1)
      calculMark(pers[i],tabObs,theDoor,flag,size);
}

void mutate(t_person* pers)
{
  int percent, amount,i,pos,new;
  percent=_MAX_MUTATION_PERCENT*_MAX_PATH_SIZE/100;
  amount=rand()%percent;
  for(i=0;i<amount;i++)
    {
      pos=rand()%_MAX_PATH_SIZE;
      new=rand()%9;
      pers->path[pos]=new;
    }
}


/* LA touch de Coni */

void			swapVillageAddr(t_person** village, int pos1, int pos2)
{
  t_person		*temp;

  temp = village[pos1];
  village[pos1] = village[pos2];
  village[pos2] = temp;
};
  

void			giveMeTheBests(t_person** village
				       ,int currentPos)
{
  int			i;
  int			localMax;
  int			localMaxPos;

  if(currentPos == MAX_POP)
    {
      return;
    }
  else
    {
      localMaxPos = currentPos;
      localMax = village[currentPos]->mark;
      
      for (i=currentPos; i<MAX_POP; i++)
  	{
	  if(village[i]->mark > localMax )
	    {
	      localMax = village[i]->mark;
	      localMaxPos = i;
	    }
  	}

      swapVillageAddr(village, currentPos, localMaxPos);      

      giveMeTheBests(village, currentPos+1);
    }
};
  
