// Nouran Mahfouz
// 4/13/24
// File: p1.cpp

// Purpose: This program implements a book recommendation system where users can create accounts, add books, rate books,
//          and receive recommendations based on their ratings. It utilizes classes such as BookList, MemberList, and
//          RatingList to manage data and interactions.

// Inputs:
// Data files paths for books and member ratings.
// Menu choices: Users select options from the main menu and member menu by entering corresponding numbers.
// New member details: When adding a new member, the user enters the member's name.
// New book details: When adding a new book, the user enters the book's author, title, and year.
// Member account: When logging in, the user enters their member account number.
// Book ISBN: When rating a book, the user enters the ISBN of the book they want to rate.
// Rating choice: Users choose a rating from the rating list when rating a book.

// Outputs:
// Welcome message: Displayed at the start of the program.
// Goodbye message: Displayed when the user chooses to quit.
// Rating list: Displayed to guide users when rating a book.
// Book list: Displayed when adding a new book, viewing ratings, or calculating recommendations.
// Member list: Displayed when adding a new member or viewing ratings.
// Ratings: Displayed when viewing ratings.
// Recommendations: Displayed when calculating recommendations, showing books that have been highly rated by a member
// with similar tastes.

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "BookList.h"
#include "MemberList.h"
#include "RatingList.h"

// Displays a welcome message at the start of the program.
void displayWelcomeMessage();
// Displays a goodbye message when the user chooses to quit.
void displayGoodbyeMessage();
// Displays a list of rating options for users to choose from.
void displayRatingList();

// Loads data from external files into corresponding lists.
void loadExternalData(BookList &, MemberList &, RatingList &);
// Populates the BookList object with data from a file.
void populateBookList(string, BookList &);
// Populates the MemberList and RatingList objects with data from a file.
void populateMemberRatingList(string, MemberList &, RatingList &);
// Displays number of Members and number of Books when program is initiated.
void printBooksMembersNumber(int, int, MemberList, RatingList);

int displayMainMenu();      // Displays the main menu and returns the user's choice.
int displayMemberMenu();    // Displays the member-specific menu and returns the user's choice.

// Adds a new member to the MemberList and updates the RatingList accordingly.
void addNewMember(MemberList &, RatingList &);
// Adds a new book to the BookList and updates the RatingList accordingly.
void addNewBook(BookList &, RatingList &);

// Allows a member to rate a book and updates the RatingList accordingly.
void rateBook(int, BookList &, RatingList &);
// Displays the ratings given by a specific member.
void viewRatings(int, BookList &, MemberList &, RatingList &);
// Calculates and displays book recommendations based on a member's ratings.
void calculateRecommendations(int, BookList &, MemberList &, RatingList &);

