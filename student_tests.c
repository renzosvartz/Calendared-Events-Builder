#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"
#include "calendar.h"
#include "my_memory_checker_216.h"

/*****************************************************/
/* In this file you will provide tests for your      */
/* calendar application.  Each test should be named  */
/* test1(), test2(), etc. Each test must have a      */
/* brief description of what it is testing (this     */
/* description is important).                        */
/*                                                   */
/* You can tell whether any test failed if after     */
/* executing the students tests, you executed        */
/* "echo $?" on the command line and you get a value */
/* other than 0.  "echo $?" prints the status of     */
/* the last command executed by the shell.           */ 
/*                                                   */
/* Notice that main just calls test1(), test2(), etc.*/
/* and once one fails, the program eventually        */
/* return EXIT_FAILURE; otherwise EXIT_SUCCESS will  */
/* be returned.                                      */
/*****************************************************/

static int comp_minutes(const void *ptr1, const void *ptr2) {
   return ((Event *)ptr1)->duration_minutes - ((Event *)ptr2)->duration_minutes;
}

static int comp_name(const void *ptr1, const void *ptr2);

typedef struct task_info {
  double num;
  char *str;
} Task_info;

static int comp_name(const void *ptr1, const void *ptr2) {
   return strcmp(((Event *)ptr1)->name, ((Event *)ptr2)->name);
}

static Task_info *create_task_info(double num, const char *str) {
   Task_info *task_info = malloc(sizeof(Task_info));

   if (task_info) {
      task_info->str = malloc(strlen(str) + 1);
      if (task_info->str) {
         task_info->num = num;
         strcpy(task_info->str, str);
         return task_info;
      }
   }

   return NULL;
}

static void free_task_info(void *ptr) {
   Task_info *task_info = (Task_info *)ptr;

   free(task_info->str);
   free(task_info);
}

/* Description here: This test checks initializing a calendar,
 * 	printing an empty calendar,
 * 	and destroying the calendar without any memory leaks  */
static int test1() {
   int days = 7;
   Calendar *calendar;

   if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      if (print_calendar(calendar, stdout, 1) == SUCCESS) {
         return destroy_calendar(calendar);
      }
   }
    
   return FAILURE;
}

/* This test checks insertions and removals*/
static int test2() {
	int days = 3;
	Calendar *calendar;

	printf("\nStarting test 2: testing insertions and removals\n");

	init_calendar("Second Calendar", days, comp_minutes, NULL, &calendar);

   	add_event(calendar, "fourth event 1", 1, 4, NULL, 1);
   	add_event(calendar, "second event 1", 1, 2, NULL, 1);
	add_event(calendar, "third event 1", 1, 3, NULL, 1);
   	add_event(calendar, "first event 1", 1, 1, NULL, 1);
	add_event(calendar, "fifth event 1", 1, 5, NULL, 1);
	print_calendar(calendar, stdout, 1);

        add_event(calendar, "fourth event 3", 1, 4, NULL, 3);
        add_event(calendar, "second event 3", 1, 2, NULL, 3);
        add_event(calendar, "third event 3", 1, 3, NULL, 3);
        add_event(calendar, "first event 3", 1, 1, NULL, 3);
        add_event(calendar, "fifth event 3", 1, 5, NULL, 3);
        print_calendar(calendar, stdout, 1);

        add_event(calendar, "fourth event 2", 1, 4, NULL, 2);
        add_event(calendar, "second event 2", 1, 2, NULL, 2);
        add_event(calendar, "third event 2", 1, 3, NULL, 2);
        add_event(calendar, "first event 2", 1, 1, NULL, 2);
        add_event(calendar, "fifth event 2", 1, 5, NULL, 2);
        print_calendar(calendar, stdout, 1);


	remove_event(calendar, "first event 2");
	print_calendar(calendar, stdout, 1);
	remove_event(calendar, "second event 2");
        print_calendar(calendar, stdout, 1);
	remove_event(calendar, "third event 2");
        print_calendar(calendar, stdout, 1);
	remove_event(calendar, "fourth event 2");
        print_calendar(calendar, stdout, 1);
	remove_event(calendar, "fifth event 2");
        print_calendar(calendar, stdout, 1);

	remove_event(calendar, "first event 3");
        print_calendar(calendar, stdout, 1);
	remove_event(calendar, "second event 3");
        remove_event(calendar, "third event 3");
        print_calendar(calendar, stdout, 1);
	remove_event(calendar, "fourth event 3");
        remove_event(calendar, "fifth event 3");
        print_calendar(calendar, stdout, 1);
        add_event(calendar, "sixth event 3", 1, 6, NULL, 3);
        print_calendar(calendar, stdout, 1);

	remove_event(calendar, "first event 1");
        print_calendar(calendar, stdout, 1);
        remove_event(calendar, "third event 1");
        print_calendar(calendar, stdout, 1);
        remove_event(calendar, "fifth event 1");
        print_calendar(calendar, stdout, 1);
        add_event(calendar, "sixth event 1", 1, 6, NULL, 1);
        print_calendar(calendar, stdout, 1);

        return destroy_calendar(calendar);
	
}

