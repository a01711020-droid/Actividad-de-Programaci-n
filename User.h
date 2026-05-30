#ifdef User_H
#define User_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std

class User{
protected:
    int id;
    string name;
    vector<User*> friends;

public:
    User()
    : name("noname"),id(0),friends(0)
    {}

    User(const Character &c)
    : name(c.name),id(c.id),friends(c.friends)
    {}

    User(string n, int id,)
    : name(n),int(id)
    {}


    string getName(){
        return name;
    }
    void setName(const string& name);
    
    int getId(){
        return id;
    }

    void setId(int id);
    vector<User*>& getFriends();

    void addFriend(User* u);
    void removeFriend(User* u);
    string toString() const;
};







#endif 
