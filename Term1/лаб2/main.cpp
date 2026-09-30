#include <iostream>
#include <fstream>
#include <windows.h>
#include "Header.h"

using namespace std;

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    const size_t CAPACITY = 10;
    Book** books = new Book * [CAPACITY];
    size_t count = 0;

    ifstream inFile("data.txt");
    if (inFile.is_open()) {
        while (!inFile.eof() && count < CAPACITY) {
            Book* newBook = new Book();
            if (inFile >> *newBook) {
                *(books + count) = newBook;
                count++;
            }
            else {
                delete newBook;
            }
        }
        inFile.close();
    }

    int choice = -1;
    while (choice != 0) {
        BookView::displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            BookView::displayTable(books, count);
            break;
        case 2:
            if (count >= 2) {
                cout << "\nПривласнення: Книга 1 = Книга 2\n";
                **books = **(books + 1);
                BookView::displayTable(books, count);
            }
            break;
        case 3:
            if (count >= 2) {
                cout << "\nПорівняння Книги 1 та Книги 2:\n";
                if ((**books).operator==(**(books + 1))) {
                    cout << "Як метод: Книги однакові.\n";
                }
                else {
                    cout << "Як метод: Книги різні.\n";
                }

                if (operator==(**books, **(books + 1))) {
                    cout << "Як дружня функція: Книги однакові.\n";
                }
                else {
                    cout << "Як дружня функція: Книги різні.\n";
                }
            }
            break;
        case 4:
            if (count >= 2) {
                Book sumMethod = (**books).operator+(**(books + 1));
                Book sumFriend = operator+(**books, **(books + 1));
                cout << "\nРезультат метода (+): " << sumMethod << "\n";
                cout << "Результат дружньої функції (+): " << sumFriend << "\n";
            }
            break;
        case 5:
            if (count > 0) {
                cout << "\nДовжина назви першої книги (через []): " << (**books)[0] << " символів.\n";
            }
            break;
        case 6:
            if (count > 0) {
                (**books)("Страуструп", "Мова C++", 2015, "Н");
                cout << "\nПерша книга після перевизначання через ():\n";
                BookView::displayTable(books, count);
            }
            break;
        case 0:
            cout << "Завершення роботи.\n";
            break;
        default:
            cout << "Невірний вибір.\n";
            break;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        delete* (books + i);
    }
    delete[] books;

    return 0;
}