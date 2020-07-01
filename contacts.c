#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "contacts.h"
#include "contactHelpers.h"

// getName:
void getName(struct Name *name)
{
	int check = -1;

	//First Name
	printf("Please enter the contact's first name: ");
	scanf("%[^\n]s", name->firstName);
	clearKeyboard();
	//Middle Initial
	printf("Do you want to enter a middle initial(s)? (y or n): ");
	check = yes();
	if (check == 1) {
		printf("Please enter the contact's middle initial(s): ");
		scanf("%[^\n]s", name->middleInitial);
	}
	//Last Name
	clearKeyboard();
	printf("Please enter the contact's last name: ");
	scanf("%[^\n]s", name->lastName);
}

// getAddress:
void getAddress(struct Address *address)
{
	int check = -1;

	//Street number
	printf("Please enter the contact's street number: ");
	address->streetNumber = getInt();
	//street Name
	printf("Please enter the contact's street name: ");
	scanf("%[^\n]s", address->street);
	//Apartment Number
	printf("Do you want to enter an apartment number? (y or n): ");
	clearKeyboard();
	check = yes();
	if (check == 1) {
		printf("Please enter the contact's apartment number: ");
		address->apartmentNumber = getInt();
	}
	else
	{
		address->apartmentNumber = '\0';
	}
	//Postal Code
	printf("Please enter the contact's postal code: ");
	scanf("%[^\n]s", address->postalCode);
	//City
	printf("Please enter the contact's city: ");
	clearKeyboard();
	scanf("%[^\n]s", address->city);
}

// getNumbers:
void getNumbers(struct Numbers *numbers)
{
	int check = -1;
	//cell number
	printf("Please enter the contact's cell phone number: ");
	getTenDigitPhone(numbers->cell);
	
	//home number
	printf("Do you want to enter a home phone number? (y or n): ");
	check = yes();
	if (check == 1)
	{
		printf("Please enter the contact's home phone number: ");
		getTenDigitPhone(numbers->home);
	}
	else
	{
		numbers->home[0] = '\0';
	}

	//business number
	printf("Do you want to enter a business phone number? (y or n): ");
	check = yes();
	if (check == 1) 
	{
		printf("Please enter the contact's business phone number: ");
		getTenDigitPhone(numbers->business);
	}
	else
	{
		numbers->business[0] = '\0';
	}
}

// getContact
void getContact(struct Contact *contact)
{
	getName(&(contact->name));
	getAddress(&(contact->address));
	getNumbers(&(contact->numbers));
}
