#define _CRT_SECURE_NO_WARNINGS

#include <string.h> 
#include<iostream> 
#include <time.h>
#include <stdlib.h>

using namespace std;



int SerialNumbercreator()
{
	srand(time(NULL));   // Initialization, should only be called once.
	int r =  rand(); // Returns a pseudo-random integer between 0 and RAND_MAX.

	return r; 
}

struct Date {

	int day;
	int month;
	int year;

};

struct Packege {

	int serial_number;
	char destination[100];
	char status[20];
	float price;
	Date start;
	Date end;
	int number_of_passengers;
	char user_name_of_buyer[100];// If the package is purchased, enter the buyer's username here

};

Date getNewDate(int day, int month, int year)
{
	Date new_date;
	new_date.day = day;
	new_date.month = month;
	new_date.year = year;
	return new_date;
}

Packege creatNewPackege(const char* destination, float price, Date start, Date end, int number_of_passengers)
{
	Packege new_packege;
	new_packege.serial_number = SerialNumbercreator();
	strcpy(new_packege.destination, destination);
	strcpy(new_packege.status, "None");// default status 
	new_packege.price = price;
	new_packege.start = start;
	new_packege.end = end;
	new_packege.number_of_passengers = number_of_passengers;
	strcpy(new_packege.user_name_of_buyer, "None"); // default 

	return new_packege;
}

// get packge (struct) and write it to the end of file
bool setPackegeToDB(Packege packege)
{
	FILE* outfile = fopen("Packeges.dat", "a");
	if (outfile == NULL)
	{
		return false;
	}

	// write struct to file 
	fwrite(&packege, sizeof(Packege), 1, outfile);

	if (fwrite == 0)
		return false;

	fclose(outfile);

	return true;

}



// searchPackegeBySerialNumber get serial_number and return the index in the file. 
//if the serial_number not exist return -1, if the opening faild return -2 
//***the indexs start from 1***
int searchPackegeBySerialNumber(int serial_number)
{
	FILE* infile = fopen("Packeges.dat", "r");
	if (infile == NULL)
		return -2;

	Packege input;
	int i = 0;

	while (fread(&input, sizeof(Packege), 1, infile))
	{
		i++;
		if (input.serial_number == serial_number)
			return i;
	}

	fclose(infile);
	return -1;

}

//return Packeges DB size if the opening failed return -1
int PackegesfileSize()
{
	FILE* infile;
	Packege input;

	// Open Packeges.dat for reading 
	infile = fopen("Packeges.dat", "r");
	if (infile == NULL)
		return -1;

	int count = 0;
	// read file contents till end of file 
	while (fread(&input, sizeof(Packege), 1, infile))
		count++;

	// close file 
	fclose(infile);

	return count;
}

//get packege ang print the destination
void printPackegeDestination(Packege packege)
{
	cout << packege.destination;
}

//get packege ang print the serial_number
void printPackegeSerialNumber(Packege packege)
{
	cout << packege.serial_number << endl;
}

//get Packege struct by index.if the opening file faild or the index is not exsit return empey packge (serial number = 0)
Packege getPackegeByIndex (int index)
{
	FILE* infile;
	Packege input;
	input.serial_number = 0;
	strcpy(input.destination, "None");
	strcpy(input.status, "None");// default status 
	input.price = 0;
	input.start = getNewDate(0, 0, 0);
	input.end = getNewDate(0, 0, 0);
	input.number_of_passengers = 0;
	strcpy(input.user_name_of_buyer, "None"); // default

	// Open Packeges.dat for reading 
	infile = fopen("Packeges.dat", "r+");
	if (infile == 0)
		return input;
	if (index >= PackegesfileSize ())
		return input;

	for (int i = 0; i <= index; i++)
		fread(&input, sizeof(Packege), 1, infile);

	fclose(infile);

	return input;
}

//return dynamic arr of all packeges
Packege* getAllPackeges()
{
	
	int size = PackegesfileSize();
	Packege* dynamic_arr_of_all_packeges = new Packege[size];
	int i = 0;

	Packege input; 
	

	for (int i = 0; i < size; i++)
	
	{
		input = getPackegeByIndex(i);
		dynamic_arr_of_all_packeges[i] = input;
	}

	return dynamic_arr_of_all_packeges;
}



