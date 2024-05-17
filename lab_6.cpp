#include <iostream>
#include <map>
#include <string>
#include <regex>
using namespace std;

// Структура для хранения записи
struct Record {
    string surname;
    string birthdate;
    string phone;

    friend ostream& operator<<(ostream& os, const Record& record) {
        os << "Фамилия: " << record.surname << ", Дата рождения: " << record.birthdate << ", Телефон: " << record.phone;
        return os;
    }
};
// Класс для работы с записной книжкой
class Notebook {
private:
    multimap<string, Record> records; // Контейнер для хранения записей

public:
    // Добавление записи
    void addRecord(const string& surname, const string& birthdate, const string& phone) {
        if (surname.empty() || birthdate.empty() || phone.empty()) {
            throw invalid_argument("Все поля должны быть заполнены.");
        }
        if (!isValidDate(birthdate)) {
            throw invalid_argument("Дата должна быть в формате ДД-ММ-ГГГГ.");
        }
        Record record = { surname, birthdate, phone };
        records.insert(make_pair(surname, record));
    }
    // Удаление записи по фамилии
    void deleteRecord(const string& surname) {
        auto range = records.equal_range(surname);
        if (range.first == range.second) {
            throw runtime_error("Запись не найдена.");
        }
        else {
            records.erase(range.first, range.second);
            cout << "Запись(и) с фамилией " << surname << " удалены." << endl;
        }
    }
    // Поиск записи по фамилии
    void searchBySurname(const string& surname) const {
        auto range = records.equal_range(surname);
        if (range.first == range.second) {
            throw runtime_error("Запись не найдена.");
        }
        else {
            for (auto it = range.first; it != range.second; ++it) {
                cout << it->second << endl;
            }
        }
    }
    // Поиск записи по номеру телефона
    void searchByPhone(const string& phone) const {
        for (const auto& pair : records) {
            if (pair.second.phone == phone) {
                cout << pair.second << endl;
                return;
            }
        }
        throw runtime_error("Запись не найдена.");
    }
    // Поиск записи по дате рождения
    void searchByBirthdate(const string& birthdate) const {
        for (const auto& pair : records) {
            if (pair.second.birthdate == birthdate) {
                cout << pair.second << endl;
                return;
            }
        }
        throw runtime_error("Запись не найдена.");
    }
    // Печать всех записей
    void printAllRecords() const {
        if (records.empty()) {
            throw runtime_error("Записей нет.");
        }
        for (const auto& pair : records) {
            cout << pair.second << endl;
        }
    }
private:
    bool isValidDate(const string& date) const {
        const regex pattern(R"(\d{2}-\d{2}-\d{4})");
        return regex_match(date, pattern);
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    Notebook notebook;
    int choice;
    string surname, birthdate, phone;

    do {
        cout << "1. Добавить запись\n";
        cout << "2. Удалить запись\n";
        cout << "3. Поиск по фамилии\n";
        cout << "4. Поиск по телефону\n";
        cout << "5. Поиск по дате рождения\n";
        cout << "6. Показать все записи\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        try {
            switch (choice) {
            case 1:
                cout << "Введите фамилию: ";
                cin >> surname;
                cout << "Введите дату рождения (ДД-ММ-ГГГГ): ";
                cin >> birthdate;
                cout << "Введите телефон: ";
                cin >> phone;
                notebook.addRecord(surname, birthdate, phone);
                break;

            case 2:
                cout << "Введите фамилию для удаления: ";
                cin >> surname;
                notebook.deleteRecord(surname);
                break;

            case 3:
                cout << "Введите фамилию для поиска: ";
                cin >> surname;
                notebook.searchBySurname(surname);
                break;

            case 4:
                cout << "Введите телефон для поиска: ";
                cin >> phone;
                notebook.searchByPhone(phone);
                break;

            case 5:
                cout << "Введите дату рождения для поиска (ДД-ММ-ГГГГ): ";
                cin >> birthdate;
                notebook.searchByBirthdate(birthdate);
                break;

            case 6:
                notebook.printAllRecords();
                break;

            case 0:
                cout << "Выход...\n";
                break;

            default:
                cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
            }
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }

    } while (choice != 0);

    return 0;
}