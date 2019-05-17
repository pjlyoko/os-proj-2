#include "Table.h"

Table::Table(int philosophers_amount, Screen_Printer &printer) : printer(printer),
																 philosophers_amount(philosophers_amount) {
	for(int i = 0; i < philosophers_amount; i++) {
		forks.push_back(new Fork(i, printer));
	}

	feast = false;
}

void Table::start_feast() {
	feast = true;

	for(int i = 0; i < philosophers_amount; i++) {
		if(i != philosophers_amount - 1) {
			philosophers.push_back(new Philosopher(i, *this, *forks[i], *forks[i + 1], printer));
		} else {
			philosophers.push_back(new Philosopher(i, *this, *forks[0], *forks[i], printer));
		}
	}
}

void Table::stop_feast() {
	feast = false;

	for(int i = 0; i < philosophers_amount; i++) {
		philosophers[i]->join();
	}
}

Table::~Table() {
	for(int i = 0; i < philosophers_amount; i++) {
		delete philosophers[i];
		delete forks[i];
	}
}