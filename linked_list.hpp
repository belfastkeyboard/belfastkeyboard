#ifndef     LINKED_LIST
#define     LINKED_LIST 1

#include    <iostream>

// removing by value is time-inefficient
// and becomes incredibly costly as list size becomes larger and larger
// if possible and if list size is large use remove_index instead

template <class T>
class linked_list
{
private:
    size_t l_size;
    struct Node
    {
        Node*   next = nullptr;
        T       data;
        Node() {}
        Node(T d) : data(d) {}
    };
    Node* start;
public:
    bool    empty()
    {
        return (l_size == 0);
    }
    size_t  size()
    {
        return l_size;
    }
    void    add(T item)
    {
        if (empty())
        {
            start = new Node(item);
            l_size++;
            return;
        }
        Node* new_node = new Node(item);
        new_node->next = start;
        start = new_node;
        l_size++;
    }
    void    insert(T item, size_t index)
    {
        if (empty() && index != 0) return;
        if (index == 0) add(item);
        Node* current = start;
        for (size_t i = 0; i < index - 1; i++)
        {
            if (current == nullptr || current->next == nullptr) return;
            current = current->next;
        }
        Node* to_add = new Node(item);
        if (current->next == nullptr)
        {
            current->next = to_add;
            l_size++;
            return;
        }
        to_add->next = current->next;
        current->next = to_add;
        l_size++;
    }
    void    remove_value(T value)
    {
        if (empty()) return;
        Node* current   =   start;
        Node* prev      =   start;
        while (current != nullptr)
        {
            if (current->data != value)
            {
                prev = current;
                current = current->next;
                continue;
            }
            if (current == start)
            {
                start = start->next;
                delete current;
                l_size--;
                return;
            }
            prev->next = current->next;
            delete current;
            l_size--;
            return;
        }
    }
    void    remove_value_all(T value)
    {
        if (empty()) return;
        Node* current   =   start;
        Node* prev      =   start;
        while (current != nullptr)
        {
            if (current->data != value)
            {
                prev = current;
                current = current->next;
                continue;
            }
            if (current == start)
            {
                start = start->next;
                delete current;
                current = start;
                l_size--;
                continue;
            }
            prev->next = current->next;
            delete current;
            current = prev->next;
            l_size--;
        }
    }
    void    remove_index(size_t index)
    {
        if (empty())
        {
            std::cout << "empty()" << std::endl;
            return;
        }
        if (index >= l_size)
        {
            std::cout << "Out of bounds!" << std::endl;
            return;
        }
        Node* current   =   start;
        Node* prev      =   start;
        if (index == 0)
        {
            if (start->next == nullptr)
            {
                delete current;
                start = nullptr;
                l_size--;
                return;
            }
            start = prev->next;
            delete current;
            l_size--;
            return;
        }
        for (size_t i = 0; i < index; i++)
        {
            prev = current;
            current = current->next;
        }
        if (current->next != nullptr)
        {
            prev->next = current->next;
            delete current;
            l_size--;
            return;
        }
        prev->next = nullptr;
        delete current;
        l_size--;
        return;
    }
    void    print()
    {
        if (empty()) {
            std::cout << "is_empty()" << std::endl;
            return;
        }
        Node* current = start;
        while (current != nullptr)
        {
            std::cout << current->data;
            if (current->next != nullptr) std::cout << ", ";
            current = current->next;
        }
        std::cout << "." << std::endl;
    }
    linked_list()
    {
        l_size = 0;
        start = nullptr;
    }
    ~linked_list()
    {
        while (start != nullptr)
        {
            remove_index(0);
        }
    }
};

#endif
