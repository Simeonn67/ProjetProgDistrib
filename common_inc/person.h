#ifndef _PERSON_H_
#define _PERSON_H_

#include "infoGame.h"
#include <time.h>
#define _MAX_PATH_SIZE 3000
//#define _DISTANCE_ 16
#define _STEP 5
#define _PERCENT_ALLOWED 80
#define _MAX_MARK 100

enum e_direction { Left, Right, Up, Down, UpLeft, DownLeft, UpRight, DownRight };
enum crossOv {LeftSide,RightSide};
//typedef enum e_direction direction;
#define direction int


typedef struct s_person {
  int current;
  int mark;
  direction path[_MAX_PATH_SIZE];
} t_person;

    /*Person();
	Person(Person Daddy, Person Mummy, Door theDoor, t_dot2d);
	~Person();*/
	void calculMark(t_person* pers, t_xdr_obstacle *tabObs[_MAX_OBSTACLE], t_xdr_door theDoor, t_dot2d flag);	
	direction* crossOver(t_person Daddy, t_person Mummy, t_xdr_door theDoor, t_dot2d flag);

	
	bool Conflict(t_dot2d currentPos, t_xdr_obstacle* tabObs[_MAX_OBSTACLE]);
	float distanceLeft(t_dot2d currentPos, t_xdr_door theDoor);
	bool isInTheDoor(t_dot2d currentPos, t_xdr_door theDoor);
	int min(int i, int j);
	float distanceBetweenStartStop(t_xdr_door,t_dot2d);

#endif
