#include <iostream>
#define max 100
using namespace std;
struct process {
  int ser = 0;
  int arrival_t = 0;
  int burst_t = 0;
  int waiting_t = 0;
  int turnaroundd_t = 0;
  int compl_t = 0;
};
  void swap(int *xp, int *yp)
  {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
  }
  void display(process pros[],int n){
    cout<<"\nProcess \tArrival time \tBurst time \tWaiting time \tTurnaround time \tCompletion time\n\n";
    int i;
    for(i=0;i<n;i++){
      cout<<"p"<<pros[i].ser<<"\t\t";
      cout<<pros[i].arrival_t<<"\t\t";
      cout<<pros[i].burst_t<<"\t\t";
      cout<<pros[i].waiting_t<<"\t\t";
      cout<<pros[i].turnaroundd_t<<"\t\t\t";
      cout<<pros[i].compl_t;
      cout<<endl;
  }
}
void sort_arr(process pj[],int n) {
int i, j;
 for (i = 0; i < n-1; i++)
     for (j = 0; j < n-i-1; j++)
         if (pj[j].arrival_t > pj[j+1].arrival_t){
            swap(&pj[j].arrival_t, &pj[j+1].arrival_t);
            swap(&pj[j].ser, &pj[j+1].ser);
            swap(&pj[j].burst_t, &pj[j+1].burst_t);
         }
}
 void roundrobin(process pj[],int n,int q){
   int i=0,time,remain=n,temp;
   int bt[n];
   while(i!=n){
     bt[i] = pj[i].burst_t;
     i++;
   }
   for(time=pj[0].arrival_t,i=0;remain!=0;){
     if(bt[i]<=q && bt[i]>0){
       time = bt[i] + time;
       bt[i] = 0;
       temp = 1;
     }
     else if(bt[i]>0){
       bt[i] -= q;
       time = q + time;
     }
     if(bt[i]==0 && temp ==1){
       remain--;
       pj[i].compl_t = time;
       pj[i].turnaroundd_t = time - pj[i].arrival_t;
       pj[i].waiting_t = pj[i].turnaroundd_t - pj[i].burst_t;
       temp = 0;
	   }

	  if(i == n-1){
       i=0;
     }
     else if(time >= pj[i+1].arrival_t){
       i++;
     }
     else{
       i=0;
     }
   }
 }
int main(){
  cout << "Enter the no. of processes:- ";
  int n;
  cin>>n;
  process pros[max];
  cout<<"Enter the Arrival time and Burst time of the processes:-"<<endl;
  int i=0;
  while(i!=n){
    cout<<"Arrival time and Burst time for process ("<<i<<") : -"<<endl;
    pros[i].ser = i+1;
    cin>>pros[i].arrival_t;
    cin>>pros[i].burst_t;
    i++;
  }
	cout << "\n\nEnter the length of the quantum [1-100]: ";
	int quantum;
	cin >> quantum;
	while (quantum < 1 || quantum > 100)
	{
		cout << "\nInvalid Length. Enter a valid quantum length in [1-100]: ";
		cin >> quantum;
	}
  sort_arr(pros,n);
  roundrobin(pros,n,quantum);
  display(pros,n);
}
