#ifndef TASK1_ORDER_HPP
#define TASK1_ORDER_HPP

#include <string>

// Order Data Structure
struct Order {
    std::string orderID;    
    std::string itemID;
    std::string itemName;
    int targetX;      
    int targetY;  
};

// Queue Node
struct QueueNode {
    Order data;
    QueueNode* next;
};

// Order Queue Class (Task 1)
class OrderQueue {
private:
    QueueNode* front;
    QueueNode* rear;
    int orderCounter; 

public:
    OrderQueue();
    ~OrderQueue();

    bool isEmpty();
    void enqueue(Order newOrder);
    bool getFrontOrder(Order &frontOrder);
    void dequeue();
    void dequeueSilent();
    void displayQueue();
};

#endif