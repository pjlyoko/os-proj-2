#include "Table.h"

Table::Table(int philosophers_amount, Screen_Printer &printer) : printer(printer) {
    this->philosophers_amount = philosophers_amount;

    forks = new Fork *[philosophers_amount];
    for (int i = 0; i < philosophers_amount; i++) {
        forks[i] = new Fork(i, printer);
    }

    feast = false;
}

void Table::start_feast() {

    feast = true;

    philosophers = new Philosopher *[philosophers_amount];
    for (int i = 0; i < philosophers_amount; i++) {
        if (i != philosophers_amount - 1)
            philosophers[i] = new Philosopher(i, *this, *forks[i], *forks[i + 1], printer);
        else
            philosophers[i] = new Philosopher(i, *this, *forks[0], *forks[i], printer);
    }
}

void Table::stop_feast() {
    feast = false;

    for (int i = 0; i < philosophers_amount; i++)
        philosophers[i]->join();
}

Table::~Table() {
    for (int i = 0; i < philosophers_amount; i++) {
        delete philosophers[i];
        delete forks[i];
    }

    delete[] forks;
    delete[] philosophers;
}