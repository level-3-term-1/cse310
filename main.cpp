#include <bits/stdc++.h>
#include "scopetable.h""

#define IN freopen("output.txt", "w+", stdout)
#define OUT freopen("input.txt", "r+", stdin)

using namespace std;

bool insert(string key, int value, separate_chaining &sc1, separate_chaining &sc2, double_hashing &dh1, double_hashing &dh2, custom_probing &cp1, custom_probing &cp2)
{
    auto flag_sc = sc1.insert(key, value);
    auto flag_dh = dh1.insert(key, value);
    auto flag_cp = cp1.insert(key, value);
    auto flag_sc2 = sc2.insert(key, value);
    auto flag_dh2 = dh2.insert(key, value);
    auto flag_cp2 = cp2.insert(key, value);
    auto flag = flag_cp & flag_dh2 & flag_dh & flag_cp2 & flag_sc2 & flag_sc;

    return flag;
}
void search(string key, separate_chaining &sc1, separate_chaining &sc2, double_hashing &dh1, double_hashing &dh2, custom_probing &cp1, custom_probing &cp2, bool probing = false)
{
    auto x_sc1 = sc1.search(key, false, probing);
    // cout << "here1 " << x_sc1.first << " " << x_sc1.second << endl;
    auto x_sc2 = sc2.search(key, false, probing);
    // cout << "here2 " << x_sc2.first << " " << x_sc2.second << endl;
    auto x_dh1 = dh1.search(key, false, probing);
    // cout << "here3 " << x_dh1.first << " " << x_dh1.second << endl;
    auto x_dh2 = dh2.search(key, false, probing);
    // cout << "here4 " << x_dh2.first << " " << x_dh2.second << endl;
    auto x_cp1 = cp1.search(key, false, probing);
    // cout << "here5 " << x_cp1.first << " " << x_cp1.second << endl;
    auto x_cp2 = cp2.search(key, false, probing);
    // cout << "here6 " << x_cp2.first << " " << x_cp2.second << endl;
    if (probing)
        return;
    if (x_sc1.second != nullptr && !x_sc1.second->getKhali())
        cout << "found " << x_sc1.second->getKey() << " " << x_sc1.second->getValue() << endl;
    else
    {
        cout << key << " not found" << endl;
    }
}
void dlt(string key, separate_chaining &sc1, separate_chaining &sc2, double_hashing &dh1, double_hashing &dh2, custom_probing &cp1, custom_probing &cp2)
{
    auto x_sc1 = sc1.dlt(key);
    // cout << "here1 " << x_sc1 << endl;
    auto x_sc2 = sc2.dlt(key);
    // cout << "here2 " << x_sc2 << endl;
    auto x_dh1 = dh1.dlt(key);
    // cout << "here3 " << x_dh1 << endl;
    auto x_dh2 = dh2.dlt(key);
    // cout << "here3 " << x_dh2 << endl;
    auto x_cp1 = cp1.dlt(key);
    // cout << "here3 " << x_cp1 << endl;
    auto x_cp2 = cp2.dlt(key);
    // cout << "here3 " << x_cp2 << endl;
    if (x_sc1 == true)
    {
        cout << "successfully deleted" << endl;
    }
    else
    {
        cout << key << " not found" << endl;
    }
}

bool file_input = true;

