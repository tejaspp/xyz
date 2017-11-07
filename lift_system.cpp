#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<malloc.h>

using namespace std;

int **sort(int **al, int num)
{
	int temp[2];
	for(int i=0;i<num-1;i++)
	{
		for(int j=i+1;j<num;j++)
		{
			if(al[i][1]>al[j][1])
			{
				temp[0] = al[i][0];
				temp[1] = al[i][1];
				al[i][0] = al[j][0];
				al[i][1] = al[j][1];
				al[j][0] = temp[0];
				al[j][1] = temp[1];
			}
		}
	}
	return al;
};

int main()
{
	printf("Please enter the number of lifts: \n");
	int n;
	scanf("%d",&n);
	int status[n];
	for(int i=0;i<n;i++)
		status[i] = 0;	//Lift i is free
	int t = 0;	//Time
	int tl[n][2];	//Time period of each lift
	for(int i=0;i<n;i++)
	{
		tl[i][0] = 0;	//Time period for lift to reach floor where asked
		tl[i][1] = 0;	//Time period for lift to reach floor desired
	}
	int fl[n][3];	//Floor where currently the lift is
	for(int i=0;i<n;i++)
	{
		fl[i][0] = 1;	//Current floor
		fl[i][1] = -1;	//Floor Asked
		fl[i][2] = -1;	//Floor Desired
	}
	while(1)
	{
		for(int i=0;i<n;i++)
		{
			if(tl[i][1]==t && t!=0)
			{
				printf("Lift %d has reached its destination.\n",i);
				status[i] = 0;
				tl[i][0] = 0;
				tl[i][1] = 0;
				fl[i][0] = fl[i][2];
			}
		}
		printf("Please enter your current floor: \n");
		int a;
		scanf("%d",&a);
		int num = 0;
		for(int i=0;i<n;i++)
			if(status[i]==0)
				num++;	//Looking for free lifts
		if(num == 0)	//No empty/free lifts available
		{
			int dmin = 10000, tmin1, tmin2, imin, state = 0;
			for(int i=0;i<n;i++)
			{
				if(a>fl[i][0] && fl[i][1]>a && tl[i][0]>t)
				{
					//printf("Lift %d is coming.\n",i);
					//tl[i][0] = tl[i][0] + 3;
					//tl[i][1] = tl[i][1] + 3;
					//break;
					printf("Floor %d asked is between Floor %d and Floor %d.\n",a,fl[i][0],fl[i][1]);
					printf("Current time: %d, Time to reach from Floor %d to Floor %d: %d.\n",t,fl[i][0],fl[i][1],tl[i][0]);
					int ddash = a - fl[i][0];
					if(dmin > ddash)
					{
						dmin = ddash;
						tmin1 = tl[i][0] + 3;
						tmin2 = tl[i][1] + 3;
						imin = i;
					}
					state = 1;
					break;
				}
				else if(a>fl[i][1] && fl[i][2]>a && t>tl[i][0] && tl[i][1]>t)
				{
					//printf("Lift %d is coming.\n",i);
					//tl[i][1] = tl[i][1] + 3;
					//break;
					printf("Floor %d asked is between Floor %d and Floor %d.\n",a,fl[i][1],fl[i][2]);
					printf("Current time: %d, Time to reach from Floor %d to Floor %d: %d.\n",t,fl[i][1],fl[i][2],tl[i][1]-tl[i][0]);
					int ddash = a - fl[i][1];
					if(dmin > ddash)
					{
						dmin = ddash;
						tmin1 = tl[i][0];
						tmin2 = tl[i][1] + 3;
						imin = i;
					}
					state = 1;
					break;
				}
				else if(fl[i][0]>a && a>fl[i][1] && tl[i][0]>t)
				{
					//printf("Lift %d is coming.\n",i);
					//tl[i][0] = tl[i][0] + 3;
					//tl[i][1] = tl[i][1] + 3;
					//break;
					printf("Floor %d asked is between Floor %d and Floor %d.\n",a,fl[i][1],fl[i][0]);
					printf("Current time: %d, Time to reach from Floor %d to Floor %d: %d.\n",t,fl[i][1],fl[i][0],tl[i][0]);
					int ddash = fl[i][0] - a;
					if(dmin > ddash)
					{
						dmin = ddash;
						tmin1 = tl[i][0] + 3;
						tmin2 = tl[i][1] + 3;
						imin = i;
					}
					state = 1;
					break;
				}
				else if(fl[i][1]>a && a>fl[i][2] && t>tl[i][0] && tl[i][1]>t)
				{
					//printf("Lift %d is coming.\n",i);
					//tl[i][1] = tl[i][1] + 3;
					//break;
					printf("Floor %d asked is between Floor %d and Floor %d.\n",a,fl[i][2],fl[i][1]);
					printf("Current time: %d, Time to reach from Floor %d to Floor %d: %d.\n",t,fl[i][2],fl[i][1],tl[i][1]-tl[i][0]);
					int ddash = fl[i][1] - a;
					if(dmin > ddash)
					{
						dmin = ddash;
						tmin1 = tl[i][0];
						tmin2 = tl[i][1] + 3;
						imin = i;
					}
					state = 1;
					break;
				}
			}
			if(state == 1)
			{
				printf("Lift %d is coming.\n",imin);
				int dfl;
				printf("Please enter your desired floor: \n");
				scanf("%d",&dfl);
				if((dfl>fl[imin][2] || fl[imin][0]>dfl) && fl[imin][2]>fl[imin][0])
				{
					tl[imin][0] = tmin1;
					tl[imin][1] = tmin2 + abs(dfl-fl[imin][2]);
					fl[imin][2] = dfl;
				}
				else if((fl[imin][2]>dfl || dfl>fl[imin][0]) && fl[imin][0]>fl[imin][2])
				{
					tl[imin][0] = tmin1;
					tl[imin][1] = tmin2 + abs(dfl-fl[imin][2]);
					fl[imin][2] = dfl;
				}
				else
				{
					tl[imin][0] = tmin1;
					tl[imin][1] = tmin2;
				}
			}
			else
				printf("No empty lifts available. Please Wait!!!\n");
		}
		else
		{
			int **al = (int **)malloc(sizeof(int *)*num);	//Available lifts
			for(int i=0;i<num;i++)
				al[i] = (int *)malloc(sizeof(int)*2);
			int num1 = 0;
			for(int i=0;i<n;i++)
				if(status[i]==0)
				{
					al[num1][0] = i;
					al[num1][1] = abs(fl[i][0]-a);
					num1++;
				}
			al = sort(al,num);	//Looking for the nearest lift to floor 'a'
			printf("Lift %d is coming now.\n",al[0][0]);
			status[al[0][0]] = 1;	//Lift al[0][0] is occupied now.
			tl[al[0][0]][0] = t + al[0][1] + 3;	//Current time + Time taken by lift to reach from its current floor to the floor asked + Time taken by lift to open, person to enter and close
			fl[al[0][0]][1] = a;	//Floor of the lift now where asked -> 'a'
			printf("Please enter the number of floors you desire to go: \n");
			int n1;
			scanf("%d",&n1);
			int **b = (int **)malloc(sizeof(int *)*n1);
			for(int i=0;i<n1;i++)
				b[i] = (int *)malloc(sizeof(int)*2);
			for(int i=0;i<n1;i++)
			{
				printf("Please enter the floors you desire to go: \n");
				scanf("%d",&b[i][0]);
				b[i][1] = abs(b[i][0]-a);
			}
			b = sort(b,n1);
			int b1[n1][2];
			b1[0][0] = b[0][0];
			b1[0][1] = b[0][1];
			int i1 = 1;
			if(b[0][0] > a)
			{
				//Lift is going up first
				for(int i=1;i<n1;i++)
				{
					if(b[i][0] > a)
					{
						b1[i1][0] = b[i][0];
						b1[i1][1] = b[i][1];
						i1++;
					}
				}
				//Then lift will go down
				for(int i=1;i<n1;i++)
				{
					if(a > b[i][0])
					{
						b1[i1][0] = b[i][0];
						b1[i1][1] = b[i][1];
						i1++;
					}
				}
			}
			else
			{
				//Lift is going down first
				for(int i=1;i<n1;i++)
				{
					if(a > b[i][0])
					{
						b1[i1][0] = b[i][0];
						b1[i1][1] = b[i][1];
						i1++;
					}
				}
				//Then lift will go up
				for(int i=1;i<n1;i++)
				{
					if(b[i][0] > a)
					{
						b1[i1][0] = b[i][0];
						b1[i1][1] = b[i][1];
						i1++;
					}
				}
			}
			tl[al[0][0]][1] = tl[al[0][0]][0] + abs(b1[0][0]-a);
			for(int i=1;i<n1;i++)
				tl[al[0][0]][1] = tl[al[0][0]][1] + abs(b1[i][0]-b1[i-1][0]) + 3;	//Time of the lift + Time taken by lift to go from floor 'a' to floor 'b' + Time taken by lift to open, allow the passengers to leave or enter and close
			fl[al[0][0]][2] = b1[n1-1][0];
		}
		t = t + 1;
	}	
	return 0;
}
