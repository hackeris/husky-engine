//
// Created by rainm on 2021/1/3.
//

#ifndef HUSKY_ENGINE_TIMER_H
#define HUSKY_ENGINE_TIMER_H

#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>
#include <utility>

class timer {
public:
    void start() {
        start_time = std::chrono::system_clock::now();
        running = true;
    }

    void stop() {
        end_time = std::chrono::system_clock::now();
        running = false;
    }

    double elapsed_ms() {
        std::chrono::time_point<std::chrono::system_clock> end;

        if (running) {
            end = std::chrono::system_clock::now();
        } else {
            end = end_time;
        }

        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start_time).count();
    }

    double elapsed_secs() {
        return elapsed_ms() / 1000.0;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> start_time;
    std::chrono::time_point<std::chrono::system_clock> end_time;
    volatile bool running = false;
};

class auto_timer {
public:
    explicit auto_timer(std::string msg) : msg(std::move(msg)) { tmr_.start(); }

    ~auto_timer() {
        std::cout << msg << ", elapsed:" << tmr_.elapsed_ms() << "ms." << std::endl;
    }

private:
    timer tmr_;
    std::string msg;
};

#endif //HUSKY_ENGINE_TIMER_H
