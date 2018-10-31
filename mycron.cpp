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
    int hour = -2; //-2 default; -1 for *; 
    int min = -2;
    int sec = -2;
    vector<string>command;
};

vector<task>Tasks;

struct task parse(string line){ //create a struct tusk from one line of input file
	struct task result;
	int t = 0;
	int i = 0;
	for(; i < line.size(); i++){
		if(line[i] == ' '){
			result.sec = t;
			break;
		}else if(line[i] != ':'){ // cipherka
			if (line[i] == '*') t = -1; else {
 				t*=10;
				t+=line[i] - '0';
			}
		}else { // :
			if (result.hour == -2) {
				result.hour = t;
			} else if (result.min == -2) {
				result.min = t;
			}
			t = 0;
		}
	}
	line.push_back(' ');
	i++;
	string tt;																		 	
		while( i < line.size() ){													
			tt.push_back(line[i]);												
			if(line[i] == ' ' ){												
				tt.pop_back();													
				result.command.push_back(tt);									
				tt.erase();														
			}	
			i++;					
		}
	return result;
}

void read_file(string path){
	//read and prepare data from input file using parse
	ifstream f(path.c_str());
	string temp_str;
	struct task temp_task;
	while(getline(f, temp_str)){
		temp_task = parse(temp_str);
		Tasks.push_back(temp_task);
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
    read_file("mycrontab");
    for(int i = 0; i < Tasks.size(); i++){
    	printf("%d:%d:%d ", Tasks[i].hour, Tasks[i].min, Tasks[i].sec);
    	for(int j = 0; j < Tasks[i].command.size(); j++){
    			printf("%s ", Tasks[i].command[j].c_str());
		}
		cout << endl;
	}
}
/*
    time_t t = time(0);
    tm* now = localtime(&t);
    tm_sec; tm_min; tm_hour;
*/

