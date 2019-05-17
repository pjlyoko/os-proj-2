#ifndef DINING_PHILOSOPHERS_TABLE_H
#define DINING_PHILOSOPHERS_TABLE_H


#include <atomic>
#include <vector>
#include "Fork.h"
#include "Philosopher.h"
#include "Screen_Printer.h"

class Philosopher;

class Table {
private:
	int philosophers_amount;
	std::atomic<bool> feast;

	Screen_Printer &printer;

	std::vector<Philosopher *> philosophers;
	std::vector<Fork *> forks;
public:
	Table(int philosophers_amount, Screen_Printer &printer);

	~Table();

	void start_feast();

	inline bool is_feast() { return feast; }

	void stop_feast();
};


#endif //DINING_PHILOSOPHERS_TABLE_H
