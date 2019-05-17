#ifndef DINING_PHILOSOPHERS_PHILOSOPHER_H
#define DINING_PHILOSOPHERS_PHILOSOPHER_H

#include <thread>
#include <iostream>
#include <random>
#include "Fork.h"
#include "Table.h"
#include "Screen_Printer.h"

class Table;

class Philosopher {
private:
	std::default_random_engine engine;
	std::uniform_int_distribution<int> rand_gen;

	int philosopher_id;
	int eating_counter;

	Table &table;
	Fork &left;
	Fork &right;

	std::thread philosopher_thread;

	Screen_Printer &printer;

	void think();

	void take_fork(Fork &fork);

	void eat();

	static void put_off_fork(Fork &fork);

	void increment_eating_counter();

public:
	Philosopher(int philosopher_id, Table &table, Fork &left, Fork &right, Screen_Printer &printer);

	void dine();

	void join();
};


#endif
