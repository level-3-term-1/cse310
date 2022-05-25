#include "scope_table.h"
using namespace std;

class symbol_table
{
private:
    scope_table* scopeTable;
public:
    symbol_table(int b_size);
    ~symbol_table();
    void enterScope();
    void exitScope();
    bool insert(string name, string type);
    bool remove(string name);
    symbol_info* lookup(string name);
    void printCurrentScopeTable();
    void printAllScopeTable();
};

symbol_table::symbol_table(int b_size)
{
    scopeTable = new scope_table(b_size, nullptr);
}

symbol_table::~symbol_table()
{
}

inline void symbol_table::enterScope() {
    scopeTable->setCount(scopeTable->getCount() + 1);
    scope_table newScopeTable(scopeTable->getBucketSize(), scopeTable);
}

inline void symbol_table::exitScope() {
    // delete operation
}

inline bool symbol_table::insert(string name, string type) {
    return scopeTable->insert(name, type);
}

inline bool symbol_table::remove(string name) {
    return scopeTable->dlt(name);
}

inline symbol_info* symbol_table::lookup(string name) {
    scope_table* temp = this->scopeTable;
    while(temp != nullptr){
        symbol_info* symbolInfo = temp->search(name);
        if(symbolInfo == nullptr){
            temp = temp->getParentScope();
        }
        else {
            return symbolInfo;
        }
    }
    return nullptr;
}

inline void symbol_table::printCurrentScopeTable() {
    this->scopeTable->print();
}

inline void symbol_table::printAllScopeTable() {
    scope_table* temp = this->scopeTable;
    while(temp != nullptr) {
        temp->print();
        temp = temp->getParentScope();
    }
}
