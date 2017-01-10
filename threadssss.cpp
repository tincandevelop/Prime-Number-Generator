#include <windows.h>

struct parameters{
	//whatever parameters thread0 needs
};

DWORD thread0(void *params){
	parameters *a=(parameters *)params;
	//put parameters into separate variables, if you want
	//thread0's body
}

//I like to use this function to start threads more easily
HANDLE newThread(LPTHREAD_START_ROUTINE routine,LPVOID parameters,int priority=0){
	HANDLE res=CreateThread(0,0,routine,parameters,0,0);
	if (priority)
		SetThreadPriority(res,priority);
	return res;
}

int main(){
	parameters *thread0data=new parameters;
	//initialize thread0data
	HANDLE *thread0handle=newThread(thread0,thread0data);
	//Let's suppose you want to wait 100 ms (10 is below the granularity of Sleep(), if I remember correctly)
	Sleep(100);
	//http://msdn.microsoft.com/en-us/library/ms684335(VS.85).aspx
	thread0handle=OpenThread(THREAD_TERMINATE,0,GetThreadId(thread0handle));
	if (!thread0handle){
		//OpenThread() has failed. Deal with the error here.
	}
	//http://msdn.microsoft.com/en-us/library/ms686717(VS.85).aspx
	TerminateThread(thread0handle,0);
	//do other stuff
	return 0;
}