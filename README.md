# Book Recommendation System

## Overview
This project is a C++ book recommendation system created as part of my Data Structures course. It demonstrates foundational programming concepts such as dynamic memory allocation, file I/O, object-oriented programming, and algorithmic design.

The system provides book recommendations to users based on their ratings and similarity to other users, calculated using vector dot products.

---

## Features
### Book Recommendation Logic:
1. Users rate books using the following scale:
   - **5**: Really liked it
   - **3**: Liked it
   - **1**: Neutral
   - **0**: Haven't read it
   - **-3**: Didn't like it
   - **-5**: Hated it
2. The program calculates similarity between users based on their ratings.
3. Books are recommended from the most similar user's list of favorites.

### Operations:
- **Load Data**:             Import data from external files for books and user ratings.
- **Add New Members**:       Add new users to the system.
- **Add New Books**:         Add books with their title, author, and year.
- **User Login/Logout**:     Login as a user to view and rate books.
- **Rate Books**:            Rate any book in the system.
- **View Personal Ratings**: Display all ratings for the logged-in user.
- **See Recommendations**:   Get book recommendations based on user similarity.
- **Quit**:                  Exit the program.

### Dynamic Memory:
- Uses dynamically allocated arrays for handling large, sparse datasets without STL containers.

### File Structure
Book-Recommendation-System-Cpp/
├── main.cpp             # Driver program (UI and main logic)
├── BookList.h/.cpp      # BookList class for managing book details
├── MemberList.h/.cpp    # MemberList class for managing user details
├── RatingList.h/.cpp    # RatingList class for managing ratings
├── books.txt            # Sample books data file
├── ratings.txt          # Sample ratings data file
└── README.md            # Project documentation

### Key Concepts Learned
  - Dynamic Memory Allocation: Efficiently managing memory using pointers and dynamic arrays.
  - File I/O: Reading and processing structured data from files.
  - Object-Oriented Design: Modularizing the system into classes for books, members, and ratings.
  - Algorithm Design: Calculating user similarity and generating personalized recommendations.
  - Custom Data Structures: Implementing without STL for a deeper understanding of C++.

