#ifndef _PERSON_H_
#define _PERSON_H_

#include "infoGame.h"
#include <time.h>
#define _MAX_PATH_SIZE 3000
//#define _DISTANCE_ 16
#define _STEP 5
#define _PERCENT_ALLOWED 80
#define _MAX_MARK 100
#define _MAX_MUTATION_PERCENT 4
#define _PERCENT_OF_NOMUTATION	90

enum e_direction { Left, Right, Up, Down, UpLeft, DownLeft, UpRight, DownRight };
enum crossOv {LeftSide,RightSide};
//typedef enum e_direction direction;
#define direction int


typedef struct s_person {
  int current;
  int mark;
  direction *path;
} t_person;

	void calculMark(t_person* pers, t_xdr_obstacle* tabObs, t_xdr_door theDoor, t_dot2d flag, int);	
	int* crossOver(t_person* Daddy, t_person* Mummy);

	
	bool Conflict(t_dot2d currentPos, t_xdr_obstacle* tabObs, int);
	float distanceLeft(t_dot2d currentPos, t_xdr_door theDoor);
	bool isInTheDoor(t_dot2d currentPos, t_xdr_door theDoor);
	int min(int i, int j);
	float distanceBetweenStartStop(t_xdr_door,t_dot2d);
	void order(int*);
	void getBests(t_person**,int);
	int getWorst(t_person**);
	void calculAllMarks(t_person** pers, t_xdr_obstacle* tabObs, t_xdr_door theDoor, t_dot2d flag, int);
	void mutate(t_person*);
#endif
