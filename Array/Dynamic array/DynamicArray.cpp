#include <iostream>
#include <cstring>
#include <string>

template <typename T>
class DynamicArray
{
private:
    T *arr;
    size_t maxSize;                          // 当前数组的最大容量
    size_t activeSize;                       // 当前存在的元素数量
    static const size_t defaultCapacity = 1; // 不主动声明数组的容量，默认为1

    // 边界检查都应该是与activeSize比较(maxSize只是用于容量判断，activeSize才是数据操作的关键)
    //  检查插入元素时的边界(用于插入)
    bool isPositionIndex(size_t index)
    {
        return index <= activeSize;
    }
    // 检查元素位置的合法(用于删除)
    bool isElementIndex(size_t index)
    {
        return index < activeSize;
    }
    // 检查 index 索引位置是否可以添加元素
    void checkPositionIndex(size_t index)
    {
        if (!isPositionIndex(index))
        {
            throw std::out_of_range("Index out of bounds");
        }
    }
    // 检查 index 索引位置是否可以存在元素
    void checkElementIndex(size_t index)
    {
        if (!isElementIndex(index))
        {
            throw std::out_of_range("Index out of bounds");
        }
    }

public:
    DynamicArray()
    {
        this->arr = new T[defaultCapacity];
        this->maxSize = defaultCapacity;
        this->activeSize = 0;
    }
    DynamicArray(size_t initCapacity)
    {
        // 防止非法容量
        if (initCapacity == 0)
        {
            initCapacity = defaultCapacity;
        }
        this->arr = new T[initCapacity];
        this->maxSize = initCapacity;
        this->activeSize = 0;
    }
    void resize(size_t newSize)
    {
        T *tempArray = new T[newSize];               // 先声明一个新的数组，容量是更新后的
        std::copy(arr, arr + activeSize, tempArray); // 正确 // 将原来的data中有元素的部分复制到新数组中
        delete[] arr;
        // 更新两个成员变量
        // 只是改变数组的最大容量, activeSize不变
        arr = tempArray;
        maxSize = newSize;
    }
    void add(T num)
    {
        // 满容就翻倍
        if (activeSize == maxSize)
        {
            resize(maxSize * 2);
        }
        arr[activeSize++] = num;
    }
    void insert(size_t index, T num)
    {
        // 如果不合法
        checkPositionIndex(index);

        if (activeSize == maxSize)
        {
            resize(maxSize * 2);
        }

        for (size_t i = activeSize; i > index; i--)
        {
            arr[i] = arr[i - 1];
        }

        arr[index] = num;
        activeSize++;
    }
    void removeLast()
    {
        arr[activeSize - 1] = T();
        activeSize--;
        // 量少缩容
        if (activeSize < maxSize / 4)
        {
            resize(maxSize / 2);
        }
    }
    void removeAt(size_t index)
    {
        // 如果不合法
        checkElementIndex(index);
        // activeSize - 2是最后一个i,把acticeSize - 1(最后一个元素的下标)赋值给activeSize - 2
        for (size_t i = index; i < activeSize - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        arr[activeSize - 1] = T();
        activeSize--;
        // 量少缩容
        if (activeSize < maxSize / 4)
        {
            resize(maxSize / 2);
        }
    }
    T get(size_t index)
    {
        checkElementIndex(index);
        return arr[index];
    }
    void set(size_t index, T element)
    {
        checkElementIndex(index);
        arr[index] = element;
    }
    void printArr()
    {
        for (size_t i = 0; i < activeSize; i++)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
    size_t getSize()
    {
        return activeSize;
    }
    bool empty()
    {
        return activeSize == 0;
    }
    ~DynamicArray()
    {
        delete[] arr;
    }
};

int main()
{
    //     DynamicArray<int> arrOne;
    //     arrOne.add(60);
    //     arrOne.add(200);
    //     arrOne.printArr();

    //     arrOne.insert(2, 300);
    //     arrOne.printArr();
    //     arrOne.insert(1, 999);
    //     arrOne.printArr();

    //     arrOne.removeAt(0);
    //     arrOne.printArr();
    //     arrOne.removeLast();
    //     arrOne.printArr();

    DynamicArray<std::string> arrTwo;
    arrTwo.add("Hello");
    arrTwo.add("World");
    arrTwo.printArr();

    arrTwo.insert(2, "ni");
    arrTwo.printArr();
    arrTwo.insert(1, "wo");
    arrTwo.printArr();

    arrTwo.removeAt(0);
    arrTwo.printArr();
    arrTwo.removeLast();
    arrTwo.printArr();
    return 0;
}