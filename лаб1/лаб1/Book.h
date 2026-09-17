#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <cstring>

using namespace std;

class Book {
private:
    char author[50];
    char title[50];
    int year;
    char group[10];

public:
    Book() {
        strcpy(author, "Невідомо");
        strcpy(title, "Без назви");
        year = 0;
        strcpy(group, "Н");
    }

    Book(const char* a, const char* t, int y, const char* g) {
        strcpy(author, a);
        strcpy(title, t);
        year = y;
        strcpy(group, g);
    }

    Book(const Book& other) {
        strcpy(author, other.author);
        strcpy(title, other.title);
        year = other.year;
        strcpy(group, other.group);
    }

    const char* getAuthor() { return author; }
    const char* getTitle() { return title; }
    int getYear() { return year; }
    const char* getGroup() { return group; }

    void setAuthor(const char* a) { strcpy(author, a); }
    void setTitle(const char* t) { strcpy(title, t); }
    void setYear(int y) { year = y; }
    void setGroup(const char* g) { strcpy(group, g); }

    void show();
};

void printTableHeader();
void printTable(Book arr[], int size);
Book createBookFromInput();

#endif