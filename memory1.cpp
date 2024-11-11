#include <iostream>
using namespace std;

class memory
{
public:
    int freespace;
    int number;
    memory *next;

    memory(int a, int b)
    {
        freespace = a;
        number = b;
        next = NULL;
    }
};

void creatememory(memory *&head, int value, int number)
{
    if (head == NULL)
    {
        head = new memory(value, number);
    }
    else
    {
        memory *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new memory(value, number);
    }
}

void checkspace(memory *&head, int value)
{
    memory *temp = head;
    memory *best_fit = NULL;
    memory *worst_fit = NULL;
    memory *first_fit = NULL;

    // Finding the appropriate blocks for each fit strategy
    while (temp != NULL)
    {
        if (value <= temp->freespace)
        {
            if (first_fit == NULL)
                first_fit = temp;

            if (best_fit == NULL || temp->freespace < best_fit->freespace)
                best_fit = temp;

            if (worst_fit == NULL || temp->freespace > worst_fit->freespace)
                worst_fit = temp;
        }
        temp = temp->next;
    }

    // Allocate space according to each fit strategy
    if (best_fit != NULL)
    {
        cout << "\nBest Fit: Allocated " << value << " units in block " << best_fit->number 
             << " with " << best_fit->freespace << " free space.\n";
        best_fit->freespace -= value;
    }
    else
    {
        cout << "\nBest Fit: No sufficient free space available.\n";
    }

    if (worst_fit != NULL)
    {
        cout << "Worst Fit: Allocated " << value << " units in block " << worst_fit->number 
             << " with " << worst_fit->freespace << " free space.\n";
        worst_fit->freespace -= value;
    }
    else
    {
        cout << "Worst Fit: No sufficient free space available.\n";
    }

    if (first_fit != NULL)
    {
        cout << "First Fit: Allocated " << value << " units in block " << first_fit->number 
             << " with " << first_fit->freespace << " free space.\n";
        first_fit->freespace -= value;
    }
    else
    {
        cout << "First Fit: No sufficient free space available.\n";
    }
}

void displayspace(memory *head)
{
    memory *temp = head;
    cout << "Current memory blocks (block number -> free space):\n";
    while (temp != NULL)
    {
        cout << "Block " << temp->number << ": " << temp->freespace << " units -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

int main()
{
    memory *head = NULL;
    creatememory(head, 20, 1);
    creatememory(head, 25, 2);
    creatememory(head, 15, 3);

    cout << "Initial memory blocks:\n";
    displayspace(head);

    checkspace(head, 10);
    displayspace(head);

    checkspace(head, 5);
    displayspace(head);

    checkspace(head, 30);
    displayspace(head);

    return 0;
}
