#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "Header.h"
using namespace std;

Book::Book()
{
    setAuthor("Невідомий автор");
    setTitle("Без назви");
    year = 2000;
    setGroup("Н");
}

Book::Book(const char* a, const char* t, int y, const char* g)
{
    setAuthor(a);
    setTitle(t);
    year = y;
    setGroup(g);
}

Book::Book(const Book& other)
{
    setAuthor(other.author);
    setTitle(other.title);
    year = other.year;
    setGroup(other.group);
}

const char* Book::getAuthor() const { return author; }
const char* Book::getTitle() const { return title; }
int Book::getYear() const { return year; }
const char* Book::getGroup() const { return group; }

void Book::setAuthor(const char* a)
{
    strncpy(author, a, AUTHOR_LEN - 1);
    author[AUTHOR_LEN - 1] = '\0';
}

void Book::setTitle(const char* t)
{
    strncpy(title, t, TITLE_LEN - 1);
    title[TITLE_LEN - 1] = '\0';
}

void Book::setYear(int y) { year = y; }

void Book::setGroup(const char* g)
{
    strncpy(group, g, GROUP_LEN - 1);
    group[GROUP_LEN - 1] = '\0';
}

void Book::saveToFile(ofstream& out) const
{
    out.write(reinterpret_cast<const char*>(this), sizeof(Book));
}

void Book::loadFromFile(ifstream& in)
{
    in.read(reinterpret_cast<char*>(this), sizeof(Book));
}

IndexException::IndexException(const char* msg)
{
    strncpy(message, msg, MESSAGE_LEN - 1);
    message[MESSAGE_LEN - 1] = '\0';
}

const char* IndexException::what() const noexcept { return message; }

FileException::FileException(const char* msg)
{
    strncpy(message, msg, MESSAGE_LEN - 1);
    message[MESSAGE_LEN - 1] = '\0';
}

const char* FileException::what() const noexcept { return message; }

const int COL_AUTHOR = 25;
const int COL_TITLE = 25;
const int COL_YEAR = 6;
const int COL_GROUP = 8;
const int TABLE_WIDTH = 2 + COL_AUTHOR + 3 + COL_TITLE + 3 + COL_YEAR + 3 + COL_GROUP + 2;

static int visibleLength(const char* s)
{
    int n = 0;
    while (*s != '\0')
    {
        if ((static_cast<unsigned char>(*s) & 0xC0) != 0x80)
            n++;
        s++;
    }
    return n;
}

static void printCell(const char* s, int width)
{
    cout << s;
    for (int i = visibleLength(s); i < width; i++)
        cout << ' ';
}

static void printLine()
{
    for (int i = 0; i < TABLE_WIDTH; i++)
        cout << '-';
    cout << endl;
}

void showHeader()
{
    printLine();
    cout << "| ";
    printCell("Автор", COL_AUTHOR);
    cout << " | ";
    printCell("Назва", COL_TITLE);
    cout << " | ";
    printCell("Рік", COL_YEAR);
    cout << " | ";
    printCell("Група", COL_GROUP);
    cout << " |" << endl;
    printLine();
}

void showBook(const Book& b)
{
    char yearText[20];
    snprintf(yearText, 20, "%d", b.getYear());

    cout << "| ";
    printCell(b.getAuthor(), COL_AUTHOR);
    cout << " | ";
    printCell(b.getTitle(), COL_TITLE);
    cout << " | ";
    printCell(yearText, COL_YEAR);
    cout << " | ";
    printCell(b.getGroup(), COL_GROUP);
    cout << " |" << endl;
}

void showArray(const Book* arr, int size)
{
    showHeader();
    for (int i = 0; i < size; i++)
        showBook(*(arr + i));
    printLine();
}

void inputBookFromKeyboard(Book& b)
{
    char buf[100];

    cout << "  Автор книги: ";
    cin.getline(buf, 100);
    b.setAuthor(buf);

    cout << "  Назва: ";
    cin.getline(buf, 100);
    b.setTitle(buf);

    int y;
    cout << "  Рік випуску: ";
    cin >> y;
    cin.ignore();
    b.setYear(y);

    cout << "  Група (Х-художня, Н-навчальна, С-довідкова): ";
    cin.getline(buf, 100);
    b.setGroup(buf);
}

void inputArrayFromKeyboard(Book* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << "Книга №" << i + 1 << endl;
        inputBookFromKeyboard(*(arr + i));
    }
}

