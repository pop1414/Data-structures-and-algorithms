#include <iostream>
// 没有处理数组隐藏越界情况
class StaticArray
{
public:
    int maxSizeOfArray;
    int numElements;
    int *arr;
    StaticArray(int maxSizeOfArray_, int numElements_)
    {
        if (numElements_ > maxSizeOfArray_)
        {
            std::cout << "Invail!" << std::endl;
            exit(1);
        }
        this->maxSizeOfArray = maxSizeOfArray_;
        this->numElements = numElements_;
        arr = new int[maxSizeOfArray];
        for (int i = 0; i < numElements_; i++)
        {
            arr[i] = i;
        }
    }
    // add at last
    void add(int num)
    {
        arr[numElements] = num;
        this->numElements++;
    }
    // delet at last
    void remove()
    {
        arr[numElements - 1] = -1;
        numElements--;
    }
    // 把index后面的元素往后移动一位，然后再插入
    void insert(int index, int num)
    {
        // i是元素被移动后的下标， i - 1是原来的，i > index意味着，循环正好停止在，原来index位置的元素被移动之后（把位置让出来了）
        // 从后往前
        for (int i = numElements; i > index; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[index] = num;
        numElements++;
    }
    // 把index后面的元素往前移动一位，然后删除最后一个元素
    // 从前往后
    void removeAt(int index)
    {
        for (int i = index; i < numElements - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        arr[numElements] = -1;
        numElements--;
    }
    void check() { ; }
    void printArray()
    {
        for (int i = 0; i < numElements; i++)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    ~StaticArray()
    {
        delete[] arr;
    }
};

int main()
{
    int maxSizeOfArray;
    int numElements;
    std::cout << "Please enter the max size of Array" << std::endl;
    std::cin >> maxSizeOfArray;
    std::cout << "Please enter the active size of Array" << std::endl;
    std::cin >> numElements;

    StaticArray newArr(maxSizeOfArray, numElements);

    newArr.add(99);
    newArr.printArray();

    newArr.insert(3, 666);
    newArr.printArray();

    newArr.removeAt(4);
    newArr.printArray();

    newArr.remove();
    newArr.printArray();
    return 0;
}