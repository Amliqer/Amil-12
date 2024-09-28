#include <iostream>

template<class T>
struct Node {
    T data;
    std::unique_ptr<Node<T>> next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template<typename T>
class List {
public:
    std::unique_ptr<Node<T>> head;

public:
    void push_front(const T& value) {
        auto new_node = std::make_unique<Node<T>>(value);
        if (!head) {
            head = std::move(new_node);
        }
        else {
            new_node->next = std::move(head);
            head = std::move(new_node);
        }
    }

    void push_back(const T& value) {
        auto new_node = std::make_unique<Node<T>>(value);
        if (!head) {
            head = std::move(new_node);
        }
        else {
            Node<T>* current = head.get();
            while (current->next) {
                current = current->next.get();
            }
            current->next = std::move(new_node);
        }
    }

    void print() {
        for (auto node = head.get(); node != nullptr; node = node->next.get())
            std::cout << node->data << '\n';
    }

    // Метод для получения элемента по индексу
    T at(size_t index) {
        Node<T>* current = head.get();
        size_t count = 0;

        while (current != nullptr) {
            if (count == index) {
                return current->data;
            }
            current = current->next.get();
            count++;
        }

        throw std::out_of_range("Index out of range");
    }

    // Метод для получения количества элементов в списке
    size_t size() const {
        size_t count = 0;
        Node<T>* current = head.get();
        while (current != nullptr) {
            count++;
            current = current->next.get();
        }
        return count;
    }
};

int main() {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    // Печать элементов списка
    list.print();

    // Доступ к элементам по индексу
    try {
        std::cout << "Element at index 1: " << list.at(1) << std::endl; // 20
        std::cout << "Element at index 3: " << list.at(3) << std::endl; // Это вызовет исключение
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
