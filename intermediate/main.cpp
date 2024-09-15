#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Class representing a book in the library
class Book
{
public:
    string title;
    string author;
    string ISBN;
    bool isBorrowed;

    // Constructor to initialize a book object
    Book(string t, string a, string i) : title(t), author(a), ISBN(i), isBorrowed(false) {}

    // Method to display book details
    void display()
    {
        cout << "Title: " << title << ", Author: " << author << ", ISBN: " << ISBN << ", Borrowed: " << (isBorrowed ? "Yes" : "No") << endl;
    }
};

// Class representing a library member
class Member
{
public:
    string name;
    int memberId;
    vector<Book> borrowedBooks;

    // Constructor to initialize a member object
    Member(string n, int id) : name(n), memberId(id) {}

    // Method to display member details
    void display()
    {
        cout << "Name: " << name << ", Member ID: " << memberId << endl;
    }
};

// Class representing the library system
class Library
{
private:
    vector<Book> books;
    vector<Member> members;

    // Method to load books from file
    void loadBooks()
    {
        ifstream file("books.txt");
        if (file.is_open())
        {
            string title, author, ISBN;
            bool isBorrowed;
            while (file >> title >> author >> ISBN >> isBorrowed)
            {
                books.push_back(Book(title, author, ISBN));
                books.back().isBorrowed = isBorrowed;
            }
            file.close();
        }
    }

    // Method to save books to file
    void saveBooks()
    {
        ofstream file("books.txt");
        if (file.is_open())
        {
            for (auto &book : books)
            {
                file << book.title << " " << book.author << " " << book.ISBN << " " << book.isBorrowed << endl;
            }
            file.close();
        }
    }

    // Method to load members from file
    void loadMembers()
    {
        ifstream file("members.txt");
        if (file.is_open())
        {
            string name;
            int memberId;
            while (file >> name >> memberId)
            {
                members.push_back(Member(name, memberId));
            }
            file.close();
        }
    }

    // Method to save members to file
    void saveMembers()
    {
        ofstream file("members.txt");
        if (file.is_open())
        {
            for (auto &member : members)
            {
                file << member.name << " " << member.memberId << endl;
            }
            file.close();
        }
    }

public:
    // Constructor to initialize the library system
    Library()
    {
        loadBooks();
        loadMembers();
    }

    // Destructor to save data before exiting
    ~Library()
    {
        saveBooks();
        saveMembers();
    }

    // Method to add a book to the library
    void addBook(Book book)
    {
        books.push_back(book);
    }

    // Method to add a member to the library
    void addMember(Member member)
    {
        members.push_back(member);
    }

    // Method to borrow a book from the library
    void borrowBook(int memberId, string ISBN)
    {
        for (auto &book : books)
        {
            if (book.ISBN == ISBN && !book.isBorrowed)
            {
                for (auto &member : members)
                {
                    if (member.memberId == memberId)
                    {
                        book.isBorrowed = true;
                        member.borrowedBooks.push_back(book);
                        cout << "Book borrowed successfully!" << endl;
                        return;
                    }
                }
            }
        }
        cout << "Book not available or member not found!" << endl;
    }

    // Method to return a borrowed book to the library
    void returnBook(int memberId, string ISBN)
    {
        for (auto &member : members)
        {
            if (member.memberId == memberId)
            {
                for (auto it = member.borrowedBooks.begin(); it != member.borrowedBooks.end(); ++it)
                {
                    if (it->ISBN == ISBN)
                    {
                        it->isBorrowed = false;
                        member.borrowedBooks.erase(it);
                        cout << "Book returned successfully!" << endl;
                        return;
                    }
                }
            }
        }
        cout << "Book not found in member's borrowed list!" << endl;
    }

    // Method to search for a book by title
    void searchBookByTitle(string title)
    {
        for (auto &book : books)
        {
            if (book.title == title)
            {
                book.display();
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    // Method to search for a member by name
    void searchMemberByName(string name)
    {
        for (auto &member : members)
        {
            if (member.name == name)
            {
                member.display();
                return;
            }
        }
        cout << "Member not found!" << endl;
    }
};

int main()
{
    // Create a library object
    Library library;

    // Add books to the library
    library.addBook(Book("The Great Gatsby", "F. Scott Fitzgerald", "123456789"));
    library.addBook(Book("1984", "George Orwell", "987654321"));

    // Add members to the library
    library.addMember(Member("John Doe", 1));
    library.addMember(Member("Jane Smith", 2));

    // Test borrowing a book
    library.borrowBook(1, "123456789"); // Should succeed
    library.borrowBook(1, "123456789"); // Should fail (already borrowed)
    library.borrowBook(2, "987654321"); // Should succeed

    // Test returning a book
    library.returnBook(1, "123456789"); // Should succeed
    library.returnBook(1, "123456789"); // Should fail (already returned)
    library.returnBook(2, "987654321"); // Should succeed

    // Test invalid scenarios
    library.borrowBook(3, "123456789"); // Should fail (invalid member)
    library.returnBook(2, "111111111"); // Should fail (invalid ISBN)

    // Test searching for a book
    library.searchBookByTitle("1984");         // Should find the book
    library.searchBookByTitle("Unknown Book"); // Should not find the book

    // Test searching for a member
    library.searchMemberByName("John Doe");       // Should find the member
    library.searchMemberByName("Unknown Member"); // Should not find the member

    return 0;
}
