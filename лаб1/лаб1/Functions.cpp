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
        arr[i].show();
    }
    cout << "-------------------------------------------------------------" << endl;
}

Book createBookFromInput() {
    char author[50];
    char title[50];
    char group[10];
    int year;

    cout << "\n--- Введення даних для книги ---" << endl;
    cout << "Введіть автора: ";
    cin >> ws;
    cin.getline(author, 50);

    cout << "Введіть назву: ";
    cin.getline(title, 50);

    cout << "Введіть рік випуску: ";
    cin >> year;

    cout << "Введіть групу (Х - художня, Н - навчальна, С - довідкова): ";
    cin >> ws;
    cin.getline(group, 10);

    return Book(author, title, year, group);
}