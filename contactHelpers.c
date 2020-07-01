#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// This source file needs to "know about" the SYSTEM string library functions.
// HINT: The library name is string.h.
//       #include the string.h header file on the next line:
#include <string.h>


// ----------------------------------------------------------
// Include your contactHelpers header file on the next line:
#include "contactHelpers.h"



// ----------------------------------------------------------
// define MAXCONTACTS for sizing contacts array (5):
#define MAXCONTACTS 5


//------------------------------------------------------
// Function Definitions
//------------------------------------------------------

// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        function definitions below...            |
// +-------------------------------------------------+

// clearKeyboard:
void clearKeyboard(void)
{
	while (getchar() != '\n'); // empty execution code block on purpose
}

// pause:
void pause(void)
{
	printf("(Press Enter to Continue)\n");
	clearKeyboard();
}

// getInt:
int getInt(void)
{
	char NL = 'x';
	int value = -1;

	do
	{
		scanf("%d%c", &value, &NL);

		if (NL != '\n') {
			clearKeyboard();
			printf("*** INVALID INTEGER *** <Please enter an integer>: ");
		}
	} while (NL != '\n');

	return value;
}


// getIntInRange:
int getIntInRange(int a, int b)
{
	int intValue;
	int flag = 0;
	
	while (flag == 0)
	{
		intValue = getInt();
		if (intValue >= a && intValue <= b)
			flag = 1;
		else
		{
			printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", a, b);
		}
	}
	return intValue;
}

// yes:
int yes(void)
{
	char NL = 'x';
	char input = '\0';
	int value;

	while (NL != '\n')
	{
		scanf("%c%c", &input, &NL);
		if (NL == '\n')
		{
			if (input == 'Y' || input == 'y')
				value = 1;
			else if (input == 'N' || input == 'n')
				value = 0;
			else
			{
				clearKeyboard();
				printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
			}
		}
		else
		{
			clearKeyboard();
			printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
		}
	}
	return value;
}

// menu:
int menu(void)
{
	int option;
	
	printf("Contact Management System\n"
		"-------------------------\n"
		"1. Display contacts\n"
		"2. Add a contact\n"
		"3. Update a contact\n"
		"4. Delete a contact\n"
		"5. Search contacts by cell phone number\n"
		"6. Sort contacts by cell phone number\n"
		"0. Exit\n\n"
		"Select an option:> ");

	option = getIntInRange(0, 6);
	printf("\n");
	return option;
}

