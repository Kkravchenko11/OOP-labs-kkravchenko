#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <fstream>
#include <stdexcept>
using namespace std;

const int AUTHOR_LEN = 50;
const int TITLE_LEN = 50;
const int GROUP_LEN = 10;

class Book
{
private:
    char author[AUTHOR_LEN];
    char title[TITLE_LEN];
    int year;
    char group[GROUP_LEN];

public:
    Book();
    Book(const char* a, const char* t, int y, const char* g);
    Book(const Book& other);

    const char* getAuthor() const;
    const char* getTitle() const;
    int getYear() const;
    const char* getGroup() const;

    void setAuthor(const char* a);
    void setTitle(const char* t);
    void setYear(int y);
    void setGroup(const char* g);

    void saveToFile(ofstream& out) const;
    void loadFromFile(ifstream& in);
};

class IndexException : public exception
{
private:
    string message;

public:
    IndexException(const string& msg);
    const char* what() const noexcept override;
};

class FileException : public exception
{
private:
    string message;

public:
    FileException(const string& msg);
    const char* what() const noexcept override;
};

void showHeader();
void showBook(const Book& b);
void showArray(Book* arr, int size);

void inputBookFromKeyboard(Book& b);
void inputArrayFromKeyboard(Book* arr, int size);
void inputArrayFromTextFile(Book* arr, int size, const string& filename);

void saveOneBookToFile(Book* arr, int size, int index, const string& filename);
void showOneBookFromFile(const string& filename, int index);

void saveArrayToFile(Book* arr, int size, const string& filename);
int loadArrayFromFile(Book* arr, int maxSize, const string& filename);

void printMenu();