// Nouran Mahfouz
// 4/11/24
// File: BookList.h
// Specification file for the BookList class that manages a blist of books, each represented by an ISBN, author, title,
//    and year. It provides methods for adding books, searching for books by ISBN, checking if the blist is empty,
//    getting the size of the blist, and converting the blist to a string.

#ifndef P1_BOOKLIST_H
#define P1_BOOKLIST_H

#include <string>
using namespace std;

class BookList {
public:
    BookList(int);        // Constructor
    ~BookList();          // Destructor
    BookList(const BookList &);               // Copy constructor
    BookList& operator=(const BookList &);    // Overloaded = operator

    int get(int) const;         // Finds a book in array, return index  where found or -1 if not found
    int getBookCount();         // Returns number of books stored in the list
    string getBook(int) const;  // Finds a book in the list and returns book info in a string form

    bool empty() const;         // Determines if booklist is empty or not
    string to_string() const;   // Returns a string representation of all elements in the book list

    void add(int, string, string, string);          // add book element to array

private:
    struct Book{
        int isbn;
        string author;
        string title;
        string year;
    };

    Book * blist;       // Pointer to the array
    int capacity;       // Capacity of array
    int numBooks;       // Number of books
    void resize();      // Resize blist array if number of books exceeds array assigned capacity
};

#endif //P1_BOOKLIST_H
