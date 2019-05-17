#include "Philosopher.h"

using namespace std;

Philosopher::Philosopher(int philosopher_id, Table &table, Fork &left, Fork &right, Screen_Printer &printer) :
        philosopher_id(philosopher_id),
        table(table),
        left(left),
        right(right),
        rand_gen(1, 1500),
        printer(printer),
        eating_counter(0),
        philosopher_thread(&Philosopher::dine, this) {}

void Philosopher::dine() {
    while (table.is_feast()) {
        think();
        if (!table.is_feast()) break;

        take_fork(left);
        if (!table.is_feast()) {
            put_off_fork(left);
            break;
        };

        take_fork(right);
        if (!table.is_feast()) {
            put_off_fork(right);
            put_off_fork(left);
            break;
        };

        eat();

        put_off_fork(right);

        put_off_fork(left);

        increment_eating_counter();
        if (!table.is_feast()) break;
    }

    printer.update_philosopher_state(philosopher_id, Philosopher_State::FINISHED);
}

void Philosopher::think() {
    printer.update_philosopher_state(philosopher_id, Philosopher_State::THINKING);
    int time_to_sleep = (rand_gen(engine) + 3500) / 10;
    for (int i = 0; i < 100; i += 10) {
        printer.update_philosopher_state_progress(philosopher_id, i);
        this_thread::sleep_for(chrono::duration<int, milli>(time_to_sleep));
    }
}

void Philosopher::take_fork(Fork &fork) {
    printer.update_philosopher_state(philosopher_id,
                                     (&fork == &left ? Philosopher_State::REQUESTING_FOR_LEFT_FORK
                                                     : Philosopher_State::REQUESTING_FOR_RIGHT_FORK));
    fork.get_fork(philosopher_id);
}

void Philosopher::eat() {
    printer.update_philosopher_state(philosopher_id, Philosopher_State::EATING);

    int time_to_sleep = (rand_gen(engine) + 3500) / 10;
    for (int i = 0; i < 100; i += 10) {
        printer.update_philosopher_state_progress(philosopher_id, i);
        this_thread::sleep_for(chrono::duration<int, milli>(time_to_sleep));
    }
}

void Philosopher::put_off_fork(Fork &fork) {
    fork.put_off_fork();
}

void Philosopher::join() {
    philosopher_thread.join();
}

void Philosopher::increment_eating_counter() {
    ++eating_counter;
    printer.update_eating_counter(philosopher_id, eating_counter);
}
