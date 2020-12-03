// Harel_travels.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <Package_purchase_process>


int main()
{
    int choise, Serial_number;
    char* user;
    cout << "enter Agent or Client" << endl;
    cin >> user;

    Log_in();
    //קריאה לפונקציית התחברות ואם הפרטים נכונים התכנית ממשיכה

    if (strcmp(user , Agent)
    {
        cout << "Please select an option:" << endl;
        cout << "for packeges management choose - 1" << endl;
        cout << "for order management choose - 2" << endl;
        cout << "for masseges choose - 3" << endl;
        cout << "for back - 4" << endl;
        cin >> choise;
        while (choise > 4 || choise < 1)
        {
            cout << "Wrong choice Please try again" << endl;
                cin >> choise;
        }
        switch (choise)
        {
        case 1:
        {

        }
        case2:
        {

        }
        case 3:
        {

        }
        case 4:
        {

        }
        default:

            break;
        
        }
    }
    if (strcmp(user, Client)
    {
        cout << "Please select an option:" << endl;
        cout << "for find vacation choose - 1" << endl;
        cout << "for order status choose - 2" << endl;
        cout << "for wish list choose - 3" << endl;
        cout << "for masseges - 4" << endl;
        cout << "for back - 5" << endl;
        cin >> choise;
        while (choise > 5 || choise < 1)
        {
            cout << "Wrong choice Please try again" << endl;
                cin >> choise;
        }
        switch (choise)
        {
        case 1://לא להתעסק עם זה בבקשה
        {
            Find_vacation(); 
        }
    case2://לא להתעסק עם זה בבקשה
        {
            cout << "Enter a serial number of the package" << endl;
            cin >> Serial_number;
            Order_status(Serial_number);
        }
        case 3:
        {

        }
        case 4:
        {

        }
        default:

            break;

        }
    }

















/*  char* location;
    std::cout << "press location\n";
    std::cin >> location;
    int size = Get_size_vacations_by_location(location);
    Vacation** vacations =  Get_vacations_by_location( location);
    fot(int i = 0; i < size; i++)
    {
        cout << vacations[i] << endl;
    }

}/*

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
