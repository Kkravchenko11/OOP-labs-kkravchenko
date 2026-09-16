#include "Book.h"
#include <iomanip>

void Book::show() {
    cout << "| " << setw(15) << left << author
        << "| " << setw(20) << left << title
        << "| " << setw(12) << left << year
        << "| " << setw(8) << left << group << " |" << endl;
}

void printTableHeader() {
    cout << "-------------------------------------------------------------" << endl;
    cout << "| " << setw(15) << left << "Автор"
        << "| " << setw(20) << left << "Назва"
        << "| " << setw(12) << left << "Рік випуску"
        << "| " << setw(8) << left << "Група" << " |" << endl;
    cout << "-------------------------------------------------------------" << endl;
}

void printTable(Book arr[], int size) {
    printTableHeader();
    for (int i = 0; i < size; i++) {
        arr[i].show()
    }
    cout << "-------------------------------------------------------------" << endl;
}

Book createBookFromInput() {
    string author, title, group;
    int year;

    cout << "\n--- Введення даних для книги ---" << endl;
    cout << "Введіть автора: ";
    cin >> ws;
    getline(cin, author);

    cout << "Введіть назву: ";
    getline(cin, title);

    cout << "Введіть рік випуску: ";
    cin >> year;

    cout << "Введіть групу (Х - художня, Н - навчальна, С - довідкова): ";
    cin >> ws;
    getline(cin, group);

    return Book(author, title, year, group);
}