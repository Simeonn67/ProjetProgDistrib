#ifndef _PERSON_H_
#define _PERSON_H_

#include "infoGame.h"
#include <time.h>
#define _MAX_PATH_SIZE 3000
//#define _DISTANCE_ 16
#define _STEP 5
#define _PERCENT_ALLOWED 80
#define _MAX_MARK 100

enum direction { Left, Right, Up, Down, UpLeft, DownLeft, UpRight, DownRight };
enum crossOv {LeftSide,RightSide};
#define true 1
#define false 0
#define direction int

typedef struct s_person {
	int current;
	int mark;
	direction path[_MAX_PATH_SIZE];
} t_person;

    /*Person();
	Person(Person Daddy, Person Mummy, Door theDoor, t_dot2d);
	~Person();*/
	void calculMark(t_person* pers, t_obstacle *tabObs[_MAX_OBSTACLE], t_door theDoor, t_dot2d flag);	
	direction* crossOver(t_person Daddy, t_person Mummy, t_door theDoor, t_dot2d flag);

	
	int Conflict(t_dot2d currentPos, t_obstacle* tabObs[_MAX_OBSTACLE]);
	float distanceLeft(t_dot2d currentPos, t_door theDoor);
	int isInTheDoor(t_dot2d currentPos, t_door theDoor);
	int min(int i, int j);
	float distanceBetweenStartStop(t_door,t_dot2d);

#endif
