#include "Header.h"
#include <iomanip>

using namespace std;

void Book::allocateAndCopy(char** dest, const char* src) {
    if (*dest != nullptr) {
        delete[] * dest;
        *dest = nullptr;
    }
    if (src != nullptr) {
        size_t len = 0;
        const char* ptr = src;
        while (*ptr != '\0') {
            len++;
            ptr++;
        }
        *dest = new char[len + 1];
        for (size_t i = 0; i < len; ++i) {
            *(*dest + i) = *(src + i);
        }
        *(*dest + len) = '\0';
    }
    else {
        *dest = new char[1];
        **dest = '\0';
    }
}

Book::Book() : m_author(nullptr), m_title(nullptr), m_year(0), m_group(nullptr) {
    allocateAndCopy(&m_author, "Невідомо");
    allocateAndCopy(&m_title, "Без назви");
    allocateAndCopy(&m_group, "Н");
}

Book::Book(const char* author, const char* title, int year, const char* group)
    : m_author(nullptr), m_title(nullptr), m_year(year), m_group(nullptr) {
    allocateAndCopy(&m_author, author);
    allocateAndCopy(&m_title, title);
    allocateAndCopy(&m_group, group);
}

Book::Book(const Book& other)
    : m_author(nullptr), m_title(nullptr), m_year(other.m_year), m_group(nullptr) {
    allocateAndCopy(&m_author, other.m_author);
    allocateAndCopy(&m_title, other.m_title);
    allocateAndCopy(&m_group, other.m_group);
}

Book::~Book() {
    delete[] m_author;
    delete[] m_title;
    delete[] m_group;
}

const char* Book::getAuthor() const { return m_author; }
const char* Book::getTitle() const { return m_title; }
int Book::getYear() const { return m_year; }
const char* Book::getGroup() const { return m_group; }

void Book::setAuthor(const char* author) { allocateAndCopy(&m_author, author); }
void Book::setTitle(const char* title) { allocateAndCopy(&m_title, title); }
void Book::setYear(int year) { m_year = year; }
void Book::setGroup(const char* group) { allocateAndCopy(&m_group, group); }

Book& Book::operator=(const Book& other) {
    if (this != &other) {
        allocateAndCopy(&m_author, other.m_author);
        allocateAndCopy(&m_title, other.m_title);
        m_year = other.m_year;
        allocateAndCopy(&m_group, other.m_group);
    }
    return *this;
}

bool Book::operator==(const Book& other) const {
    if (m_year != other.m_year) return false;

    const char* p1 = m_author;
    const char* p2 = other.m_author;
    while (*p1 != '\0' && *p2 != '\0') {
        if (*p1 != *p2) return false;
        p1++; p2++;
    }
    if (*p1 != *p2) return false;

    p1 = m_title;
    p2 = other.m_title;
    while (*p1 != '\0' && *p2 != '\0') {
        if (*p1 != *p2) return false;
        p1++; p2++;
    }
    if (*p1 != *p2) return false;

    p1 = m_group;
    p2 = other.m_group;
    while (*p1 != '\0' && *p2 != '\0') {
        if (*p1 != *p2) return false;
        p1++; p2++;
    }
    return *p1 == *p2;
}

Book Book::operator+(const Book& other) const {
    size_t len1 = 0, len2 = 0;
    const char* ptr = m_author;
    while (*ptr != '\0') { len1++; ptr++; }
    ptr = other.m_author;
    while (*ptr != '\0') { len2++; ptr++; }

    char* newAuthor = new char[len1 + len2 + 4];
    for (size_t i = 0; i < len1; ++i) *(newAuthor + i) = *(m_author + i);
    *(newAuthor + len1) = ' ';
    *(newAuthor + len1 + 1) = '&';
    *(newAuthor + len1 + 2) = ' ';
    for (size_t i = 0; i < len2; ++i) *(newAuthor + len1 + 3 + i) = *(other.m_author + i);
    *(newAuthor + len1 + 3 + len2) = '\0';

    Book result(newAuthor, m_title, m_year + other.m_year, m_group);
    delete[] newAuthor;
    return result;
}

size_t Book::operator[](int) const {
    size_t len = 0;
    const char* ptr = m_title;
    while (*ptr != '\0') {
        len++;
        ptr++;
    }
    return len;
}

void Book::operator()(const char* author, const char* title, int year, const char* group) {
    allocateAndCopy(&m_author, author);
    allocateAndCopy(&m_title, title);
    m_year = year;
    allocateAndCopy(&m_group, group);
}

bool operator==(const Book& lhs, const Book& rhs) {
    return lhs.operator==(rhs);
}

Book operator+(const Book& lhs, const Book& rhs) {
    return lhs.operator+(rhs);
}

ostream& operator<<(ostream& os, const Book& book) {
    os << book.m_author << ";" << book.m_title << ";" << book.m_year << ";" << book.m_group;
    return os;
}

istream& operator>>(istream& is, Book& book) {
    char bufferAuthor[100];
    char bufferTitle[100];
    char bufferGroup[20];
    int year = 0;

    if (is.getline(bufferAuthor, 100, ';')) {
        is.getline(bufferTitle, 100, ';');
        is >> year;
        is.ignore();
        is.getline(bufferGroup, 20);
        book(bufferAuthor, bufferTitle, year, bufferGroup);
    }
    return is;
}

void BookView::displayHeader() {
    cout << "-------------------------------------------------------------\n";
    cout << "| " << setw(15) << left << "Автор"
        << "| " << setw(20) << left << "Назва"
        << "| " << setw(10) << left << "Рік"
        << "| " << setw(5) << left << "Група" << " |\n";
    cout << "-------------------------------------------------------------\n";
}

void BookView::displayBook(const Book& book) {
    cout << "| " << setw(16) << left << book.getAuthor()
        << "| " << setw(22) << left << book.getTitle()
        << "| " << setw(10) << left << book.getYear()
        << "| " << setw(1) << left << book.getGroup() << " |\n";
}

void BookView::displayTable(const Book* const* books, size_t count) {
    displayHeader();
    for (size_t i = 0; i < count; ++i) {
        displayBook(**(books + i));
    }
    cout << "-------------------------------------------------------------\n";
}

void BookView::displayMenu() {
    cout << "\n=== МЕНЮ ЛАБОРАТОРНОЇ РОБОТИ №2 ===\n";
    cout << "1. Показати всі книги з файлу\n";
    cout << "2. Демонстрація оператора привласнення (=)\n";
    cout << "3. Демонстрація оператора порівняння (==)\n";
    cout << "4. Демонстрація оператора додавання (+)\n";
    cout << "5. Перевірка оператора [] (довжина назви)\n";
    cout << "6. Перевірка оператора () (переініціалізація)\n";
    cout << "0. Вихід\n";
    cout << "Ваш вибір: ";
}