#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

int Length_of_card(int y)
{
	int count = 0;
	while (y)
	{
		count++;
		y /= 10;

	}
	return count;
}


bool Payment(int x)
{
	pakage**h = get_pakage();
	int price,id,card,i=0,cvc, Expire_dade;
	string fullname;
	while (h[i])
	{
		if (h[i].Serial == x) 
		{
			price = h[i].price;
			cout << "The price to pay is:" << price << endl;
			cout << "Please enter your full name" << endl;
			cin >> fullname;
			cout << "Please enter your ID" << endl;
			cin >> id;
			cout << "Please enter the debit card number" << endl;
			cin >> card;
			cout << "Enter the expiration date of a card enter- 4 number 2 for month then 2 for year" << endl;
			cin >> Expire_dade;
			cout << "Insert the last 3 digits on the back of the card" << endl;
			cin >> cvc;
			if (Length_of_card(card) == 9) {
				cout << "The card is charged" << endl;
				return true;

			}

			else {
				cout << "Invalid card" << endl;
				return false;
			}

		}

		i++;
	}
}
