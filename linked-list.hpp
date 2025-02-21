#include "header.h"
#include <iostream>
#include <fstream>
using namespace std;

// Структура LLNode для узла односвязного списка
struct LLNode {
    std::string data;  // Данные узла
    LLNode* next;      // Указатель на следующий узел

    // Конструктор для создания узла
    LLNode(std::string value) : data(value), next(nullptr) {}
};

// Структура LinkedList для работы с односвязным списком
struct LinkedList {
    LLNode* head;  // Указатель на начало списка

    // Конструктор: инициализация списка и загрузка данных из файла
    LinkedList() : head(nullptr) {
        loadFromFile("linkedlist.data");  // Загружаем данные из файла при создании объекта
    }

    // Методы для работы со списком
    void addToTheHead(std::string value);  // Добавление элемента в начало списка
    void addToTheEnd(std::string value);   // Добавление элемента в конец списка
    void removeFromTheHead();              // Удаление элемента из начала списка
    void removeFromTheEnd();               // Удаление элемента из конца списка
    void removeByValue(std::string value); // Удаление элемента по значению
    void searchByValue(std::string value); // Поиск элемента по значению
    void display();                        // Вывод списка на экран
    void saveToFile(const std::string& filename);  // Сохранение данных в файл
    void loadFromFile(const std::string& filename); // Загрузка данных из файла
};

// Добавление элемента в начало списка
void LinkedList::addToTheHead(std::string value) {
    LLNode* newNode = new LLNode(value);  // Создаем новый узел
    newNode->next = head;  // Новый узел указывает на текущую голову
    head = newNode;        // Новый узел становится новой головой
    saveToFile("linkedlist.data");  // Сохраняем изменения в файл
}

// Добавление элемента в конец списка
void LinkedList::addToTheEnd(std::string value) {
    LLNode* newNode = new LLNode(value);  // Создаем новый узел
    if (head == nullptr) {  // Если список пуст
        head = newNode;     // Новый узел становится головой
    } else {
        LLNode* current = head;
        while (current->next != nullptr) {  // Идем до последнего узла
            current = current->next;
        }
        current->next = newNode;  // Добавляем новый узел в конец
    }
    saveToFile("linkedlist.data");  // Сохраняем изменения в файл
}

// Удаление элемента из начала списка
void LinkedList::removeFromTheHead() {
    if (head == nullptr) {
        std::cout << "Deletion is not possible: the list is empty" << std::endl;
        return;
    }
    LLNode* temp = head;  // Сохраняем текущую голову
    head = head->next;    // Перемещаем голову на следующий узел
    delete temp;          // Удаляем старую голову
    saveToFile("linkedlist.data");  // Сохраняем изменения в файл
}

// Удаление элемента из конца списка
void LinkedList::removeFromTheEnd() {
    if (head == nullptr) {
        std::cout << "Deletion is not possible: the list is empty" << std::endl;
        return;
    }
    if (head->next == nullptr) {
        delete head;  // Удаляем единственный узел
        head = nullptr;
    } else {
        LLNode* current = head;
        while (current->next->next != nullptr) {  // Идем до предпоследнего узла
            current = current->next;
        }
        delete current->next;  // Удаляем последний узел
        current->next = nullptr;  // Обнуляем указатель на последний узел
    }
    saveToFile("linkedlist.data");  // Сохраняем изменения в файл
}

// Удаление элемента по значению
void LinkedList::removeByValue(std::string value) {
    if (head == nullptr) {
        std::cout << "Deletion is not possible: the list is empty" << std::endl;
        return;
    }
    if (head->data == value) {  // Если значение находится в голове
        removeFromTheHead();
        return;
    }

    LLNode* current = head;
    while (current->next != nullptr && current->next->data != value) {  // Ищем узел с нужным значением
        current = current->next;
    }
    if (current->next == nullptr) {  // Если значение не найдено
        std::cout << "This value is not in the list" << std::endl;
        return;
    }

    LLNode* temp = current->next;  // Сохраняем узел для удаления
    current->next = temp->next;    // Связываем текущий узел со следующим
    delete temp;                   // Удаляем узел
    saveToFile("linkedlist.data");  // Сохраняем изменения в файл
}

// Поиск элемента по значению
void LinkedList::searchByValue(std::string value) {
    LLNode* current = head;
    while (current != nullptr) {  // Проходим по списку
        if (current->data == value) {  // Если значение найдено
            std::cout << "Value " << value << " is in the list" << std::endl;
            return;
        }
        current = current->next;
    }
    std::cout << "There is no " << value << " in the list" << std::endl;
}

// Вывод списка на экран
void LinkedList::display() {
    LLNode* current = head;
    if (current == nullptr) {  // Если список пуст
        std::cout << "Linked list is empty" << std::endl;
    } else {
        while (current != nullptr) {  // Проходим по списку
            std::cout << current->data << " ";  // Выводим данные узла
            current = current->next;
        }
        std::cout << std::endl;
    }
}

// Сохранение данных в файл
void LinkedList::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {  // Если файл не удалось открыть
        std::cout << "Cannot open file for writing: " << filename << std::endl;
        return;
    }

    LLNode* current = head;
    while (current != nullptr) {  // Проходим по списку
        file << current->data << std::endl;  // Записываем данные узла в файл
        current = current->next;
    }
    file.close();
}

// Загрузка данных из файла
void LinkedList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {  // Если файл не удалось открыть
        std::cout << "Cannot open file for reading: " << filename << std::endl;
        return;
    }

    std::string value;
    while (file >> value) {  // Читаем данные из файла
        addToTheEnd(value);  // Добавляем элементы в конец списка
    }
    file.close();
}