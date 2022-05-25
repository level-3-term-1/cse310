#include <bits/stdc++.h>
#include "symbol_table.h"

#define IN freopen("output.txt", "w+", stdout)
#define OUT freopen("input.txt", "r+", stdin)

using namespace std;



int main()
{
    IN; OUT;
    int bucket_size;
    cin >> bucket_size;
    string s;
    string x, y;
    symbol_table symbolTable(bucket_size);
    while(cin >> s){
        switch (s[0])
        {
        case 'I':
            cin >> x >> y;
            symbolTable.insert(x, y);
            break;
        
        case 'L':
            cin >> x;
            symbolTable.lookup(x);
            break;
        
        case 'D':
            cin >> x;
            symbolTable.remove(x);
            break;
        
        case 'P':
            cin >> x;
            if(x == "A"){
                symbolTable.printAllScopeTable();
            } 
            else if(x == "C") {
                symbolTable.printCurrentScopeTable();
            }
            break;
        
        case 'S':
            symbolTable.enterScope();
            break;
        
        case 'E':
            symbolTable.exitScope();
            break;
        
        default:
            break;
        }
    }

}