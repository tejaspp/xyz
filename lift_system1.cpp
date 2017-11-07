#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<math.h>

using namespace std;

int main()
{
	printf("Please enter the number of lifts: \n");
	int n;
	scanf("%d",&n);
	int status[n], tl[n], fl[n], dl[n];
	for(int i=0;i<n;i++)
	{
		status[i] = 0;	//Lift is empty
		tl[i] = 0;	//Time taken for lift
		fl[i] = 0;	//Current floor of the lift
		dl[i] = 0;	//Destination floor of the lift
	}
	int t = 0;
	while(1)
	{
		for(int i=0;i<n;i++)
		{
			if(status[i]==1 || status[i]==2)
			{
				if(t==tl[i])
				{
					status[i] = 0;
					tl[i] = 0;
					fl[i] = dl[i];
				}
			}
		}
		printf("Please enter your direction: \n");
		int d;
		scanf("%d",&d);
		printf("Please enter your floor: \n");
		int f;
		scanf("%d",&f);
		if((d==2 && f==0) || (d==1 && f==8))
			printf("You cannot go in the desired direction from the current floor.\n");
		else
		{
			if(d==1)	//You want to go up
			{
				int imin, dmin=10000, state=0;
				for(int i=0;i<n;i++)
				{
					if(status[i]==0)	//The lift is empty
					{
						if(dmin>abs(f-fl[i]))
						{
							dmin = abs(f-fl[i]);
							imin = i;
							state = 1;
						}
					}
					else if(status[i]==1 && f>=fl[i] && tl[i]-(dl[i]-f)>t)	//Lift is going up and time taken for lift to reach from its current floor to your current floor is more than t
					{
						int v = f - (fl[i]+tl[i]-t);
						if(v>0 && dmin>v)
						{
							dmin = v;
							imin = i;
							state = 1;
						}
					}
				}
				if(state==1)
				{
					printf("Lift %d is coming.\n",imin);
					if(status[imin]==0)
					{
						if(f>fl[imin])
						{
							status[imin] = 1;
							tl[imin] = t + f-fl[imin];
							dl[imin] = f;
						}
						else
						{
							status[imin] = 2;
							tl[imin] = t + abs(f-fl[imin]);
							dl[imin] = f;
						}
					}
					else
					{
						tl[imin] = tl[imin] + f-fl[imin];
					}
					printf("Please enter your desired floor: \n");
					int dll;
					scanf("%d",&dll);
					if(dll>dl[imin])
					{
						tl[imin] = tl[imin] + dll - dl[imin];
						dl[imin] = dll;
					}
					else if(dl[imin]>dll)
					{
						tl[imin] = tl[imin] + dll - f;
					}
					else if(f>dll)
						printf("It is not possible to go to your desired floor since it is below and you want to go up.\n");
				}
				else
					printf("Please Wait! Lifts are occupied!\n");
			}
			else if(d==2)	//You want to go down
			{
				int imin, dmin=10000, state=0;
				for(int i=0;i<n;i++)
				{
					if(status[i]==0)	//The lift is empty
					{
						if(dmin>abs(f-fl[i]))
						{
							dmin = abs(f-fl[i]);
							imin = i;
							state = 1;
						}
					}
					else if(status[i]==2 && fl[i]>=f && tl[i]-abs(dl[i]-f)>t)	//Lift is going down and time taken for lift to reach from its current floor to your current floor is more than t
					{
						int v = abs(f - (fl[i]+tl[i]-t));
						if(v>0 && dmin>v)
						{
							dmin = v;
							imin = i;
							state = 1;
						}
					}
				}
				if(state==1)
				{
					printf("Lift %d is coming.\n",imin);
					if(status[imin]==0)
					{
						if(fl[imin]>f)
						{
							status[imin] = 2;
							tl[imin] = t + fl[imin]-f;
							dl[imin] = f;
						}
						else
						{
							status[imin] = 1;
							tl[imin] = t + abs(fl[imin]-f);
							dl[imin] = f;
						}
					}
					else
					{
						tl[imin] = tl[imin] + fl[imin]-f;
					}
					printf("Please enter your desired floor: \n");
					int dll;
					scanf("%d",&dll);
					if(dl[imin]>dll)
					{
						tl[imin] = tl[imin] + dl[imin] - dll;
						dl[imin] = dll;
					}
					else if(dll>dl[imin])
					{
						tl[imin] = tl[imin] + f - dll;
					}
					else if(dll>f)
						printf("It is not possible to go to your desired floor since it is above and you want to go down.\n");
				}
				else
					printf("Please Wait! Lifts are occupied!\n");
			}
		}
		t = t + 1;
	}
}
