#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <cstdlib>

//------------task 1-------------
std::mutex mutex1;

class myOut {

public: 
    myOut(std::ostream& out): os(out) {
        mutex1.lock();
    }

    template<typename T> 
    void operator<<(const T& inData) {
        os << inData << std::endl;
    }

    ~myOut() {
        mutex1.unlock();
    }

private: 
    std::ostream& os;
};

void print1() {
    myOut pcout(std::cout);
    for (size_t i = 0u; i < 10; i++)
    {
        pcout << i;
    }
}

void print2() {
    myOut pcout(std::cout);
    for (size_t i = 0u; i < 10; i++)
    {
        pcout << i;
    }
}

//------------task 2-------------

std::condition_variable cv2;
std::mutex mutex2;
int progress; //текущий прогресс

int simple(int i) {
    int current_num = 2;
    
    size_t it = 1;
    int key = 0;
    int number = 0;

    while (it <= i) {

        key = 0;
        for (size_t j = 2; j <= current_num; j++) {
            if (current_num % j == 0)
            {
                key++;
            }
        }

        //если (key < 2) -> число простое
        if (key < 2)
        {
            it++;
            number = current_num;
           
            //оповещаем основной поток
            std::lock_guard<std::mutex> lg(mutex2);
            progress = it;
            cv2.notify_one();

        }
        current_num++;
    }
    return number;
}

//------------task 3-------------

std::mutex mutex3;
std::priority_queue<int> things;
std::condition_variable cv3;

void master() {
    int randNumber;
    for (size_t i = 0u; i < 20; i++) {
        std::lock_guard<std::mutex> lg(mutex3);
        randNumber = std::rand();
        std::cout << "put " << randNumber << std::endl;
        things.push(randNumber);
        cv3.notify_one();
    }
}

void thief() {   
    for (size_t i = 0u; i < 20; i++) {
        std::unique_lock<std::mutex> ul(mutex3);
        cv3.wait(ul, [] {return !things.empty(); });
        std::cout << "removed: " << things.top() << std::endl;
        things.pop();
    }
}



int main()
{
// ------------task 1------------
    std::cout << "task 1" << std::endl;
    std::thread worker1(print1);
    std::thread worker2(print2);

    worker1.join();
    worker2.join();

// ------------task 2------------
    
    std::cout << "task 2" << std::endl;
    int number = 200;
    std::thread worker3(simple, number);
    worker3.detach();

    while (progress != number) {
        std::unique_lock<std::mutex> ul(mutex2);
        cv2.wait(ul);
        std::cout << progress << "/" << number;
        system("CLS");
    }
    
    //------------task 3-------------
    std::cout << "task 3" << std::endl;
    std::thread worker4(master);
    std::thread worker5(thief);
    worker4.join();
    worker5.join();


    
    
    return 0;
}

