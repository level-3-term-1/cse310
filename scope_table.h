#include "symbol_info_list.h"
#include "hash_function.h"
using namespace std;

class scope_table
{
private:
    symbol_info_list *arrayOfSymbolInfoList;
    long bucketSize;
    scope_table *parentScope;
    string id;
    int count;

public:
    scope_table(int s, scope_table* parent) : bucketSize(s), parentScope(parent)
    {
        arrayOfSymbolInfoList = new symbol_info_list[s];
        id = parent->id + "." + to_string(parent->count);
        count = 0;
    }
    ~scope_table();

    bool insert(string key, string value)
    {
        symbol_info* x = this->search(key);
        if (x == nullptr)
        {
            // not found, now insert
            this->arrayOfSymbolInfoList[call_hash(key)].insert(key, value);
            return true;
        }
        return false;
    }

    unsigned long call_hash(string key){
        return sdbmhash(key) % bucketSize;
    }

    symbol_info* search(string key)
    {
        unsigned long idx = call_hash(key);
        symbol_info* x = this->arrayOfSymbolInfoList[idx].getHead();
        while (x != nullptr)
        {
            if (x->getName() == key)
            {
                return x;
            }
            x = x->getNext();
        }
        return nullptr;
    }

    bool dlt(string key)
    {
        symbol_info *x = search(key);
        if (x == nullptr)
        {
            return false;
        }
        this->arrayOfSymbolInfoList[call_hash(key)].dlt(key);
        return true;
    }

    void print(){
        for (size_t i = 0; i < bucketSize; i++)
        {
            cout << i << " --> ";
            this->arrayOfSymbolInfoList[i].print();
        }
        
    }

    long getBucketSize() const { return bucketSize; }

    scope_table *getParentScope() const { return parentScope; }

    int getCount() const { return count; }
    void setCount(int count_) { count = count_; }
};

scope_table::~scope_table()
{
}
