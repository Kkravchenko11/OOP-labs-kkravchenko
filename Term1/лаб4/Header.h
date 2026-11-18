#ifndef HEADER_H
#define HEADER_H

#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <exception>
using namespace std;

const int AUTHOR_LEN = 50;
const int TITLE_LEN = 50;
const int GROUP_LEN = 10;
const int MESSAGE_LEN = 120;

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
    char message[MESSAGE_LEN];

public:
    IndexException(const char* msg);
    const char* what() const noexcept override;
};

class FileException : public exception
{
private:
    char message[MESSAGE_LEN];

public:
    FileException(const char* msg);
    const char* what() const noexcept override;
};

void showHeader();
void showBook(const Book& b);
void showArray(const Book* arr, int size);

void inputBookFromKeyboard(Book& b);
void inputArrayFromKeyboard(Book* arr, int size);
void inputArrayFromTextFile(Book* arr, int size, const char* filename);

void saveOneBookToFile(const Book* arr, int size, int index, const char* filename);
void showOneBookFromFile(const char* filename, int index);

void saveArrayToFile(const Book* arr, int size, const char* filename);
int loadArrayFromFile(Book* arr, int maxSize, const char* filename);

void printMenu();

#endif