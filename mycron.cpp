#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <cstddef>
#include <cstring>
#include <vector>

using namespace std;

struct Task{											//DONE
    int hour = -2;	//-2 default; 24 for *; 
    int min = -2; 	//2*24*60 for *
    int sec = -2;
   // int mass;		// sort using mass
    vector<string>command;
};
time_t last_change = 0;
vector<pid_t>shoot_list;
vector<Task>Tasks;
// bool compare_mass(const Task &a, const Task &b)			//DONE
// {
//     return a.mass < b.mass;
// }


struct Task parse(string line){ //create a struct tusk from one line of input file DONE
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
//	result.mass = result.hour + result.min + result.sec;
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
	};
//	sort(Tasks.begin(), Tasks.end(), compare_mass);			//?
}
	

int changed(){ //function that will look for changes in input file		//?
	struct stat mycrontab;
	stat("mycrontab", &mycrontab);
	if (mycrontab.st_mtime > last_change) {
		last_change = mycrontab.st_mtime;
		return 1;
	} else
		return 0;
}

void kill_all(){						
	for(int i = 0; i< shoot_list.size(); i++){
		kill(shoot_list[i], 0);
	}
	shoot_list.clear();
	Tasks.clear();

}

pid_t do_task(struct Task task){				//DONE ? WITH KILL
	const char **args = new const char*[task.command.size()];	
	for(int i = 1; i < task.command.size(); i++){
		args[i-1] = task.command[i].c_str();
	}
	args[task.command.size()] = NULL;
	const char *path = task.command[0].c_str();
	pid_t parent_pid = getpid();
	pid_t temp_pid = fork();
	if(getpid() != parent_pid){
		cout << "execute " << task.command[0] << endl;
		execv(path, (char**)args);
	}
	return temp_pid;
}

void do_all_tasks(){
	time_t rawtime; 											
	time (&rawtime);
	struct tm *cur_time = localtime(&rawtime);
	pid_t temp_pid;
	for(int i = 0; i < Tasks.size(); i++){
		if((cur_time->tm_hour == Tasks[i].hour || Tasks[i].hour == 24) && (cur_time->tm_min == Tasks[i].min || Tasks[i].min == 2880) && cur_time->tm_sec == Tasks[i].sec){
			temp_pid = do_task(Tasks[i]);
			shoot_list.push_back(temp_pid);
			if(Tasks[i].hour < 24){
				Tasks.erase(Tasks.begin()+i);				///TODO ZOMBIE
			}
		}
	}
}


int main(){
//*
    read_tasks("mycrontab");
    cout << Tasks[0].command.size()<< " ";
    cout << Tasks[0].command[0] <<" "<< Tasks[0].command[1] << endl;
    do_task(Tasks[0]);

/*/
	time_t rawtime;
	time (&rawtime);
	struct tm *cur_time;
	int c;
	do{
		time(&rawtime);
		cur_time = localtime(&rawtime);
		if(changed()){
			kill_all();
			read_tasks("mycrontab");
			cout << asctime(cur_time) << " rereaded" << endl;
		}else{
			for(int i = 0; i < Tasks.size(); i++){
				cout << Tasks[i].hour << " "<<Tasks[i].min<<" "<<Tasks[i].sec<<" ";
				for(int j = 0; j < Tasks[i].command.size(); j++){
					cout << Tasks[i].command[j] << " ";
				}  
				cout << endl;
			}
			do_all_tasks();
		};
	} while(true);
//*/
}