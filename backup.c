#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calendar.h"
#include "event.h"
#include "my_memory_checker_216.h"

static int create_event(Event **event, const char *name, int start_time,
              int duration_minutes, void *info);

/* Initializes a Calendar by allocated memory for the Calendar object
 * and its attributes */
int init_calendar(const char *name, int days,
                  int (*comp_func) (const void *ptr1, const void *ptr2),
                  void (*free_info_func) (void *ptr), Calendar ** calendar) {
	Calendar *new_calendar = NULL;
	
	/* Validate arguments */
	if (!calendar || !name || days < 1) {
		return FAILURE;
	}

	/* Allocate and validate memory for the calendar and attributes */
	if (!(new_calendar = malloc(sizeof(Calendar)))) {
		return FAILURE;
	}

	if (!(new_calendar->name = malloc(sizeof(strlen(name) + 1)))) {
		return FAILURE;
	}
	
	if (!(new_calendar->events = calloc(days, sizeof(Event *)))) {
		return FAILURE;
	}

	/* Assign attributes */
	strcpy(new_calendar->name, name);
	new_calendar->days = days;
	new_calendar->total_events = 0;
	new_calendar->comp_func = comp_func;
	new_calendar->free_info_func = free_info_func;

	*calendar = new_calendar;

	return SUCCESS;

}

/* Iteratively prints out each day in the calendar and the information 
 * about all of the events on any day */
int print_calendar(Calendar *calendar, FILE *output_stream, int print_all) {
	int i = 0, days = 0;
	Event *curr_event = NULL;

	/* Validate arguments */
	if (!calendar || !output_stream) {
		return FAILURE;
	}

	/* Print header */
	fprintf(output_stream, "**** Events ****\n");

	/* Allocate memory for Event iterator curr_event */
	/*if (!(curr_event = malloc(sizeof(Event)))) {
                return FAILURE;
        }*/

	days = calendar->days;

	for (; i < days; i++) {

		/* Obtains access to the i-th linked list of events */
		curr_event = *(calendar->events + i);

		/* Print out the linked list */
		while (curr_event) {
		
			/* Print Day i */
			if (curr_event == *(calendar->events)) {
				fprintf(output_stream, "Day %d\n", i);
			}

			/* Print Event */
			fprintf(output_stream, "Event's Name: \"%s\", Start_time: %d, Duration: %d\n", curr_event->name, curr_event->start_time, curr_event->duration_minutes);

			/* Traverse linked lits */
			curr_event = curr_event->next;
		} 
	}

	/* Optional print total events */
	if (print_all) {
		fprintf(output_stream, "Total Events: %d\n", calendar->total_events);
	}
	
	return SUCCESS;

}

/* Adds an event to a specified day in the Calendar */
int add_event(Calendar *calendar, const char *name, int start_time,
              int duration_minutes, void *info, int day) {
	Event *new_event = NULL, *curr_event = NULL, *prev_event = NULL;	
	int (*comp_func)(const void *, const void *) = NULL;


	/* Validate arguments */
	if (!calendar || !name || start_time < 0 || start_time > 2400
		|| duration_minutes <= 0 || day < 1 || day > calendar->days) {
		return FAILURE;
	}
	
	/* Allocate memory for Event iterator curr_event */
	/*if (!(curr_event = malloc(sizeof(Event)))) {
		return FAILURE;
	}*/

	/* Obtain Event at the i-th day in the linked list of Events */
	curr_event = *(calendar->events + day - 1);
	
	/* Obtain comparator function */
	comp_func = calendar->comp_func;

	/* Traverse the linked list to place new_event or find duplicate */
	while (curr_event && comp_func(curr_event, curr_event->next) > 0
		&& !strcmp(curr_event->name, name)) {
	}

	/* Process outcome of traversal (While loop) */

	/* Event already exits */
	if (!strcmp(curr_event->name, name)) {
		return FAILURE;
        }

	/* Allocate new event memory */
	if (!(new_event = malloc(sizeof(Event)))) {
		return FAILURE;
	}

	/* Create new event */
	if (create_event(&new_event, name, start_time, duration_minutes, info) == FAILURE) {
		return FAILURE;
	}

	/* Place new event in the linked list*/
	if (!curr_event) {
	
		/* Place at beginning */
		if (!prev_event) {
			new_event->next = curr_event;
			curr_event = new_event;
		}
		else {
	
			/* Place at end */
			prev_event->next = new_event;
		}

	}
	else {
		
		/* Place inbetween events */
		prev_event->next = new_event;
		new_event->next = curr_event;
	}

	calendar->total_events++;

	return SUCCESS;
}

static int create_event(Event **event, const char *name, int start_time,
              int duration_minutes, void *info) {
	Event *new_event = NULL;

	/* Allocate and validate memory for the new event */
	if (!(new_event = malloc(sizeof(Event)))) {
		return FAILURE;
	}	
	if (!(new_event->name = malloc(sizeof(strlen(name) + 1)))) {
		return FAILURE;
	}

	/* Assign attributes */
	strcpy(new_event->name, name);
	new_event->start_time = start_time;
	new_event->duration_minutes = duration_minutes;
	new_event->info = info;
	new_event->next = NULL;

	/* Assign target event memory as new_event memory */
	*event = new_event;

	return SUCCESS;
}

/* Deallocates all dynamically-allocated memory for the Calendar */
int destroy_calendar(Calendar *calendar) {
	int i = 0, days = 0; 
       	Event *temp = NULL;
	Event *curr_event = NULL;
	
	/* Validate arguments */
	if (!calendar) {
		return FAILURE;
	}

	/*
	if (!(curr_event = malloc(sizeof(Event)))) {
                return FAILURE;
        }
	if (!(temp = malloc(sizeof(Event)))) {
                return FAILURE;
        }*/


	days = calendar->days;
	
	for (; i < days; i++) {

                /* Obtains access to the i-th linked list of events */
                curr_event = *(calendar->events + i);

                /* Free the linked list */
                while (curr_event) {

			/* Maintain a reference to the rest of the list */
			temp =  curr_event->next;

			/* Free name */
			free(curr_event->name);

			/* Optionally free info */
			if (curr_event->info && calendar->free_info_func) {
				calendar->free_info_func(curr_event->info);
			}
		
			/* Free the Event node */
			free(curr_event);

			/* Traverse the list */
			curr_event = temp;	
		}
	}

	free(calendar->name);
	free(calendar);
	
	return SUCCESS;		
}

/**/
int find_event(Calendar *calendar, const char *name, Event **event) {
        return -1;
}

/**/
int find_event_in_day(Calendar *calendar, const char *name, int day,
                      Event **event) {
        return -1;
}

/**/
int remove_event(Calendar *calendar, const char *name){
        return -1;
}

/**/
void *get_event_info(Calendar *calendar, const char *name) {
        return NULL;
}

/**/
int clear_calendar(Calendar *calendar) {
        return -1;
}

/**/
int clear_day(Calendar *calendar, int day) {
	return -1;
}
