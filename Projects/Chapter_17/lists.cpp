#include <iostream>
#include <string>

struct link
{
    std::string data;
    link* prev;
    link* next;

    link(std::string d, link* p = nullptr, link* n = nullptr)
        :data{d}, prev{p}, next{n} {}
};

//a List is a conglomerataion of links.
//the List object needs only to hold the last element of the list
class List
{
    link* last; //the last element of the List

public:
    link* get_last() { return last; }

    void add_back(link* n);
    void insert (link* p, link* n); //insert in any place of the list
    List(link* head) : last{head} {}
};

void List::add_back(link* n)
{
    n->next = last;
    last->prev = n;
    last = n;
}

void List::insert(link* p, link* n)
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
    //create a new List with the last(and here, single) element being "Lebron"
    List* all_stars = new List(new link{"Lebron"});
    all_stars->add_back(new link{"Kareem"}); // Kareem becomes the last of the list; links are updated : Kareem <=> Lebron
    all_stars->add_back(new link{"Jordan"}); // Jordan becomes the last of the list; links are updated : Jordan <=> Kareem <=> Lebron
    all_stars->insert(all_stars->get_last()->next, new link{"Jamaica"}); // add Jamaica before the next to last element (Kareem)
                                                             // the list becomes : Jordam <=> Jamaica <=> Kareem <=> Lebron

    std::cout << all_stars->get_last()->data << " " << all_stars->get_last()->next->data << " " << all_stars->get_last()->next->next->data << " " << all_stars->get_last()->next->next->next->data; 
    return 0;
}