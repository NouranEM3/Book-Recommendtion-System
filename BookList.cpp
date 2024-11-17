// Nouran Mahfouz
// 4/11/24
// File: BookList.cpp
// Implementation file for the BookList class that manages a list of books, by providing methods for  adding,
//      searching, checking if the list is empty, getting the size of the list, and converting the list to a string.

#include "BookList.h"
#include <sstream>

BookList::BookList(int c)
{
    blist = new Book[c];
    capacity = c;
    numBooks = 0;
}

BookList::~BookList()
{
    delete [] blist;
}

BookList::BookList(const BookList &obj)
{
    // assign numBooks and capacity (from obj)
    capacity = obj.capacity;
    numBooks = obj.numBooks;

    // allocate memory based on new capacity
    blist = new Book[capacity];

    // copy over elements (from obj)
    for (int i = 0; i < numBooks; i++)
        blist[i] = obj.blist[i];
}

BookList& BookList::operator=(const BookList &obj)
 {
    if (this != &obj) {
        // deallocate memory
        delete [] blist;

        // assign numBooks and capacity (from obj)
        capacity = obj.capacity;
        numBooks = obj.numBooks;

        // allocate memory based on new capacity
        blist = new Book[capacity];

        // copy over elements (from obj)
        for (int i = 0; i < numBooks; i++)
            blist[i] = obj.blist[i];
    }
    return *this;
}

void BookList::add(int isbn, string a, string t, string y)
{
    // If List is full
    if (numBooks >= capacity)
        resize();

    // Create a Book struct with given data
    Book b;
    b.isbn = isbn;
    b.author = a;
    b.title = t;
    b.year = y;
    blist[numBooks++] = b;      // Add Book to list
}

int BookList::get(int isbn) const{
    for (int i = 0; i < numBooks; i++) {
        if (blist[i].isbn == isbn)
            return i;
    }
    return -1;
}

int BookList::getBookCount()
{
    return numBooks;
}

string BookList::getBook(int isbn) const
{
    stringstream ss;
    ss << blist[isbn].isbn << ", " << blist[isbn].author << ", " << blist[isbn].title << ", " << blist[isbn].year;
    return ss.str();
}

bool BookList::empty() const
{
    return numBooks == 0;
}

string BookList::to_string() const
{
    stringstream ss;
    for (int i = 0; i < numBooks; i++)
        ss << blist[i].isbn << ", " << blist[i].author << ", "
           << blist[i].title << ", " << blist[i].year << ", " << endl;
    return ss.str();
}

void BookList::resize()
{
    // update capacity
    capacity *= 2;

    // create new array based on updated capacity
    Book * tempArr = new Book[capacity];

    // copy old array values to new array
    for (int i = 0; i < numBooks; i++)
        tempArr[i] = blist[i];

    // delete old array
    delete [] blist;

    // reassign old array to new array
    blist = tempArr;
}
