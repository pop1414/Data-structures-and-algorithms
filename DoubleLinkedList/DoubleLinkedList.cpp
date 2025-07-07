#include <iostream>
#include <string>

// #include <exception>

template <typename T>
class DoubleLinkedList
{
public:
    // 先定义节点
    struct Node
    {
        T value;
        Node *next;
        Node *prev;

        Node(T value_) : value(value_), next(nullptr), prev(nullptr) {};
    };
    DoubleLinkedList()
    {
        // pay attention to (T());
        dummyHead = new Node(T());
        dummyTail = new Node(T());
        dummyHead->next = dummyTail;
        dummyTail->prev = dummyHead;
        size = 0;
    }
    // adding
    void addFirst(T value_)
    {
        // using temp to point dummyHead->next is clearly
        // insert newNode between dummyHead and temp
        // dummyHead<->temp to dummyHead<->newNode<->temp
        Node *newNode = new Node(value_);
        Node *temp = dummyHead->next;

        newNode->prev = dummyHead;
        dummyHead->next = newNode;

        newNode->next = temp;
        temp->prev = newNode;
        size++;
    }
    void addLast(T value_)
    {
        Node *newNode = new Node(value_);
        Node *temp = dummyTail->prev;

        newNode->next = dummyTail;
        dummyTail->prev = newNode;

        newNode->prev = temp;
        temp->next = newNode;
        size++;
    }
    void insert(size_t index, T value_)
    {
        checkPositionIndex(index);

        if (index == 0)
        {
            addFirst(value_);
        }
        else if (index == size)
        {
            addLast(value_);
        }
        else
        {
            Node *newNode = new Node(value_);
            // 找到index - 1的节点，再插入新节点的下标才是index
            Node *first = getNode(index - 1);
            Node *second = first->next;

            newNode->prev = first;
            first->next = newNode;

            newNode->next = second;
            second->prev = newNode;
            size++;
        }
    }
    // removing
    void removeFirst()
    {
        checkSize();
        Node *x = dummyHead->next;
        Node *y = x->next;

        dummyHead->next = y;
        y->prev = dummyHead;

        delete x;
        size--;
    }
    void removeLast()
    {
        checkSize();
        Node *x = dummyTail->prev;
        Node *y = x->prev;

        dummyTail->prev = y;
        y->next = dummyTail;

        delete x;
        size--;
    }
    void removeAt(size_t index)
    {
        checkSize();
        checkElementIndex(index);
        if (index == 0)
        {
            removeFirst();
        }
        else if (index == size - 1)
        {
            removeLast();
        }
        else
        {
            Node *middle = getNode(index);
            Node *left = middle->prev;
            Node *right = middle->next;

            left->next = right;
            right->prev = left;

            delete middle;
            size--;
        }
    }
    // updating element
    T get(size_t index)
    {
        checkSize();
        checkElementIndex(index);
        return getNode(index)->value;
    }
    T getFirst()
    {
        checkSize();
        return dummyHead->next->value;
    }
    T getLast()
    {
        checkSize();
        return dummyTail->prev->value;
    }
    // Tool
    size_t getSize() const
    {
        return size;
    }
    bool isEmpty()
    {
        return size == 0;
    }
    void printLinkedList()
    {
        Node *temp = dummyHead->next;
        while (temp != dummyTail)
        {
            std::cout << temp->value << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    ~DoubleLinkedList()
    {
        while (size > 0)
        {
            removeFirst();
        }
        delete dummyHead;
        delete dummyTail;
    }

private:
    // 虚拟头尾节点
    Node *dummyHead;
    Node *dummyTail;
    // 节点数量
    size_t size;

    Node *getNode(size_t index)
    {
        checkElementIndex(index);
        // 比一半大从尾节点找
        if (index > size / 2)
        {
            Node *temp = dummyTail->prev;
            for (size_t i = size - 1; i > index; i--)
            {
                temp = temp->prev;
            }
            return temp;
        }
        // 否则从头节点找
        else
        {

            Node *temp = dummyHead->next;
            for (size_t i = 0; i < index; i++)
            {
                temp = temp->next;
            }
            return temp;
        }
    }
    // uesd to insert
    bool isPositionIndex(size_t index)
    {
        return index <= size;
    }
    // uesd to get/remove/set...
    bool isElementIndex(size_t index)
    {
        return index < size;
    }
    void checkPositionIndex(size_t index)
    {
        if (!isPositionIndex(index))
        {

            throw std::out_of_range("Index: " + std::to_string(index) + ", Size: " + std::to_string(size));
        }
    }
    void checkElementIndex(size_t index)
    {
        if (!isElementIndex(index))
        {
            throw std::out_of_range("Index: " + std::to_string(index) + ", Size: " + std::to_string(size));
        }
    }
    void checkSize()
    {
        if (size < 1)
        {
            throw std::invalid_argument("No elements in the list");
        }
    }
};

int main()
{
    DoubleLinkedList<int> list;
    list.addFirst(1);
    list.printLinkedList(); // 输出: 1 3 2
    list.addLast(2);
    list.printLinkedList(); // 输出: 1 3 2
    list.insert(1, 3);      // 在 index 1 插入 3
    list.printLinkedList(); // 输出: 1 3 2

    list.removeAt(1);       // 删除 index 1 的元素
    list.printLinkedList(); // 输出: 1 2

    std::cout << "First: " << list.getFirst() << std::endl; // 输出: First: 1
    std::cout << "Last: " << list.getLast() << std::endl;   // 输出: Last: 2
    std::cout << "Size: " << list.getSize() << std::endl;   // 输出: Size: 2

    DoubleLinkedList<std::string> list2;
    list2.addFirst("apple");
    list2.printLinkedList(); // 输出: apple cherry banana
    list2.addLast("banana");
    list2.printLinkedList();   // 输出: apple cherry banana
    list2.insert(1, "cherry"); // 在 index 1 插入 cherry
    list2.printLinkedList();   // 输出: apple cherry banana

    list2.removeFirst();     // 删除第一个元素
    list2.printLinkedList(); // 输出: cherry banana

    std::cout << "Size: " << list2.getSize() << std::endl;   // 输出: Size: 2
    std::cout << "First: " << list2.getFirst() << std::endl; // 输出: First: cherry
    return 0;
}
