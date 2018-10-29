#include <stdio.h>
#include <unistd.h>
#include <algorithm>
#include <ctime>
#include <iostream>
using namespace std;

struct task{
    int hour;
    int min;
    int sec;
    string task_roll;
}

vector<task>Tasks;

void read_file(){
	//function that read and prepare data from input file for use
	FILE *f;
	f = fopen("mycrontab", "r");
	string temp_str;
	char* temp_Cstring;
	struct task temp_task;
	while(getline(f, temp_str) > 0){
		sscanf(temp_str, "%d:%d:%d %s", &temp_task.hour, &temp_task.min, &temp_task.sec, temp_task.task_roll);	//Now we have one of tasks in temp_task

	}
	printf("%s\n", temp_str);
}

void changed(){ //function that will look for changes in input file
	//TODO
}

void update_tasks(){ //function that will update vector of tasks 
	//TODO
}

int main(){
   /* for(;;){	// main loop 
	if(changed){
	    update_tasks();
	}
	for(int i = 0; i < Tasks.size(); i++){
	    if(current_Time >= Tasks[i].Time) exec();
	}
    }*/
    read_file();

}
/*
    time_t t = time(0);
    tm* now = localtime(&t);
    tm_sec; tm_min; tm_hour;
    things about time_t I will need. Just not ot forget
*/



