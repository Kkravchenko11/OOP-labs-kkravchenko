#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Book {
private:
    char* m_author;
    char* m_title;
    int m_year;
    char* m_group;

    void allocateAndCopy(char** dest, const char* src);

public:
    Book();
    Book(const char* author, const char* title, int year, const char* group);
    Book(const Book& other);
    ~Book();

    const char* getAuthor() const;
    const char* getTitle() const;
    int getYear() const;
    const char* getGroup() const;

    void setAuthor(const char* author);
    void setTitle(const char* title);
    void setYear(int year);
    void setGroup(const char* group);

    Book& operator=(const Book& other);
    bool operator==(const Book& other) const;
    Book operator+(const Book& other) const;

    size_t operator[](int index) const;
    void operator()(const char* author, const char* title, int year, const char* group);

    friend bool operator==(const Book& lhs, const Book& rhs);
    friend Book operator+(const Book& lhs, const Book& rhs);

    friend ostream& operator<<(ostream& os, const Book& book);
    friend istream& operator>>(istream& is, Book& book);
};

class BookView {
public:
    static void displayHeader();
    static void displayBook(const Book& book);
    static void displayTable(const Book* const* books, size_t count);
    static void displayMenu();
};

#endif