#include "task1_order.hpp"
#include <iostream>
#include <sstream>

using namespace std;

OrderQueue::OrderQueue() {
    front = NULL;
    rear = NULL;
    orderCounter = 1;
}

OrderQueue::~OrderQueue() {
    while (!isEmpty()) {
        dequeueSilent();
    }
}

bool OrderQueue::isEmpty() {
    return (front == NULL);
}

void OrderQueue::enqueue(Order newOrder) {
    stringstream ss;
    ss << "ORD-" << (orderCounter < 10 ? "00" : (orderCounter < 100 ? "0" : "")) << orderCounter;
    newOrder.orderID = ss.str();
    orderCounter++;

    QueueNode* newNode = new QueueNode();
    newNode->data = newOrder;
    newNode->next = NULL;

    if (isEmpty()) {
        front = newNode;
        rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    cout << "\n[SUCCESS] Order created with ID: " << newOrder.orderID << "\n";
    cout << "Item Ordered   : " << newOrder.itemName << " (ID: " << newOrder.itemID << ")\n";
    cout << "Target Location: (" << newOrder.targetX << ", " << newOrder.targetY << ")\n";
}

bool OrderQueue::getFrontOrder(Order &frontOrder) {
    if (isEmpty()) return false;
    frontOrder = front->data;
    return true;
}

void OrderQueue::dequeue() {
    if (isEmpty()) {
        cout << "\n[WARNING] Queue is empty! No orders to process.\n";
        return;
    }
    QueueNode* temp = front;
    front = front->next;
    if (front == NULL) rear = NULL;
    delete temp;
}

void OrderQueue::dequeueSilent() {
    if (isEmpty()) return;
    QueueNode* temp = front;
    front = front->next;
    delete temp;
}

void OrderQueue::displayQueue() {
    if (isEmpty()) {
        cout << "\n-------------------- ORDER QUEUE IS EMPTY --------------------\n";
        return;
    }
    cout << "\n-----------------------------------------------------------------------------\n";
    cout << "CURRENT WAREHOUSE PENDING ORDER QUEUE\n";
    cout << "------------------------------------------------------------------------------\n";
    cout << "No.\tOrder ID\tItem ID\tItem Name\t\tLocation (X,Y)\n";
    cout << "------------------------------------------------------------------------------\n";
    
    QueueNode* current = front;
    int no = 1;
    while (current != NULL) {
        cout << no << "\t" << current->data.orderID << "\t\t" << current->data.itemID << "\t" << current->data.itemName;
        if (current->data.itemName.length() < 16) cout << "\t\t";
        else cout << "\t";
        cout << "(" << current->data.targetX << "," << current->data.targetY << ")\n";
        current = current->next;
        no++;
    }
    cout << "------------------------------------------------------------------------------\n";
}