#include "Hostel.h"
int checkIfRoomExists(Hostel* ht, int roomNumber);

// Name: Almog Afuta
// Id:319114245
// Name: Gil Didi
// Id:318353422


/******************************************************************************
Name: Hostle AddRoom
Inputs: ht(HOstle*), room(Room*)
Output: Hostle*

Description: Add a new room to an existing Hostel

********************************************************************************/
Hostel* AddRoom(Hostel* ht, const  Room* room)
{
	//check of pointer ht exists, if no create "unknown hostel"
		//if exists check if room number exists, if exists update values and done
		//if room does not exist, create new room, add it to room* array, number of rooms++.

		//in order to add new room to list of rooms
		//I create new rooms ** which has size+1
		//copy relevant rooms into new array
		//add new room into new aray
		//delete old pointer array
		//move new pointer into field rooms

		//I need to check if room exists inside the hostel
		//I need to write a function that does it!

	if (ht == NULL) // if the hostel is NULL, create a new
	{
		ht = (Hostel*)malloc(sizeof(Hostel));//memory allocation
		if (ht == NULL)//memory allocation failed
		{
			return NULL;
		}
		ht->hostel_name = "Unknown Hostel";//set the values
		ht->rate = 0;
		ht->num_of_rooms = 1;
		ht->rooms = (Room**)malloc(sizeof(Room*));//memory allocation 
		if (ht->rooms == NULL)
		{
			free(ht);
			return NULL;
		}
		ht->rooms[0] = DuplicateRoom(room);// add's room to hostel
		return ht;
	}

	//now ht not NULL
	int check = checkIfRoomExists(ht, room->number);//-1 if room not in list, returns index otherwise
	if (check == -1)//fail to find, now I need to Add new room to rooms
	{
		Room** temp = (Room**)malloc(sizeof(Room*) * (ht->num_of_rooms + 1));//creates new space for extra room

		if (temp == NULL)
		{
			free(ht);
			return NULL;
		}
		for (int j = 0; j < ht->num_of_rooms; j++)
		{
			temp[j] = DuplicateRoom(ht->rooms[j]);
			FreeRoom(ht->rooms[j]);

		}

		ht->rooms = temp;
		ht->rooms[ht->num_of_rooms] = DuplicateRoom(room);
		ht->num_of_rooms++;//update num of rooms
		return ht;

	}
	else//manage to find,check holds index of room inside rooms
		//now I need to update values
	{
		FreeRoom(ht->rooms[check]);
		ht->rooms[check] = DuplicateRoom(room);//result is the same as directly updating values
	}
	return ht;
}

/******************************************************************************
Name: checkIfRoomExists
Inputs: ht(HOstle*), roomNumber(int)
Output: int

Description: checks if room exists inside hostel, if exists return index inside rooms if not returns -1
This is a local function only, should not be used outside of Hostel.c scope
********************************************************************************/
int checkIfRoomExists(Hostel* ht, int roomNumber)
{
	if (ht == NULL)
	{
		return -1;//no hostel no room
	}
	int count = ht->num_of_rooms;//number of rooms for for loop
	int i;
	for (i = 0; i < count; i++)
	{
		if (roomNumber == ht->rooms[i]->number)//if number is the same, done
		{
			return i;
		}
	}
	return -1;//if not room number matches, we return value for failure
}



/**********************************************************************
Name: printHostel
Inputs: ht(Holstel*)
Output: -

Description: prints the values of all fields of the hostel, primarily used for debugging the  code

***********************************************************************/
void printHostel(Hostel* ht)
{
	printf("Name of Hostel:%s\n", ht->hostel_name);
	printf("Rate:%f\n", ht->rate);
	printf("Number of rooms:%d\n", ht->num_of_rooms);
	int i;
	for (i = 0; i < ht->num_of_rooms; i++)
	{
		printRoom(ht->rooms[i]);
	}
}

/*********************************************************************************
Name: Hostel DuplicateHostel
Inputs: source(const Hostel*)
Outputs: Hostel*

Description: Duplicate Hostel, duplicates all the fields of the struct

**********************************************************************************/
Hostel* DuplicateHostel(const Hostel* source)
{
	if (source == NULL)//nothing to copy
	{
		return NULL;
	}
	Hostel* copy = (Hostel*)malloc(sizeof(Hostel));// memory allocation for new hostel
	if (copy == NULL)
	{
		return NULL;
	}
	copy->rooms = (Room**)malloc(sizeof(Room*) * (source->num_of_rooms));// memory allocation for rooms
	if (copy->rooms == NULL)
	{
		free(copy);
		return NULL;
	}
	copy->rate = source->rate;
	copy->num_of_rooms = 0;

	copy->hostel_name = (char*)(malloc((strlen(source->hostel_name) + 1) * sizeof(char)));//memory allocation for hostel name
	if (copy->hostel_name == NULL)
	{
		FreeHostel(copy);
		return NULL;
	}
	strcpy(copy->hostel_name, source->hostel_name);//copy of string

	int i;
	for (i = 0; i < source->num_of_rooms; i++)//duplicate room in loop
	{
		copy->rooms[i] = DuplicateRoom(source->rooms[i]);
		if (copy->rooms[i] == NULL)//if fail, trouble
		{
			FreeHostel(copy);
			return NULL;
		}
		copy->num_of_rooms++;// update the num of rooms
	}
	return copy;
}
/*********************************************************************************
Name: FreeHostel
Inputs: ht(const Hostel*)
Outputs: -
Description:Frees all relevant memory
**********************************************************************************/
void	FreeHostel(Hostel* ht)
{
	if (ht == NULL)
	{
		return;
	}
	int i;
	for (i = 0; i < ht->num_of_rooms; i++)// free all the rooms in loop
	{
		FreeRoom(ht->rooms[i]);
	}
	free(ht->rooms);
	if (strcmp(ht->hostel_name, "Unknown Hostel") != 0) {
		free(ht->hostel_name);
	}
	free(ht);
}
/*********************************************************************************
Name: GetAvailableRooms
Inputs: ht(const Hostel*), type( const char*)
Outputs: int
Description:Cheak if the room is available
**********************************************************************************/
int		GetAvailableRooms(const Hostel* ht, const char* type)
{
	if (ht == NULL)
	{
		return 0;//if no hostel there are no rooms
	}
	int counter = 0;
	int i;
	for (i = 0; i < ht->num_of_rooms; i++)
	{
		if (strcmp(ht->rooms[i]->type, type) == 0 && ((ht->rooms[i]->available) == 1))//compration between 2 types
		{
			counter++;//update
		}
	}
	return counter;
}
