#include<iostream>
using namespace std;
int main()
{
	int mat[50][3];
	cout<<"Enter the no. of processes: ";
	int n;
	cin>>n;
	int i,j;
	for(i=0;i<n;i++)
	{
		mat[i][0] = i+1;
		cout<<"Enter the arrival time and burst time for "<<i+1<<" process:\n";
		for(j=1;j<3;j++)
		{
			cin>>mat[i][j];
		}
	}
			//	cout<<"\nProcess \tArrival time \tBurst time\n\n";
			//	for(i=0;i<n;i++)
			//	{
			//		for(j=0;j<3;j++)
			//			cout<<mat[i][j]<<"\t\t";
			//		cout<<endl;
			//	}
			//	cout<<endl<<"After sorting processes acc. to arrival time: \n";
	int c,c_loc,temp,temp1,temp2;
	for(i=0;i<n;i++)
	{
		c = mat[i][1];
		c_loc = i;
		for(j=i+1;j<n;j++)
		{
			if(mat[j][1] < c)
			{
				c = mat[j][1];
				c_loc = j;
			}
		}
		if(i!=c_loc)
		{
			temp = mat[c_loc][1];
			mat[c_loc][1] = mat[i][1];
			mat[i][1] = temp;
			temp1 = mat[c_loc][2];
			mat[c_loc][2]= mat[i][2];
			mat[i][2] = temp1;
			temp2 = mat[c_loc][2];
			mat[c_loc][0]= mat[i][0];
			mat[i][0] = temp2;
		}
	}
			//	cout<<"\nProcess \tArrival time \tBurst time\n\n";
			//	for(i=0;i<n;i++)
			//	{
			//		for(j=0;j<3;j++)
			//			cout<<mat[i][j]<<"\t\t";
			//		cout<<endl;
			//	}
	int awt[50];
	float awtime,att[50],burst,attime,a_wait;
	//Calculating Avg Waiting time
	awt[0] = 0;
	awtime = 0;
	a_wait = mat[0][1];
	for(i=0;i<n-1;i++)
	{
		awt[i+1]=a_wait+(mat[i][2]-mat[i+1][1]);
		a_wait=a_wait+mat[i][2];	
	}
	for(i=0;i<n;i++)
		awtime = awtime + awt[i];
	awtime=awtime/n;  //here we got our avg waiting time...
	//Calculating Average Turnaround time
	att[0] = mat[0][2] - mat[0][1];
	burst = mat[0][2];
	for(i=1;i<n;i++)
	{
		//	cout<<"burst = "<<burst<<"\n";
		burst = burst + mat[i][2];
		att[i] = (burst - mat[i][1]);
	}
	for(i=0;i<n;i++)
	{
		attime=attime+att[i];
	}
	attime=attime/n;  // here we got our avg turnaround time...
	cout<<"\nProcess \tArrival time \tBurst time \tWaiting time \tTurnaround time \tCompletion time\n\n";
	for(i=0;i<n;i++)
	{
		for(j=0;j<3;j++)
		cout<<mat[i][j]<<"\t\t";
		cout<<awt[i]<<"\t\t";
		cout<<att[i]<<"\t\t\t";
		cout<<att[i]+mat[i][1];
		cout<<endl;
	}
	cout<<"\n Avg. Waiting time = "<<awtime;
	cout<<"\n Avg. Turnaround time = "<<attime;
	return 0;
}
