#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <exception>
#include "json (2).hpp"
using namespace std;
using json = nlohmann::json;
class FileNotFoundException : public exception {
public:
    const char* what() const noexcept override {
        return "File not found";
    }
};
struct User {
    string id;
    string name;
    string email;
};
int main() {
    try {
        ifstream file("users.csv");
        if (!file.is_open()) {
            throw FileNotFoundException();
        }
        vector<User> users;
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            User u;
            getline(ss, u.id, ',');
            getline(ss, u.name, ',');
            getline(ss, u.email);
            if (!u.email.empty() && u.email.back() == '\r')
                u.email.pop_back();
            users.push_back(u);
        }
        file.close();
        json j = json::array();
        for (size_t i = 0; i < users.size(); i++) {
            json obj;
            obj["id"] = users[i].id;
            obj["name"] = users[i].name;
            obj["email"] = users[i].email;
            j.push_back(obj);
        }
        ofstream out("users.json");
        out << j.dump(4);
        out.close();
        cout << "Done\n";
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }
    return 0;
}