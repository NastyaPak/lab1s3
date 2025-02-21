#include "header.h"
#include <iostream>
#include <fstream>
using namespace std;

// Структура DLLNode для узла двусвязного списка
struct DLLNode {
    std::string data;  // Данные узла
    DLLNode* next;     // Указатель на следующий узел
    DLLNode* prev;     // Указатель на предыдущий узел

    // Конструктор для создания узла
    DLLNode(std::string value) : data(value), next(nullptr), prev(nullptr) {}
};

// Структура DoubleLinkedList для работы с двусвязным списком
struct DoubleLinkedList {
    std::string* doubleLinkedList;  // Указатель на массив (не используется в текущей реализации)
    DLLNode* head;  // Указатель на начало списка
    DLLNode* tail;  // Указатель на конец списка

    // Конструктор: инициализация списка и загрузка данных из файла
    DoubleLinkedList() : head(nullptr), tail(nullptr) {
        loadFromFile("DLList.data");  // Загружаем данные из файла при создании объекта
    }

    // Методы для работы со списком
    void addToTheHead(std::string value);  // Добавление элемента в начало списка
    void addToTheEnd(std::string value);    // Добавление элемента в конец списка
    void removeFromTheHead();               // Удаление элемента из начала списка
    void removeFromTheEnd();                // Удаление элемента из конца списка
    void removeByValue(std::string value);  // Удаление элемента по значению
    bool searchByValue(std::string value);  // Поиск элемента по значению
    void display();                         // Вывод списка на экран
    void loadFromFile(const std::string& filename);  // Загрузка данных из файла
    void saveToFile(const std::string& filename);    // Сохранение данных в файл
    void clear();  // Очистка списка
};

// Очистка списка
void DoubleLinkedList::clear() {
    while (head != nullptr) {
        removeFromTheHead();  // Удаляем элементы с головы, пока список не станет пустым
    }
}

// Добавление элемента в начало списка
void DoubleLinkedList::addToTheHead(std::string value) {
    DLLNode* newNode = new DLLNode(value);  // Создаем новый узел
    if (head == nullptr) {  // Если список пуст
        head = tail = newNode;  // Новый узел становится и головой, и хвостом
    } else {
        newNode->next = head;  // Новый узел указывает на текущую голову
        head->prev = newNode;  // Текущая голова указывает на новый узел
        head = newNode;        // Новый узел становится новой головой
    }
    saveToFile("DLList.data");  // Сохраняем изменения в файл
}

// Добавление элемента в конец списка
void DoubleLinkedList::addToTheEnd(std::string value) {
    DLLNode* newNode = new DLLNode(value);  // Создаем новый узел
    if (head == nullptr) {  // Если список пуст
        head = tail = newNode;  // Новый узел становится и головой, и хвостом
    } else {
        newNode->prev = tail;  // Новый узел указывает на текущий хвост
        tail->next = newNode;  // Текущий хвост указывает на новый узел
        tail = newNode;        // Новый узел становится новым хвостом
    }
    saveToFile("DLList.data");  // Сохраняем изменения в файл
}

// Удаление элемента из начала списка
void DoubleLinkedList::removeFromTheHead() {
    if (head == nullptr) {  // Если список пуст
        cout << "Deletion is not possible: the list is empty" << endl;
        return;
    } else if (head == tail) {  // Если в списке только один элемент
        delete head;
        head = nullptr;
        tail = nullptr;
    } else {
        DLLNode* temp = head;  // Сохраняем текущую голову
        head = head->next;  // Перемещаем голову на следующий узел
        head->prev = nullptr;  // Убираем связь с предыдущим узлом
        delete temp;  // Удаляем старую голову
    }
    saveToFile("DLList.data");  // Сохраняем изменения в файл
}

// Удаление элемента из конца списка
void DoubleLinkedList::removeFromTheEnd() {
    if (head == nullptr) {  // Если список пуст
        cout << "Deletion is not possible: the list is empty" << endl;
        return;
    } else if (head == tail) {  // Если в списке только один элемент
        delete head;
        head = nullptr;
        tail = nullptr;
    } else {
        DLLNode* temp = tail;  // Сохраняем текущий хвост
        tail = tail->prev;  // Перемещаем хвост на предыдущий узел
        tail->next = nullptr;  // Убираем связь с последним узлом
        delete temp;  // Удаляем старый хвост
    }
    saveToFile("DLList.data");  // Сохраняем изменения в файл
}
// Удаление элемента по значению
void DoubleLinkedList::removeByValue(std::string value) {
    if (head == nullptr) {  // Если список пуст
        cout << "Deletion is not possible: the list is empty" << endl;
        return;
    }

    // Если значение находится в голове
    if (head->data == value) {
        removeFromTheHead();
        return;
    }

    // Если значение находится в хвосте
    if (tail->data == value) {
        removeFromTheEnd();
        return;
    }

    // Ищем узел с нужным значением
    DLLNode* current = head;
    while (current != nullptr && current->data != value) {
        current = current->next;
    }

    // Если значение не найдено
    if (current == nullptr) {
        cout << "This value is not in the list" << endl;
        return;
    }

    // Обновляем связи между узлами
    if (current->prev) {
        current->prev->next = current->next;
    }
    if (current->next) {
        current->next->prev = current->prev;
    }

    delete current;  // Удаляем текущий узел
    saveToFile("DLList.data");  // Сохраняем изменения в файл
}

// Поиск элемента по значению
bool DoubleLinkedList::searchByValue(std::string value) {
    DLLNode* current = head;
    while (current) {  // Проходим по списку
        if (current->data == value) {  // Если значение найдено
            std::cout << "Value " << value << " is in the list" << std::endl;
            return true;
        }
        current = current->next;
    }
    std::cout << "There is no " << value << " in the list" << std::endl;
    return false;
}

// Вывод списка на экран
void DoubleLinkedList::display() {
    DLLNode* current = head;
    if (current == nullptr) {  // Если список пуст
        cout << "Doubly linked list is empty" << endl;
    } else {
        while (current != nullptr) {  // Проходим по списку
            cout << current->data << " ";  // Выводим данные узла
            current = current->next;
        }
        cout << endl;
    }
}

// Загрузка данных из файла
void DoubleLinkedList::loadFromFile(const std::string& filename) {
    clear();  // Очищаем текущий список
    std::ifstream file(filename);
    if (!file) {  // Если файл не удалось открыть
        cout << "Cannot open file for reading: " << filename << endl;
        return;
    }

    std::string line;
    while (getline(file, line)) {  // Читаем данные из файла
        addToTheEnd(line);  // Добавляем элементы в конец списка
    }
    file.close();
}

// Сохранение данных в файл
void DoubleLinkedList::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {  // Если файл не удалось открыть
        std::cout << "Cannot open file for writing: " << filename << std::endl;
        return;
    }

    DLLNode* current = head;
    while (current) {  // Проходим по списку
        file << current->data << std::endl;  // Записываем данные узла в файл
        current = current->next;
    }
    file.close();
}