/* This test checks clear_day */
static int test3() {
        int days = 3;
        Calendar *calendar;

	printf("\nStarting test 3: clear_day\n");

        init_calendar("Third Calendar", days, comp_minutes, NULL, &calendar);

        add_event(calendar, "fourth event 1", 1, 4, NULL, 1);
        add_event(calendar, "second event 1", 1, 2, NULL, 1);
        add_event(calendar, "third event 1", 1, 3, NULL, 1);
        add_event(calendar, "first event 1", 1, 1, NULL, 1);
        add_event(calendar, "fifth event 1", 1, 5, NULL, 1);
	print_calendar(calendar, stdout, 1); 

	add_event(calendar, "fourth event 3", 1, 4, NULL, 3);
        add_event(calendar, "second event 3", 1, 2, NULL, 3);
        add_event(calendar, "third event 3", 1, 3, NULL, 3);
        add_event(calendar, "first event 3", 1, 1, NULL, 3);
        add_event(calendar, "fifth event 3", 1, 5, NULL, 3);
	print_calendar(calendar, stdout, 1); 

	add_event(calendar, "fourth event 2", 1, 4, NULL, 2);
        add_event(calendar, "second event 2", 1, 2, NULL, 2);
        add_event(calendar, "third event 2", 1, 3, NULL, 2);
        add_event(calendar, "first event 2", 1, 1, NULL, 2);
        add_event(calendar, "fifth event 2", 1, 5, NULL, 2);		
	print_calendar(calendar, stdout, 1);

	clear_day(calendar, 2);
	print_calendar(calendar, stdout, 1);	

	clear_day(calendar, 3);
	print_calendar(calendar, stdout, 1);

	clear_day(calendar, 1);
        print_calendar(calendar, stdout, 1);

        return destroy_calendar(calendar);

}

/* This test checks clear_calendar */
static int test4() {
        int days = 3;
        Calendar *calendar;

	printf("\nStarting test 4: clear_calendar\n");

        init_calendar("Fourth Calendar", days, comp_minutes, NULL, &calendar);

        add_event(calendar, "fourth event 1", 1, 4, NULL, 1);
        add_event(calendar, "second event 1", 1, 2, NULL, 1);
        add_event(calendar, "third event 1", 1, 3, NULL, 1);
        add_event(calendar, "first event 1", 1, 1, NULL, 1);
        add_event(calendar, "fifth event 1", 1, 5, NULL, 1);
        print_calendar(calendar, stdout, 1);

        add_event(calendar, "fourth event 3", 1, 4, NULL, 3);
        add_event(calendar, "second event 3", 1, 2, NULL, 3);
        add_event(calendar, "third event 3", 1, 3, NULL, 3);
        add_event(calendar, "first event 3", 1, 1, NULL, 3);
        add_event(calendar, "fifth event 3", 1, 5, NULL, 3);
        print_calendar(calendar, stdout, 1);

        add_event(calendar, "fourth event 2", 1, 4, NULL, 2);
        add_event(calendar, "second event 2", 1, 2, NULL, 2);
        add_event(calendar, "third event 2", 1, 3, NULL, 2);
        add_event(calendar, "first event 2", 1, 1, NULL, 2);
        add_event(calendar, "fifth event 2", 1, 5, NULL, 2);
        print_calendar(calendar, stdout, 1);

        clear_calendar(calendar);
        print_calendar(calendar, stdout, 1);

        return destroy_calendar(calendar);

}

