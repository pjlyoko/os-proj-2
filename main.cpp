#include <iostream>
#include <thread>
#include <sstream>
#include "Table.h"
#include "Philosopher.h"
#include "Screen_Printer.h"

using namespace std;

const int philosophers_amount = 10;

int main() {
    Screen_Printer printer(philosophers_amount);
    Table table(philosophers_amount, printer);

    table.start_feast();

    printer.close_program();

    table.stop_feast();

    return 0;
}