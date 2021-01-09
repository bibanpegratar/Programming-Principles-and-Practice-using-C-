#include <iostream>

struct Node
{
    int data;
    Node* next;

    Node(int data);
};

Node::Node(int data) 
{
    this->data = data;
    this->next = nullptr;
}

class LinkedList
{
    int length;
public:
    Node* head;
    Node* last;

    explicit LinkedList(int data);
    ~LinkedList()
    {
        delete head;
        delete last;
    }

    void add(int data);
    int get_length() {return length;}
};

LinkedList::LinkedList(int data)
{
    this->head = new Node(data);
    this->last = head;
    this->length = 1;
}

void LinkedList::add(int data)
{
    Node* n = new Node(data);
    last->next = n;
    last = n;
    length++;
}

int main()
{
    LinkedList list(1);
    list.add(2);
    list.add(3);
    list.add(4);
    std::cout << list.head->next->next->next->data;
    return 0;
}