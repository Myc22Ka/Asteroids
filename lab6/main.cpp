#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>
#include <condition_variable>

using namespace std;

atomic<int> counter(0);

mutex mtx1;
mutex mtx2;
condition_variable cv;

atomic<int> message_counter(0);

void zad1()
{
    for (size_t i = 0; i < 100; i++)
    {
        thread thread1([&]()
                       { cout << "Watek " << i << endl;
                         counter++; });
        this_thread::sleep_for(chrono::milliseconds(100));

        thread1.join();
    }

    cout << "Zmienna atomic: " << counter << endl;
}

void loop1()
{
    unique_lock<mutex> lock(mtx2);
    cv.wait(lock, []
            { return message_counter < 10; });
    cout << "Cześć z wątku 1" << endl;
    ++message_counter;
    this_thread::sleep_for(chrono::milliseconds(100));
}

void loop2()
{
    unique_lock<mutex> lock(mtx1);
    cv.wait(lock, []
            { return message_counter < 10; });
    cout << "Cześć z wątku 2" << endl;
    ++message_counter;
    this_thread::sleep_for(chrono::milliseconds(200));
}

void zad2()
{
    while (true)
    {

        loop1();
        loop2();
        if (message_counter == 10)
        {
            cout << "Minało 10 komunikatów" << endl;
            message_counter = 0;
        }

        cv.notify_all();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main(int argc, char const *argv[])
{
    zad1();

    thread t1(zad2);
    thread t2(zad2);

    t1.join();
    t2.join();

    return 0;
}
