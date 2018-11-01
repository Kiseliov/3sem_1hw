#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <cstddef>
#include <cstring>
#include <vector>

using namespace std;

struct Task{
    int hour = -2; //-2 default; 24 for *; 
    int min = -2;				//2*24*60 for *
    int sec = -2;
    int mass;			// sort using mass
    pid_t pid;
    vector<string>command;
};
time_t last_change = 0;

vector<Task>Tasks;
bool compare_mass(const Task &a, const Task &b)
{
    return a.mass > b.mass;
}


struct Task parse(string line){ //create a struct tusk from one line of input file
	struct Task result;
	int t = 0;
	int i = 0;
	int first = 0;
	for(; i < line.size(); i++){
		if(line[i] == ' '){
			result.sec = t;
			break;
		}else if(line[i] != ':'){ // cipherka
			if (line[i] == '*'){
				if(first == 0)t = 24;
				if(first == 1)t = 2*24*60;
				first++;
			} else {
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
	result.mass = result.hour + result.min + result.sec;
	return result;
}

void read_tasks(string path){
	//read and prepare data from input file using parse
	ifstream f(path.c_str());
	string temp_str;
	struct Task temp_task;
	while(getline(f, temp_str)){
		temp_task = parse(temp_str);
		Tasks.push_back(temp_task);
	}
}
	

int changed(){ //function that will look for changes in input file
	struct stat mycrontab;
	stat("mycrontab", &mycrontab);
	if (mycrontab.st_mtime > last_change) {
		last_change = mycrontab.st_mtime;
		return 1;
	} else
		return 0;
}

void kill_all(){
	for(int i = 0; i < Tasks.size(); i++){
		kill(Tasks[0].pid, 0);
		Tasks.erase(0);
	}

}
void do_task(struct Task task){

}


int main(){
//*
    read_tasks("mycrontab");
    sort(Tasks.begin(), Tasks.end(), compare_mass);
    for(int i = 0; i < Tasks.size(); i++){
    	printf("%d:%d:%d ", Tasks[i].hour, Tasks[i].min, Tasks[i].sec);
    	for(int j = 0; j < Tasks[i].command.size(); j++){
    			printf("%s ", Tasks[i].command[j].c_str());
		}
		cout << endl;
	}	
/*/
	for(;;){
		if(changed()){
			kill_all();
			read_tasks();
		}
		time_t rawtime; 											//1970 in ms
		time (&rawtime);
		struct tm *current_time = localtime(&rawtime);				//	
		for(int i = 0; i < Tasks.size(); i++){
			if(Tasks[i].hour <= current_time.tm_hour && Tasks[i].min <= current_time.tm_min 
					&& Tasks[i].sec <= current_time.tm_sec){
				do_task(Tasks[i]);
				if(Tasks[i].hour != -1){
					Tasks.erase(i);
				}
			}else break;
		}
	}
//*/
}

/*
    time_t t = time(0);
    tm* now = localtime(&t);
    tm_sec; tm_min; tm_hour;
*/

