#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>

using namespace std;

class Book {
private:
    string author;
    string title;
    int year;
    string group;

public:
    Book() {
        author = "Невідомо";
        title = "Без назви";
        year = 0;
        group = "Н";
    }

    Book(string a, string t, int y, string g) {
        author = a;
        title = t;
        year = y;
        group = g;
    }

    Book(const Book& other) {
        author = other.author;
        title = other.title;
        year = other.year;
        group = other.group;
    }

    string getAuthor() { return author; }
    string getTitle() { return title; }
    int getYear() { return year; }
    string getGroup() { return group; }

    void setAuthor(string a) { author = a; }
    void setTitle(string t) { title = t; }
    void setYear(int y) { year = y; }
    void setGroup(string g) { group = g; }

    void show();
};

void printTableHeader();
void printTable(Book arr[], int size);
Book createBookFromInput();

#endif