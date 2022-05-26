#include <bits/stdc++.h>
#include "symbol_table.h"
using namespace std;

#define IN freopen("output.txt", "w+", stdout)
#define OUT freopen("input.txt", "r+", stdin)

int main()
{
    IN;
    OUT;
    int bucket_size;
    cin >> bucket_size;
    // cout << bucket_size;
    string s, x, y;
    symbol_table symbolTable(bucket_size);
    while (cin >> s)
    {
        switch (s[0])
        {
        case 'I':
            cin >> x >> y;
            cout << s << " " << x << " " << y << endl;
            cout << endl;
            symbolTable.insert(x, y);
            cout << endl;
            break;

        case 'L':
            cin >> x;
            cout << s << " " << x << endl;
            cout << endl;
            symbolTable.lookup(x);
            cout << endl;
            break;

        case 'D':
            cin >> x;
            cout << s << " " << x << endl;
            cout << endl;
            symbolTable.remove(x);
            cout << endl;
            break;

        case 'P':
            cin >> x;
            if (x == "A")
            {
                cout << s << " " << x << endl;
                cout << endl;
                symbolTable.printAllScopeTable();
                cout << endl;
            }
            else if (x == "C")
            {
                cout << s << " " << x << endl;
                cout << endl;
                symbolTable.printCurrentScopeTable();
                cout << endl;
            }
            break;

        case 'S':
            cout << s << endl;
            cout << endl;
            symbolTable.enterScope();
            cout << endl;
            break;

        case 'E':
            cout << s << endl;
            cout << endl;
            symbolTable.exitScope();
            cout << endl;
            break;

        default:
            break;
        }
    }
}