/* This test checks find_event and find_event_in_day */
static int test5() {
        int days = 3;
        Calendar *calendar;
	Event *event;
	
	printf("\nStarting test 5: find_event and find_event_in_day\n");

        init_calendar("Fifth Calendar", days, comp_minutes, NULL, &calendar);

        add_event(calendar, "fourth event 1", 1, 4, NULL, 1);
        add_event(calendar, "second event 1", 1, 2, NULL, 1);
        add_event(calendar, "third event 1", 1, 3, NULL, 1);
        add_event(calendar, "first event 1", 1, 1, NULL, 1);
        add_event(calendar, "fifth event 1", 1, 5, NULL, 1);
        print_calendar(calendar, stdout, 1);

        add_event(calendar, "fourth event 3", 1, 4, NULL, 3);
        add_event(calendar, "second event 3", 1, 2, NULL, 3);
        add_event(calendar, "third event 3", 1, 3, NULL, 3);
        add_event(calendar, "first event 3", 1, 1, NULL, 3);
        add_event(calendar, "fifth event 3", 1, 5, NULL, 3);
        print_calendar(calendar, stdout, 1);

        add_event(calendar, "fourth event 2", 1, 4, NULL, 2);
        add_event(calendar, "second event 2", 1, 2, NULL, 2);
        add_event(calendar, "third event 2", 1, 3, NULL, 2);
        add_event(calendar, "first event 2", 1, 1, NULL, 2);
        add_event(calendar, "fifth event 2", 1, 5, NULL, 2);
        print_calendar(calendar, stdout, 1);


	if (find_event(calendar, "first event 1", &event) == SUCCESS) {
     		printf("found %s as expected\n", event->name);
   	} 
	else {
     		printf("event not found\n");
   	}
	if (find_event(calendar, "third event 1", &event) == SUCCESS) {
        	printf("found %s as expected\n", event->name);
	}
        else {
                printf("event not found\n");
        }
	if (find_event(calendar, "fifth event 1", &event) == SUCCESS) {
        	printf("found %s as expected\n", event->name);
	}
        else {
                printf("event not found\n");
        }
	if (find_event(calendar, "first event 2", &event) == SUCCESS) {
        	printf("found %s as expected\n", event->name);
	}
        else {
                printf("event not found\n");
        }
        if (find_event(calendar, "third event 2", &event) == SUCCESS) {
        	printf("found %s as expected\n", event->name);
	}
        else {
                printf("event not found\n");
        }
        if (find_event(calendar, "fifth event 2", &event) == SUCCESS) {
        	printf("found %s as expected\n", event->name);
	}
        else {
                printf("event not found\n");
        }
	if (find_event(calendar, "first event 3", &event) == SUCCESS) {
        	printf("found %s as expected\n", event->name);
	}
        else {
                printf("event not found\n");
        }
        if (find_event(calendar, "third event 3", &event) == SUCCESS) {
        	printf("found %s as expected\n", event->name);
	}
        else {
                printf("event not found\n");
        }
        if (find_event(calendar, "fifth event 3", &event) == SUCCESS) {
        	printf("found %s as expected\n", event->name);
	}
        else {
                printf("event not found\n");
        }

	if (find_event_in_day(calendar, "first event 1", 1, &event) == SUCCESS) {
        	printf("found %s as expected\n", event->name);
	}
        else {
                printf("event not found\n");
        }
	if (find_event_in_day(calendar, "first event 1", 3, &event) == SUCCESS) {
                printf("found %s\n", event->name);
        }
        else {
                printf("event not found as expected\n");
        }
	if (find_event_in_day(calendar, "first event 2", 2, &event) == SUCCESS) {
                printf("found %s as expected\n", event->name);
        }
        else {
                printf("event not found\n");
        }
        if (find_event_in_day(calendar, "first event 2", 1, &event) == SUCCESS) {
                printf("found %s\n", event->name);
        }
        else {
                printf("event not found as expected\n");
        }
	if (find_event_in_day(calendar, "first event 3", 3, &event) == SUCCESS) {
        	printf("found %s as expected\n", event->name);
	}
        else {
                printf("event not found\n");
        }
        if (find_event_in_day(calendar, "first event 3", 1, &event) == SUCCESS) {
                printf("found %s\n", event->name);
        }
        else {
                printf("event not found as expected\n");
        }

        return destroy_calendar(calendar);
}

