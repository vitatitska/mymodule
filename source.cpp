#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
struct Book {
    string title;
    string author;
    string year;
    string isbn;
};
int main() {
    ifstream file("books.csv");
    if (!file.is_open()) {
        cout << "File not found\n";
        return 1;
    }
    vector<Book> books;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        Book b;
        getline(ss, b.title, ',');
        getline(ss, b.author, ',');
        getline(ss, b.year, ',');
        getline(ss, b.isbn);
        if (!b.author.empty() && b.author[0] == ' ')
            b.author.erase(0, 1);
        if (!b.title.empty() && b.title[0] == ' ')
            b.title.erase(0, 1);

        books.push_back(b);
    }
    file.close();
    ofstream out("books.json");
    out << "[\n";
    for (size_t i = 0; i < books.size(); i++) {
        out << "  {\n";
        out << "    \"title\": \"" << books[i].title << "\",\n";
        out << "    \"author\": \"" << books[i].author << "\",\n";
        out << "    \"year\": \"" << books[i].year << "\",\n";
        out << "    \"isbn\": \"" << books[i].isbn << "\"\n";
        out << "  }";
        if (i != books.size() - 1) out << ",";
        out << "\n";
    }
    out << "]";
    out.close();
    cout << "Done! " << books.size() <<  " books added to authors.json" << "\n";
    return 0;
}