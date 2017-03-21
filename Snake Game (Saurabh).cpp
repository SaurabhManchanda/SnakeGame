#include<iostream>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<ctime>

using namespace std;
struct snake
{
	char body;
	int x;
	int y;
	struct snake *next;
}*ptr,*start,*new_node,*pptr;
void food_eat(snake* snake_head)
{
	ptr=snake_head;
	while(ptr->next!=NULL)
	ptr=ptr->next;
	new_node=new snake;
	new_node->body='*';
	new_node->x=ptr->x;
	new_node->y=ptr->y;
	new_node->next=NULL;
	ptr->next=new_node;
}
int food_check(snake* snake_head,int& i,int& j)
{
	int flag=0;
	if(snake_head->x==i && snake_head->y==j)
	flag=1;
	return flag;
}
int snake_check(snake* snake_head)
{
	int flag=1;
	ptr=snake_head;
	ptr=ptr->next;
	while(ptr!=NULL)
	{
		if(snake_head->x==ptr->x && snake_head->y==ptr->y)
		{
			flag=0;
			break;
		}
		ptr=ptr->next;
	}
	return flag;
}
void swap(snake* snake_head,int n,int m)
{
	int x1,x2,y1,y2;
	ptr=snake_head;
	x1=ptr->x;
	y1=ptr->y;
	while(ptr->next!=NULL)
	{
		ptr=ptr->next;
		x2=ptr->x;
		y2=ptr->y;
		ptr->x=x1;
		ptr->y=y1;
		x1=x2;
		y1=y2;
	}
	snake_head->x=n;
	snake_head->y=m;
}
void snake_move(snake* snake_head,char st,char st1)
{
	int n,m;
	if(st=='d' && st1!='a')
	{
		ptr=snake_head;
		if(ptr->y==20)
		n=ptr->x,m=1;
		else
		n=ptr->x,m=ptr->y+1;
		swap(snake_head,n,m);
	}
	else if(st=='s' && st1!='w')
	{
		ptr=snake_head;
		if(ptr->x==20)
		n=1,m=ptr->y;
		else
		n=ptr->x+1,m=ptr->y;
		swap(snake_head,n,m);
	}
	else if(st=='a' && st1!='d')
	{
		ptr=snake_head;
		if(ptr->y==1)
		n=ptr->x,m=20;
		else
		n=ptr->x,m=ptr->y-1;
		swap(snake_head,n,m);
	}
	else if(st=='w' && st1!='s')
	{
		ptr=snake_head;
		if(ptr->x==1)
		n=20,m=ptr->y;
		else
		n=ptr->x-1,m=ptr->y;
		swap(snake_head,n,m);
	}
}
void print_screen(char screen[22][22],snake* snake_head)
{
	int a,b;
	ptr=snake_head;
	while(ptr!=NULL)
	{
		screen[ptr->x][ptr->y]=ptr->body;
		ptr=ptr->next;
	}
	for(a=0;a<22;a++)
	{
		for(b=0;b<22;b++)
		{
			cout<<screen[a][b]<<" ";
			
		}
		cout<<endl;
	}
}
int update_food_location(char screen[22][22],int &i,int &j)
{
	screen[i][j]='@';
	return 1;
}
int generate_food_location(char screen[22][22],int maxx,int maxy,int& i,int& j,snake* snake_head)
{
	screen[i][j]=' ';
	int flag=1;
	while(flag)
	{
		i=rand()%20+1;
		j=rand()%20+1;
		ptr=snake_head;
		while(ptr!=NULL)
		{
			if(ptr->x!=i && ptr->y!=j)
			flag=0;
			else
			{
				flag=1;
				break;
			}
			ptr=ptr->next;
		}
		return 1;
	}
	if(i<=maxx && j<=maxy)
	return 1;
	else
	return 0;
}
snake* generate_snake(int n)
{
	int i=11,j=11;
	start=NULL;
	do
	{
		new_node=new snake;
		new_node->body='*';
		new_node->x=i;
		new_node->y=j--;
		new_node->next=NULL;
		if(start==NULL)
		{
			start=new_node;
		}
		else
		{
			ptr=start;
			while(ptr->next!=NULL)
			ptr=ptr->next;
			ptr->next=new_node;
		}
		n--;
	}
	while(n>0);
	return start;
}
int generate_screen(char screen[][22],int maxx,int maxy)
{
	for(int i=0;i<maxx;i++)
	{
		for(int j=0;j<maxy;j++)
		{
			if(i==0 || j==0 || i==21 || j==21)
			screen[i][j]='.';
			else
			screen[i][j]=' ';
		}
	}
	return 1;
}
int main()
{
	char screen[22][22];
	int maxx=22,maxy=22,score=0;
	long unsigned int speed=401.00;
	srand(time(0));
	if(generate_screen(screen,maxx,maxy))
	{
	    struct snake *snake_head=generate_snake(5);
	    if(snake_head!=NULL)
	    {
	    	int i=0,j=0;
	    	if(generate_food_location(screen,maxx,maxy,i,j,snake_head))
	    	{
	    		if(update_food_location(screen,i,j))
	    		{
	    			print_screen(screen,snake_head);
	    			char st='d',st1=0;
	    			while(snake_check(snake_head))
	    			{
						_sleep(speed);
	    				snake_move(snake_head,st,st1);
	    				if(kbhit())
	    				{
	    					st1=st;
	    					st=getch();
	    				}
	    				if(food_check(snake_head,i,j))
	    				{
	    					food_eat(snake_head);
	    					score++;
	    					speed=speed-1;
	    					generate_food_location(screen,maxx,maxy,i,j,snake_head);
						}
	    				generate_screen(screen,maxx,maxy);
	    				update_food_location(screen,i,j);
	    				system("cls");
	    				print_screen(screen,snake_head);
	    				cout<<"Score : "<<score;
					}
				}
				else
				cout<<"Error4"<<endl;
			}
			else
			cout<<"Error3"<<endl;
		}
		else
		cout<<"Error2"<<endl;
	}
	else
	cout<<"Error1"<<endl;
	system("cls");
	cout<<endl<<"Final Score : "<<score;
	
	return 0;
}
//Code By Saurabh Manchanda
