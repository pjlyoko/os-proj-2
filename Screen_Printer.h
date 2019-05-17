#ifndef DINING_PHILOSOPHERS_SCREENPRINTER_H
#define DINING_PHILOSOPHERS_SCREENPRINTER_H


#include <mutex>
#include "Philosopher_State.h"

class Screen_Printer {
private:
	const int screen_width = 80;
	const int screen_height = 24;

	const std::string philosopher_str = "PHIL";
	const std::string eating_str = "EATING    ";
	const std::string thinking_str = "THINKING  ";
	const std::string waiting_left_str = "WAITING L ";
	const std::string waiting_right_str = "WAITING R ";
	const std::string finished_str = "FINISHED  ";
	const std::string fork_str = "FORK";
	const std::string free_fork_str = "FREE  ";

	int philosophers_amount;

	std::mutex out_mutex;

	void clean_progress(int philosopher);

	void move_cursor();

	void draw_hlines();

	void draw_vlines();

	void draw_headlines();

	void draw_basics();

	void draw_info();

public:
	explicit Screen_Printer(int philosophers_amount);

	~Screen_Printer();

	void update_philosopher_state(int philosopher, Philosopher_State state);

	void update_philosopher_state_progress(int philosopher, int progress);

	void update_eating_counter(int philosopher, int eating_counter);

	void update_fork_owner(int fork, int philosopher);

	void free_fork(int fork);

	void close_program();
};


#endif
