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
	pakage** h = get_pakage();
	int price, id, card, i = 0, cvc, Expire_date;
	string full_name;
	bool choise = true;
	while (h[i])
	{
		if (h[i].Serial == x)
		{
			price = h[i].price;
			cout << "The price to pay is:" << price << endl;
			cout << "Please enter your full name" << endl;
			cin >> full_name;
			cout << "Please enter your ID" << endl;
			cin >> id;
			while (choise)
			{
				cout << "Please enter the debit card number" << endl;
				cin >> card;
				cout << "Enter the expiration date of a card enter- 4 number 2 for month then 2 for year" << endl;
				cin >> Expire_date;
				cout << "Insert the last 3 digits on the back of the card" << endl;
				cin >> cvc;
				if (Length_of_card(card) == 9) {
					cout << "The card is charged" << endl;
					return true;
				}
				else
				{
					cout << "Invalid card" << endl;
					cout << "if u want to try again Press 1-for yes or 0-for no:"
					cin >> choise;
				}
					if (choise == 0)
						return false;
			}
		}
		i++;
	}
}
