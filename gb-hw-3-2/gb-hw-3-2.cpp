#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <iterator>
#include <chrono>

template<typename T>
void Swap(T& p1, T& p2) {
    T c(std::move(p1));
    p1 = std::move(p2);
    p2 = std::move(c);
}

template<typename T>
void SortPointers(std::vector<T*>& vec) {
    sort(vec.begin(), vec.end(), [](auto& x, auto& y) {return *x < *y; });
}

const std::string vowel = "aeiouyAEIOUY";

//первый способ count_if and find
int count1(std::ifstream& in) {
    int sum = 0;

    auto start = std::chrono::system_clock::now();
    if (in.is_open()) {
        
        std::istreambuf_iterator<char> it(in), end;
        sum = std::count_if(it, end, [](char temp) { return (vowel.find(temp) != std::string::npos); });
    }

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> diff = end - start;
    std::cout << "Time 1: " << diff.count() << " s " << std::endl;
    return sum;
}

//второй способ count_if and for
int count2(std::ifstream& in) {
    int sum = 0;

    auto start = std::chrono::system_clock::now();
    if (in.is_open()) {

        std::istreambuf_iterator<char> it(in), end;
        sum = std::count_if(it, end, [](char temp) { for (size_t i = 0; i < vowel.size(); i++) { if (temp == vowel[i]) return true; } return false; });
    }

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> diff = end - start;
    std::cout << "Time 2: " << diff.count() << " s " << std::endl;

    return sum;
}

//третий способ цикл for и find
int count3(std::ifstream& in) {
    int sum = 0;

    auto start = std::chrono::system_clock::now();
    if (in.is_open()) {
        std::istreambuf_iterator<char> it(in), end;

        for (; it != end; it++) {
            if (vowel.find(*it) != std::string::npos)
                sum++;
       }

    }

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> diff = end - start;
    std::cout << "Time 3: " << diff.count() << " s " << std::endl;
    return sum;
}

//четвертый способ 2 цикла for
int count4(std::ifstream& in) {
    int sum = 0;

    auto start = std::chrono::system_clock::now();
    if (in.is_open()) {
        std::istreambuf_iterator<char> it(in), end;

        for (; it != end; it++) {
            for (size_t i = 0; i < vowel.size(); i++) {
                if (*it == vowel[i])
                    sum++;
            }
        }

    }
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> diff = end - start;
    std::cout << "Time 4: " << diff.count() << " s " << std::endl;
    return sum;
}

int main()
{
    std::cout << "------task 1------" << std::endl;
    int a1 = 5;
    int a2 = 10;

    std::cout << "a1: " << a1 << " a2: " << a2 << std::endl;
    Swap<int>(a1, a2);
    std::cout << "a1: " << a1 << " a2: " << a2 << std::endl;

    std::cout << "------task 2------" << std::endl;
    int* p1 = new int(5);
    int* p2 = new int(1);
    int* p3 = new int(9);
    int* p4 = new int(8);

    std::vector<int*> vecInt = { p1, p2, p3, p4 };
    std::vector<int*>::iterator it;

    for (it = vecInt.begin(); it != vecInt.end(); it++) {
        std::cout << **it << " ";
    }
    std::cout << std::endl;

    SortPointers(vecInt);

    for (it = vecInt.begin(); it != vecInt.end(); it++) {
        std::cout << **it << " ";
    }
    std::cout << std::endl;

    std::cout << "------task 3------" << std::endl;


    std::ifstream novel("War and peace.txt");
   
    count1(novel);
    novel.seekg(0);
    count2(novel);
    novel.seekg(0);
    count3(novel);
    novel.seekg(0);
    count4(novel);

    return 0;
}