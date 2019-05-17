#include <ncurses.h>
#include "Screen_Printer.h"

Screen_Printer::Screen_Printer(int philosophers_amount) {
    this->philosophers_amount = philosophers_amount;

    WINDOW *win = initscr();
    noecho();
    box(win, ACS_VLINE, ACS_HLINE);

    draw_hlines();
    draw_vlines();
    draw_headlines();
    draw_basics();
    draw_info();

    mvaddch(1, 2, ACS_ULCORNER);
    mvaddch(21, 2, ACS_LLCORNER);
    mvaddch(1, 40, ACS_URCORNER);
    mvaddch(21, 40, ACS_LRCORNER);

    mvaddch(1, 50, ACS_ULCORNER);
    mvaddch(21, 50, ACS_LLCORNER);
    mvaddch(1, 69, ACS_URCORNER);
    mvaddch(21, 69, ACS_LRCORNER);

    move_cursor();
}

void Screen_Printer::close_program() {
    getch();
}

Screen_Printer::~Screen_Printer() {
    endwin();
}

void Screen_Printer::update_philosopher_state(int philosopher, Philosopher_State state) {
    std::lock_guard<std::mutex> lock(out_mutex);
    std::string state_str;
    switch (state) {
        case (Philosopher_State::EATING):
            state_str = eating_str;
            break;
        case (Philosopher_State::REQUESTING_FOR_LEFT_FORK):
            state_str = waiting_left_str;
            clean_progress(philosopher);
            break;
        case (Philosopher_State::REQUESTING_FOR_RIGHT_FORK):
            state_str = waiting_right_str;
            clean_progress(philosopher);
            break;
        case (Philosopher_State::THINKING):
            state_str = thinking_str;
            break;
        case (Philosopher_State::FINISHED):
            state_str = finished_str;
            clean_progress(philosopher);
            break;
    }

    mvprintw(philosopher + 4, 21, state_str.c_str());
    move_cursor();
}

void Screen_Printer::update_philosopher_state_progress(int philosopher, int progress) {
    std::lock_guard<std::mutex> lock(out_mutex);
    std::string progress_str = std::to_string(progress) + "%% ";
    mvprintw(philosopher + 4, 32, progress_str.c_str());
    move_cursor();
}

void Screen_Printer::clean_progress(int philosopher) {
    mvprintw(philosopher + 4, 32, "     ");
    move_cursor();
}

void Screen_Printer::update_eating_counter(int philosopher, int eating_counter) {
    std::lock_guard<std::mutex> lock(out_mutex);
    std::string counter_str = std::to_string(eating_counter);
    mvprintw(philosopher + 4, 12, counter_str.c_str());
    move_cursor();
}

void Screen_Printer::free_fork(int fork) {
    std::lock_guard<std::mutex> lock(out_mutex);
    mvprintw(fork + 4, 60, free_fork_str.c_str());
    move_cursor();
}

void Screen_Printer::update_fork_owner(int fork, int philosopher) {
    std::lock_guard<std::mutex> lock(out_mutex);
    std::string owner_str = philosopher_str + std::to_string(philosopher);
    mvprintw(fork + 4, 60, owner_str.c_str());
    move_cursor();
}

void Screen_Printer::move_cursor() {
    move(screen_height - 2, 1);
    refresh();
}

void Screen_Printer::draw_hlines() {
    move(1, 2);
    hline(ACS_HLINE, 39);

    move(3, 2);
    hline(ACS_HLINE, 39);

    move(21, 2);
    hline(ACS_HLINE, 39);

    move(1, 50);
    hline(ACS_HLINE, 20);

    move(3, 50);
    hline(ACS_HLINE, 20);

    move(21, 50);
    hline(ACS_HLINE, 20);
}

void Screen_Printer::draw_vlines() {
    move(2, 2);
    vline(ACS_VLINE, 19);

    move(2, 11);
    vline(ACS_VLINE, 19);

    move(2, 20);
    vline(ACS_VLINE, 19);

    move(2, 31);
    vline(ACS_VLINE, 19);

    move(2, 40);
    vline(ACS_VLINE, 19);

    move(2, 50);
    vline(ACS_VLINE, 19);

    move(2, 59);
    vline(ACS_VLINE, 19);

    move(2, 69);
    vline(ACS_VLINE, 19);
}

void Screen_Printer::draw_headlines() {
    mvprintw(2, 3, "PHIL NO");
    mvprintw(2, 12, "COUNTER");
    mvprintw(2, 21, "STATE");
    mvprintw(2, 32, "PROGRESS");
    mvprintw(2, 51, "FORK NO");
    mvprintw(2, 60, "OWNER NO");
}

void Screen_Printer::draw_basics() {
    for (int i = 0; i < philosophers_amount; i++) {
        std::string phil_print = philosopher_str + std::to_string(i);
        mvprintw(i + 4, 3, phil_print.c_str());
        mvprintw(i + 4, 12, "0");
        std::string fork_print = fork_str + std::to_string(i);
        mvprintw(i + 4, 51, fork_print.c_str());
        mvprintw(i + 4, 60, free_fork_str.c_str());
    }
}

void Screen_Printer::draw_info() {
    mvprintw(screen_height - 2, 5, "key - quit");
}
