#include "task4_menu.hpp"
#include <iostream>
#include <limits>
#include "task4.hpp"

using namespace std;
using namespace task4_module;

namespace task4_menu
{
    void printMenu()
    {
        cout << "\n========== ITEM SEARCH AND MANAGEMENT MODULE ==========\n";
        cout << "1. Add Item\n";
        cout << "2. Search Item\n";
        cout << "3. Update Item Name by ID\n";
        cout << "4. Update Item Name by Name\n";
        cout << "5. Update Item Position by ID\n";
        cout << "6. Update Item Position by Name\n";
        cout << "7. Delete Item by ID\n";
        cout << "8. Delete Item by Name\n";
        cout << "9. Display Sorted by ID\n";
        cout << "10. Display Sorted by Name\n";
        cout << "0. Exit\n";
        cout << "========================================================\n";
    }

    int getInteger(string msg)
    {
        int number;
        cout << msg;
        while (!(cin >> number))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!\n";
            cout << msg;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return number;
    }

    int showMainMenu()
    {
        ItemBST bst;
        int choice;

        do
        {
            printMenu();
            choice = getInteger("Select Option: ");

            if (choice == 1)
            {
                int id, x, y;
                string name;

                id = getInteger("Enter ID: ");

                cout << "Enter Name: ";
                getline(cin, name);

                x = getInteger("Enter X: ");

                y = getInteger("Enter Y: ");

                if (bst.insertItem(id, name, x, y))
                    cout << "Item added successfully.\n";
                else
                    cout << "Failed to add item.\n";
            }

            else if (choice == 2)
            {
                int type;
                type = getInteger("Search by (1=ID, 2=Name): ");

                if (type == 1)
                {
                    int id;
                    id = getInteger("Enter ID: ");

                    Item* item = bst.searchByID(id);
                    if (item)
                        cout << "Found:\nID = " << item->id << "\nName = " << item->name << "\nLocation = (" << item->x << "," << item->y << ")\n";
                    else
                        cout << "Item not found.\n";
                }
                else
                {
                    string name;
                    cout << "Enter Name: ";
                    getline(cin, name);

                    Item* item = bst.searchByName(name);
                    if (item)
                        cout << "Found:\nID = " << item->id << "\nName = " << item->name << "\nLocation = (" << item->x << "," << item->y << ")\n";
                    else
                        cout << "Item not found.\n";
                }
            }

            else if (choice == 3)
            {
                int id;
                string newName;

                id = getInteger("Enter ID: ");

                cout << "Enter new Name: ";
                getline(cin, newName);

                if (bst.updateItemNameByID(id, newName))
                    cout << "Updated successfully.\n";
                else
                    cout << "Update failed.\n";
            }

            else if (choice == 4)
            {
                string name, newName;

                cout << "Enter old Name: ";
                getline(cin, name);
            

                cout << "Enter new Name: ";
                getline(cin, newName);
    

                if (bst.updateItemNameByName(name, newName))
                    cout << "Updated successfully.\n";
                else
                    cout << "Update failed.\n";
            }

            else if (choice == 5)
            {
                int id, x, y;

                id = getInteger("Enter ID: ");

                x = getInteger("Enter X: ");

                y = getInteger("Enter Y: ");

                if (bst.updateItemByID(id, x, y))
                    cout << "Updated successfully.\n";
                else
                    cout << "Update failed.\n";
            }

            else if (choice == 6)
            {
                string name;
                int x, y;

                cout << "Enter Name: ";
                getline(cin, name);

                x = getInteger("Enter X: ");

                y = getInteger("Enter Y: ");

                if (bst.updateItemByName(name, x, y))
                    cout << "Updated successfully.\n";
                else
                    cout << "Update failed.\n";
            }

            else if (choice == 7)
            {
                int id;
                id = getInteger("Enter ID to delete: ");

                if (bst.removeItemByID(id))
                    cout << "Deleted successfully.\n";
                else
                    cout << "Delete failed.\n";
            }

            else if (choice == 8)
            {
                string name;

                cout << "Enter Name to delete: ";
                getline(cin, name);

                if (bst.removeItemByName(name))
                    cout << "Deleted successfully.\n";
                else
                    cout << "Delete failed.\n";
            }

            else if (choice == 9)
            {
                bst.displaySortedByID();
            }

            else if (choice == 10)
            {
                bst.displaySortedByName();
            }

            if (choice != 0 && choice != 2 && choice != 9 && choice != 10)
            {
                bst.updateFile();
            }

        } while (choice != 0);

        cout << "Exiting menu...\n";
        return 0;
    }
}