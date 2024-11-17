// Nouran Mahfouz
// 4/11/24
// File: RatingList.h
// Specification file for the RatingList class that manages a 2D dynamic array, that holds each member's rating for a
//      list of books , each row represents a member and each column represents a book. The array is populated with
//      members ratings. It provides methods for adding a book, a member or a rate, and holds number of books and
//      members in the list. Besides allows resizing list if number of elements exceeds list capacity.


#ifndef P1_RATINGLIST_H
#define P1_RATINGLIST_H

#include <string>
using namespace std;

class RatingList {
public:
    RatingList(int, int);       // Constructor
    ~RatingList();              // Destructor
    RatingList(const RatingList &);             // Copy constructor
    RatingList& operator=(const RatingList &);  // Overloaded = operator

    void setBookCount(int bc);      // Gets number of books from driver

    void addMember();       // When a member is added checks if resize is needed
    void addBook();         // When a book is added checks if resize is needed
    void addRate(int mID, int bISBN, int r);    // Add members rate to list

    int getRate(int mID, int bISBN);    // Return rate associated with given member ID and book ISBN
    int getBooksCount() const;          // Returns number of book stored
    int getMembersCount() const;        // Returns number of members stored
    int getBestMatch(int) const;        // Returns member ID that has best rating match with the given member


    bool empty() const;         // Checks if the list is empty or not
    int size() const;           // Number of members in array
    string to_string() const;   // Returns string representation of all ratings in the list

private:
    int ** rlist;
    int mCapacity; // members capacity
    int numMembers; // number of members
    int bCapacity;      // books capacity
    int numBooks;       // number of books

    void resize();
};

#endif //P1_RATINGLIST_H
