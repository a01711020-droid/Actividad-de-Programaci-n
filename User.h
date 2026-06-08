#ifndef User_H
#define User_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

class User {
protected:
    int id;
    string name;
    vector<User*> friends;

public:
    User()
    : id(0), name("noname")
    {}

    User(const User& c)
    : id(c.id), name(c.name), friends(c.friends)
    {}

    User(string n, int id)
    : id(id), name(n)
    {}

    string getName() {
        return name;
    }
    void setName(const string& name) { this->name = name; }

    int getId() {
        return id;
    }
    void setId(int id) { this->id = id; }

    vector<User*>& getFriends() { return friends; }

    void addFriend(User* u) {
        for (User* f : friends)
            if (f->id == u->id) return;
        friends.push_back(u);
    }

    void removeFriend(User* u) {
        for (int i = 0; i < (int)friends.size(); i++) {
            if (friends[i]->id == u->id) {
                friends.erase(friends.begin() + i);
                return;
            }
        }
    }

    string toString() const {
        string result = "[" + to_string(id) + "] " + name;
        if (!friends.empty()) {
            result += " -> Friends: ";
            for (int i = 0; i < (int)friends.size(); i++) {
                if (i > 0) result += ", ";
                result += friends[i]->name;
            }
        }
        return result;
    }
};

#endif
