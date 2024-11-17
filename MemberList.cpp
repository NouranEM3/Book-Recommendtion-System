// Nouran Mahfouz
// 4/11/24
// File: MemberList.cpp
// Implementation file for the MemberList class that manages a list of members, by providing methods for  adding,
//      searching, checking if the list is empty, getting the size of the list, and converting the list to a string.

#include "MemberList.h"
#include <sstream>

MemberList::MemberList(int c)
{
    mlist = new Member[c];
    capacity = c;
    numMembers = 0;
}

MemberList::~MemberList()
{
    delete [] mlist;
}

MemberList::MemberList(const MemberList &obj)
{
    // assign numMembers and capacity (from obj)
    capacity = obj.capacity;
    numMembers = obj.numMembers;

    // allocate memory based on new capacity
    mlist = new Member[capacity];

    // copy over elements (from obj)
    for (int i = 0; i < numMembers; i++)
        mlist[i] = obj.mlist[i];
}

MemberList& MemberList::operator=(const MemberList &obj)
 {
    if (this != &obj)
    {
        // deallocate memory
        delete [] mlist;

        // assign numMembers and capacity (from obj)
        capacity = obj.capacity;
        numMembers = obj.numMembers;

        // allocate memory based on new capacity
        mlist = new Member[capacity];

        // copy over elements (from obj)
        for (int i = 0; i < numMembers; i++)
            mlist[i] = obj.mlist[i];
    }
    return *this;
}

void MemberList::add(int id, string name)
{
    // If list is full
    if (numMembers >= capacity)
        resize();

    // Create a Member struct with given data
    Member m;
    m.id = id;
    m.name = name;
    mlist[numMembers++] = m;        // Add Member to list
}

int MemberList::get(int id) const
{
    for (int i = 0; i < numMembers; i++)
    {
        if (mlist[i].id == id)
            return i;
    }
    return -1;
}

int MemberList::getMemberCount() const
{
    return numMembers;
}

string MemberList::getMemberName(int i) const
{
    return  mlist[i].name;
}

bool MemberList::empty() const
{
    return numMembers == 0;
}

string MemberList::to_string() const
{
    stringstream ss;
    for (int i = 0; i < numMembers; i++)
        ss << mlist[i].id << ", " << mlist[i].name << endl;
    return ss.str();
}

void MemberList::resize()
{
    // update capacity
    capacity *= 2;

    // create new array based on updated capacity
    Member *tempArr = new Member[capacity];

    // copy old array values to new array
    for (int i = 0; i < numMembers; i++)
        tempArr[i] = mlist[i];

    // delete old array
    delete[] mlist;

    // reassign old array to new array
    mlist = tempArr;
}
