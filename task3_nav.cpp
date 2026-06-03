#include "task3_nav.hpp"
#include <iostream>

using namespace std;

NavigationStack::NavigationStack() { topNode = NULL; }
NavigationStack::~NavigationStack() { clear(); }

bool NavigationStack::isEmpty() { return topNode == NULL; }

void NavigationStack::push(Move step) {
    StackNode* newNode = new StackNode();
    newNode->moveData = step;
    newNode->next = topNode;
    topNode = newNode;
}

Move NavigationStack::pop() {
    if (isEmpty()) return { -1, -1, "Empty" };
    StackNode* temp = topNode;
    Move data = temp->moveData;
    topNode = topNode->next;
    delete temp;
    return data;
}

void NavigationStack::clear() {
    while (!isEmpty()) pop();
}

bool RobotNavigator::isObstacle(int x, int y) {
    // You can adjust these based on your grid-DSTR.xlsx map layout
    if (x == 5 && y == 5) return true;
    if (x == 10 && y == 12) return true;
    return false;
}

string RobotNavigator::getOppositeDirection(string dir) {
    if (dir == "Forward/North") return "Backward/South";
    if (dir == "Backward/South") return "Forward/North";
    if (dir == "Right/East") return "Left/West";
    if (dir == "Left/West") return "Right/East";
    return "Stay";
}

void RobotNavigator::navigateToItem(int startX, int startY, int targetX, int targetY) {
    forwardPath.clear();
    reversePath.clear();

    int currentX = startX;
    int currentY = startY;

    forwardPath.push({currentX, currentY, "Initial Base Hub"});
    cout << "\n>>> STARTING NAVIGATION PATH LOG TO POSITION (" << targetX << ", " << targetY << ") <<<\n";

    while (currentX != targetX || currentY != targetY) {
        int nextX = currentX;
        int nextY = currentY;
        string moveDir = "";

        if (currentX < targetX) { nextX++; moveDir = "Right/East"; }
        else if (currentX > targetX) { nextX--; moveDir = "Left/West"; }
        else if (currentY < targetY) { nextY++; moveDir = "Forward/North"; }
        else if (currentY > targetY) { nextY--; moveDir = "Backward/South"; }

        if (isObstacle(nextX, nextY)) {
            cout << "[ALERT] Obstacle block identified at (" << nextX << ", " << nextY << ")! Adjusting trajectory...\n";
            if (moveDir == "Right/East" || moveDir == "Left/West") {
                if (currentY <= targetY) { nextY++; moveDir = "Forward/North"; nextX = currentX; }
                else { nextY--; moveDir = "Backward/South"; nextX = currentX; }
            } else {
                if (currentX <= targetX) { nextX++; moveDir = "Right/East"; nextY = currentY; }
                else { nextX--; moveDir = "Left/West"; nextY = currentY; }
            }
            cout << "  [DETOUR] Rerouted step direction: " << moveDir << " -> (" << nextX << ", " << nextY << ")\n";
        }

        currentX = nextX;
        currentY = nextY;
        forwardPath.push({currentX, currentY, moveDir});
        cout << "  Robot Step: " << moveDir << " -> Reached Coordinates: (" << currentX << ", " << currentY << ")\n";
    }
    cout << "[SUCCESS] Arrived at shelf. Item extracted.\n";
}

void RobotNavigator::returnToPackingStation() {
    if (forwardPath.isEmpty()) return;

    cout << "\n=======================================================\n";
    cout << "EXECUTE REVERSE RETURN JOURNEY PATH LOG\n";
    cout << "=======================================================\n";

    while (!forwardPath.isEmpty()) {
        Move step = forwardPath.pop();
        if (step.direction == "Initial Base Hub") continue;

        Move returnMove;
        returnMove.x = step.x; 
        returnMove.y = step.y;
        returnMove.direction = getOppositeDirection(step.direction);
        reversePath.push(returnMove);
    }

    while (!reversePath.isEmpty()) {
        Move returnStep = reversePath.pop();
        cout << "  Counter-Step: " << returnStep.direction << " -> Safe Zone: (" << returnStep.x << ", " << returnStep.y << ")\n";
    }
    cout << "[HOME BASE] Robot returned safely back to dispatch station node.\n";
}