#ifndef CONTACTS_H_
#define CONTACTS_H_

// Structure type Name declaration
struct Name {
	char firstName[31];
	char middleInitial[7];
	char lastName[36];
};

// Structure type Address declaration
struct Address {
	unsigned int streetNumber;
	char street[41];
	unsigned int apartmentNumber;
	char postalCode[8];
	char city[41];
};

// Structure type Numbers declaration
struct Numbers {
	char cell[11];
	char home[11];
	char business[11];
};

// Structure type Contact declaration
struct Contact {
	struct Name name;
	struct Address address;
	struct Numbers numbers;
};

// getName:
void getName(struct Name *);

// getAddress:
void getAddress(struct Address *);

// getNumbers:
void getNumbers(struct Numbers *);

// getContact:
void getContact(struct Contact *);

#endif 
