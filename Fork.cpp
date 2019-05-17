#include "Fork.h"

Fork::Fork(int fork_id, Screen_Printer& printer) : printer(printer) {
    this->fork_id = fork_id;
}

void Fork::get_fork(int philosopher_id) {
    mutex.lock();
    printer.update_fork_owner(fork_id, philosopher_id);
}

void Fork::put_off_fork() {
    printer.free_fork(fork_id);
    mutex.unlock();
}