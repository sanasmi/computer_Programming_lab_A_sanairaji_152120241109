#include <iostream>
#include <string>
using namespace std;
struct Package {
    string packageID;
    string destinationCity;
    int dimensions[3]; 
};
struct Node {
    Package data;
    Node* next;
};
class PackageStack {
private:
    Node* top;
public:
    PackageStack() {
        top = NULL;
    }
    void push(Package p) {
        Node* newNode = new Node;
        newNode->data = p;
        newNode->next = top;
        top = newNode;
    }
    bool pop(Package &p) {
        if (top == NULL) {
            cout << "No package to dispatch!\n";
            return false;
        }
        Node* temp = top;
        p = temp->data;
        top = top->next;
        delete temp;
        return true;
    }
    void display() {
        if (top == NULL) {
            cout << "No packages in stack.\n";
            return;
        }
        Node* temp = top;
        cout << "\nPackages in Stack:\n";
        while (temp != NULL) {
            cout << "ID: " << temp->data.packageID
                 << ", City: " << temp->data.destinationCity
                 << ", Dimensions: "
                 << temp->data.dimensions[0] << "x"
                 << temp->data.dimensions[1] << "x"
                 << temp->data.dimensions[2] << endl;
            temp = temp->next;
        }
    }
};
struct Courier {
    string courierName;
    string vehicleType;
};
class CourierQueue {
private:
    Courier arr[5];
    int front, rear, count;
public:
    CourierQueue() {
        front = 0;
        rear = -1;
        count = 0;
    }
    void enqueue(Courier c) {
        if (count == 5) {
            cout << "Queue is full!\n";
            return;
        }
        rear = (rear + 1) % 5;
        arr[rear] = c;
        count++;
    }
    bool dequeue(Courier &c) {
        if (count == 0) {
            cout << "No courier available!\n";
            return false;
        }
        c = arr[front];
        front = (front + 1) % 5;
        count--;
        return true;
    }
    void display() {
        if (count == 0) {
            cout << "No couriers in queue.\n";
            return;
        }
        cout << "\nCouriers in Queue:\n";
        int i = front;
        for (int j = 0; j < count; j++) {
            cout << "Name: " << arr[i].courierName
                 << ", Vehicle: " << arr[i].vehicleType << endl;
            i = (i + 1) % 5;
        }
    }
};
int main() {
    PackageStack stack;
    CourierQueue queue;

    Package p1 = {"P1", "Ankara", {10, 20, 30}};
    Package p2 = {"P2", "Istanbul", {15, 25, 35}};

    Courier c1 = {"Alex", "Motorbike"};
    Courier c2 = {"Alvin", "Van"};

    stack.push(p1);
    stack.push(p2);

    queue.enqueue(c1);
    queue.enqueue(c2);

    stack.display();
    queue.display();

    Package dispatchedPackage;
    Courier dispatchedCourier;
    
    if (stack.pop(dispatchedPackage) && queue.dequeue(dispatchedCourier)) {
        cout << "\nDispatch Done:\n";
        cout << "Courier " << dispatchedCourier.courierName
             << " took package " << dispatchedPackage.packageID << endl;
    }
    stack.display();
    queue.display();
    
    return 0;
}