int main() {
    // Constants
    const int BOOKS_CAPACITY = 56;
    const int MEMBERS_CAPACITY = 87;

    // Variables
    string filename;
    bool login = false;      // To allow user to login and logout
    bool quit = false;       // To quit profram
    int memberAccount;       // Holds user ID number
    int menuChoice;          // Stores user choices from menu

    // Create instances of required classes
    MemberList mList(MEMBERS_CAPACITY);
    BookList bList(BOOKS_CAPACITY);
    RatingList rList(MEMBERS_CAPACITY, BOOKS_CAPACITY);

    // Display welcome message
    displayWelcomeMessage();

    // Load data from external files
    loadExternalData(bList, mList, rList);

    // Main program loop
    while(!quit)
    {
        menuChoice = displayMainMenu();
        // Switch depending on user choice
        switch (menuChoice)
        {
            // Add new member
            case 1:
                addNewMember(mList, rList);
                break;
            // Add new book
            case 2:
                addNewBook(bList, rList);
                break;
            // Login
            case 3:
                cout << endl;
                cout << "Enter member account: ";
                cin >> memberAccount;
                cin.ignore();
                // Check if member account number exists
                if (memberAccount < mList.getMemberCount())
                {
                    cout << endl;
                    cout <<  "***** Welcome " << mList.getMemberName(memberAccount) << "! *****" << endl;
                    cout << "***** You are logged in! *****" << endl;
                    login = true;
                }
                // If user doesn't have account, ask him to create an account
                else
                    cout << "Account number doesn't exist!\n Add a new member to login.";

                break;
            case 4:
                displayGoodbyeMessage();
                quit = true;
                break;

            // If user entered an invalid entry
            default:
                cout << "Invalid Entry!" << endl << "Choose a number from the menu." << endl;
                break;
        }
        // Member-specific menu loop
        while(login)
        {
            menuChoice = displayMemberMenu();
            switch (menuChoice)
            {
                case 1:
                    addNewMember(mList, rList);

                    break;
                case 2:
                    addNewBook(bList, rList);

                    break;
                case 3:
                    rateBook(memberAccount, bList, rList);

                    break;
                case 4:
                    viewRatings(memberAccount, bList, mList, rList);
                    break;
                case 5:
                    calculateRecommendations(memberAccount, bList,mList,rList);
                    break;

                // Logout
                case 6:
                    login = false;
                    break;
                default:
                    cout << "Invalid Entry!" << endl << "Choose a number from the menu." << endl;
                    break;
            }
        }
    }
    return 0;
}
//----------------------------------------------------------------------------------------------------------------------
void displayWelcomeMessage(){
    cout << endl;
    cout << "Welcome to the Book Recommendation Program." << endl;
    cout << "Create an account and add your favourite books!" << endl;
    cout << "Rate books you have read and get book recommendations from members with your best match! " << endl;
    cout << endl;
}

void populateMemberRatingList(string fname, MemberList &mList, RatingList &rList)
{
    int count = 0;              // counts number of lines in file to decide where to store data in members array
    // or ratings array
    int memberCount = 0;        // Keeps track of number of members read from file
    int bookCount;              // Keeps track of number of books rated read from file

    int rate;                   // Hold rate value read from file after converting it to integer
    string line;                // Holds whole line read from file as a string
    string value;               // Holds rate value read from file as a string before converting to integer

    ifstream inFile;            // Input file object to read from file

    inFile.open(fname);      // Open file
    if(inFile.is_open())       // verify file is opened successfully
    {
        while(getline(inFile, line) )    //as long as data exists
        {
            if (count % 2 == 0)               // if count is even number then the data is a members name
            {
                mList.add(memberCount, line); // addRate data to members array
                rList.addMember();
                memberCount++;                //count member
            }
            else                              // if count is odd then data is a string of book ratings
            {
                bookCount = 0;                // initialize bookCount (to store all book ratings for each member)
                istringstream iss(line);   // to separate each character from string create an istringstream object
                                                    // and pass the string to it
                while (iss >> value)          // as long as string has characters
                {
                    stringstream s;           // create stringstream buffer to convert characters to integers
                    s << value;
                    s >> rate;
                    // store rate values extracted to ratings array
                    rList.addRate(memberCount - 1, bookCount, rate);
                    bookCount++;                          // book count
                }
            }
            count++;
        }
    }
    else        // if failed to open file
    {
        cout << "ERROR: cannot open file.\n";
    }

    rList.setBookCount(bookCount);

    // call print arrays to print arrays after populated with data read from files
    printBooksMembersNumber(memberCount, bookCount, mList, rList);

    inFile.close();
}

void populateBookList(string fname, BookList &bl)
{
    int bookCount = 0;
    string line, author, title, year, str;
    ifstream inFile;            // Input file object to read from file

    inFile.open(fname);      // Open file
    if(inFile.is_open())       // verify file is opened successfully
    {
        while(getline(inFile, line) )   //as long as data exists
        {
            stringstream s(line);
            getline(s, author, ',');
            getline(s, title, ',');
            getline(s, year, ',');
            bl.add(bookCount, author, title, year);
            bookCount++;
        }
    }
    else        // if failed to open file
    {
        cout << "ERROR: cannot open file.\n";
    }
}

void loadExternalData(BookList &bl, MemberList &ml, RatingList &rl)
{
    string bookFile;
    string ratingFile;
    cout << "Enter books file: ";
    cin >> bookFile;
    cout << "Enter ratings file: ";
    cin >> ratingFile;
    cin.ignore();

    populateBookList( bookFile, bl);
    populateMemberRatingList(ratingFile, ml, rl);
}

