#include <iostream>
#include <windows.h>
#include "Book.h"

using namespace std;

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    const int SIZE = 3;

    cout << "=== Створення масивів трьома видами конструкторів ===\n";

    Book defaultArr[SIZE];
    cout << "\nЗаповнення 2-го масиву через введення даних (Варіант №6):";
    Book paramArr[SIZE] = {
        createBookFromInput(),
        createBookFromInput(),
        createBookFromInput()
    };

    Book copyArr[SIZE] = {
        Book(paramArr[0]),
        Book(paramArr[1]),
        Book(paramArr[2])
    };

    int choice = 0;

    while (choice != 4) {
        cout << "\n================ МЕНЮ ================\n";
        cout << "1. Друкувати первинні таблиці (show)\n";
        cout << "2. Змінити параметри (set) та вивести первинну і нову таблиці\n";
        cout << "3. Перевірити параметри через get()-аксесори\n";
        cout << "4. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\n>>> Масив 1 (Конструктор за умовчанням) <<<\n";
            printTable(defaultArr, SIZE);

            cout << "\n>>> Масив 2 (Конструктор з параметрами) <<<\n";
            printTable(paramArr, SIZE);

            cout << "\n>>> Масив 3 (Конструктор копіювання) <<<\n";
            printTable(copyArr, SIZE);
        }
        else if (choice == 2) {
            int index;
            string newTitle;
            int newYear;

            cout << "\nОберіть елемент у 1-му масиві для зміни (0, 1 або 2): ";
            cin >> index;

            if (index >= 0 && index < SIZE) {
                cout << "\n--- Первинна таблиця (до змін) ---\n";
                printTable(defaultArr, SIZE);

                cout << "\nВведіть нову назву книги: ";
                cin >> ws;
                getline(cin, newTitle);
                cout << "Введіть новий рік випуску: ";
                cin >> newYear;

                defaultArr[index].setTitle(newTitle);
                defaultArr[index].setYear(newYear);
                cout << "\n--- Таблиця, яка вийшла після зміни параметрів (set) ---\n";
                printTable(defaultArr, SIZE);
            }
            else {
                cout << "Некоректний індекс!\n";
            }
        }
        else if (choice == 3) {
            int index;
            cout << "\nОберіть елемент у 2-му масиві (0, 1 або 2): ";
            cin >> index;

            if (index >= 0 && index < SIZE) {
                cout << "\n--- Читання даних об'єкта через get() ---" << endl;
                cout << "getAuthor(): " << paramArr[index].getAuthor() << endl;
                cout << "getTitle():  " << paramArr[index].getTitle() << endl;
                cout << "getYear():   " << paramArr[index].getYear() << endl;
                cout << "getGroup():  " << paramArr[index].getGroup() << endl;
            }
            else {
                cout << "Некоректний індекс!\n";
            }
        }
        else if (choice == 4) {
            cout << "Завершення роботи програми.\n";
        }
        else {
            cout << "Невірний вибір! Спробуйте ще раз.\n";
        }
    }

    return 0;
}