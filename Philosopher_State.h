#ifndef DINING_PHILOSOPHERS_PHILOSOPHER_STATE_H
#define DINING_PHILOSOPHERS_PHILOSOPHER_STATE_H


enum Philosopher_State {
	THINKING,
	REQUESTING_FOR_LEFT_FORK,
	REQUESTING_FOR_RIGHT_FORK,
	EATING,
	FINISHED,
};


#endif //DINING_PHILOSOPHERS_PHILOSOPHER_STATE_H
