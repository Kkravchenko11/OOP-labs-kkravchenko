#define _CRT_SECURE_NO_WARNINGS

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include "Header.h"
using namespace std;

int main()
{
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    const int SIZE = 3;
    Book* arr = new Book[SIZE];
    const string textDataFile = "test_data.txt";
    const string binaryFile = "books.dat";

    int choice;
    do
    {
        printMenu();
        cin >> choice;
        cin.ignore();

        try
        {
            if (choice == 1)
            {
                inputArrayFromKeyboard(arr, SIZE);
            }
            else if (choice == 2)
            {
                inputArrayFromTextFile(arr, SIZE, textDataFile);
                cout << "Масив заповнено з файлу " << textDataFile << endl;
            }
            else if (choice == 3)
            {
                showArray(arr, SIZE);
            }
            else if (choice == 4)
            {
                cout << "Номер елемента (1.." << SIZE << "): ";
                int num;
                cin >> num;
                cin.ignore();
                int idx = num - 1;

                if (idx < 0 || idx >= SIZE)
                    throw IndexException("Невірний номер елемента масиву");

                char buf[100];
                cout << "  Новий автор: ";
                cin.getline(buf, 100);
                (*(arr + idx)).setAuthor(buf);

                cout << "  Нова назва: ";
                cin.getline(buf, 100);
                (*(arr + idx)).setTitle(buf);

                int y;
                cout << "  Новий рік: ";
                cin >> y;
                cin.ignore();
                (*(arr + idx)).setYear(y);

                cout << "  Нова група: ";
                cin.getline(buf, 100);
                (*(arr + idx)).setGroup(buf);
            }
            else if (choice == 5)
            {
                cout << "Номер об'єкта для збереження (1.." << SIZE << "): ";
                int num;
                cin >> num;
                cin.ignore();
                saveOneBookToFile(arr, SIZE, num - 1, binaryFile);
                cout << "Об'єкт збережено у файл " << binaryFile << endl;
            }
            else if (choice == 6)
            {
                cout << "Номер об'єкта для перегляду з файлу (починаючи з 1): ";
                int num;
                cin >> num;
                cin.ignore();
                showOneBookFromFile(binaryFile, num - 1);
            }
            else if (choice == 7)
            {
                saveArrayToFile(arr, SIZE, binaryFile);
                cout << "Масив збережено у файл " << binaryFile << endl;
            }
            else if (choice == 8)
            {
                int loaded = loadArrayFromFile(arr, SIZE, binaryFile);
                cout << "Зчитано об'єктів: " << loaded << endl;
            }
            else if (choice == 0)
            {
                cout << "Завершення програми." << endl;
            }
            else
            {
                cout << "Невірний вибір." << endl;
            }
        }
        catch (const exception& e)
        {
            cout << "Помилка: " << e.what() << endl;
        }

    } while (choice != 0);

    delete[] arr;
    return 0;
}