//Update Packege Status by serial number and status: 0 = none, 1 = In procces, 2 = Paid up 3 = Canceled. 
//if the update success return true else return false
bool UpdatePackegeStatus(int status, int serial_number)
{
	int index = searchPackegeBySerialNumber(serial_number);

	if (index == -1)// the packege not exist; 
		return false;

	Packege update = getPackegeByIndex(index-1);// get the source packege

	switch (status)// Inserts the correct status according to the input
	{
	case 1:
		strcpy(update.status, "In procces");
		break;

	case 2:
		strcpy(update.status, "Paid up");
		break;

	case 3:
		strcpy(update.status, "Canceled");
		break;

	default:
		break;
	}


	FILE* outfile = fopen("Packeges.dat", "r+");

	if (outfile == NULL)
		return false;

	Packege input;

	for (int i = 0; i < index - 1; i++)// Move to the correct location in the file to write the updated package
		fread(&input, sizeof(Packege), 1, outfile);

	fseek(outfile, 0, SEEK_CUR);

	fwrite(&update, sizeof(Packege), 1, outfile);

	if (fwrite == 0)
		return false;


	fclose(outfile);

	return true;

}

void printDate(Date date)
{
	cout << date.day << "/" << date.month << "/" << date.year << endl;
}

//Print packege for the Client (dont print status & buyer name)
void printPackege(Packege packege)
{
	cout << "Serial number: " << packege.serial_number << endl;
	cout << "Destination: " << packege.destination << endl;
	cout << "Price: " << packege.price << "$" << endl;
	cout << "Arrival: "; printDate(packege.start);
	cout << "leaving: "; printDate(packege.end);
	cout << "Number of passengers: " << packege.number_of_passengers << endl;
}

//Update packege price by serial number and new price
//if the update success return true else return false
bool UpdatePackegePrice(float price, int serial_number)
{
	int index = searchPackegeBySerialNumber(serial_number);

	if (index == -1)// the packege not exist; 
		return false;

	Packege update = getPackegeByIndex(index-1);// get the source packege
	update.price = price;

	FILE* outfile = fopen("Packeges.dat", "r+");

	if (outfile == NULL)
		return false;

	Packege input;

	for (int i = 0; i < index - 1; i++)// Move to the correct location in the file to write the updated package
		fread(&input, sizeof(Packege), 1, outfile);

	fseek(outfile, 0, SEEK_CUR);
	
	fwrite(&update, sizeof(Packege), 1, outfile);

	if (fwrite == 0)
		return false;


	fclose(outfile);

	return true;

}

//Update packege arrival daet by serial number and new date
//if the update success return true else return false
bool UpdatePackegeArrivalDate(Date date, int serial_number)
{
	int index = searchPackegeBySerialNumber(serial_number);

	if (index == -1)// the packege not exist; 
		return false;

	Packege update = getPackegeByIndex(index-1);// get the source packege
	update.start = date;

	FILE* outfile = fopen("Packeges.dat", "r+");

	if (outfile == NULL)
		return false;

	Packege input;

	for (int i = 0; i < index - 1; i++)// Move to the correct location in the file to write the updated package
		fread(&input, sizeof(Packege), 1, outfile);

	fseek(outfile, 0, SEEK_CUR);

	fwrite(&update, sizeof(Packege), 1, outfile);

	if (fwrite == 0)
		return false;


	fclose(outfile);

	return true;

}

//Update packege leaving daet by serial number and new date
//if the update success return true else return false
bool UpdatePackegeLeavingDate(Date date, int serial_number)
{
	int index = searchPackegeBySerialNumber(serial_number);

	if (index == -1)// the packege not exist; 
		return false;

	Packege update = getPackegeByIndex(index-1);// get the source packege
	update.end = date;

	FILE* outfile = fopen("Packeges.dat", "r+");

	if (outfile == NULL)
		return false;

	Packege input;

	for (int i = 0; i < index - 1; i++)// Move to the correct location in the file to write the updated package
		fread(&input, sizeof(Packege), 1, outfile);

	fseek(outfile, 0, SEEK_CUR);

	fwrite(&update, sizeof(Packege), 1, outfile);

	if (fwrite == 0)
		return false;


	fclose(outfile);

	return true;

}

//Receives a package and creates a new package with its details.
//(Does not copy: status, serial number, and name of buyer - get a default value)
Packege DuplicatePackage(Packege source)
{
	Packege new_packege;
	new_packege.serial_number = SerialNumbercreator();
	strcpy(new_packege.destination, source.destination);
	strcpy(new_packege.status, "None");// default status 
	new_packege.price = source.price;
	new_packege.start = source.start;
	new_packege.end = source.end;
	new_packege.number_of_passengers = source.number_of_passengers;
	strcpy(new_packege.user_name_of_buyer, "None"); // default 

	return  new_packege;
}


