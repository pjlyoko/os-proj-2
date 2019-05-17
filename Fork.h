#ifndef DINING_PHILOSOPHERS_FORK_H
#define DINING_PHILOSOPHERS_FORK_H


#include <mutex>
#include <condition_variable>
#include "Screen_Printer.h"

class Fork {
private:
    int fork_id;
    std::mutex mutex;

    Screen_Printer &printer;
public:
    Fork(int fork_id, Screen_Printer &printer);

    void get_fork(int philosopher_id);

    void put_off_fork();
};


#endif //DINING_PHILOSOPHERS_FORK_H
