#include<stdio.h>
#include<stdlib.h>
#include<event.h>
#include<event2/util.h>

struct event ev;
struct timeval tv;

void time_cb(int fd, short event, void*argc)
{
	printf("timer wakeup\n");
	event_add(&ev, &tv);  // reschedule timer
}
int main(){
	// struct event_base *base = event_init();
	event_init();
	
	tv.tv_sec = 10;
	tv.tv_usec = 0;
	evtimer_set(&ev, time_cb, NULL);
	event_add(&ev, &tv);
	// event_base_dispatch(base);
	event_dispatch();
	return 0;
	
}
