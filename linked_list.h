#include "symbol_info.h"
using namespace std;

class symbol_info_list
{
private:
    symbol_info *tail;
    symbol_info *head;

public:
    symbol_info_list()
    {
        head = nullptr;
        tail = nullptr;
    }
    void insert(string k, string v)
    {
        if (isEmpty())
        {
            head = new symbol_info(k, v);
            tail = head;
            return;
        }
        symbol_info *y = new symbol_info(k, v);
        y->setNext(tail);
        tail->setNext(y);
        tail = tail->getNext();
    }
    void dlt(string k)
    {
        auto x = head;
        // cout << x->getKey() << " " << x->getValue() << endl;
        while (x->getName() != k)
        {
            // cout << x->getKey() << " " << x->getValue() << endl;
            x = x->getNext();
        }
        // cout << "deleting dfsdfsdf" << endl;
        if (x->getName() == k)
        {
            // cout << "deleting" << endl;
            if (x == head)
            {
                // cout << "head" << endl;
                head = x->getNext();
                if (head == nullptr)
                {
                    // cout << "head = nullptr" << endl;
                    tail = nullptr;
                }
                else
                    head->setPrev(nullptr);
            }
            else if (x == tail)
            {
                tail = x->getPrev();
                tail->setNext(nullptr);
            }
            else
            {
                x->getPrev()->setNext(x->getNext());
                x->getNext()->setPrev(x->getPrev());
            }
            delete x;
        }
    }
    bool isEmpty()
    {
        return head == nullptr;
    }

    symbol_info *getTail() const { return tail; }

    symbol_info *getHead() const
    {
        return head;
    }
};
