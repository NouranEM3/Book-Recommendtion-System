// Nouran Mahfouz
// 4/11/24
// File: RatingList.cpp
// Implementation file for the RatingList class that manages a 2D dynamic array, that holds each member's rating for a
//      list of books , each row represents a member and each column represents a book. The array is populated with
//      members ratings. It provides methods for adding a book, a member or a rate, and holds number of books and
//      members in the list. Besides allows resizing list if number of elements exceeds list capacity.

#include "RatingList.h"
#include <sstream>
#include <vector>

RatingList::RatingList(int m, int b)
{
    rlist = new int * [m];
    for(int i = 0; i < m; i++)
    {
        rlist[i] = new int[b];
    }
        mCapacity = m;
        bCapacity = b;
        numMembers = 0;
        numBooks = 0;
}

RatingList::~RatingList()
{
    for(int i = 0; i < mCapacity; i++)
        delete [] rlist[i];

    delete [] rlist;
}

RatingList::RatingList(const RatingList &obj)
{
    // assign fields values  (from obj)
    mCapacity = obj.mCapacity;
    bCapacity = obj.bCapacity;
    numBooks = obj.numBooks;
    numMembers = obj.numMembers;

    // allocate memory for rows based on new capacity
    rlist = new int* [mCapacity];

    // allocate memory for columns based on new capacity
    for(int i = 0; i < mCapacity; i++)
        rlist[i] = new int[bCapacity];

    // copy over elements (from obj)
    for(int m = 0; m < mCapacity; m++){
        for(int b = 0; b < bCapacity; b++){
            rlist[m][b] = obj.rlist[m][b];
        }
    }
}

RatingList& RatingList::operator=(const RatingList &obj)
{
    if(this != &obj)
    {
        // deallocate memory
        for(int i = 0; i < mCapacity; i++){
            delete [] rlist[i];
        }
        delete [] rlist;
    }
    // assign numMembers and capacity (from obj)
    mCapacity = obj.mCapacity;
    bCapacity = obj.bCapacity;
    numMembers = obj.numMembers;
    numBooks = obj.numBooks;

    // allocate memory based on new capacity
    rlist = new int* [mCapacity];
    for(int i = 0; i < mCapacity; i++)
        rlist[i] = new int[bCapacity];

    // copy over elements (from obj)
    for(int m = 0; m < mCapacity; m++)
    {
        for (int b = 0; b < bCapacity; b++)
        {
            rlist[m][b] = obj.rlist[m][b];
        }
    }
    return *this;
}

void RatingList::setBookCount(int bc)
{
    numBooks = bc;
}

void RatingList::addMember()
{
    // If list is full
    if(numMembers >= mCapacity)
        resize();
    numMembers++;
}

void RatingList:: addBook()
{
    // If list is full
    if(numBooks >= bCapacity)
        resize();
    numBooks++;
}

void RatingList::addRate(int mID, int bISBN, int r)
{
    rlist[mID][bISBN] = r;
}

int RatingList::getRate(int mID, int bISBN)
{
    return rlist[mID][bISBN];
}

int RatingList::getMembersCount() const
{
    return numMembers;
}

int RatingList::getBooksCount() const
{
    return numBooks;
}

bool RatingList::empty() const
{
    return(numMembers == 0 && numBooks == 0);
}

int RatingList::size() const
{
    return numMembers * numBooks;
}

string RatingList::to_string() const
{
    stringstream ss;

    for (int m = 0; m < numMembers; m++)
    {
        ss << "Member ID: " << m << " ratings: " << "\n";
        for (int b = 0; b < numBooks; b++)
        {
            ss << "Book ISBN: " << b << " rate: " << rlist[m][b] << endl;
            rlist[m][b] = rlist[m][b];
        }
        ss << endl;
    }
    return ss.str();
}

void RatingList::resize()
{
    // update capacity depending you want to add a member or book
    if (numMembers >= mCapacity)
    {
        mCapacity *= 2;
    } else if (numBooks >= bCapacity)
    {
        bCapacity *= 2;
    }

    // create new array based on updated capacity
    int **temp = new int *[mCapacity];
    for (int i = 0; i < mCapacity; i++)
        temp[i] = new int[bCapacity];

    // copy old array values to new array
    for (int m = 0; m < numMembers; m++)
    {
        for (int b = 0; b < numBooks; b++)
            temp[m][b] = rlist[m][b];
    }

    // delete old array
    for (int i = 0; i < numMembers; i++)
    {
        delete[] rlist[i];
    }
    delete[] rlist;

    // reassign old array to new array
    rlist = temp;
}

int RatingList::getBestMatch(int mID) const
{
    int bestMatchID;            // Stores member ID with best match with the user
    vector<int> vUser;          // Holds user ratings
    vector<int> vCompare;       // Temporarily holds members ratings to calculate dot product with user

    int product;        // Holds dot product of 2 users ratings
    int maxSimilarity = -200;   // Holds highest dot product value(initialized with a very low value

    // Populate user's vector with his ratings
    for(int i = 0; i < numBooks; i++)
    {
        vUser.push_back(rlist[mID][i]);
    }

    for(int i = 0; i < numMembers; i++)
    {
        if( i != mID) {
            vCompare.clear();
            product = 0;
            // populate member vector to compare it with user
            for (int j = 0; j < numBooks; j++)
                vCompare.push_back(rlist[i][j]);
            // Calculate dot product
            for (int j = 0; j < numBooks; j++)
                product = product + vUser[j] * vCompare[j];

            // Store highest dot product and store its member ID
            if (maxSimilarity < product)
            {
                maxSimilarity = product; // Highest dot product
                bestMatchID = i;         // ID with the highest dot product
            }
        }
    }
    return bestMatchID;
}
