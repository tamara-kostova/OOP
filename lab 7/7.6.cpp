#include<iostream>
#include<cstring>
using namespace std;

class Task{
    protected:
    char id[5];

    public:
    Task (char *id){
        strcpy(this->id, id);
    }
    char *getid(){
        return id;
    }
    ~Task(){}

    virtual int getOrder() = 0;
    virtual void print() = 0;
};
bool operator == (Task *t1, Task &t2){
        if (!strcmp(t1->getid(), t2.getid())&&t1->getOrder()==t2.getOrder())
            return true;
        return false;
    }
class TimedTask : public Task{//izraz za nasleduvanje od Task
    private:
    int time;

    public:
    TimedTask (char *id="", int time=0) : Task(id){
        this->time=time;
    }
    int getOrder() {
        return time;
    }
    void print(){
        cout<<"TT->"<<id<<":"<<getOrder()<<endl;
    }
};

class PriorityTask : public Task{
    private:
    int priority;

    public:
    PriorityTask (char *id="", int priority=0) : Task(id){
        this->priority=priority;
    }

    int getOrder() {
        return priority;
    }
    void print(){
        cout<<"PT->"<<id<<":"<<getOrder()<<endl;
    }


};
void sort (Task ** tasks, int n){
    for (int i=0; i<n; i++)
        for (int j=0; j<n-i-1; j++)
            if (tasks[j]->getOrder()>tasks[j+1]->getOrder()){
                Task *tmp=tasks[j];
                tasks[j]=tasks[j+1];
                tasks[j+1]=tmp;
            }
}
void scheduleTimedTasks(Task ** tasks, int n, int t) {
    sort(tasks,n);
    for (int i=0; i<n; i++){
        TimedTask *t1=dynamic_cast<TimedTask *>(tasks[i]);
        if (t1)
            if (tasks[i]->getOrder()<t)
                tasks[i]->print();
    }
}

void schedulePriorityTasks(Task ** tasks, int n, int p) {
    sort(tasks,n);
    for (int i=0; i<n; i++){
        PriorityTask *p1 = dynamic_cast<PriorityTask*>(tasks[i]);
        if (p1)
            if (tasks[i]->getOrder()<p)
                tasks[i]->print();
    }
}

int main () {
    int testCase;
    int n;
    cin>>testCase;

    if (testCase==0){
        cin>>n;
    	Task ** tasks;
        tasks = new Task * [n];
    	for (int i=0;i<n;i++){
        char id [5];
        int timeOrPriority;
        int type; //0 za timed, 1 za priority
        cin >> type >>id >> timeOrPriority;
        if (type==0)
        	tasks[i] = new TimedTask(id,timeOrPriority);
        else
            tasks[i] = new PriorityTask(id,timeOrPriority);
        //tasks[i]->print();
    	}

    	cout<<"SCHEDULING PRIORITY TASKS WITH PRIORITY DEGREE LESS THAN 10"<<endl;
    	schedulePriorityTasks(tasks,n,10);

    }
    else if (testCase==1) {
        cin>>n;
    	Task ** tasks;
        tasks = new Task * [n];
    	for (int i=0;i<n;i++){
        char id [5];
        int timeOrPriority;
        int type; //0 za timed, 1 za priority
        cin >> type >>id >> timeOrPriority;
        if (type==0)
        	tasks[i] = new TimedTask(id,timeOrPriority);
        else
            tasks[i] = new PriorityTask(id,timeOrPriority);
        //tasks[i]->print();
    	}


        cout<<"SCHEDULING TIMED TASKS WITH EXECUTION TIME LESS THAN 50"<<endl;
        scheduleTimedTasks(tasks,n,50);
    }
    else {
        TimedTask * tt1 = new TimedTask("11",10);
        TimedTask * tt2 = new TimedTask("11",11);
        TimedTask * tt3 = new TimedTask("11",11);
        PriorityTask * pp1 = new PriorityTask("aa",10);
        PriorityTask * pp2 = new PriorityTask("11",10);

        cout << (tt1==(*tt2))<<endl;
        cout << (tt2==(*tt3))<<endl;
        cout << (pp1==(*pp2))<<endl;
        cout << (pp2==(*tt1))<<endl;
    }

	return 0;
}
