#include <iostream>   // cout/cin para el menú y mensajes
#include <iomanip>    // formateo de salida: setw, setprecision, etc.
#include <string>     // tipo string para nombres y nombre de archivo
#include <fstream>    // ifstream para leer el archivo users.txt
#include <vector>     // vector<User*> para el arreglo dinámico de usuarios
#include <algorithm>  // sort, find, remove_if, útil al manipular colecciones
#include "User.h"
using namespace std;

int counter = 0;      // total de usuarios registrados
vector<User*> users;  // cada posición [i] es el usuario con ID i

bool loadFile(string filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "[ERROR] No se pudo abrir: " << filename << "\n";
		return false;
	}

	int n;
	file >> n;

	users.resize(n, nullptr); // reservar espacio para n punteros

	// Leer usuarios: ID y nombre
	for (int i = 0; i < n; i++) {
		int id;
		string name;
		file >> id >> name;
		users[id] = new User(name, id); // crear en heap, guardar puntero
	}

	// Leer relaciones de amistad
	for (int i = 0; i < n; i++) {
		int userId, m;
		file >> userId >> m; // m = cantidad de amigos
		for (int j = 0; j < m; j++) {
			int friendId;
			file >> friendId;
			users[userId]->addFriend(users[friendId]); // pasar puntero al amigo
		}
	}

	counter = n;
	file.close();
	return true;
}

void displayUsers() {
	for (int i = 0; i < counter; i++) {
		cout << users[i]->toString() << "\n";
	}
}

void addAUser() {
	string name;

	cout << "Name? ";
	getline(cin, name);

	// counter actúa como ID y como posición en el vector
	users.push_back(new User(name, counter));
	counter++;
}

void addFriendToUser() {
	int id1, id2;
	displayUsers();
	cout << "Which user do you want to add a friend to? ";
	cin >> id1;
	displayUsers();
	cout << "Which user do you want to add as a friend? ";
	cin >> id2;

	// Validar que ambos IDs existan y no sean el mismo
	if (id1 < 0 || id1 >= counter || id2 < 0 || id2 >= counter || id1 == id2) {
		cout << "[ERROR] ID invalido.\n";
		return;
	}

	users[id1]->addFriend(users[id2]); // pasar puntero de id2 a id1
}

void deleteFriendFromUser() {
	int id1, id2;
	displayUsers();
	cout << "Which user do you want to unfriend? ";
	cin >> id1;
	displayUsers();
	cout << "Which user do you want to unfriend? ";
	cin >> id2;

	if (id1 < 0 || id1 >= counter || id2 < 0 || id2 >= counter) {
		cout << "[ERROR] ID invalido.\n";
		return;
	}

	users[id1]->removeFriend(users[id2]);
}

int main(int argc, char* argv[]) {
	int option;
	if (!loadFile("users.txt")) {
		return -1;
	}
	do { 
		cin.clear();
		
		cout << "1. Add a new User\n";
		cout << "2. Display all users\n";
		cout << "3. Add a new Friend to a User\n";
		cout << "4. Remove a Friend from a User\n";
		cout << "5. Exit\n";
		cout << "What do you want to do? ";
		cin >> option;
		
		cin.ignore(); // limpiar el \n que queda tras cin >>
		switch (option) {
			case 1 : addAUser(); break;
			case 2 : cout << "Users:\n"; displayUsers(); break;
			case 3 : addFriendToUser(); break;
			case 4 : deleteFriendFromUser(); break;
		}
	} while (option != 5);

	// Liberar memoria del heap antes de salir
	for (int i = 0; i < (int)users.size(); i++) {
		delete users[i];
	}
	return 0;
}
