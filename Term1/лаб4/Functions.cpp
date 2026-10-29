#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Header.h"
using namespace std;

Book::Book()
{
    strcpy(author, "Невідомий автор");
    strcpy(title, "Без назви");
    year = 2000;
    strcpy(group, "Н");
}

Book::Book(const char* a, const char* t, int y, const char* g)
{
    strcpy(author, a);
    strcpy(title, t);
    year = y;
    strcpy(group, g);
}

Book::Book(const Book& other)
{
    strcpy(author, other.author);
    strcpy(title, other.title);
    year = other.year;
    strcpy(group, other.group);
}

const char* Book::getAuthor() const { return author; }
const char* Book::getTitle() const { return title; }
int Book::getYear() const { return year; }
const char* Book::getGroup() const { return group; }

void Book::setAuthor(const char* a) { strcpy(author, a); }
void Book::setTitle(const char* t) { strcpy(title, t); }
void Book::setYear(int y) { year = y; }
void Book::setGroup(const char* g) { strcpy(group, g); }

void Book::saveToFile(ofstream& out) const
{
    out.write(reinterpret_cast<const char*>(this), sizeof(Book));
}

void Book::loadFromFile(ifstream& in)
{
    in.read(reinterpret_cast<char*>(this), sizeof(Book));
}

IndexException::IndexException(const string& msg) : message(msg) {}
const char* IndexException::what() const noexcept { return message.c_str(); }

FileException::FileException(const string& msg) : message(msg) {}
const char* FileException::what() const noexcept { return message.c_str(); }

void showHeader()
{
    cout << "| " << left;
    cout.width(20); cout << "Автор";
    cout << "| "; cout.width(20); cout << "Назва";
    cout << "| "; cout.width(6);  cout << "Рік";
    cout << "| "; cout.width(8);  cout << "Група";
    cout << "|" << endl;
    cout << string(62, '-') << endl;
}

void showBook(const Book& b)
{
    cout << "| " << left;
    cout.width(20); cout << b.getAuthor();
    cout << "| "; cout.width(20); cout << b.getTitle();
    cout << "| "; cout.width(6);  cout << b.getYear();
    cout << "| "; cout.width(8);  cout << b.getGroup();
    cout << "|" << endl;
}

void showArray(Book* arr, int size)
{
    showHeader();
    for (int i = 0; i < size; i++)
        showBook(*(arr + i));
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

void inputArrayFromTextFile(Book* arr, int size, const string& filename)
{
    ifstream in(filename);
    if (!in.is_open())
        throw FileException("Не вдалося відкрити файл тестових даних: " + filename);

    for (int i = 0; i < size; i++)
    {
        string line;
        if (!getline(in, line))
            throw FileException("У файлі недостатньо даних для масиву");

        size_t p1 = line.find(';');
        size_t p2 = (p1 == string::npos) ? string::npos : line.find(';', p1 + 1);
        size_t p3 = (p2 == string::npos) ? string::npos : line.find(';', p2 + 1);

        if (p1 == string::npos || p2 == string::npos || p3 == string::npos)
        {
            in.close();
            throw FileException("Невірний формат рядка у файлі тестових даних");
        }

        string a = line.substr(0, p1);
        string t = line.substr(p1 + 1, p2 - p1 - 1);
        string yStr = line.substr(p2 + 1, p3 - p2 - 1);
        string g = line.substr(p3 + 1);

        int y = stoi(yStr);

        (*(arr + i)).setAuthor(a.c_str());
        (*(arr + i)).setTitle(t.c_str());
        (*(arr + i)).setYear(y);
        (*(arr + i)).setGroup(g.c_str());
    }

    in.close();
}

void saveOneBookToFile(Book* arr, int size, int index, const string& filename)
{
    if (index < 0 || index >= size)
        throw IndexException("Невірний номер об'єкта для збереження");

    ofstream out(filename, ios::binary | ios::app);
    if (!out.is_open())
        throw FileException("Не вдалося відкрити файл для запису: " + filename);

    (*(arr + index)).saveToFile(out);
    out.close();
}

void showOneBookFromFile(const string& filename, int index)
{
    ifstream in(filename, ios::binary);
    if (!in.is_open())
        throw FileException("Не вдалося відкрити файл для читання: " + filename);

    in.seekg(0, ios::end);
    long fileSize = static_cast<long>(in.tellg());
    int count = fileSize / static_cast<long>(sizeof(Book));

    if (index < 0 || index >= count)
    {
        in.close();
        throw IndexException("Невірний номер об'єкта у файлі (всього записів: " + to_string(count) + ")");
    }

    in.seekg(static_cast<streamoff>(index) * sizeof(Book), ios::beg);
    Book temp;
    temp.loadFromFile(in);
    in.close();

    showHeader();
    showBook(temp);
}

void saveArrayToFile(Book* arr, int size, const string& filename)
{
    ofstream out(filename, ios::binary);
    if (!out.is_open())
        throw FileException("Не вдалося відкрити файл для запису масиву: " + filename);

    for (int i = 0; i < size; i++)
        (*(arr + i)).saveToFile(out);

    out.close();
}

int loadArrayFromFile(Book* arr, int maxSize, const string& filename)
{
    ifstream in(filename, ios::binary);
    if (!in.is_open())
        throw FileException("Не вдалося відкрити файл для читання масиву: " + filename);

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