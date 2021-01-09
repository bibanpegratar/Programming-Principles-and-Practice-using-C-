#include <iostream>
#include <string>

struct Node
{
    std::string data;
    Node* prev;
    Node* next;

    Node(std::string d, Node* p = nullptr, Node* n = nullptr)
        :data{d}, prev{p}, next{n} {}
};

//a DoubleList is a conglomerataion of Nodes.
//the DoubleList object needs only to hold the last element of the DoubleList
class DoubleList
{
    Node* last; //the last element of the DoubleList

public:
    Node* get_last() { return last; }

    void add_back(Node* n);
    void insert (Node* p, Node* n); //insert in any place of the DoubleList
    explicit DoubleList(Node* head) : last{head} {}
};

void DoubleList::add_back(Node* n)
{
    n->next = last;
    last->prev = n;
    last = n;
}

void DoubleList::insert(Node* p, Node* n)
{
    if(n==nullptr) return;
    if(p==nullptr) 
    {
        p=n;
        return;
    }
    if (p->prev) p->prev->next = n;
    //if p's prev is nullptr, then it's last
    else
    {
        this->add_back(n);
        return;
    }
    n->next = p;
    n->prev = p->prev;
    p->prev = n;
    p = n;
}

int main()
{
    //create a new DoubleList with the last(and here, single) element being "Lebron"
    DoubleList* all_stars = new DoubleList(new Node{"Lebron"});
    all_stars->add_back(new Node{"Kareem"}); // Kareem becomes the last of the DoubleList; Nodes are updated : Kareem <=> Lebron
    all_stars->add_back(new Node{"Jordan"}); // Jordan becomes the last of the DoubleList; Nodes are updated : Jordan <=> Kareem <=> Lebron
    all_stars->insert(all_stars->get_last()->next, new Node{"Jamaica"}); // add Jamaica before the next to last element (Kareem)
                                                             // the DoubleList becomes : Jordam <=> Jamaica <=> Kareem <=> Lebron

    std::cout << all_stars->get_last()->data << " " << all_stars->get_last()->next->data << " " << all_stars->get_last()->next->next->data << " " << all_stars->get_last()->next->next->next->data; 
    return 0;
}