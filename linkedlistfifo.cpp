#include <iostream>
using namespace std;
class cpu
{
public:
    int bt;   //burst time
    int wt;    //wait itme
    int at;     //arrivial time
    cpu *next = NULL;
    cpu(int b, int a)   //parametrized constructor
    {
        bt = b;       
        at = a;
        next = NULL;
    }
};
void calculateWaitTime(cpu *head)
{
    if (head == nullptr)
        return; // No processes

    int currentTime = 0; // To keep track of current time
    cpu *temp = head;

    while (temp != nullptr)
    {
        // Wait time is the max of current time or arrival time minus arrival time
        /*if (currentTime <= temp->at)
        {
            currentTime = temp->at; // Jump to the arrival time
        }*/
        temp->wt = currentTime;  // Calculate waiting time
        currentTime += temp->bt; // Update current time to the end of this process
        temp = temp->next;       // Move to the next process
    }
}

void process(cpu *&head, int c, int d)
{
    if (head == NULL)       //head node is created
    {
        cpu *new_node = new cpu(c, d);
        new_node->next = head;
        head = new_node;
    }

    else         //creating after head node
    {
        cpu *temp = head;
        cpu *new_node = new cpu(c, d);
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}
void display(cpu *head)
{
    cpu *temp = head;
    while (temp != NULL)
    {
        cout << "Burst time: " << temp->bt <<"\n"<<
         " Arrivial time:  " << temp->at << "\n"<<
         " Wait time:" << temp->wt << "\n"<<
         "->";
        temp = temp->next;
    }
    cout << "Null" << endl;
}
int main()
{
    cpu *head = NULL;
    process(head, 5, 0);
    process(head, 3, 0);
    process(head, 2, 0);
    calculateWaitTime(head);
    display(head);
    return 0;
}