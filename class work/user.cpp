#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Book {
    int pages;
    string name;
    double prise;
    int count;
public:
    Book(string fromFile) {
        auto a = find(fromFile.begin(), fromFile.end(), ';');
        string name(fromFile.begin(), a);
        this->name = name;

        auto b = find(a + 1, fromFile.end(), ';');
        string pages(a + 1, b);
        this->pages = stoi(pages);

        a = find(b + 1, fromFile.end(), ';');
        string prise(b + 1, a);
        this->prise = stod(prise);

        b = find(a + 1, fromFile.end(), ';');
        string count(a + 1, b);
        this->count = stoi(count);

    }
    void printBook() {
        cout << this->name << endl;
        cout << this->pages << endl;
        cout << this->prise << endl;
        cout << this->count << endl;
    }
    bool ifOKtoDel(string name) {
        if (this->name == name)
            return true;
        return false;
    }

    friend ofstream& operator<<(ofstream& file, Book& book) {
        file << book.name << ';';
        file << book.pages << ';';
        file << book.prise << ';';
        file << book.count << ';';
        return file;
    }

    int getCount() { return this->count; }
    void setCount(int Count) { count = Count; }
    int getPrice() { return this->prise; }
};
//Name1;100;15.0;50;
//Name2; 150; 25.0; 100;
//Name3; 200; 20.0; 20;


class User {
    string login;
    string password;
public:

    User(string name, string pass) : login(name), password(pass) {}

    bool LogIn(string log, string pass) {
        if (this->login == log && this->password == pass)
        {
            return true;
        }
        else {
            return false;
        }
    }
    void printUser() {
        cout << this->login << endl;
        cout << this->password << endl;
    }
    virtual void Virtual() = 0;

    ~User() {
        cout << "User dest" << endl;
    }
};

class Admin : public User {
public:
    Admin(string name, string pass) : User(name, pass) {};


    ~Admin() {
        cout << "Admin dest" << endl;
    }
    void Virtual() { cout << "Olec loh"; }
};

class CommonUser : public User {
public:
    CommonUser(string name, string pass) : User(name, pass) {};

    ~CommonUser() {
        cout << "CommonUser dest" << endl;
    }
    void Virtual() { cout << "Olec loh"; }
};

class BlockedUser : public User {
public:
    BlockedUser(string name, string pass) : User(name, pass) {};

    ~BlockedUser() {
        cout << "BlockedUser dest" << endl;
    }
    void Virtual() { cout << "Olec loh"; }
};

string getUserType(const User* user) {
    return typeid(*user).name();
}

