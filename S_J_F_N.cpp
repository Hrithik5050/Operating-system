#include <iostream>
using namespace std;
class cpu
{
public:
    int bt; // burst time
    int wt; // wait itme
    int at; // arrivial time
    string name;
    cpu *next = NULL;
    cpu(int b, int a,string d)  // parametrized constructor
    {
        bt = b;
        at = a;
        name =d;
        next = NULL;
    }
};

void shortest(cpu *head)
{
    if (head == NULL || head->next == NULL)
        return; // No need to sort if the list is empty or has only one node

    cpu *i = head->next;  // Outer loop pointer

    // Traverse the list
    while (i != NULL)
    {
        cpu *smallest = i;  // Assume the current node has the smallest burst time
        cpu *j = i->next;   // Inner loop pointer

        // Find the node with the smallest burst time in the remaining list
        while (j != NULL)
        {
            if (j->at < smallest->at || j->bt < smallest->bt)
            {
                smallest = j;  // Update the smallest node
            }
            j = j->next;  // Move to the next node in the inner loop
        }

        // Swap the burst time and arrival time of the current node with the smallest node
        if (smallest != i)
        {
            swap(i->bt, smallest->bt);
            swap(i->at, smallest->at);
            swap(i->name,smallest->name);
        }

        i = i->next;  // Move to the next node in the outer loop
    }
}

void calculateWaitTime(cpu *head)
{
    if (head == nullptr)
        return; // No processes

    int currentTime = 0; // To keep track of current time
    cpu *temp = head;

    while (temp != nullptr)
    {
        // Wait time is the max of current time or arrival time minus arrival time
        if (currentTime <= temp->at)
        {

            currentTime = temp->at; // Jump to the arrival time
        }
        temp->wt = currentTime - temp->at; // Calculate waiting time
        currentTime += temp->bt;           // Update current time to the end of this process
        temp = temp->next;                 // Move to the next process
    }
}

void process(cpu *&head, int c, int d,string name)
{
    if (head == NULL) // head node is created
    {
        cpu *new_node = new cpu(c, d,name);
        new_node->next = head;
        head = new_node;
    }

    else // creating after head node
    {
        cpu *temp = head;
        cpu *new_node = new cpu(c, d,name);
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
        cout << "Process:" <<temp->name <<" Wait time is:"<<temp->wt << endl;
        temp = temp->next;
    }
}
int main()
{
    cpu *head = NULL;
    process(head,3,0,"P4");
    process(head, 6, 2,"P1");
    process(head, 2, 5,"P2");
    process(head, 8, 1,"P3");
    process(head,4,4,"P5");
    shortest(head);
    calculateWaitTime(head);
    display(head);
    return 0;
}