#include "header.h"

struct HashNode {
    std::string key;
    std::string data;
    HashNode* next;
    HashNode* prev;

    HashNode(const string& key, const string& data) : key(key), data(data), next(nullptr) {}
};

const int SIZE = 500;

struct HashTableItem {
    std::string key;
    std::string data;
    HashTableItem* next; // указатель на следующий элемент в цепочке
};

struct HashTable {
    HashTableItem* items[SIZE];
    int count;

    HashTable() : count(0) {//заполнение таблицы
        for (int i = 0; i < SIZE; i++) { // все элементы nullptr
            items[i] = nullptr;
        }
        loadFromFile("hashtable.data"); // загружаем данные из файла при создании
    }
    int HashFun(const std::string& key);
    HashTableItem* createItem(const std::string& key, std::string data);
    void push(const std::string& key, std::string data);
    void get(const std::string& key);
    void pop(const std::string& key);
    void clear();
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
};

void HashTable::clear() {
     for (int i = 0; i < SIZE; ++i) {
        HashTableItem* current = items[i];
        while (current != nullptr) {
            HashTableItem* temp = current;
            current = current->next;
            delete temp; // удаляем текущий элемент 
        }
        items[i] = nullptr; // элемент теперь указывает на nullptr
    }
}

int HashTable::HashFun(const std::string& key) {//хэш функция
    const int prime = 43; // простое число
    int hash = 0;
    for (char letter : key) {
        hash = (hash * prime + static_cast<int>(letter)) % SIZE;//хэширование через ASCII
    } // остаток от деления, чтобы гарантировать, что значение будет в пределах массива
    return hash;
}

HashTableItem* HashTable::createItem(const std::string& key, std::string data) {//создание элемента таблицы
    return new HashTableItem{ key, data, NULL };
}

void HashTable::push(const std::string& key, std::string data) {
    if (count >= SIZE) {
        cout << "Table is full" << endl;
        return;
    }

    int index = HashFun(key);
    HashTableItem* item = createItem(key, data);

    if (items[index] == NULL) {
        items[index] = item; // вставляем как первый элемент в ячейке
        count++;
    } else {
        HashTableItem* current = items[index];
        while (current != nullptr) {
            if (current->key == key) {
                current->data = data; // обновляем существующий ключ
                delete item; // удаляем новый элемент, так как ключ уже существует
                return;
            }
            if (current->next == nullptr) {
                current->next = item; // добавляем новый элемент в конец цепочки
                count++;
                break;
            }
            current = current->next;
        }
    }
    saveToFile("hashtable.data"); // сохраняем изменения в файл
}

void HashTable::get(const std::string& key) {
    if (count == 0) { // проверка на пустоту
        std::cout << "Table is empty" << std::endl;
        return;
    }

    int index = HashFun(key);
    HashTableItem* current = items[index];

    while (current != nullptr) {
        if (current->key == key) {
            std::cout << "Element by key: " << current->key << " is: " << current->data << std::endl;
            return; // найден элемент, выходим из функции
        }
        current = current->next; // переходим к следующему элементу
    }

    std::cout << "Key not found: " << key << std::endl; // если ключ не найден
}

void HashTable::pop(const std::string& key) {
    if (count == 0) {
        return;
    }

    int index = HashFun(key);
    HashTableItem* current = items[index];
    HashTableItem* prev = nullptr;

    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                items[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            count--;
            saveToFile("hashtable.data");
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "This value is not in the table" << endl;
}

void HashTable::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Cannot open file for writing: " << filename << std::endl;
        return;
    }

    for (int i = 0; i < SIZE; ++i) {
        HashTableItem* current = items[i];
        while (current != nullptr) {
            file << current->key << ":" << current->data << std::endl; // сохраняем в формате "ключ:значение"
            current = current->next;
        }
    }

    file.close();
}

void HashTable::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Cannot open file for reading: " << filename << std::endl;
        return;
    }

    clear();  // Отчистим таблицу перед сохранением
    std::string line;

    while (std::getline(file, line)) {
        size_t separator = line.find(':');
        if (separator != std::string::npos) {
            std::string key = line.substr(0, separator);
            std::string data = line.substr(separator + 1);
            push(key, data); // добавим в хеш таблицу ключ и значение
        }
    }

    file.close();
}