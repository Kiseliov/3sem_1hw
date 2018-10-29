#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>
#include <cstddef>
#include <cstring>
#include <vector>
using namespace std;

struct task{
    int hour;
    int min;
    int sec;
    vector<string>roll;
};


vector<task>Tasks;

void read_file(){
	//function that read and prepare data from input file for use
	ifstream f("mycrontab");
	string temp_str;
	int j = 0;
	while(getline(f, temp_str)){														//get new line from file
		char *temp_Cstr = new char[temp_str.size() + 1];								//init C-string in order to use it for reading HH:MM:SS on 33 line
		strcpy(temp_Cstr,temp_str.c_str());												//copying our c++String to C-string
		struct task temp_task;															//init temporary structure that we will push_back in Tasks
		sscanf(temp_Cstr,"%d:%d:%d", &temp_task.hour, &temp_task.min, &temp_task.sec);	//reading HH:MM:SS to temporary
		int i = temp_str.find_first_of(' ') + 1;										//init i - counter that on the begining points on 1 symbol of roll
		string tt;																		//init temporary string that we well push_back in temp_task.roll
		while( i < temp_str.size() ){													//init cycle
			tt.push_back(temp_str[i]);													//adding symbol by symbol to tt
/*trouble*/	if(temp_str[i] == ' ' || temp_str[i] == '\n' || temp_str[i] == EOF){		//while we dont have spaces, new lines or EOF ##here is problem it doesnt understand EOFs 
				tt.pop_back();															//if we have this symbol we should to throw it away from task
				temp_task.roll.push_back(tt);											//this symbol means the end of one part of command, so we add it to roll
				tt.erase();																//clean temporary string
			}
			i++;					
		}	
		Tasks.push_back(temp_task);														//add temporary struct to our general vector


		cout << Tasks[j].hour;															// this part just to prove that everything works
		printf("%d ", Tasks[j].hour);
		printf("%d ", Tasks[j].min);
		printf("%d ", Tasks[j].sec);
		for(int i = 0; i < Tasks[j].roll.size(); i++){
			cout << Tasks[j].roll[i] << ' ';
		}

		j++;
		temp_task = {};
		temp_str = {};
		temp_Cstr = {};
		//TODO it may be a good idea to sort Tasks?? but who knows...
	}
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