int main()
{
    IN; OUT;
    // int a;
    // cin >> a;
    // string x, y;
    // string s;
    // while(cin >> s){
    //     switch (s[0])
    //     {
    //     case 'I':
    //         cin >> x >> y;
    //         cout << x << y;
    //         break;
        
    //     default:
    //         break;
    //     }
    // }



    int m, n, c1 = 2, c2 = 3;
    if (!file_input)
        cout << "enter the size of hash table: ";
    cin >> m;
    m = (m & 1) ? m : m + 1;

    while (!is_prime(m))
        m += 2;

    if (file_input)
        cout << m << endl;
    string s;

    separate_chaining sc_hash1(m, hash1);
    separate_chaining sc_hash2(m, hash2);

    double_hashing dh_hash1(m, hash1, 1);
    double_hashing dh_hash2(m, hash2, 2);

    custom_probing cp_hash1(m, hash1, c1, c2, 1);
    custom_probing cp_hash2(m, hash2, c1, c2, 2);
    srand(time(0));

    n = 10000;
    int c = 0;
    int selected_number = 0;
    bool flag;

    vector<string> words;

    while (selected_number != -1 && !file_input)
    {
        cout << "1. inserting" << endl;
        cout << "2. searching" << endl;
        cout << "3. deleting" << endl;
        cout << "4. report generate" << endl;
        cin >> selected_number;
        switch (selected_number)
        {
        case 1:
            cin >> s;
            flag = insert(s, c + 1, sc_hash1, sc_hash2, dh_hash1, dh_hash2, cp_hash1, cp_hash2);
            c += flag;
            if (flag)
            {
                cout << s << " inserted." << endl;
            }
            else
            {
                cout << s << " already existed" << endl;
            }
            words.push_back(s);
            break;
        case 2:
            cin >> s;
            search(s, sc_hash1, sc_hash2, dh_hash1, dh_hash2, cp_hash1, cp_hash2);
            break;
        case 3:
            cin >> s;
            dlt(s, sc_hash1, sc_hash2, dh_hash1, dh_hash2, cp_hash1, cp_hash2);
            break;
        case 4:
            selected_number = -1;
            break;
        default:
            selected_number = -1;
            break;
        }
    }
    int remaining = n - c;
    for (int i = 0; i < remaining; i++)
    {
        string s = "";
        // cin >> s;
        for (int j = 0; j < 7; j++)
        {
            int x = (rand() % 26) + 'a';
            s += x;
        }
        // cout << s << endl;
        c += insert(s, c + 1, sc_hash1, sc_hash2, dh_hash1, dh_hash2, cp_hash1, cp_hash2);
        words.push_back(s);
        // cout << s <<  endl;
    }

    // cout << words.size() << endl;

    // cout << "count = " << c << endl;
    // cout << "duplicate separate_chaining hash1 = " << sc_hash1.getDuplicate() << endl;
    // cout << "duplicate separate_chaining hash2 = " << sc_hash2.getDuplicate() << endl;
    // cout << "duplicate double_hashing hash1 = " << dh_hash1.getDuplicate() << endl;
    // cout << "duplicate double_hashing hash2 = " << dh_hash2.getDuplicate() << endl;
    // cout << "duplicate custom_probing hash1 = " << cp_hash1.getDuplicate() << endl;
    // cout << "duplicate custom_probing hash2 = " << cp_hash2.getDuplicate() << endl;

    cout << "collision separate_chaining hash1 = " << sc_hash1.getCollision() << endl;
    cout << "collision separate_chaining hash2 = " << sc_hash2.getCollision() << endl;
    cout << "collision double_hashing hash1 = " << dh_hash1.getCollision() << endl;
    cout << "collision double_hashing hash2 = " << dh_hash2.getCollision() << endl;
    cout << "collision custom_probing hash1 = " << cp_hash1.getCollision() << endl;
    cout << "collision custom_probing hash2 = " << cp_hash2.getCollision() << endl;

    //probing
    double k = 1000;
    for (int j = 0; j < k; j++)
    {
        int x = (rand() % n);
        search(words[x], sc_hash1, sc_hash2, dh_hash1, dh_hash2, cp_hash1, cp_hash2, true);
    }
    cout << "probing separate_chaining hash1 = " << sc_hash1.getProbe() / k << endl;
    cout << "probing separate_chaining hash2 = " << sc_hash2.getProbe() / k << endl;
    cout << "probing double_hashing hash1 = " << dh_hash1.getProbe() / k << endl;
    cout << "probing double_hashing hash2 = " << dh_hash2.getProbe() / k << endl;
    cout << "probing custom_probing hash1 = " << cp_hash1.getProbe() / k << endl;
    cout << "probing custom_probing hash2 = " << cp_hash2.getProbe() / k << endl;

    // for (auto x : words)
    // {
    //     cout << x << endl;
    // }
}