/* This test checks expected failures, duplicate entries, and
 * removals of non-existant events */
static int test6() {
        int days = 3;
        Calendar *calendar;

        printf("\nStarting test 6: expected failures\n");

	if (init_calendar("No calendar fail", days, comp_minutes, NULL, NULL) == FAILURE) {
		printf("Fail #1 as expected\n");
	}

	if (init_calendar(NULL, days, comp_minutes, NULL, &calendar) == FAILURE) {
                printf("Fail #2 as expected\n");
        }

        init_calendar("Sixth Calendar", days, comp_minutes, NULL, &calendar);

	if (print_calendar(NULL, stdout, 1) == FAILURE) {
                printf("Fail #3 as expected\n");
        }
	if (print_calendar(calendar, NULL, 1) == FAILURE) {
                printf("Fail #4 as expected\n");
        }

	if (add_event(NULL, "fail", 1, 1, NULL, 1) == FAILURE) {
		printf("Fail #5 as expected\n");
	}
	if (add_event(calendar, NULL, 1, 1, NULL, 1) == FAILURE) {
                printf("Fail #6 as expected\n");
        }
	if (add_event(calendar, "fail", -1, 1, NULL, 1) == FAILURE) {
                printf("Fail #7 as expected\n");
        }
	if (add_event(calendar, "fail", 2401, 1, NULL, 1) == FAILURE) {
                printf("Fail #8 as expected\n");
        }
	if (add_event(calendar, "fail", 1, 0, NULL, 1) == FAILURE) {
                printf("Fail #9 as expected\n");
        }
	if (add_event(calendar, "fail", 1, 1, NULL, 0) == FAILURE) {
                printf("Fail #10 as expected\n");
        }
	if (add_event(calendar, "fail", 1, 1, NULL, 4) == FAILURE) {
                printf("Fail #11 as expected\n");
        }
	if (add_event(calendar, "don't duplicate me", 1, 1, NULL, 1) == SUCCESS) {
                if (add_event(calendar, "don't duplicate me", 1, 1, NULL, 1) == FAILURE) {
                	printf("Fail #12 as expected\n");
        	}
		if (add_event(calendar, "don't duplicate me", 2, 1, NULL, 1) == FAILURE) {
                        printf("Fail #12.1 as expected\n");
                }
		if (add_event(calendar, "don't duplicate me", 1, 2, NULL, 1) == FAILURE) {
                        printf("Fail #12.2 as expected\n");
                }
		if (add_event(calendar, "don't duplicate me", 1, 1, NULL, 2) == FAILURE) {
                        printf("Fail #12.3 as expected\n");
                }
        }
	print_calendar(calendar, stdout, 1);

	if (remove_event(calendar, "don't duplicate me") == SUCCESS) {
		if (remove_event(calendar, "don't duplicate me") == FAILURE) {
			printf("Fail #13 as expected\n");
		}	
		if (remove_event(NULL, "fail") == FAILURE) {
                        printf("Fail #13.1 as expected\n");
                }
		if (remove_event(calendar, NULL) == FAILURE) {
                        printf("Fail #13.2 as expected\n");
                }
			
	}
	print_calendar(calendar, stdout, 1);

	if (add_event(calendar, "will succeed", 1, 1, NULL, 1) == FAILURE) {
		printf("Fail #13.3 unexpected\n");
	}	
	else {
		printf("added event as expected\n");
	}
	if (find_event(calendar, "does not exist", NULL) == FAILURE) {
		printf("Fail #14 as expected\n");
	}
	if (find_event(NULL, "does not exist", NULL) == FAILURE) {
                printf("Fail #15 as expected\n");
        }
	if (find_event(calendar, NULL, NULL) == FAILURE) {
                printf("Fail #16 as expected\n");
        }
	if (find_event_in_day(calendar, "does not exist", 1, NULL) == FAILURE) {
                printf("Fail #17 as expected\n");
        }
	if (find_event_in_day(NULL, "does not exist", 1, NULL) == FAILURE) {
                printf("Fail #18 as expected\n");
        }
	if (find_event_in_day(calendar, NULL, 1, NULL) == FAILURE) {
                printf("Fail #19 as expected\n");
        }
	if (find_event_in_day(calendar, "does not exist", 0, NULL) == FAILURE) {
                printf("Fail #20 as expected\n");
        }
	if (find_event_in_day(calendar, "does not exist", 4, NULL) == FAILURE) {
                printf("Fail #21 as expected\n");
        }


        add_event(calendar, "fourth event 1", 1, 4, NULL, 1);
        add_event(calendar, "second event 1", 1, 2, NULL, 1);
        add_event(calendar, "third event 1", 1, 3, NULL, 1);
        add_event(calendar, "first event 1", 1, 1, NULL, 1);
        add_event(calendar, "fifth event 1", 1, 5, NULL, 1);
        print_calendar(calendar, stdout, 1);

	if (clear_day(NULL, 1) == FAILURE) {
		printf("Fail #22 as expected\n");
	}	
	if (clear_day(calendar, 0) == FAILURE) {
                printf("Fail #23 as expected\n");
        }
	if (clear_day(calendar, 4) == FAILURE) {
                printf("Fail #24 as expected\n");
        }
	if (clear_calendar(NULL) == FAILURE) {
                printf("Fail #25 as expected\n");
        }
	if (clear_day(calendar, 1) == SUCCESS) {
                printf("Clear Day 1 (1) successful as expected\n");
		
		if (add_event(calendar, "will succeed 1", 1, 1, NULL, 1) == FAILURE) {
                	printf("Fail #25.1 unexpected failure\n");
        	}
        	else {
                	printf("added event as expected\n");
        	}
        }
	if (clear_day(calendar, 1) == SUCCESS) {
                printf("Clear Day 1 (2) successful as expected\n");
        }
	if (clear_calendar(calendar) == SUCCESS) {
                printf("Clear Calendar successful as expected\n");
		if (add_event(calendar, "will succeed 2", 1, 1, NULL, 1) == FAILURE) {
                        printf("Fail #25.2 unexpected failure\n");
                }
                else {
                        printf("added event as expected\n");
                }	
        }	

	if (destroy_calendar(NULL) == FAILURE) {
		printf("Fail #26 as expected\n");
	}
	if (destroy_calendar(calendar) == SUCCESS) {
                printf("Destroy Calendar successful as expected\n");
        }

	return SUCCESS;
}

