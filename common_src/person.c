#include "person.h"

void calculMark(t_person* pers, t_xdr_obstacle *tabObs, t_xdr_door theDoor, t_dot2d theFlag, int size)
{
  int MaxMark=_MAX_MARK;
  t_dot2d currentPos;
  currentPos.x=theFlag.x;
  currentPos.y=theFlag.y;
  int contact=false;
  int i=0;
  //printf("%f\n",distanceLeft(currentPos, theDoor));
  for(i=0;i<_MAX_PATH_SIZE && !contact;i++)
<<<<<<< HEAD
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
      
=======
  {
		if(isInTheDoor(currentPos,theDoor))
		{
			  printf("END!");
			  pers->current=i;
			  contact=true;			//We exit the loop
		}
  	    if(Conflict(currentPos,tabObs, size))
		{
			  //MaxMark=_MAX_MARK/2;				/****************************
			  //printf("CONTACT!");					* FOR OLD STYLE COMPUTATION *
			  //contact=true;						****************************/
			  MaxMark-=_PENALITY;
		}
      //MaxXXi code compressor
>>>>>>> 22ee4b9ebcdd0dba3cd3d168cfe790e8ebdd73d1
      if(pers->path[i] == Left || pers->path[i] == UpLeft || pers->path[i] == DownLeft)
			currentPos.x=currentPos.x-_STEP;
      if(pers->path[i] == Right || pers->path[i] == UpRight || pers->path[i] == DownRight)
			currentPos.x=currentPos.x+_STEP;
	  if(pers->path[i] == Up || pers->path[i] == UpRight || pers->path[i] == UpLeft)
			currentPos.y=currentPos.y-_STEP;
      if(pers->path[i] == Down || pers->path[i] == DownLeft || pers->path[i] == DownRight)
<<<<<<< HEAD
	currentPos.y=currentPos.y+_STEP;

=======
			currentPos.y=currentPos.y+_STEP;
>>>>>>> 22ee4b9ebcdd0dba3cd3d168cfe790e8ebdd73d1
    }
	if(distanceLeft(currentPos, theDoor)>distanceBetweenStartStop(theDoor,theFlag))		//If we have been more on the left than on the right
    {
		pers->mark=0;
    }
	else
    {
		pers->mark=MaxMark-(distanceLeft(currentPos, theDoor)*_MAX_MARK/2)/(distanceBetweenStartStop(theDoor, theFlag));
    }
    if(pers->mark<=0)
		pers->mark=0;
    //if(distanceLeft(currentPos, theDoor)<200 || contact)
		//printf(" : %d---%f---\n",pers->mark,distanceLeft(currentPos, theDoor));
};

direction* crossOver(t_person* Daddy, t_person* Mummy)
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
		son[i]=Mummy->path[i];		//We take the left side of the mother
      for(i=randomForSize;i<_MAX_PATH_SIZE;i++)
		son[i]=Daddy->path[i];		//And the right side of the father
      break;

    case RightSide:					//And up side down if you really want.........
      for(i=0;i<randomForSize;i++)
	son[i]=Daddy->path[i];
      for(i=randomForSize;i<_MAX_PATH_SIZE;i++)
	son[i]=Mummy->path[i];
      break;
    }
  return son;
};

int Conflict(t_dot2d currentPos, t_xdr_obstacle *tabObs, int size)
{
  int i,j;
	
  for(i=0;i<size;i++)
    {
		
      if(distance(currentPos.x,currentPos.y,tabObs[i].obsCenter.x,tabObs[i].obsCenter.y)<=tabObs[i].obsRadius)		//If we hit an obstacle...
	return true;
    }
  return false;
}

float distanceLeft(t_dot2d currentPos, t_xdr_door theDoor)
{
  return distance(currentPos.x,currentPos.y,theDoor.doorCenter.x,theDoor.doorCenter.y);		//Distance left from the current position to the exit
}

int isInTheDoor(t_dot2d currentPos, t_xdr_door theDoor)
{
  return (currentPos.x>=theDoor.doorCenter.x && currentPos.x<=(theDoor.doorCenter.x+theDoor.doorWidth) && currentPos.y>=theDoor.doorCenter.y && currentPos.y<=(theDoor.doorCenter.y+theDoor.doorHeight));		//Are we hitting the door?
}

int min(int i, int j)			//Needed when we are crossing over
{
  if(i<j)
    return i;
  return j;
}

float distanceBetweenStartStop(t_xdr_door theDoor, t_dot2d PosFlag)			//The best distance (the less ;) )
{
  return distance(PosFlag.x,PosFlag.y,theDoor.doorCenter.x,theDoor.doorCenter.y);
}

void calculAllMarks(t_person** village, t_xdr_obstacle* tabObs, t_xdr_door theDoor, t_dot2d flag, int size)		//Let's calculate all people of the village
{
  int i;
  for(i=0;i<MAX_POP;i++)
    if(village[i]->mark==-1)		//If the mark haven't been compute
      calculMark(village[i],tabObs,theDoor,flag,size);
}

void mutate(t_person* pers)
{
  int percent, amount,i,pos,new;
  percent=_MAX_MUTATION_PERCENT*_MAX_PATH_SIZE/100;		//What amount of mutation can we do?
  amount=rand()%percent;
  for(i=0;i<amount;i++)
    {
      pos=rand()%_MAX_PATH_SIZE;		//Where to mutate?
      new=rand()%8;						//What's the new value?
      pers->path[pos]=new;
    }
    //printf("Mutate : %d\n",amount);
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
  
  
void reGen(t_person** village,t_xdr_obstacle* tabObs,t_xdr_door door,t_dot2d posFlag,int size, int howMuch)
{
	int j,momId,dadId,who2Mutate,oldMark,doWeMutate;
	for(j=0;j<howMuch;j++)
	{
		printf("Ignition...\n");
		momId=rand()%MAX_POP;		//Which mom?
		dadId=rand()%MAX_POP;		//Which dad?
		//printf("old : %d, old2 : %d\n",village[MAX_POP-1]->mark,village[who2Mutate]->mark);
		oldMark=village[MAX_POP-1]->mark;
		village[MAX_POP-1]->path=crossOver(village[momId],village[dadId]);		//Let's crossOver!
		calculAllMarks(village,tabObs,door,posFlag,size);		//We calculate again the whole village's marks
		if(village[MAX_POP-1]->mark<=oldMark)
		{
			printf("We need to try again\n");
			momId=rand()%MAX_POP;		//Which mom?
			dadId=rand()%MAX_POP;		//Which dad?		
			village[MAX_POP-1]->path=crossOver(village[momId],village[dadId]);		//Let's crossOver!
			calculAllMarks(village,tabObs,door,posFlag,size);		//We calculate again the whole village's marks
		}
		doWeMutate=rand()%100;
		if(doWeMutate>=_CHANCES_OF_MUTATION)
		{
			printf("This time, we mutate\n");
			who2Mutate=rand()%MAX_POP;	//Who do we mutate?
			mutate(village[who2Mutate]);	//We can mutate too...
			calculAllMarks(village,tabObs,door,posFlag,size);
		}
		
	//	printf("--- : %d, ---2 : %d\n\n\n",village[MAX_POP-1]->mark,village[who2Mutate]->mark);
		giveMeTheBests(village,0);		//We order the village
		if(j%1000==0)
		{		
			printf("%d--%d--%d\n",j,village[0]->mark,village[MAX_POP-1]->mark);		//We print. We can send the best from here
		}
	}
}