// print all the Packeges that paid up and await approvell. 
//if the serial_number not exist return -1, if the opening faild return -2
int PrintAllPackagesAwaitingApproval()
{
	FILE* infile = fopen("Packeges.dat", "r");
	if (infile == NULL)
		return -2;

	Packege input;
	int i = 0;

	while (fread(&input, sizeof(Packege), 1, infile))
	{
		i++;
		if (strcmp(input.status, "Paid up") == 0)
		{
			printPackege(input);
			cout << "\n";
		}
	}

	fclose(infile);
	return -1;
}

// print all the Packeges that canceled by clients. 
//if the serial_number not exist return -1, if the opening faild return -2
int PrintAllPackagesCanceled()
{
	FILE* infile = fopen("Packeges.dat", "r");
	if (infile == NULL)
		return -2;

	Packege input;
	int i = 0;

	while (fread(&input, sizeof(Packege), 1, infile))
	{
		i++;
		if (strcmp(input.status, "Canceled") == 0)
		{
			printPackege(input);
			cout << "\n";
		}
	}

	fclose(infile);
	return -1;
}

//**********************************************
struct Message {

	char title[50];
	char content[300];
	char status[10] = "Unread";// or Answer
	Date sending_date;
	char response[300] = "0";
};

struct Client {

	char user_name[100];
	char password[8];
	char mail_adress[20];
	char name[20];
	char last_name[20];
	int phone;
	int id;
	int cerdit_card_number;
	Message message_list[10];
	int message_list_size;
	int wish_list[20];// serial_number of reserved package
	int wish_list_size;
	int vacations_list[20];// serial_number of vacations purchased by the user
	int vacations_list_size;
};

//creat new client (user name, password, mail_adress). use to creat new user at sing up
Client creatNewClient(const char* user_name, const char* password, const char* mail_adress)
{
	Client new_client;
	strcpy(new_client.user_name, user_name);
	strcpy(new_client.password, password);
	strcpy(new_client.mail_adress, mail_adress);
	strcpy(new_client.name, "None");
	strcpy(new_client.last_name, "None");
	new_client.phone = 0;
	new_client.id = 0;
	new_client.cerdit_card_number = 0;
	new_client.message_list_size = 0;
	new_client.vacations_list_size = 0;
	new_client.wish_list_size = 0;
	
	return new_client;
}

// get client (struct) and write it to the end of file
bool setClientToDB(Client client)
{
	FILE* outfile = fopen("Clients.dat", "a");
	if (outfile == NULL)
	{
		return false;
	}

	// write struct to file 
	fwrite(&client, sizeof(Client), 1, outfile);

	if (fwrite == 0)
		return false;

	fclose(outfile);

	return true;

}

// searchClientByUserName get user_name and return the index in the file. 
//if the user_name not exist return -1, if the opening faild return -2
//***return index from 1 and so on***
int searchClientByUserName(const char* user_name)
{
	FILE* infile = fopen("Clients.dat", "r");
	if (infile == NULL)
		return -2;

	Client input;
	int i = 0;

	while (fread(&input, sizeof(Client), 1, infile))
	{
		i++;
		if (strcmp(input.user_name, user_name) == 0)
			return i;
	}

	fclose(infile);
	return -1;

}

//return Clients DB size if the opening failed return -1
int ClientsfileSize()
{
	FILE* infile;
	Client input;

	// Open Packeges.dat for reading 
	infile = fopen("Clients.dat", "r");
	if (infile == NULL)
		return -1;

	int count = 0;
	// read file contents till end of file 
	while (fread(&input, sizeof(Client), 1, infile))
		count++;

	// close file 
	fclose(infile);

	return count;
}


//return dynamic arr of all clients
Client* getAllClients()
{
	FILE* infile;
	Client input;

	// Open Packeges.dat for reading 
	infile = fopen("Clients.dat", "r");
	if (infile == NULL)
		return NULL;

	Client* dynamic_arr_of_all_clients = new Client[ClientsfileSize()];
	int i = 0;
	// read file contents till end of file 
	while (fread(&input, sizeof(Client), 1, infile))
	{
		dynamic_arr_of_all_clients[i] = input;
		i++;
	}


	// close file 
	fclose(infile);

	return dynamic_arr_of_all_clients;
}

