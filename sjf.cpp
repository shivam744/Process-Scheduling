//Non pre-emptive
#include <iostream>
#define  max 100
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
  void sort_burst(process pj[],int n) {
    int i,j;
      for(j = 0; j < n-1; j++)
          for(i = 0; i < n-j-1; i++)
          if (pj[i].burst_t > pj[i+1].burst_t){
            swap(&pj[i].arrival_t, &pj[i+1].arrival_t);
            swap(&pj[i].ser, &pj[i+1].ser);
            swap(&pj[i].burst_t, &pj[i+1].burst_t);
          }
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
  void find_t_time_np(process pros[], int n){
    //to find turnaround time:
    int i=0;
    pros[i].turnaroundd_t=pros[i].burst_t;
    i++;
    while(i!=n){
      pros[i].turnaroundd_t = pros[i-1].turnaroundd_t + pros[i-1].arrival_t + pros[i].burst_t - pros[i].arrival_t ;
      i++;
    }
  }
  void find_t_time_p(process pros[], int n){
    //to find turnaround time in pre-emptive:
    int i =0;
    int sum=0;
    int bt[n+1];
    bt[n] = 99999;
    while(i!=n){
      sum = sum + pros[i].burst_t;
      bt[i] = pros[i].burst_t;
      pros[i].turnaroundd_t= 0;
      i++;
    }
    int small;
    for(int count = 0;count<sum;){
      small = n;
      for(i=0;i<n;i++)
        if(pros[i].arrival_t<=count&&bt[i]>0&&bt[i]<bt[small]){
          small =i;
        }
        count++;
        pros[small].turnaroundd_t = count;
      //  cout<<endl<<small<<" =   "<<pros[small].turnaroundd_t<<endl;
        bt[small]--;
    }
    i = 0;
    while(i!=n){
      pros[i].turnaroundd_t = pros[i].turnaroundd_t - pros[i].arrival_t;
      i++;
    }
  }
  void find_time(process pros[],int n){
    // to find waiting time:
    int i=0;
    pros[i].waiting_t = 0;
    i++;
    while(i!=n){
      pros[i].waiting_t = pros[i].turnaroundd_t - pros[i].burst_t;
      i++;
    }
    //to find compeletion time:
    i = 0;
    while(i!=n){
      pros[i].compl_t = pros[i].turnaroundd_t + pros[i].arrival_t;
      i++;
    }
  }
  int main() {
    std::cout << "Enter the no. of processes:- ";
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
    sort_burst(pros,n);
    sort_arr(pros,n);
    // non-pre-emptive
    find_t_time_np(pros,n);
    find_time(pros,n);
    display(pros,n);
    //pre-emptive
    find_t_time_p(pros,n);
    find_time(pros,n);
    display(pros,n);
    return 0;
  }
