#include <iostream>
#define max 100
using namespace std;
struct process {
  int ser = 0;
  int arrival_t = 0;
  int burst_t = 0;
  int burst_tt = 0;
  int waiting_t = 0;
  int turnaroundd_t = 0;
  int compl_t = 0;
  int prio = 0;
};
  void swap(int *xp, int *yp)
  {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
  }
void sort_arr(process pj[],int n) {
int i, j;
 for (i = 0; i < n-1; i++)
     for (j = 0; j < n-i-1; j++){
         if (pj[j].arrival_t > pj[j+1].arrival_t){
            swap(&pj[j].arrival_t, &pj[j+1].arrival_t);
            swap(&pj[j].ser, &pj[j+1].ser);
            swap(&pj[j].burst_t, &pj[j+1].burst_t);
            swap(&pj[j].burst_tt, &pj[j+1].burst_tt);
            swap(&pj[j].prio, &pj[j+1].prio);
         }
       }
}
void sort_prior(process pj[],int start,int end) {
	if(start==end)
		return;
	else{
int i, j;
 for (i = start; i < end-1; i++)
     for (j = start; j < end-i-1; j++){
         if (pj[j+1].prio > pj[j].prio){
            swap(&pj[j].arrival_t, &pj[j+1].arrival_t);
            swap(&pj[j].ser, &pj[j+1].ser);
            swap(&pj[j].burst_t, &pj[j+1].burst_t);
            swap(&pj[j].burst_tt, &pj[j+1].burst_tt);
            swap(&pj[j].prio, &pj[j+1].prio);
         }
       }
   }
}
void display(process pros[],int n){
  cout<<"\nProcess \tArrival time \tBurst time \tPriority \tWaiting time \tTurnaround time \tCompletion time\n\n";
  int i;
  for(i=0;i<n;i++){
    cout<<"p"<<pros[i].ser<<"\t\t";
    cout<<pros[i].arrival_t<<"\t\t";
    cout<<pros[i].burst_t<<"\t\t";
    cout<<pros[i].prio<<"\t\t";
    cout<<pros[i].waiting_t<<"\t\t";
    cout<<pros[i].turnaroundd_t<<"\t\t\t";
    cout<<pros[i].compl_t;
    cout<<endl;
  }
}
void priority_p(process pro[],int n){
  int i=0,cur,chk;
  int time =0;
  int remain = n;
  while(remain!=0){
  	chk = 0;
    for(i=0;i<n;i++){
      if(pro[i].arrival_t<=time&& pro[i].burst_tt!=0 && pro[i].prio > chk){
      	chk = pro[i].prio;
      	cur = i;
	  }
	}
		time++;
	pro[cur].compl_t = time;
	pro[cur].burst_tt--;
	remain=n;
    for(i=0;i<n;i++){
      if(pro[i].burst_tt==0){
        remain--;
      }
    }
  }
}
void priority_np(process pro[],int n){
  int i =1;
  pro[0].turnaroundd_t = pro[0].burst_t;
  pro[0].compl_t = pro[0].turnaroundd_t + pro[0].arrival_t;
  while(i!=n){
  	if(pro[i].arrival_t<=pro[i-1].compl_t){
    	pro[i].turnaroundd_t = pro[i-1].compl_t + pro[i].burst_t - pro[i].arrival_t;
    	pro[i].waiting_t = pro[i].turnaroundd_t - pro[i].burst_t;
    	pro[i].compl_t = pro[i].turnaroundd_t + pro[i].arrival_t;
	}
	else{
		pro[i].compl_t = pro[i].arrival_t + pro[i].burst_t;
		pro[i].turnaroundd_t = pro[i].burst_t;
		pro[i].waiting_t = 0;
	}
    i++;
  }
}
void find_time(process pros[],int n){
  // to find waiting time:
  int i=0;
  while(i!=n){
    pros[i].waiting_t = pros[i].compl_t - pros[i].burst_t -pros[i].arrival_t;
    pros[i].turnaroundd_t = pros[i].compl_t - pros[i].arrival_t;
    i++;
  }
}
int main(){
  cout << "Enter the no. of processes:- ";
  int n;
  cin>>n;
  process pros[max];
  cout<<"Enter the Arrival time, Burst time and priority of the processes:-"<<endl;
  int i=0;
  while(i!=n){
    cout<<"Arrival time, Burst time and priority for process ("<<i+1<<") : -"<<endl;
    pros[i].ser = i+1;
    cin>>pros[i].arrival_t;
    cin>>pros[i].burst_t;
    pros[i].burst_tt = pros[i].burst_t;
    cin>>pros[i].prio;
    i++;
  }
  sort_prior(pros,0,n);
  sort_arr(pros,n);
  //non pre-emptive prirority scheduling
  priority_np(pros,n);
  cout<<"Non-Preemptive Scheduling:-"<<endl;
  display(pros,n);
  // pre-emptive scheduling
  priority_p(pros,n);
  find_time(pros,n);
  cout<<"Preemptive Scheduling:-"<<endl;
  display(pros,n);
  return 0;
}
