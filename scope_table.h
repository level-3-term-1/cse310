#include "symbol_info_list.h"
#include "hash_function.h"
using namespace std;

class scope_table
{
private:
    symbol_info_list *arrayOfSymbolInfoList;
    unsigned long bucketSize;
    scope_table *parentScope;
    string id;
    int count;
    bool flagForDeletingParentScope;

public:
    scope_table(long s, scope_table *parent) : bucketSize(s), parentScope(parent)
    {
        arrayOfSymbolInfoList = new symbol_info_list[s];
        count = 0;
        flagForDeletingParentScope = true;
        if (parent != nullptr)
        {
            id = parent->id + "." + to_string(parent->count);
            cout << "New ScopeTable with id " << id << " created" << endl;
        }
        else
            id = "1";
    }
    ~scope_table();

    bool insert(string key, string value)
    {
        symbol_info *x = this->lookup(key).second;
        if (x == nullptr)
        {
            // not found, now insert
            unsigned int idx = call_hash(key);
            int pos = this->arrayOfSymbolInfoList[idx].insert(key, value);
            cout << "Inserted in ScopeTable# " << id << " at position " << idx << ", " << pos << endl;
            return true;
        }
        else
        {
            cout << "This word already exists" << endl
                 << "< " << key << ", " << value << " > already exist in the currentScopeTable" << endl;
        }
        return false;
    }

    unsigned int call_hash(string key)
    {
        return sdbmhash(key) % bucketSize;
    }

    pair<int, symbol_info *> lookup(string key, bool printResult = false)
    {
        unsigned int idx = call_hash(key);
        pair<int, symbol_info *> obj = this->arrayOfSymbolInfoList[idx].search(key);
        if (printResult)
        {
            string str = obj.first == -1 ? "Not found" : "Found in ScopeTable# " + id + " at position " + to_string(idx) + ", " + to_string(obj.first);
            cout << str << endl;
        }
        return obj;
    }

    bool dlt(string key)
    {
        pair<int, symbol_info *> x = lookup(key, true);
        if (x.second == nullptr)
        {
            cout << key << " not found" << endl;
            return false;
        }
        cout << "found it" << endl;
        if (this->arrayOfSymbolInfoList[call_hash(key)].dlt(x.second))
        {
            cout << "deleted entry at " << call_hash(key) << ", " << x.first << " in the current scopetable" << endl;
        }
        return true;
    }

    void print()
    {
        cout << endl << endl << "ScopeTable # " << id << endl;
        for (size_t i = 0; i < bucketSize; i++)
        {
            cout << i << " -->  ";
            this->arrayOfSymbolInfoList[i].print();
            cout << endl;
        }
        // cout << endl;
    }

    long getBucketSize() const { return bucketSize; }

    scope_table *getParentScope() const { return parentScope; }

    int getCount() const { return count; }
    void setCount(int count_) { count = count_; }

    void setFlagForDeletingParentScope(bool flagForDeletingParentScope_) { flagForDeletingParentScope = flagForDeletingParentScope_; }
};

scope_table::~scope_table()
{
    // cout << "calling the destructor of scope table" << endl;
    cout << "ScopeTable with id " << id << " removed" << endl;
    delete[] arrayOfSymbolInfoList;
    if(flagForDeletingParentScope)
        delete parentScope;
    else 
        parentScope = nullptr;

    // for (size_t i = 0; i < 1; i++)
    // {
    //     delete arrayOfSymbolInfoList;
    // }
}