//get Client struct by index. the indexes start from 0. 
Client getClientByIndex(int index)
{
	FILE* infile;
	Client new_client;
	strcpy(new_client.user_name, "None");
	strcpy(new_client.password, "None");
	strcpy(new_client.mail_adress, "None");
	strcpy(new_client.name, "None");
	strcpy(new_client.last_name, "None");
	new_client.phone = 0;
	new_client.id = 0;
	new_client.cerdit_card_number = 0;
	new_client.message_list_size = 0;
	new_client.vacations_list_size = 0;
	new_client.wish_list_size = 0;

	// Open Packeges.dat for reading 
	infile = fopen("Clients.dat", "r+");
	if (infile == NULL)
		return new_client;
	if (index >= ClientsfileSize ())
		return new_client;

	for (int i = 0; i <= index; i++)
		fread(&new_client, sizeof(Client), 1, infile);

	fclose(infile);

	return new_client;
}


//get user name, full name (name, last name) and phone and update the details in this client
bool UpdateClientsOrderDetails(const char* user_name, const char* name, const char* last_name, int phone)
{
	int index = searchClientByUserName(user_name);

	if (index == -1)// the packege not exist; 
		return false;

	Client update = getClientByIndex(index-1);// get the source packege
	strcpy(update.name, name);
	strcpy(update.last_name, last_name);
	update.phone = phone;

	FILE* outfile = fopen("Clients.dat", "r+");

	if (outfile == NULL)
		return false;

	Client input;

	for (int i = 0; i < index - 1; i++)// Move to the correct location in the file to write the updated Client
		fread(&input, sizeof(Client), 1, outfile);

	fseek(outfile, 0, SEEK_CUR);


	fwrite(&update, sizeof(Client), 1, outfile);

	if (fwrite == 0)
		return false;


	fclose(outfile);

	return true;

}

//get user name, and cerdit card number and id update the details in this client
bool UpdateClientPaymentDetails(const char* user_name, int id, int cerdit_card_number, int serial_number)
{
	int index = searchClientByUserName(user_name);

	if (index == -1)// the packege not exist; 
		return false;

	Client update = getClientByIndex(index-1);// get the source packege
	update.id = id;
	update.cerdit_card_number = cerdit_card_number;

	if (update.vacations_list_size == 20)// the mail box is full
		update.vacations_list_size = 0; // deliet the oldest massage

	update.vacations_list[update.vacations_list_size] = serial_number;
	update.vacations_list_size++;

	FILE* outfile = fopen("Clients.dat", "r+");

	if (outfile == NULL)
		return false;

	Client input;

	for (int i = 0; i < index - 1; i++)// Move to the correct location in the file to write the updated Client
		fread(&input, sizeof(Client), 1, outfile);

	fseek(outfile, 0, SEEK_CUR);

	fwrite(&update, sizeof(Client), 1, outfile);

	if (fwrite == 0)
		return false;


	fclose(outfile);

	return true;

}

// creat new date struct by up to date date
Date creatTodayDate()
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	Date today = getNewDate(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
	return today;
}

//creat new massage from the client. get title and content.
//the default status is Unread. the default date is Today's date.
Message creatNewMessage(const char* title, const char* content)
{
	Message new_message;
	strcpy(new_message.title, title);
	strcpy(new_message.content, content);
	new_message.sending_date = creatTodayDate();

	return new_message;
}

//get user name, response and message index and update the response and the massege status to Answer
bool UpdateClientMessageResponse(const char* user_name, const char* response, int message_index)
{
	int index = searchClientByUserName(user_name);

	if (index == -1)// the packege not exist; 
		return false;

	Client update = getClientByIndex(index-1);// get the source packege

	strcpy(update.message_list[message_index].response, response);
	strcpy(update.message_list[message_index].status, "Answer");


	FILE* outfile = fopen("Clients.dat", "r+");

	if (outfile == NULL)
		return false;

	Client input;

	for (int i = 0; i < index - 1; i++)// Move to the correct location in the file to write the updated Client
		fread(&input, sizeof(Client), 1, outfile);

	fseek(outfile, 0, SEEK_CUR);

	fwrite(&update, sizeof(Client), 1, outfile);

	if (fwrite == 0)
		return false;


	fclose(outfile);

	return true;

}

//get user name, and message and add it to his list. it used to send message
bool UpdateClientMessage(const char* user_name, Message message)
{
	int index = searchClientByUserName(user_name);

	if (index == -1)// the packege not exist; 
		return false;

	Client update = getClientByIndex(index-1);// get the source packege

	if (update.message_list_size == 10)// the mail box is full
		update.message_list_size = 0; // deliet the oldest massage

	update.message_list[update.message_list_size] = message;
	update.message_list_size++;

	FILE* outfile = fopen("Clients.dat", "r+");

	if (outfile == NULL)
		return false;

	Client input;

	for (int i = 0; i < index - 1; i++)// Move to the correct location in the file to write the updated Client
		fread(&input, sizeof(Client), 1, outfile);

	fseek(outfile, 0, SEEK_CUR);

	fwrite(&update, sizeof(Client), 1, outfile);

	if (fwrite == 0)
		return false;


	fclose(outfile);

	return true;

}

