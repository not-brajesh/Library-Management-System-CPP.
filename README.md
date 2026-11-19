# Library Management System (C++)

A console-based Library Management System built in C++ using Object-Oriented Programming, STL containers, and CSV file handling.

## Features
- Add new books with unique Book ID, Title, and Author
- Search books by Book ID or by Title/Author keyword
- List all books with current availability status
- Issue and return books with validation for unknown or unavailable IDs
- Automatic data persistence using `books.csv`

## Project Structure
- `main.cpp` - Complete source code
- `books.csv` - Sample dataset and persistent storage
- `README.md` - Project documentation

## Compilation and Execution
Compile the code using a C++17 compiler:
```bash
g++ -std=c++17 main.cpp -o library
# Library-Management-System-CPP.
