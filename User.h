#ifndef User_H
#define User_H

#include <iostream>  // cout/cin, útil para clases que hereden de User
#include <iomanip>   // formateo de salida: setw, setprecision, etc.
#include <string>    // tipo string para name y métodos
#include <vector>    // vector<User*> para la lista de amigos
using namespace std;

class User {
protected:
    int id;
    string name;
    vector<User*> friends; // punteros a los amigos del usuario

public:
    // Constructor por defecto
    User()
    : id(0), name("noname")
    {}

    // Constructor de copia
    User(const User& c)
    : id(c.id), name(c.name), friends(c.friends)
    {}

    // Constructor con datos iniciales
    User(string n, int id)
    : id(id), name(n)
    {}

    string getName() { return name; }
    void setName(const string& name) { this->name = name; }

    int getId() { return id; }
    void setId(int id) { this->id = id; }

    // Retorna referencia al vector para poder modificarlo desde afuera
    vector<User*>& getFriends() { return friends; }

    void addFriend(User* u);
    void removeFriend(User* u);
    string toString() const;
};

#endif
