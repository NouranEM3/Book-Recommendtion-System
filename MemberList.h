// Nouran Mahfouz
// 4/11/24
// File: MemberList.h
// Specification file for the MemberList class that manages a list of members, each represented by an ID and a name.
//    It provides methods for adding members to list, searching for books by ISBN, checking if the list is empty,
//    getting the list capacity, getting number of members, and displays all members in the list in a string
//    representation.

#ifndef P1_MEMBERLIST_H
#define P1_MEMBERLIST_H

#include <string>
using namespace std;

class MemberList {
public:
    MemberList(int);           // Constructor
    ~MemberList();             // Destructor
    MemberList(const MemberList &);               // Copy constructor
    MemberList& operator=(const MemberList &);    // Overloaded = operator

    void add(int, string);          // Add a member to the list

    int get(int) const;                 // Finds a member in array; return index where found or -1 if not found
    int getMemberCount() const;         // Returns number of members registered
    string getMemberName(int) const;    // Returns a members name for a given ID

    bool empty() const;        // determines if blist is empty or not
    string to_string() const;  // returns string representation of all mebmers in the list

private:
    struct Member{
        int id;
        string name;
    };

    Member * mlist;        // Pointer to the array
    int capacity;          // capacity of array
    int numMembers;        // Number of members
    void resize();
};

#endif //P1_MEMBERLIST_H
