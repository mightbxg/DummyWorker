#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;
using namespace chrono;

void busy_wait(size_t nanosec)
{
    using namespace std::chrono;
    auto t0 = high_resolution_clock::now();
    while (duration_cast<nanoseconds>(high_resolution_clock::now() - t0).count() < nanosec) {
    }
}

[[noreturn]] void work(float percentage)
{
    assert(percentage >= 0.f && percentage <= 1.f);
    constexpr float period = 1000000.0f;
    while (true) {
        //busy_wait(900000);
        //this_thread::sleep_for(100000ns);
        busy_wait(static_cast<size_t>(period * percentage));
        this_thread::sleep_for(nanoseconds(static_cast<size_t>(period * (1.f - percentage))));
    }
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        cout << "Args: worker_num occupation_rate.\n";
        return 0;
    }
    const int num = stoi(argv[1]);
    const float percentage = stof(argv[2]);
    if (num < 1) {
        cout << "Error: num of workers less than 1.\n";
        return 0;
    }
    if (percentage < 0.f || percentage > 1.f) {
        cout << "Error: occupation rate should be between [0.0, 1.0].\n";
        return 0;
    }
    cout << "num of workers: " << num << "\n"
         << "occupation rate: " << percentage << "\n";

    // do the work
    vector<thread> tds;
    for (size_t i = 0; i < num; ++i) {
        tds.emplace_back(work, percentage);
    }
    tds[0].join();
}