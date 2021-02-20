
#include "Room.h"

// Name: Almog Afuta
// Id:319114245
// Name: Gil Didi
// Id:318353422

/*******************************************************************************
Name: CreateNewRoom
Inputs: number(int) ,_cost(float),_available(int),_type(const char*)
Output: pointer of struct Room
Description: Creates new instance of struct object Room and returns it by reference
Name of Writer:
Date:
*********************************************************************************/
Room* CreateNewRoom(int _number,//number of room
	float _cost,//cost of room
	int _available,//is room available
	const char* _type)//type of room, deluxe or simple
{
	//create pointer of type Room so we can return it
	//initialize pointer with malloc
	//set values inside struct with values provided
	//done, return pointer
	Room* newRoom = (Room*)malloc(sizeof(Room));
	if (newRoom != NULL) //check if memory allocation has failed
	{
		newRoom->number = _number;
		newRoom->cost_for_night = _cost;
		newRoom->available = _available;
		newRoom->type = (char*)(malloc((strlen(_type) + 1) * sizeof(char)));
		if (newRoom->type != NULL)
		{
			strcpy(newRoom->type, _type);
			return newRoom;// Room is ready, done
		}
		else//if malloc of type failed
		{
			free(newRoom);//if malloc failed room is unuseable
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}
/*
Name:PrintRoom
Description: printer function for self testing is always usefull
*/
void printRoom(Room* room)
{
	if (room == NULL)
	{
		printf("why are you printing a null?\n");
		return;
	}
	printf("Room Values:\nnumber=%d\ncost=%f\navailable=%d\ntype=%s\n", room->number, room->cost_for_night, room->available, room->type);
}
/*****************************************************************
Name: DuplicateRoom
Inputs: source(const Room*)
Output: Room*
Description: create's duplicate of given room
******************************************************************/
Room* DuplicateRoom(const Room* source)
{
	return CreateNewRoom(source->number, source->cost_for_night, source->available, source->type);
}
/******************************************************************
Name: FreeRoom
Inputs: rm(Room*)
Output: -
Description: Free's all memory
******************************************************************/
void FreeRoom(Room* rm)
{
	free(rm->type);
	free(rm);
}

