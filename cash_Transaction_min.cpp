#include <bits/stdc++.h>

using namespace std;
//money splitwise algorithm
//graph implementation
//output=contain all details with transaction 

//rakesh pay= 100 to jevven
//jeevan pay =50 to bhavesh
//bhavesh pay =40 to rakesh
ṇ
//our algo make above transaction sort to
//rakesh pay=50 to jeevan
//rakesh pay =10 to bhavesh

//creating the constructor for max amount(custom comparator);

//sort according to person_comapre
class person_compare {
public:
    bool operator()(pair<string, int> p1, pair<string, int> p2) {
        return p1.second < p2.second;
    }
}; 

int main() {
    int numberOfTransaction, friends;
    cin >> numberOfTransaction;
    cin >> friends;

    string person1, person2;
    int amount;

    map<string, int> mp;
    while (numberOfTransaction--) {
        cin >> person1 >> person2 >> amount;
        mp[person1] += amount;
        mp[person2] -= amount; 
    }
 //now we iterate over the mp map and those person have value non zero we will add those to multiset.. ,
    multiset<pair<string, int>, person_compare> multi;

    for (auto i : mp) {
        string person = i.first;
        int amount = i.second;

        if (mp[person] != 0) {
            multi.insert(make_pair(person, amount));
        }
    }
   //settlement amount;
    int count = 0;
    while (!multi.empty()) {
        auto low = multi.begin();
        auto high = prev(multi.end());

        auto debit = low->second;
        string debit_person = low->first;

        auto credit = high->second;
        string credit_person = high->first;

        multi.erase(low);
        multi.erase(high);

        int settled_amount = min(-debit, credit);
        debit += settled_amount;
        credit -= settled_amount;

        cout << debit_person << " will pay " << settled_amount << " to " << credit_person << endl;

        if (debit != 0) {
            multi.insert(make_pair(debit_person, debit));
        }
        if (credit != 0) {
            multi.insert(make_pair(credit_person, credit));
        }

        count++;
    }

    cout << "Total number of transactions: " << count << endl;

    return 0;
}