int displayMainMenu(){
    int input;
    cout << endl;
    cout << "*************** MENU ***************" << endl;
    cout << "* 1. Add a new member              *" << endl;
    cout << "* 2. Add a new book                *" << endl;
    cout << "* 3. Login                         *" << endl;
    cout << "* 4. Quit                          *" << endl;
    cout << "************************************" << endl;
    cout << endl;
    cout << "Enter a menu option: ";
    cin >> input;
    return input;
}

int displayMemberMenu(){
    int input;
    cout << endl;
    cout << "*************** MENU ***************" << endl;
    cout << "* 1. Add a new member              *" << endl;
    cout << "* 2. Add a new book                *" << endl;
    cout << "* 3. Rate book                     *" << endl;
    cout << "* 4. View ratings                  *" << endl;
    cout << "* 5. See recommendations           *" << endl;
    cout << "* 6. Logout                        *" << endl;
    cout << "************************************" << endl;
    cout << endl;
    cout << "Enter a menu option: ";
    cin >> input;
    return input;
}

void addNewMember(MemberList &ml, RatingList &rl)
{
    string newMemberName;
    int accountNumber;

    cout << endl;
    cout << "Enter the name of the new member: ";
    cin.ignore();
    getline(cin, newMemberName);

    // assign account number to new member
    accountNumber = ml.getMemberCount();
    // add member to MemberList
    ml.add(accountNumber, newMemberName);
    // add member in RatingList
    rl.addMember();

    cout << endl;
    // display that member added successfully with new members data and new account number assigned to him
    cout << "**************************************************" << endl;
    cout << " " << newMemberName << " (account #: " << accountNumber << " ) is added." << endl;
    cout << "**************************************************" << endl;
}

void addNewBook(BookList &bl, RatingList &rl)
{
    string author, bookName, year;
    int bookISBN;

    cout << endl;
    cout << "Enter the author of the new book: ";
    cin.ignore();
    getline(cin, author);
    cout << "Enter the title of the new book: ";
    getline(cin, bookName);
    cout << "Enter the year (or range of years) of the new book: ";
    getline(cin, year);

    // assign new book an ISBN
    bookISBN = bl.getBookCount();
    // add book to BookList
    bl.add(bookISBN,author, bookName, year);
    // add book to RatingList
    rl.addBook();
    cout << endl;

    // display that book is added successfully with new book data and new ISBN number assigned to it
    cout << "***************************************************************************************" << endl;
    cout << " " << bookISBN << ", " << author << ", " << bookName << ", " << year << " is added." << endl;
    cout << "***************************************************************************************" << endl;
}

// Displays number of books and members when program starts
void printBooksMembersNumber(int mCount, int bCount, MemberList m, RatingList r)
{
    cout << endl;
    cout << "# of books: " << bCount << endl;
    cout << "# of members: " << mCount << endl;
}

void rateBook(int mA, BookList &bl, RatingList &rl)
{
    int bookISBN;
    int oldRate, newRate;
    char yesOrNo;

    cout << endl;
    cout << "Enter the ISBN for the book you'd like to rate: ";
    cin >> bookISBN;
    cin.ignore();
    cout << endl;
    oldRate = rl.getRate(mA, bookISBN);

    // If book has no rate
    if (oldRate == 0) {
        displayRatingList();
        cout << "Choose your rating: ";
        cin >> newRate;
        cin.ignore();

        rl.addRate(mA, bookISBN, newRate);
        cout << endl;
        cout << "Your new rating for: " << endl;
        cout << "      " << bl.getBook(bookISBN) << ". is: ";
        cout << " *** " << rl.getRate(mA, bookISBN) << " *** " << endl;

      // if book was already rated
    } else {
        cout << "Your current rating for: " << endl;
        cout << "      " << bl.getBook(bookISBN) << ". is: ";
        cout << " *** " << rl.getRate(mA, bookISBN) << " ***" << endl;
        cout << endl;
        cout << "Would you like to re-rate this book (y/n)? ";
        cin >> yesOrNo;
        cin.ignore();

        if (yesOrNo == 'y')
        {
            displayRatingList();
            cout << "Choose your rating: ";
            cin >> newRate;
            cin.ignore();
            cout << endl;

            rl.addRate(mA, bookISBN, newRate);
            cout << "Your new rating for: " << endl;
            cout << "      " << bl.getBook(bookISBN) << ". is: ";
            cout << " *** " << rl.getRate(mA, bookISBN) << " *** " << endl;
        }
    }
}