void inputArrayFromTextFile(Book* arr, int size, const char* filename)
{
    ifstream in(filename);
    if (!in.is_open())
    {
        char msg[MESSAGE_LEN];
        snprintf(msg, MESSAGE_LEN, "Не вдалося відкрити файл тестових даних: %s", filename);
        throw FileException(msg);
    }

    char line[200];
    for (int i = 0; i < size; i++)
    {
        if (!in.getline(line, 200))
        {
            in.close();
            throw FileException("У файлі недостатньо даних для масиву");
        }

        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\r')
            line[len - 1] = '\0';

        char* p1 = strchr(line, ';');
        char* p2 = (p1 == NULL) ? NULL : strchr(p1 + 1, ';');
        char* p3 = (p2 == NULL) ? NULL : strchr(p2 + 1, ';');

        if (p1 == NULL || p2 == NULL || p3 == NULL)
        {
            in.close();
            throw FileException("Невірний формат рядка у файлі тестових даних");
        }

        *p1 = '\0';
        *p2 = '\0';
        *p3 = '\0';

        (*(arr + i)).setAuthor(line);
        (*(arr + i)).setTitle(p1 + 1);
        (*(arr + i)).setYear(atoi(p2 + 1));
        (*(arr + i)).setGroup(p3 + 1);
    }

    in.close();
}

void saveOneBookToFile(const Book* arr, int size, int index, const char* filename)
{
    if (index < 0 || index >= size)
        throw IndexException("Невірний номер об'єкта для збереження");

    ofstream out(filename, ios::binary | ios::app);
    if (!out.is_open())
    {
        char msg[MESSAGE_LEN];
        snprintf(msg, MESSAGE_LEN, "Не вдалося відкрити файл для запису: %s", filename);
        throw FileException(msg);
    }

    (*(arr + index)).saveToFile(out);
    out.close();
}

void showOneBookFromFile(const char* filename, int index)
{
    ifstream in(filename, ios::binary);
    if (!in.is_open())
    {
        char msg[MESSAGE_LEN];
        snprintf(msg, MESSAGE_LEN, "Не вдалося відкрити файл для читання: %s", filename);
        throw FileException(msg);
    }

    in.seekg(0, ios::end);
    long fileSize = static_cast<long>(in.tellg());
    int count = fileSize / static_cast<long>(sizeof(Book));

    if (index < 0 || index >= count)
    {
        in.close();
        char msg[MESSAGE_LEN];
        snprintf(msg, MESSAGE_LEN, "Невірний номер об'єкта у файлі (всього записів: %d)", count);
        throw IndexException(msg);
    }

    in.seekg(static_cast<streamoff>(index) * sizeof(Book), ios::beg);
    Book temp;
    temp.loadFromFile(in);
    in.close();

    showHeader();
    showBook(temp);
    printLine();
}

void saveArrayToFile(const Book* arr, int size, const char* filename)
{
    ofstream out(filename, ios::binary);
    if (!out.is_open())
    {
        char msg[MESSAGE_LEN];
        snprintf(msg, MESSAGE_LEN, "Не вдалося відкрити файл для запису масиву: %s", filename);
        throw FileException(msg);
    }

    for (int i = 0; i < size; i++)
        (*(arr + i)).saveToFile(out);

    out.close();
}

int loadArrayFromFile(Book* arr, int maxSize, const char* filename)
{
    ifstream in(filename, ios::binary);
    if (!in.is_open())
    {
        char msg[MESSAGE_LEN];
        snprintf(msg, MESSAGE_LEN, "Не вдалося відкрити файл для читання масиву: %s", filename);
        throw FileException(msg);
    }

    in.seekg(0, ios::end);
    long fileSize = static_cast<long>(in.tellg());
    in.seekg(0, ios::beg);

    int count = fileSize / static_cast<long>(sizeof(Book));
    if (count > maxSize)
        count = maxSize;

    for (int i = 0; i < count; i++)
        (*(arr + i)).loadFromFile(in);

    in.close();
    return count;
}

void printMenu()
{
    cout << endl;
    cout << "============ МЕНЮ ============" << endl;
    cout << "1. Ввести масив з клавіатури" << endl;
    cout << "2. Ввести масив з тестового файлу" << endl;
    cout << "3. Показати масив на екрані" << endl;
    cout << "4. Змінити елемент масиву (set)" << endl;
    cout << "5. Зберегти один об'єкт у бінарний файл" << endl;
    cout << "6. Вивести один об'єкт з бінарного файлу" << endl;
    cout << "7. Зберегти весь масив у бінарний файл" << endl;
    cout << "8. Зчитати весь масив з бінарного файлу" << endl;
    cout << "0. Вихід" << endl;
    cout << "Ваш вибір: ";
}