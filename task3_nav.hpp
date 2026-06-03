#ifndef TASK3_NAV_HPP
#define TASK3_NAV_HPP

#include <string>

// Coordinate step
struct Move {
    int x;
    int y;
    std::string direction; 
};

// Stack Node
struct StackNode {
    Move moveData;
    StackNode* next;
};

// LIFO Stack Class
class NavigationStack {
private:
    StackNode* topNode;

public:
    NavigationStack();
    ~NavigationStack();
    bool isEmpty();
    void push(Move step);
    Move pop();
    void clear();
};

// Navigation Engine
class RobotNavigator {
private:
    NavigationStack forwardPath;
    NavigationStack reversePath;

    bool isObstacle(int x, int y);
    std::string getOppositeDirection(std::string dir);

public:
    void navigateToItem(int startX, int startY, int targetX, int targetY);
    void returnToPackingStation();
};

#endif