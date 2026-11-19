#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool available;
};

class Library {
private:
    map<int, Book> books;
    const string filename = "books.csv";

    string toLower(string str) const {
        transform(str.begin(), str.end(), str.begin(),
                  [](unsigned char c) { return tolower(c); });
        return str;
    }

    string sanitizeCSV(string text) const {
        replace(text.begin(), text.end(), ',', ';');
        return text;
    }

public:
    Library() {
        loadFromFile();
    }

    void loadFromFile() {
        ifstream file(filename);
        if (!file.is_open()) {
            return;
        }

        books.clear();
        string line;
        bool isFirstLine = true;

        while (getline(file, line)) {
            if (line.empty()) continue;

            if (isFirstLine) {
                isFirstLine = false;
                if (line.rfind("ID,", 0) == 0) continue;
            }

            stringstream ss(line);
            string idStr, title, author, availStr;

            if (getline(ss, idStr, ',') &&
                getline(ss, title, ',') &&
                getline(ss, author, ',') &&
                getline(ss, availStr, ',')) {
                try {
                    Book b;
                    b.id = stoi(idStr);
                    b.title = title;
                    b.author = author;
                    b.available = (availStr == "1" || toLower(availStr) == "true");
                    books[b.id] = b;
                } catch (...) {
                    continue;
                }
            }
        }
        file.close();
    }

    void saveToFile() const {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Could not save data to " << filename << "\n";
            return;
        }

        file << "ID,Title,Author,Available\n";
        for (const auto& pair : books) {
            const Book& b = pair.second;
            file << b.id << ","
                 << sanitizeCSV(b.title) << ","
                 << sanitizeCSV(b.author) << ","
                 << (b.available ? "1" : "0") << "\n";
        }
        file.close();
    }

    void addBook(int id, const string& title, const string& author) {
        if (books.find(id) != books.end()) {
            cout << "Book ID " << id << " already exists\n";
            return;
        }

        if (title.empty() || author.empty()) {
            cout << "Title and author cannot be empty\n";
            return;
        }

        books[id] = {id, title, author, true};
        saveToFile();
        cout << "Book " << title << " added and saved\n";
    }

    void searchById(int id) const {
        auto it = books.find(id);
        if (it == books.end()) {
            cout << "Book ID " << id << " not found\n";
            return;
        }

        const Book& b = it->second;
        cout << "\nBook Details\n"
             << "ID " << b.id << "\n"
             << "Title " << b.title << "\n"
             << "Author " << b.author << "\n"
             << "Status " << (b.available ? "Available" : "Issued") << "\n";
    }

    void searchByKeyword(const string& keyword) const {
        string query = toLower(keyword);
        bool found = false;

        cout << "\nSearch Results\n";
        for (const auto& pair : books) {
            const Book& b = pair.second;
            if (toLower(b.title).find(query) != string::npos ||
                toLower(b.author).find(query) != string::npos) {
                cout << b.id << " " << b.title << " by " << b.author
                     << " " << (b.available ? "Available" : "Issued") << "\n";
                found = true;
            }
        }

        if (!found) {
            cout << "No matching book found for " << keyword << "\n";
        }
    }

    void listBooks() const {
        if (books.empty()) {
            cout << "Library is empty please add some books first\n";
            return;
        }

        cout << "\n" << left
             << setw(8)  << "ID"
             << setw(30) << "Title"
             << setw(25) << "Author"
             << setw(12) << "Status" << "\n\n";

        for (const auto& pair : books) {
            const Book& b = pair.second;
            cout << left
                 << setw(8)  << b.id
                 << setw(30) << b.title.substr(0, 28)
                 << setw(25) << b.author.substr(0, 23)
                 << setw(12) << (b.available ? "Available" : "Issued") << "\n";
        }
    }

    void issueBook(int id) {
        auto it = books.find(id);
        if (it == books.end()) {
            cout << "Unknown Book ID " << id << "\n";
            return;
        }

        if (!it->second.available) {
            cout << it->second.title << " is already issued\n";
            return;
        }

        it->second.available = false;
        saveToFile();
        cout << it->second.title << " has been issued\n";
    }

    void returnBook(int id) {
        auto it = books.find(id);
        if (it == books.end()) {
            cout << "Unknown Book ID " << id << "\n";
            return;
        }

        if (it->second.available) {
            cout << it->second.title << " is already available in the library\n";
            return;
        }

        it->second.available = true;
        saveToFile();
        cout << it->second.title << " has been returned\n";
    }
};

int getValidInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input please enter a number only\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    Library lib;
    int choice;

    while (true) {
        cout << "\nLibrary Management System\n"
             << "1 Add Book\n"
             << "2 Search Book by ID\n"
             << "3 Search Book by Title or Author\n"
             << "4 List All Books\n"
             << "5 Issue Book\n"
             << "6 Return Book\n"
             << "7 Exit\n";

        choice = getValidInt("Choose an option from 1 to 7 ");

        switch (choice) {
            case 1: {
                int id = getValidInt("Enter book ID ");
                string title, author;
                cout << "Enter book title ";
                getline(cin, title);
                cout << "Enter author name ";
                getline(cin, author);
                lib.addBook(id, title, author);
                break;
            }
            case 2: {
                int id = getValidInt("Enter book ID to search ");
                lib.searchById(id);
                break;
            }
            case 3: {
                string keyword;
                cout << "Enter title or author name ";
                getline(cin, keyword);
                lib.searchByKeyword(keyword);
                break;
            }
            case 4:
                lib.listBooks();
                break;
            case 5: {
                int id = getValidInt("Enter book ID to issue ");
                lib.issueBook(id);
                break;
            }
            case 6: {
                int id = getValidInt("Enter book ID to return ");
                lib.returnBook(id);
                break;
            }
            case 7:
                cout << "Data saved exiting program\n";
                return 0;
            default:
                cout << "Wrong choice please select a number between 1 and 7\n";
        }
    }
}