// ContactManagerSystem:
void ContactManagerSystem(void)
{
	int option;
	int flag = 0;
	
	//creating the starting struct
	struct Contact contact[MAXCONTACTS] = 
	{ { { "Rick",{ '\0' }, "Grimes" },
		{ 11, "Trailer Park", 0, "A7A 2J2", "King City" },
		{ "4161112222", "4162223333", "4163334444" }
		},
			{
			{ "Maggie", "R.", "Greene" },
			{ 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
			{ "9051112222", "9052223333", "9053334444" }
			},
				{
				{ "Morgan", "A.", "Jones" },
				{ 77, "Cottage Lane", 0, "C7C 9Q9", "Peterborough" },
				{ "7051112222", "7052223333", "7053334444" }
				},
					{
					{ "Sasha",{ '\0' }, "Williams" },
					{ 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
					{ "9052223333", "9052223333", "9054445555" }
					}
	};

	//selecting options
	while (flag == 0)
	{
		option = menu();
		while (option != 0)
		{
			switch (option)
			{
			case 1:
				displayContacts(contact, MAXCONTACTS);
				pause();
				break;

			case 2:
				addContact(contact, MAXCONTACTS);
				pause();
				break;

			case 3:
				updateContact(contact, MAXCONTACTS);
				pause();
				break;

			case 4:
				deleteContact(contact, MAXCONTACTS);
				pause();
				break;

			case 5:
				searchContacts(contact, MAXCONTACTS);
				pause();
				break;

			case 6:
				sortContacts(contact, MAXCONTACTS);
				pause();
				break;

			default:
				break;
			}
			option = menu();
		}
		
		//exiting
		printf("Exit the program? (Y)es/(N)o: ");
		
		if (yes() == 1)
			flag = 1;
		printf("\n");
	}
	printf("Contact Management System: terminated\n");
}

// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        empty function definitions below...      |
// +-------------------------------------------------+

// Generic function to get a ten-digit phone number (ensures 10 chars entered)
void getTenDigitPhone(char telNum[])
{
	int needInput = 1;

	while (needInput == 1)
	{
		scanf("%10s", telNum);
		clearKeyboard();

		// (String Length Function: validate entry of 10 characters)
		if (strlen(telNum) == 10)
			needInput = 0;
		else
			printf("Enter a 10-digit phone number: ");
	}
}

// findContactIndex:
int findContactIndex(const struct Contact contacts[], int length, const char cellNumber[])
{
	int i, index = -1;

	for (i = 0; i < length && index == -1; i++)
	{
		if (!strcmp(cellNumber, contacts[i].numbers.cell))
			index = i;
	}
	return index;
}


void displayContactHeader(void)
{
	printf("+-----------------------------------------------------------------------------+\n");
	printf("|                              Contacts Listing                               |\n");
	printf("+-----------------------------------------------------------------------------+\n");
}


// displayContactFooter:
void displayContactFooter(int i)
{
	printf("+-----------------------------------------------------------------------------+\n");
	printf("Total contacts: %d\n\n", i);
}


// displayContact:
void displayContact(const struct Contact * info)
{
	//displaying name
	if (strlen(info->name.middleInitial) != 0)
	{
		printf(" %s %s %s\n", info->name.firstName, info->name.middleInitial, info->name.lastName);
	}
	else
		printf(" %s %s\n", info->name.firstName, info->name.lastName);

	//displaying contact number
	printf("    C: %-10s   H: %-10s   B: %-10s\n", info->numbers.cell, info->numbers.home, info->numbers.business);

	//displaying contact address
	printf("       %d %s, ", info->address.streetNumber, info->address.street);
	if (info->address.apartmentNumber > 0)
	{
		printf("Apt# %d, ", info->address.apartmentNumber);
	}
	printf("%s, %s\n", info->address.city, info->address.postalCode);
}
// displayContacts:
void displayContacts(const struct Contact display[], int length)
{
	int i, counter = 0;
	
	//displaying header
	displayContactHeader();
	
	//displaying info
	for (i = 0; i < length; i++)
	{
		if (*display[i].numbers.cell > 0)
		{
			displayContact(&display[i]);
			counter++;
		}
	}

	//displaying footer
	displayContactFooter(counter);
}

// searchContacts:
void searchContacts(const struct Contact search[], int length) 
{
	
	char cellNumber[11];
	int index;

	//finding the cell entered index
	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(cellNumber);
	index = findContactIndex(search, length, cellNumber);
	printf("\n");
	
	//displaying info for that cell number
	if (index != -1)
		displayContact(&search[index]);
	else
		printf("*** Contact NOT FOUND ***");
	printf("\n");
}


// addContact:
void addContact(struct Contact add[], int length)
{
	int i, index = -1;

	//checking array index
	for (i = 0; i < length && index == -1; i++)
	{
		if (strlen(add[i].numbers.cell) == 0)
			index = i;
	}
	
	//storing new contact if space is avalible
	if (index != -1)
	{
		getContact(&add[index]);
		printf("--- New contact added! ---\n");
	}
	else
		printf("*** ERROR: The contact list is full! ***\n");
}


// updateContact:
void updateContact(struct Contact update[], int length) {
	int index, check;
	char cellNumber[11];
	
	//finding cell number entered index
	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(cellNumber);
	index = findContactIndex(update, length, cellNumber);

	//promting and updating the correct index for the cell number entered
	if (index == -1)
		printf("*** Contact NOT FOUND ***\n");
	else
	{
		printf("\nContact found:\n");
		displayContact(&update[index]);
		
		printf("\nDo you want to update the name? (y or n): ");
		check = yes();
		if (check == 1)
		{
			getName(&update[index].name);
		}

		clearKeyboard();
		printf("Do you want to update the address? (y or n): ");
		check = yes();
		if (check == 1) {
			getAddress(&update[index].address);
		}
		
		clearKeyboard();
		printf("Do you want to update the numbers? (y or n): ");
		check = yes();
		if (check == 1) {
			getNumbers(&update[index].numbers);
		}
		printf("--- Contact Updated! ---\n");
	}
}


// deleteContact:
void deleteContact(struct Contact delete[], int length) {
	int index;
	char cellNumber[11];
	
	//finding cell number entered index
	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(cellNumber);
	index = findContactIndex(delete, length, cellNumber);
	
	//deleting contact if found after a secondary confirmation
	if (index == -1)
		printf("*** Contact NOT FOUND ***\n");
	else
	{
		printf("\nContact found:\n");
		displayContact(&delete[index]);
		printf("\nCONFIRM: Delete this contact? (y or n): ");
		if (yes() == 1)
		{
			*delete[index].numbers.cell = '\0';
			printf("--- Contact deleted! ---\n");
		}
	}
}


// sortContacts:
void sortContacts(struct Contact sort[], int length) {
	
	int flag = 0;
	int i, counter;
	
	//temp struc to hold the temp data
	struct Contact temporary;
	
	//comparing the cell strings and sorting them according to that
	while (flag == 0)
	{
		counter = 0;
		for (i = 0; i < length - 1; i++)
		{
			if (strcmp(sort[i].numbers.cell, sort[i + 1].numbers.cell) > 0)
			{
				temporary = sort[i];
				sort[i] = sort[i + 1];
				sort[i + 1] = temporary;
				counter++;
			}
		}
		if (counter == 0)
			flag = 1;
	}
	printf("--- Contacts sorted! ---\n");
}