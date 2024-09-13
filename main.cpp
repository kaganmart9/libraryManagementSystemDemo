#include <iostream>
#include <vector>
#include <string>

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
};

// Class representing the library system
class Library
{
private:
    vector<Book> books;
    vector<Member> members;

public:
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
};

// TEST CASES
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

    return 0;
}