int main()
{
    vector<User*> users;
    ifstream file;
    file.open("users.txt");

    if (!file.is_open())
    {
        return 0;
    }

    string line;
    getline(file, line);
    while (!file.eof())
    {
        getline(file, line);
        if (line == "admin")
        {
            string login, pass;

            while (true)
            {
                getline(file, line);
                if (line != "-")
                {
                    login = line;
                }
                else {
                    break;
                }
                getline(file, line);
                if (line != "-")
                {
                    pass = line;
                }
                else {
                    break;
                }



                users.push_back(new Admin(login, pass));
            }
        }
        else if (line == "user")
        {
            string login, pass;

            while (true)
            {
                getline(file, line);
                if (line != "-")
                {
                    login = line;
                }
                else {
                    break;
                }
                getline(file, line);
                if (line != "-")
                {
                    pass = line;
                }
                else {
                    break;
                }

                users.push_back(new CommonUser(login, pass));
            }
        }
        else if (line == "blocked") {
            string login, pass;

            while (true)
            {
                getline(file, line);
                if (line != "-")
                {
                    login = line;
                }
                else {
                    break;
                }
                getline(file, line);
                if (line != "-")
                {
                    pass = line;
                }
                else {
                    break;
                }


                users.push_back(new BlockedUser(login, pass));
            }
        }
    }

    file.close();

    for_each(users.begin(), users.end(), [](auto user) {user->printUser(); });

    string name, password;

    cout << "please enter name: ";
    cin >> name;
    cout << "please enter password: ";
    cin >> password;

    auto it = find_if(users.begin(), users.end(), [name, password](auto user) { return user->LogIn(name, password); });
    bool entered = false;

    if (it != users.end())
    {

        //BlockedUser* Bloc = static_cast<BlockedUser*> (*it);
        if (getUserType(*it) != "class BlockedUser")
        {

            entered = true;
        }
        else {
            cout << "you are blocked" << endl;
            return 0;
        }

    }

    if (!entered) {
        return 0;
    }

    ifstream fileBooks;
    string filepath = "Books.txt";
    fileBooks.open(filepath);

    vector<Book> Books;
    string list;
    while (!fileBooks.eof())
    {
        getline(fileBooks, list);
        Books.push_back(Book(list));
    }
    fileBooks.close();
    vector<Book>::iterator QQ;
    if (getUserType(*it) == "class Admin") {
        bool toExit = false;
        while (!toExit)
        {
            cout << "//////////\n/ MENU /\n//////////";
            cout << "\n1) Print list of books\n2) Add new book\n3) Delate book\nEnter your choice:";
            int choice;
            cin >> choice;
            string finalList;
            string tmpList;
            string name;
            switch (choice)
            {
            case 1:
                for_each(Books.begin(), Books.end(), [](auto Book) {Book.printBook(); });
                break;
            case 2:
                cout << "Enter book`s name:";
                cin >> tmpList;
                finalList = tmpList + ';';

                cout << "\nEnter book`s pages:";
                cin >> tmpList;
                finalList += tmpList + ';';

                cout << "\nEnter book`s prise:";
                cin >> tmpList;
                finalList += tmpList + ';';

                cout << "\nEnter book`s count:";
                cin >> tmpList;
                finalList += tmpList + ';';

                Books.push_back(Book(finalList));
                break;
            case 3:
                cout << "Enter name of book to delate:";
                cin >> name;
                QQ = find_if(Books.begin(), Books.end(), [name](Book book) {return book.ifOKtoDel(name); });
                if (QQ != Books.end()) {
                    Books.erase(QQ);
                }
                else {
                    cout << "Bra, no";
                }
                break;
            case 0:
                toExit = true;
                break;
            default:
                toExit = true;
                break;
            }
            system("pause");
            system("cls");
        }

    }

    else if (getUserType(*it) == "class CommonUser") {
        bool toExit = false;
        while (!toExit)
        {
            cout << "//////////\n/ MENU /\n//////////";
            int choice;
            cout << "\n1) Print list of books\n2) buy book\n Enter your choice:";
            cin >> choice;
            switch (choice) {
            case 0:
                toExit = true;
                break;
            case 1:
                for_each(Books.begin(), Books.end(), [](auto Book) {Book.printBook(); });
                break;
            case 2:
                cout << "Enter name of book to buy:";
                cin >> name;
                QQ = find_if(Books.begin(), Books.end(), [name](Book book) {return book.ifOKtoDel(name); });
                if (QQ != Books.end()) {
                    cout << QQ->getCount();
                    int CC;//count choise 
                    cout << "Enter count of book`s you want";
                    cin >> CC;
                    if (CC > QQ->getCount()) {
                        cout << "Nazar WTF are you doing?!";
                    }
                    else {
                        cout << "it`s cost: " << CC * QQ->getPrice();
                        QQ->setCount(QQ->getCount() - CC);
                        if (QQ->getCount() == 0)
                        {
                            Books.erase(QQ);
                        }
                    }
                }
                else {
                    cout << "Bra, no";
                }
                break;
            }
        }
    }
    ofstream fileB;
    fileB.open(filepath);
    int N = 0;
    for_each(Books.begin(), Books.end(), [&fileB, Books, &N](Book Book) {fileB << Book; N++; if (N < Books.size()) fileB << '\n'; });

}