void displayRatingList(){
    cout << endl;
    cout << "***************** Rating List *****************" << endl;
    cout << "* -5 ---> Hated it!                           *" << endl;
    cout << "* -3 ---> Didn't like it!                     *" << endl;
    cout << "*  0 ---> Haven't read it!                    *" << endl;
    cout << "*  1 ---> ok - neither hot nor cold about it  *" << endl;
    cout << "*  3 ---> Liked it!                           *" << endl;
    cout << "*  5 ---> Really liked it!                    *" << endl;
    cout << "***********************************************" << endl;
    cout << endl;
}

void viewRatings(int mA, BookList &bl, MemberList &ml, RatingList &rl)
{
    int numberOfBooks = bl.getBookCount();
    cout << endl;
    cout << "************* " << ml.getMemberName(mA) << " Ratings ************* " << endl;
    cout << endl;

    cout << "        Books you really liked (Rated 5)" << endl;
    cout << "**********************************************************" << endl;

    for(int i = 0; i < numberOfBooks; i++ )
    {
        if(rl.getRate(mA, i) == 5)
        {
            cout << bl.getBook(i) << " ----> Rating : " << rl.getRate(mA, i) << endl;
        }
    }
    cout << endl;
    cout << "        Books you liked (Rated 3)" << endl;
    cout << "**********************************************************" << endl;
    for(int i = 0; i < numberOfBooks; i++ )
    {
        if(rl.getRate(mA, i) == 3)
        {
            cout << bl.getBook(i) << " ----> Rating : " << rl.getRate(mA, i) << endl;
        }
    }
    cout << endl;
    cout << "        Books that are just ok (Rated 1)" << endl;
    cout << "**********************************************************" << endl;

    for(int i = 0; i < numberOfBooks; i++ )
    {
        if(rl.getRate(mA, i) == 1)
        {
            cout << bl.getBook(i) << " ----> Rating : " << rl.getRate(mA, i) << endl;
        }
    }
    cout << endl;
    cout << "        Books you didn't read" << endl;
    cout << "**********************************************************" << endl;

    for(int i = 0; i < numberOfBooks; i++ )
    {
        if(rl.getRate(mA, i) == 0)
        {
            cout << bl.getBook(i) << " ----> Rating : " << rl.getRate(mA, i) << endl;
        }
    }
}

void calculateRecommendations(int mA, BookList &bl, MemberList &ml, RatingList &rl)
{
    int bestMatchID = rl.getBestMatch(mA);
    int numberOfBooks = bl.getBookCount();
    cout << endl;
    cout << "******* You have similar taste in books as " << ml.getMemberName(bestMatchID) << "! *******" << endl;

    cout << endl;
    cout << "        These are the books they really liked (Rated 5)" << endl;
    cout << "**********************************************************" << endl;

    for(int i = 0; i < numberOfBooks; i++ )
    {
        if(rl.getRate(bestMatchID, i) == 5)
        {
            cout << bl.getBook(i) << " ----> Rating : " << rl.getRate(bestMatchID, i) << endl;
        }
    }
    cout << endl;
    cout << "        These are the books they liked (Rated 3)" << endl;
    cout << "**********************************************************" << endl;
    for(int i = 0; i < numberOfBooks; i++ )
    {
        if(rl.getRate(bestMatchID, i) == 3)
        {
            cout << bl.getBook(i) << " ----> Rating : " << rl.getRate(bestMatchID, i) << endl;
        }
    }
}

void displayGoodbyeMessage(){
    cout << endl;
    cout << "********************************************************" << endl;
    cout << "* Thank you for using the Book Recommendation Program! *" << endl;
    cout << "********************************************************" << endl;
}