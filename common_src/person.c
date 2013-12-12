#include "person.h"
#include "data.h"


/*t_dot2dPerson()
{
  direction randomDirection;
  int randomInteger;

  current = 0;
  mark = -1;

//  srand (time(NULL));

  for(int i=0;i<_MAX_PATH_SIZE;i++)
    {
      randomInteger = rand() % 8 + 1;
      randomDirection = static_cast<direction>(randomInteger);
      path[i] = randomDirection;
    }

};

Person(Person Daddy, Person Mummy,Door theDoor, t_dot2d theFlag)
{
  direction* crossOverResult;
  current = 0;
  mark = -1;
  
  crossOverResult = crossOver(Daddy,Mummy,theDoor, theFlag);
  for(int i=0;i<_MAX_PATH_SIZE;i++)
	path[i] = crossOverResult[i];
};
*/

void calculMark(t_person pers, t_obstacle* tabObs[_MAX_OBSTACLE], t_door theDoor, t_dot2d theFlag)
{
 	int MaxMark=_MAX_MARK;
	t_dot2d currentPos;
	currentPos.x=theFlag.x;
	currentPos.y=theFlag.y;
	bool contact=false;
	int i=0;
	for(i=0;i<_MAX_PATH_SIZE && !contact;i++)
	{
		if(isInTheDoor(currentPos,theDoor))
		{
			printf("END!");
			current=i;
			contact=true;
		}
		if(Conflict(currentPos,tabObs))
		{
			MaxMark=_MAX_MARK/2;
			printf("CONTACT!");
			contact=true;
		}
		switch(path[i])
		{
			case DownRight:
			currentPos.x=currentPos.x+_STEP;
			currentPos.y=currentPos.y+_STEP;
			break;
			case Right:
			currentPos.x=currentPos.x+_STEP;
			break;
			case UpRight:
			currentPos.x=currentPos.x+_STEP;
			currentPos.y=currentPos.y-_STEP;
			break;
			case Down:
			currentPos.y=currentPos.y+_STEP;
			break;
			case UpLeft:
			currentPos.x=currentPos.x-_STEP;
			currentPos.y=currentPos.y-_STEP;
			break;
			case Left:
			currentPos.x=currentPos.x-_STEP;
			break;
			case DownLeft:
			currentPos.x=currentPos.x-_STEP;
			currentPos.y=currentPos.y+_STEP;
			break;
			case Up:
			currentPos.y=currentPos.y-_STEP;
			break;
		}
	}
	if(distanceLeft(currentPos, theDoor)>distanceBetweenStartStop(theDoor,theFlag))
	{
		//printf("%f/%f",distanceLeft(currentPos, theDoor),distanceBetweenStartStop(theDoor,theFlag));
		mark=0;
	}
	else
	{
		//printf("%f/%f",(distanceLeft(currentPos, theDoor)*_MAX_MARK/2),(distanceBetweenStartStop(theDoor, theFlag)));
		//printf("$$ %d $$ ",MaxMark);
		mark=MaxMark-(distanceLeft(currentPos, theDoor)*_MAX_MARK/2)/(distanceBetweenStartStop(theDoor, theFlag));
	}
};

direction* crossOver(Person Daddy, Person Mummy, Door theDoor, t_dot2d theFlag)
{
	int randomForSide, randomForSize;
	static direction son[_MAX_PATH_SIZE];
	srand(time(NULL));
	randomForSide=rand() % 2+1;
	randomForSize=rand() % _MAX_PATH_SIZE;
	while((_PERCENT_ALLOWED*min(Mummy.current,Daddy.current))/100>=randomForSize || randomForSize*_STEP<distanceBetweenStartStop(theDoor,theFlag))
		randomForSize=rand()%_MAX_PATH_SIZE;
	switch(randomForSide)
	{
		case LeftSide:
		for(int i=0;i<randomForSize;i++)
			son[i]=Mummy.path[i];
		for(int i=randomForSize;i<_MAX_PATH_SIZE;i++)
			son[i]=Daddy.path[i];
		break;

		case RightSide:
		for(int i=0;i<randomForSize;i++)
			son[i]=Daddy.path[i];
		for(int i=randomForSize;i<_MAX_PATH_SIZE;i++)
			son[i]=Mummy.path[i];
		break;
	}
	for(int i=0;i<_MAX_PATH_SIZE;i++)
	{
		printf("%d",Daddy.path[i]);
	}
	printf("\n\n");
	
	for(int i=0;i<_MAX_PATH_SIZE;i++)
	{
		printf("%d",Mummy.path[i]);
	}
	printf("\n\n");
	

	for(int i=0;i<_MAX_PATH_SIZE;i++)
		printf("%d",son[i]);
  return son;
};

bool Conflict(t_dot2d currentPos, t_obstacle* tabObs[_MAX_OBSTACLE])
{
	for(int i=0;i<_MAX_OBSTACLE;i++)
	{
		if(distance(currentPos.x,currentPos.y,tabObs[i].obsCenter.x,tabObs[i].obsCenter.y)<=tabObs[i].obsRadius)
			return true;
	}
	return false;
}

float distanceLeft(t_dot2d currentPos, t_dot2d theDoor)
{
	return distance(currentPos.x,currentPos.y,theDoor.doorCenter.x,theDoor.doorCenter.y);
}

bool t_dot2disInTheDoor(t_dot2d currentPos, t_dot2d theDoor)
{
	return (currentPos.x>=theDoor.doorCenter.x && currentPos.x<=(theDoor.doorCenter.x+theDoor.doorWidth) && currentPos.y>=theDoor.doorCenter.y && currentPos.y<=(theDoor.doorCenter.y+theDoor.doorHeight));
}
int t_dot2dmin(int i, int j)
{
	if(i<j)
		return i;
	return j;
}

float distanceBetweenStartStop(t_dot2d theDoor, t_dot2d PosFlag)
{
	return distance(PosFlag.x,PosFlag.y,theDoor.doorCenter.x,theDoor.doorCenter.y);
}
