#include <iostream>
#include <list>
#include <cstring>
using namespace std;

// Hashtable to implement 

#define hashGroups 65536

class HashTable
{
protected:
    int threshold=128;
    int cumulative_count=0;
    list<pair<int, int>> table[hashGroups]; //List1, list2, ....

    
public:
    //tested
bool isEmpty() const {
    return cumulative_count==0;
}

//tested
void initialize(int threshold){
    //this->hashGroups=hashGroups;
    this->threshold=threshold;
    clear();
}

//tested
int hashFunction(uint16_t key){
    uint16_t hashedv = key * 37;
    hashedv = hashedv ^ 0x5678;
    // hashedv = hashedv & 0xFFFFFFFF;
    // return hashedv;
    return hashedv % hashGroups;
}

int insert(uint16_t key){
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue]; //get the list
    auto bItr = begin(cell);
    bool keyExists = false;

    for (; bItr != end(cell); bItr++){ //iterate over the list yo check whether the key exists or not
        if(bItr->first){
            keyExists = true;
            int counter = bItr->second;
            if (test(key)){
                counter++;
                 bItr->second = counter;
                 cumulative_count++;
            }
            break;
        }
    }

    if (!keyExists){
        cell.emplace_back(key, 1);
        cumulative_count++;

    }
    return cumulative_count;
}


//modify this
int accessesNum(uint16_t key){
    int hashedValue = hashFunction(key);
     auto& cell = table[hashedValue]; //get the list
    auto bItr = begin(table[hashedValue]); 
    for (; bItr != end(cell); bItr++){ //iterate over the list yo check whether the key exists or not
        if(bItr->first){
            return bItr->second;
        }
    }
    return 0;
}

bool test(uint16_t key){
    if (accessesNum(key)>=threshold){
        cout << "cant access row for now" << endl;
        return false;
    }
    return true;
}

void removeItem(int key){
        int hashValue = hashFunction(key);
    auto& cell = table[hashValue]; //get the list
    auto bItr = begin(cell);
    bool keyExists = false;

    for (; bItr != end(cell); bItr++){ //iterate over the list yo check whether the key exists or not
        if(bItr->first){
            keyExists = true;
            bItr = cell.erase(bItr);
            cout << "item removed" << endl;
            break;
        }
    }

    if (!keyExists){
        cout << "item NOT found" << endl;
    }
    return;
}

void clear(){   
    for (int i = 0; i<hashGroups; i++){
        auto& cell = table[i]; //get the list
        auto bItr = begin(cell);
        for (; bItr != end(cell); bItr++){ //iterate over the list to check whether the key exists or not
           bItr = cell.erase(bItr);
      }
    }
    cumulative_count=0;
}

void printTable(){
    for (int i{}; i<hashGroups; i++){
        if (table[i].size() == 0) continue;

        auto bItr = table[i].begin();
        for (; bItr != table[i].end(); bItr++){
            cout << "key: "<< bItr->first << "value: "<< bItr->second << endl;

        } 
    }
    return;
}
};

/*int main(){
    HashTable HT;
     HT.insert(0x1234);
     HT.insert(0x1235);
     HT.insert(0x1234);
     HT.insert(0x1234);
     cout << HT.accessesNum(0x1234);
      HT.printTable();
     HT.clear();
 HT.printTable();
}*/