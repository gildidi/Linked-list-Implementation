#include "Trivadog.h"

// Name: Almog Afuta
// Id:319114245
// Name: Gil Didi
// Id:318353422
int checkIfHostelExists(Trivadog* td, const Hostel* ht);
/*******************************************************************************
Name:AddHostel
Inputs:td(Trivadog*),ht(const Hostel*)
Outputs:Trivadog*
Description: Add hostel to Trivadog
********************************************************************************/
Trivadog* AddHostel(Trivadog* td, const Hostel* ht)
{
	//if the Trivadog* NULL, create a new Trivadog
	//if Rrivadog exist,check if hostel is in the list
	//if hostel exists , nothing to be done
	//if not, add new hostel
	if (td == NULL)
	{
		Trivadog* destination = (Trivadog*)malloc(sizeof(Trivadog));//memory allocation

		if (destination == NULL)
		{
			return NULL;
		}
		destination->hostels = (Hostel**)malloc(sizeof(Hostel*));//memory allocation
		if (destination->hostels == NULL)
		{
			FreeTrivadog(destination);
			return NULL;
		}
		destination->hostels[0] = DuplicateHostel(ht);//duplicate hostel
		if (destination->hostels[0] == NULL)
		{
			FreeTrivadog(destination);
			return NULL;
		}
		destination->num_of_hostels = 1;//now have a 1 hostel
		return destination;
	}

	//now td is not NULL
	int check = checkIfHostelExists(td, ht);
	if (check == -1)//hostel not in the list
	{
		Hostel** temp = (Hostel**)malloc(sizeof(Hostel*) * (td->num_of_hostels + 1));//memory allocation and add a new place
		if (temp == NULL)
		{
			FreeTrivadog(td);
			return NULL;
		}
		td->hostels = temp;
		td->hostels[td->num_of_hostels] = DuplicateHostel(ht);
		td->num_of_hostels++;//update the num of hostels
		return td;
	}
	else
	{
		return td;
	}
}
/***************************************************************************
Name:checkIfHostelExist
Inputs: td(Trivadog*), ht(const Hostel*)
Outputs: int
Description: The function return the index of the hostel if found, -1 otherwise
****************************************************************************/
int checkIfHostelExists(Trivadog* td, const Hostel* ht)
{
	int i;
	for (i = 0; i < td->num_of_hostels; i++)
	{
		if (strcmp(td->hostels[i]->hostel_name, ht->hostel_name) == 0)//success!
		{
			return i;
		}
	}
	return -1;//if no success we have failed!
}
/********************************************************************
Name:printTrivado
Inputs: td(Trivadog*)
Outputs: -
Description: Print everything for debugg
*********************************************************************/
void printTrivadog(Trivadog* tr)//print function for debugg
{
	if (tr == NULL)
	{
		printf("why we printing nulls?\n");
		return;
	}
	int i;
	printf("This Trivadog print:\nnumber of hostels:%d\n", tr->num_of_hostels);
	for (i = 0; i < tr->num_of_hostels; i++)
	{
		printf("the adress of the hostel is: %p\n", &tr->hostels);
		printHostel(tr->hostels[i]);
	}
}
/********************************************************************
Name:FreeTrivadog
Inputs: td(Trivadog*)
Outputs: -
Description:Free Trivadog
*********************************************************************/
void FreeTrivadog(Trivadog* td)
{
	int i;
	for (i = 0; i < td->num_of_hostels; i++)
	{
		FreeHostel(td->hostels[i]);//free all the Trivadog
	}
	if (td->num_of_hostels > 0) {
		free(td->hostels);
	}
	free(td);
}
/********************************************************************
Name:SortByName
Inputs: td(Trivadog*)
Outputs: -
Description:Sort by alpabat the name - bubble sort
*********************************************************************/
void		SortByName(Trivadog* td)
{
	int i, j;
	if (td == NULL)
	{
		return;
	}
	if (td->num_of_hostels == 0 || td->num_of_hostels == 1) // Basis
	{
		return;
	}

	for (i = 0; i < td->num_of_hostels - 1; i++)
	{
		for (j = 0; j < td->num_of_hostels - 1; j++)
		{
			int check = strcmp(td->hostels[j]->hostel_name, td->hostels[j + 1]->hostel_name);
			if (check > 0)//left>right
			{//swap
				Hostel* tmp = DuplicateHostel(td->hostels[j]);
				FreeHostel(td->hostels[j]);
				td->hostels[j] = DuplicateHostel(td->hostels[j + 1]);
				FreeHostel(td->hostels[j + 1]);
				td->hostels[j + 1] = DuplicateHostel(tmp);
				FreeHostel(tmp);
			}
		}
	}
}
/********************************************************************
Name:SortByRate
Inputs: td(Trivadog*)
Outputs: -

Description:Sort by alpabat the rate - bubble sort
*********************************************************************/
void		SortByRate(Trivadog* td)
{
	int i, j;
	if (td == NULL)
	{
		return;
	}
	if (td->num_of_hostels == 0 || td->num_of_hostels == 1) // Basis
	{
		return;
	}
	for (i = 0; i < td->num_of_hostels - 1; i++)
	{
		for (j = 0; j < td->num_of_hostels - 1; j++)
		{
			if ((td->hostels[j]->rate) < (td->hostels[j + 1]->rate))//left<right
			{//swap
				Hostel* tmp = DuplicateHostel(td->hostels[j]);
				FreeHostel(td->hostels[j]);
				td->hostels[j] = DuplicateHostel(td->hostels[j + 1]);
				FreeHostel(td->hostels[j + 1]);
				td->hostels[j + 1] = DuplicateHostel(tmp);
				FreeHostel(tmp);
			}
		}
	}
}
/********************************************************************
Name:GetTotalAvailableRoo
Inputs: td(Trivadog*), type(const char*)
Outputs: int
Description: Counts all available rooms of this type
*********************************************************************/
int GetTotalAvailableRooms(Trivadog* td, const char* type)
{
	if (td == NULL)//if inputs is NULL return 0
	{
		return 0;
	}
	int counter = 0;
	int i;
	for (i = 0; i < td->num_of_hostels; i++)
	{
		counter += GetAvailableRooms(td->hostels[i], type);//loop that counter the available rooms in hostel
	}
	return counter;
}
/********************************************************************
Name:GetTotalAvailableRoomsInArr
Inputs: td(Trivadog*), arr_type(char**), size(int)
Outputs: int*
Description: Function that count the available rooms
*********************************************************************/
int* GetTotalAvailableRoomsInArr(Trivadog* td, char** arr_type, int size)
{
	if (td == NULL)
	{
		return NULL;
	}
	int* arr = (int*)malloc(sizeof(int) * size);//memory allocation
	if (arr == NULL)
	{
		return NULL;
	}
	int i;
	for (i = 0; i < size; i++)
	{
		(arr[i]) = GetTotalAvailableRooms(td, arr_type[i]);//for each type in arr_type we run a check and get result
	}
	return arr;//return answer array
}

