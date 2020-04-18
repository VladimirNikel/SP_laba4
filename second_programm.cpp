#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;
sem_t semaphore;

int main(int argc, char *argv[]){
	cout<<"Введите интересующий Вас ip-адрес: ";
	string adres;
	cin>>adres;
	/*
	string name="first";
	string tmp="";
	char *argm[3];
	argm[0]=(char*) name.c_str();
	argm[2]=NULL;
	*/
	for(int i=adres.size()-1;adres[i]!='.';i--)	//удаление символов до первой точки
		adres.pop_back();

	sem_init(&semaphore, 0, 1);

	for(int i=1;i<255;i++){
		string tmp = adres+std::to_string(i);
		//argm[1]=(char*) tmp.c_str();
		sem_wait(&semaphore);

		pid_t pr;
 		pr = fork();
		int status;
		if(pr == 0){
			cout<<"\n\nPID: "<<getpid()<<endl;
			execl("first", "-c 1", (char*) tmp.c_str(), NULL);
		}
		else if (pr > 0){
			wait(&status);
		}
		sem_post(&semaphore);
	}
	sem_destroy(&semaphore);
	return 0;
}