//update wish list by serial_number of packege
bool UpdateClientWishlist(const char* user_name, int serial_number)
{
	int index = searchClientByUserName(user_name);

	if (index == -1)// the packege not exist; 
		return false;
	

	Client update = getClientByIndex(index-1);// get the source packege

	if (update.wish_list_size == 20)// the mail box is full
		update.wish_list_size = 0; // deliet the oldest massage
	
	 
	update.wish_list[update.wish_list_size] = serial_number;
	update.wish_list_size++;



	FILE* outfile = fopen("Clients.dat", "r+");

	if (outfile == NULL)
		return false;

	Client input;

	for (int i = 0; i < index - 1; i++)// Move to the correct location in the file to write the updated Client
		fread(&input, sizeof(Client), 1, outfile);

	fseek(outfile, 0, SEEK_CUR);

	fwrite(&update, sizeof(Client), 1, outfile);
	
	if (fwrite == 0)
		return false;


	fclose(outfile);

	return true;

}

// print massege (title, date, content) if it was answer it print the response
void printMassege(Message message)
{
	cout << "***" << message.title << "***" << endl;
	printDate(message.sending_date);
	cout << message.content << endl;

	if (strcmp(message.status, "Answer") == 0)
	{
		cout << "Answer:" << endl;
		cout << message.response << endl;
	}
}
// print all the unread massege of client by user name that. use to show agent all the massege he need to answer
//if the user_name not exist return -1, if the opening faild return -2
int PrintAllUnReadMasseges()
{
	FILE* infile = fopen("Clients.dat", "r");
	if (infile == NULL)
		return -2;

	Client input;
	int i = 0;

	while (fread(&input, sizeof(Client), 1, infile))
	{
		i++;
		for (int i = 0; i < input.message_list_size; i++)
			if (strcmp(input.message_list[i].status, "Unread") == 0)
			{
				cout << input.user_name;
				printMassege(input.message_list[i]);
			}
	}

	fclose(infile);
	return -1;
}



// Checking the validity of an agent's detaisl by user name and password
//if the user name dont exist return - 2
//If the username exists and the password is incorrect return -1
//If the username and password are correct return 0 
//If the file opening failed return -3
static int CheckingValidityAgentDetials(const char* name, const char* password)
{
    FILE* f = fopen("Agents.txt", "rt");
    if (f == NULL)
        return -3;

    char agent_name[100];
    char agent_password[100];
    char signed_char[100];

    char name_buffer[20];
    char password_buffer[20];
    while (fgets(agent_name, 99, f))
    {
        fgets(agent_password, 99, f);
        fgets(signed_char, 99, f);

        for (int i = 0; i < (strlen(agent_name)); i++)
        {
            name_buffer[i] = agent_name[i];
        }
        name_buffer[strlen(agent_name) - 1] = '\0';

        for (int i = 0; i < (strlen(agent_password)); i++)
        {
            password_buffer[i] = agent_password[i];
        }
        password_buffer[strlen(agent_password) - 1] = '\0';
        if (strcmp(name_buffer, name) == 0)
        {
            if (strcmp(password_buffer, password) == 0)
            {
                return 0;
            }
            else
                return-1;
        }
    }
    return -2;
}


int main()
{
	/*Date a;
	a = getNewDate(11, 11, 11);

	Packege p = creatNewPackege("omer", 104.5, a, a, 3);
	cout << "t" << endl;
	int y;
	cin >> y;
	Packege p1 = creatNewPackege("Tmer", 104.5, a, a, 3);
	cout << "t" << endl;
	cin >> y;
	Packege p2 = creatNewPackege("Smer", 104.5, a, a, 3);
	cout << "t" << endl;
	cin >> y;
	Packege p3 = creatNewPackege("Dmer", 104.5, a, a, 3);


	setPackegeToDB(p);
	setPackegeToDB(p1);
	setPackegeToDB(p2);
	setPackegeToDB(p3);*/

	
	
	UpdatePackegeLeavingDate(creatTodayDate(), 2231);
	UpdatePackegeLeavingDate(creatTodayDate(), 2247);

	Packege* ptr = getAllPackeges();

	for (int i = 0; i < PackegesfileSize(); i++)
	{
		printPackege(ptr[i]);
		cout << ptr[i].status<< "\n";
		cout << "\n";
	}

	
	
		
	


	return 0;
}





