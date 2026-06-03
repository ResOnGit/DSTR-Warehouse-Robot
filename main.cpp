#include <iostream>
#include <limits>
#include <string>

// Include your modular team files
#include "task1_order.hpp"
#include "task2_079957.hpp"
#include "task3_nav.hpp"
#include "task4.hpp"

using namespace std;
using namespace task4_module;

void showMainMenu() {
    cout << "\n========== INTEGRATED WAREHOUSE MANAGEMENT SYSTEM ==========\n";
    cout << "1. Add New Order (Task 1 Queue + Task 4 BST Database Search)\n";
    cout << "2. Process Next Order & Dispatch Robot (Task 1 Dequeue + Task 3 Stack Nav)\n";
    cout << "3. Display All Pending Orders\n";
    cout << "4. Open Inventory Master Control (Task 4 BST)\n";
    cout << "5. Open Robot Assignment Control (Task 2 Circular Queue)\n";
    cout << "0. Exit System\n";
    cout << "============================================================\n";
}

int getInteger(string msg) {
    int number;
    cout << msg;
    while (!(cin >> number)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid format! Try again.\n";
        cout << msg;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return number;
}

int main() {
    ItemBST bst; 
    OrderQueue orderQueue;
    RobotNavigator dispatchUnit;

    int packingStationX = 0, packingStationY = 0; 
    int choice;

    do {
        showMainMenu();
        choice = getInteger("Select Option: ");

        if (choice == 1) { 
            int searchType = getInteger("Lookup via: (1 = Item ID Number, 2 = Exact Name Value): ");
            Item* targetRecord = nullptr;

            if (searchType == 1) {
                int id = getInteger("Enter Item ID (1-680): ");
                targetRecord = bst.searchByID(id);
            } else {
                string name;
                cout << "Enter Item Name String: ";
                getline(cin, name);
                targetRecord = bst.searchByName(name);
            }

            if (targetRecord != nullptr) {
                Order newOrder;
                newOrder.itemID = to_string(targetRecord->id);
                newOrder.itemName = targetRecord->name;
                newOrder.targetX = targetRecord->x;
                newOrder.targetY = targetRecord->y;
                orderQueue.enqueue(newOrder);
            } else {
                cout << "\n[ERROR] Record could not be localized within BST database shelves!\n";
            }
        }
        else if (choice == 2) { 
            Order activeJob;
            if (orderQueue.getFrontOrder(activeJob)) {
                cout << "\n-------------------------------------------------------";
                cout << "\nDISPATCHING ROBOT FOR ORDER: " << activeJob.orderID << "\n";
                cout << "Item Objective: " << activeJob.itemName << "\n";
                cout << "-------------------------------------------------------";
                
                dispatchUnit.navigateToItem(packingStationX, packingStationY, activeJob.targetX, activeJob.targetY);
                dispatchUnit.returnToPackingStation();
                orderQueue.dequeue();
                
                cout << "\n[JOB COMPLETE] Queue updated successfully.\n";
            } else {
                cout << "\n[WARNING] Dispatch canceled: No pending customer requests in the queue.\n";
            }
        }
        else if (choice == 3) {
            orderQueue.displayQueue();
        }
        else if (choice == 4) {
            // Keep your task4 menu logic here or separate it out as needed!
            cout << "Inventory Management is active.\n";
            bst.displaySortedByID(); // Example quick-display
        }
        else if (choice == 5) {
            runRobotAssignmentMenu();
        }
    } while (choice != 0);

    return 0;
}
