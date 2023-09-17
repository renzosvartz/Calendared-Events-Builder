/* Renzo Alejo Moron-Svartz */
/* UID: 114145086 */
/* grace id: rsvartz */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calendar.h"
#include "event.h"
#include "my_memory_checker_216.h"

static int create_event(Event **event, const char *name, int start_time,
              int duration_minutes, void *info);
static void free_event(Calendar *calendar, Event *event);

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
	new_calendar = malloc(sizeof(Calendar));
	if (!new_calendar) {
		return FAILURE;
	}
	new_calendar->name = malloc(strlen(name) + 1);
	if (!(new_calendar->name)) {
		return FAILURE;
	}
	new_calendar->events = calloc(days, sizeof(Event *));
	if (!(new_calendar->events)) {
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

/* Iteratiively prints out each day in the calendar and the information 
 * about all of the events on any day */
int print_calendar(Calendar *calendar, FILE *output_stream, int print_all) {
	int i = 0, days = 0;
	Event *curr_event = NULL;

	/* Validate arguments */
	if (!calendar || !output_stream) {
		return FAILURE;
	}

	/* Print header */
	if (print_all) {
		fprintf(output_stream, "Calendar's Name: \"%s\"\n", calendar->name);
        	fprintf(output_stream, "Days: %d\n", calendar->days);
                fprintf(output_stream, "Total Events: %d\n\n", calendar->total_events);
        }

	fprintf(output_stream, "**** Events ****\n");

	days = calendar->days;

	for (; calendar->total_events > 0 && i < days; i++) {

		/* Obtains access to the i-th linked list of events */
		curr_event = calendar->events[i];

                fprintf(output_stream, "Day %d\n", i + 1);

		/* Print out the linked list */
		while (curr_event) {

			/* Print Event */
			fprintf(output_stream, "Event's Name: \"%s\", Start_time: %d, Duration: %d\n", curr_event->name, curr_event->start_time, curr_event->duration_minutes);

			/* Traverse linked lits */
			curr_event = curr_event->next;
		}
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

	if ((find_event(calendar, name, NULL) == SUCCESS)) {
                return FAILURE;
        }
	
	/* Create new event */
        if ((create_event(&new_event, name, start_time, duration_minutes, info) == FAILURE)) {
                return FAILURE;
        }

	/* Obtain Event at the i-th day in the linked list of Events */
	curr_event = calendar->events[day - 1];

	/* Obtain comparator function */
	comp_func = calendar->comp_func;

	/* Traverse the linked list to place new_event or find duplicate */
	while (curr_event && comp_func(new_event, curr_event) > 0) {
		prev_event = curr_event;
		curr_event = curr_event->next;
	}

	/* Place new event in the linked list*/
	if (!prev_event) {
	
		/* Place at beginning */
		new_event->next = curr_event;
		calendar->events[day - 1] = new_event;

	}
	else if (!curr_event) {
	
		/* Place at end */
	       	prev_event->next = new_event;

	}
	else {
	
		/* Place inbetween events */
		prev_event->next = new_event;
		new_event->next = curr_event;
	}

	calendar->total_events++;

	return SUCCESS;
}

/* Helper function allocates and creates a new event */
static int create_event(Event **event, const char *name, int start_time,
              int duration_minutes, void *info) {
	Event *new_event = NULL;

	/* Allocate and validate memory for the new event */
	if (!(new_event = malloc(sizeof(Event)))) {
		return FAILURE;
	}	
	if (!(new_event->name = malloc(strlen(name) + 1))) {
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
	
	/* Validate arguments */
	if (!calendar) {
		return FAILURE;
	}

	/* Free calendar using clear_calendar */
	if (clear_calendar(calendar) == FAILURE) {
		return FAILURE;
	}
	free(calendar->name);
	free(calendar->events);
	free(calendar);
	
	return SUCCESS;		
}

/* Helper function frees events */
static void free_event(Calendar *calendar, Event *event) {

	/* Free name */
        free(event->name);

        /* Optionally free info */
        if (event->info && calendar->free_info_func) {
             	calendar->free_info_func(event->info);
       	}

     	/* Free the Event node */
     	free(event);

}

/* Finds an event in the calendar by using calls to find_event_in_day */
int find_event(Calendar *calendar, const char *name, Event **event) {
	int day = 1, days, not_found = FAILURE;

	/* Validate calendar and name */
	if (!calendar || !name) {
		return FAILURE;
	}

	days = calendar->days;

	/* Iterate through all list of events 
  	 * by using function find_event_in_day
  	 * to find the target event */
	while (day <= days && 
		(not_found = find_event_in_day(calendar, name, day, event))) {
		day++;
	}

	/* Found target */
	if (!not_found) {
		return SUCCESS;
	}
	
	return FAILURE;
}

/* Iterates through the events in a day to find a target event 
 * and returns the event in the event parameter if not NULL */
int find_event_in_day(Calendar *calendar, const char *name, int day,
                      Event **event) {
	Event *curr_event = NULL;

        /* Validate calendar and name */
        if (!calendar || !name || day < 1 || day > calendar->days) {
                return FAILURE;
        }

        /* Iterate through all list of events to find the target event */
        curr_event = calendar->events[day - 1];

        /* Iterate through the day */
        while (curr_event) {

            	/* Target Event found */
             	if (!strcmp(curr_event->name, name)) {

             		/* Return event */
            		if (event) {
             			*event = curr_event;
          		}
         	
			return SUCCESS;
        	
		}

            	curr_event = curr_event->next;
        }

        return FAILURE;
	        
}

/* Removes and event from the calendar composed of linked lists of 
 * events for each day */
int remove_event(Calendar *calendar, const char *name){
        Event *curr_event = NULL;
	Event *prev_event = NULL;
        int i = 0, days;

        /* Validate calendar and name */
        if (!calendar || !name) {
                return FAILURE;
        }

	days = calendar->days;
        /* Iterate through all list of events to find the target event */
	for (; i < days; i++) {

		curr_event = calendar->events[i];

		prev_event = NULL;	

        	/* Iterate through i-th list */
        	while (curr_event) {

                	/* Target Event found */
                	if (!strcmp(curr_event->name, name)) {

				/* Remove head of list */
				if (!prev_event) {
					calendar->events[i] =
							curr_event->next;
				}
				else {
					prev_event->next = curr_event->next;
				}
				
				/* Free event */
				free_event(calendar, curr_event);
				curr_event = NULL;
				calendar->total_events--;
				return SUCCESS;
				
                	}

			prev_event = curr_event;
             		curr_event = curr_event->next;
        	}
	}

        return FAILURE;
}

/* Returns the information for a given event if found in the calendar */
void *get_event_info(Calendar *calendar, const char *name) {
	Event *event = NULL;
	
	if ((find_event(calendar, name, &event) == SUCCESS)) {
		return event->info;
	}

	return NULL;
}

/* Clears all events from a calendar, leaving empty Event lists
 * by making calls to clear_day */
int clear_calendar(Calendar *calendar) {
        int day = 1, days = 0;

        /* Validate arguments */
        if (!calendar) {
                return FAILURE;
        }

        days = calendar->days;

	/* Clear the calendar by successive alls to clear_day */
        for (; day <= days; day++) {
	
		clear_day(calendar, day);
	
        }

        return SUCCESS;

}

/* Clears all events in a day by using free_event in a loop */
int clear_day(Calendar *calendar, int day) {
        Event *temp = NULL;
        Event *curr_event = NULL;

        /* Validate arguments */
        if (!calendar || day < 1 || day > calendar->days) {
                return FAILURE;
        }

        /* Obtains access to the i-th linked list of events */
        curr_event = calendar->events[day - 1];

        /* Free the linked list */
        while (curr_event) {
	

        	/* Maintain a reference to the rest of the list */
                temp =  curr_event->next;

                /* Free the Event node */
                free_event(calendar, curr_event);

                /* Traverse the list */
                curr_event = temp;
        
		calendar->total_events--;
        }

	curr_event = NULL;
	calendar->events[day - 1] = NULL;

        return SUCCESS;

}