/* Tests get_event_info */
int test7() {
   	Calendar *calendar;
   	Task_info *info;

	printf("\nStarting test 7: testing get_event_info\n");

   	init_calendar("Seventh Calendar", 1, comp_name, free_task_info, &calendar);

   	info = create_task_info(1, "Task 1 Info");
   	add_event(calendar, "Task 1", 1, 1, info, 1);
	info = get_event_info(calendar, "Task 1");
        printf("Num: %.2f, Str: %s\n", info->num, info->str);
	
	if (get_event_info(calendar, "does not exist") == NULL) {
		printf("Info not found as expected\n");
	}

	return destroy_calendar(calendar);
}

int main() {
   int result = SUCCESS;

   /***** Starting memory checking *****/
   start_memory_check();
   /***** Starting memory checking *****/

   if (test1() == FAILURE) result = FAILURE;
   if (test2() == FAILURE) result = FAILURE;
   if (test3() == FAILURE) result = FAILURE;
   if (test4() == FAILURE) result = FAILURE;
   if (test5() == FAILURE) result = FAILURE;
   if (test6() == FAILURE) result = FAILURE;
   if (test7() == FAILURE) result = FAILURE;

   /****** Gathering memory checking info *****/
   stop_memory_check();
   /****** Gathering memory checking info *****/
   
   if (result == FAILURE) {
      exit(EXIT_FAILURE);
   }

   return EXIT_SUCCESS;
}
