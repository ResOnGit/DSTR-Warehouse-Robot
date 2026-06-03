#include "task2_079957.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

const char* RobotAssignmentModule::statusText(RobotStatus status) {
    if (status == AVAILABLE) return "Available";
    if (status == BUSY) return "Busy";
    return "Maintenance";
}

int RobotAssignmentModule::findRobotIndexById(int robotId) {
    for (int i = 0; i < robotCount; i++) {
        if (robots[i].id == robotId) {
            return i;
        }
    }
    return -1;
}

RobotAssignmentModule::RobotAssignmentModule() {
    robotCount = 0;
    assignmentCount = 0;
    nextRobotIndex = 0;
}

bool RobotAssignmentModule::addRobot(int id, const char name[]) {
    if (robotCount >= MAX_ROBOTS || findRobotIndexById(id) != -1) {
        return false;
    }

    robots[robotCount].id = id;
    strncpy(robots[robotCount].name, name, MAX_TEXT - 1);
    robots[robotCount].name[MAX_TEXT - 1] = '\0';
    robots[robotCount].status = AVAILABLE;
    robots[robotCount].taskCount = 0;
    robotCount++;
    return true;
}

bool RobotAssignmentModule::updateStatus(int robotId, RobotStatus status) {
    int index = findRobotIndexById(robotId);
    if (index == -1) {
        return false;
    }

    robots[index].status = status;
    return true;
}

bool RobotAssignmentModule::loadRobotsFromFile(const char fileName[]) {
    ifstream input(fileName);
    if (!input) {
        return false;
    }

    int loadedCount = 0;
    int id;
    int statusNumber;
    char name[MAX_TEXT];

    while (input >> id >> name >> statusNumber) {
        if (robotCount >= MAX_ROBOTS) {
            cout << "Robot storage is full. Extra records were ignored.\n";
            break;
        }

        if (statusNumber < AVAILABLE || statusNumber > MAINTENANCE) {
            cout << "Invalid status for robot " << id << ". Record skipped.\n";
            continue;
        }

        if (addRobot(id, name)) {
            updateStatus(id, static_cast<RobotStatus>(statusNumber));
            loadedCount++;
        } else {
            cout << "Duplicate robot ID " << id << " was skipped.\n";
        }
    }

    input.close();
    return loadedCount > 0;
}

bool RobotAssignmentModule::assignTask(const char taskName[]) {
    if (robotCount == 0 || assignmentCount >= MAX_ASSIGNMENTS) {
        return false;
    }

    int checked = 0;
    while (checked < robotCount) {
        int index = (nextRobotIndex + checked) % robotCount;

        if (robots[index].status == AVAILABLE) {
            assignments[assignmentCount].assignmentId = assignmentCount + 1;
            assignments[assignmentCount].robotId = robots[index].id;
            strncpy(assignments[assignmentCount].taskName, taskName, MAX_TEXT - 1);
            assignments[assignmentCount].taskName[MAX_TEXT - 1] = '\0';

            robots[index].status = BUSY;
            robots[index].taskCount++;
            assignmentCount++;

            nextRobotIndex = (index + 1) % robotCount;
            cout << "Task assigned to " << robots[index].name
                 << " (Robot " << robots[index].id << ").\n";
            return true;
        }

        checked++;
    }

    return false;
}

void RobotAssignmentModule::completeTask(int robotId) {
    int index = findRobotIndexById(robotId);
    if (index == -1) {
        cout << "Robot not found.\n";
        return;
    }

    if (robots[index].status == BUSY) {
        robots[index].status = AVAILABLE;
        cout << "Robot " << robotId << " is now available.\n";
    } else {
        cout << "Robot " << robotId << " is not currently busy.\n";
    }
}

void RobotAssignmentModule::displayRobotStatus() {
    cout << "\nRobot Status Overview\n";
    cout << "ID\tName\t\tStatus\t\tTasks\n";
    for (int i = 0; i < robotCount; i++) {
        cout << robots[i].id << "\t" << robots[i].name << "\t\t"
             << statusText(robots[i].status) << "\t\t"
             << robots[i].taskCount << "\n";
    }
}

void RobotAssignmentModule::displayAssignments() {
    cout << "\nRobot Assignment List\n";
    if (assignmentCount == 0) {
        cout << "No assignments yet.\n";
        return;
    }

    cout << "No.\tRobot ID\tTask\n";
    for (int i = 0; i < assignmentCount; i++) {
        cout << assignments[i].assignmentId << "\t"
             << assignments[i].robotId << "\t\t"
             << assignments[i].taskName << "\n";
    }
}

void runRobotAssignmentMenu() {
    RobotAssignmentModule module;

    if (module.loadRobotsFromFile("task2_robots.txt")) {
        cout << "Robots loaded from task2_robots.txt.\n";
    } else {
        cout << "task2_robots.txt not found or invalid. Loading sample robots.\n";
        module.addRobot(101, "Alpha");
        module.addRobot(102, "Bravo");
        module.addRobot(103, "Charlie");
        module.addRobot(104, "Delta");
    }

    int choice;
    do {
        cout << "\n=== Task 2: Robot Assignment Module ===\n";
        cout << "1. Assign new task\n";
        cout << "2. Complete robot task\n";
        cout << "3. Set robot under maintenance\n";
        cout << "4. Set robot available\n";
        cout << "5. Display robot status overview\n";
        cout << "6. Display assignment list\n";
        cout << "0. Return to main menu\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            char taskName[MAX_TEXT];
            cout << "Enter task name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.getline(taskName, MAX_TEXT);

            if (!module.assignTask(taskName)) {
                cout << "No available robot or assignment storage is full.\n";
            }
        } else if (choice == 2) {
            int robotId;
            cout << "Enter robot ID: ";
            cin >> robotId;
            module.completeTask(robotId);
        } else if (choice == 3) {
            int robotId;
            cout << "Enter robot ID: ";
            cin >> robotId;
            if (!module.updateStatus(robotId, MAINTENANCE)) {
                cout << "Robot not found.\n";
            }
        } else if (choice == 4) {
            int robotId;
            cout << "Enter robot ID: ";
            cin >> robotId;
            if (!module.updateStatus(robotId, AVAILABLE)) {
                cout << "Robot not found.\n";
            }
        } else if (choice == 5) {
            module.displayRobotStatus();
        } else if (choice == 6) {
            module.displayAssignments();
        }
    } while (choice != 0);
}
