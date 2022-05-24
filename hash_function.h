#include<bits/stdc++.h>
using namespace std;

unsigned long sdbmhash(string key)
{
    unsigned long hash = 0;
    int c;
    for (auto x : key)
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

// static unsigned long
// sdbm(str)
// unsigned char *str;
// {
//     unsigned long hash = 0;
//     int c;

//     while (c = *str++)
//         hash = c + (hash << 6) + (hash << 16) - hash;

//     return hash;
// }