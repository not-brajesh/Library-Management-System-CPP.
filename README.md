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



---

### 3. UML Class Diagram Add Karein
UML diagram aapki implemented classes (`Library` aur `Book`) aur unke relationship ko match karna chahiye[span_6](start_span)[span_6](end_span). Aapke code mein `Library` class `Book` objects ko `map<int, Book>` mein store karti hai (Composition relationship).

Is diagram ko aap `README.md` ke neeche add kar sakte hain ya draw.io par bana kar `uml_diagram.png` ke naam se folder mein save kar sakte hain:

```text
+-----------------------------------+          +---------------------------+
|              Library              |          |           Book            |
+-----------------------------------+          +---------------------------+
| - books : map<int, Book>          |◆-------->| + id : int                |
| - filename : string               | 1      * | + title : string          |
+-----------------------------------+          | + author : string         |
| - toLower(str : string) : string  |          | + available : bool        |
| - sanitizeCSV(text : string)      |          +---------------------------+
| + Library()                       |
| + loadFromFile() : void           |
| + saveToFile() : void             |
| + addBook(...) : void             |
| + searchById(id : int) : void     |
| + searchByKeyword(...) : void     |
| + listBooks() : void              |
| + issueBook(id : int) : void      |
| + returnBook(id : int) : void     |
+-----------------------------------+
