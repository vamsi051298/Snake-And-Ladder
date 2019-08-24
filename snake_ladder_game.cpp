#include<stdio.h>
#include<cstdlib>
#include<ctime>
#include<conio.h>
#include<windows.h>
#include<malloc.h>
#define NON 100
int arr[NON];
int res_arr[NON];
typedef struct node
{
	int data;
	struct node *ladder_snake;
	struct node *next;
}snake_ladder;
typedef snake_ladder* snake_ladder_PTR;
snake_ladder_PTR create_board(snake_ladder_PTR start,int val)
{
	snake_ladder_PTR NN,TPTR;
	NN=(snake_ladder_PTR)malloc(sizeof(snake_ladder));
	NN->data=val;
	NN->next=NULL;
	NN->ladder_snake=NULL;
	if(!start)
		start=NN;
	else
	{
		TPTR=start;
		while(TPTR->next)
			TPTR=TPTR->next;
		TPTR->next=NN;
	}
	return start;
}
void display_board(snake_ladder_PTR start)
{
	snake_ladder_PTR TPTR=start;
	int k=10;
	printf("								(:~~~~~~~~  AND   IIIIIIIIIII\n\n\n");
	HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE);
	while(TPTR)
	{
		printf("					");
		while(k-- && TPTR)
		{
			if(TPTR->data==1)
			{
        		SetConsoleTextAttribute(color, 4);
				printf("  %d	",TPTR->data);
				TPTR=TPTR->next;
			}
			else if(TPTR->data==100)
			{
        		SetConsoleTextAttribute(color, 3);
				printf("%d	",TPTR->data);
				TPTR=TPTR->next;
			}
			else if(TPTR->data>=2 && TPTR->data<=9)
			{
        		SetConsoleTextAttribute(color, 3);
				printf("  %d	",TPTR->data);
				TPTR=TPTR->next;
			}
			else
			{
				printf(" %d	",TPTR->data);
				TPTR=TPTR->next;
			}
		}
		k=10;
		printf("\n\n");
	}
	printf(" GAME RULE:\n");
	printf(" ---------\n");
	printf("	* If any player rolls a dice of value '6' for continously more than for two times\nthen the particular player starts the game from begining\n\n\n");
}
void reverse(int arr[],int start,int end)
{
	int temp;
	while(start<end)
	{
		temp=arr[start];
		arr[start]=arr[end];
		arr[end]=temp;
		start++;
		end--;
	}
}
snake_ladder_PTR build_ladder(snake_ladder_PTR Game,int ladd_S,int ladd_E)
{
	snake_ladder_PTR TPTR=Game,ladd_S_PTR=NULL,ladd_E_PTR=NULL;
	while(TPTR)
	{
		if(TPTR->data==ladd_S)
			break;
		else
			TPTR=TPTR->next;
	}
	ladd_S_PTR=TPTR;
	while(TPTR)
	{
		if(TPTR->data==ladd_E)
			break;
		else
			TPTR=TPTR->next;
	}
	ladd_E_PTR=TPTR;
	ladd_S_PTR->ladder_snake=ladd_E_PTR;
	return Game;
}
snake_ladder_PTR build_snake(snake_ladder_PTR Game,int snake_S,int snake_E)
{
	snake_ladder_PTR TPTR=Game,snake_S_PTR=NULL,snake_E_PTR=NULL;
	while(TPTR)
	{
		if(TPTR->data==snake_E)
			break;
		else
			TPTR=TPTR->next;
	}
	snake_E_PTR=TPTR;
	while(TPTR)
	{
		if(TPTR->data==snake_S)
			break;
		else
			TPTR=TPTR->next;
	}
	snake_S_PTR=TPTR;
	snake_S_PTR->ladder_snake=snake_E_PTR;
	return Game;
}
snake_ladder_PTR player2_game(snake_ladder_PTR Game,snake_ladder_PTR player2,snake_ladder_PTR start,int *count,snake_ladder_PTR *TPTR_player2)
{
	int dice,check_ladd_snake,prev_dice,range=6,check;
	snake_ladder_PTR TPTR=*TPTR_player2;
	while(TPTR->ladder_snake==NULL && range--)
		TPTR=TPTR->next;
	if(TPTR->ladder_snake==NULL)
		printf("There will be no ladder and snake when you roll a dice\n");
	else
	{
		check=TPTR->data;
		TPTR=TPTR->ladder_snake;
		if(check<TPTR->data)
			printf("If you are lucky then your next move at %d is a ladder\n\n",check);
		else
			printf("If you are unlucky then your next move at %d is a snake. Becareful!!!\n\n",check);
	}
	range=6;
	//printf("Enter the dice values from range(1 to 6)");
	//scanf("%d",&dice);
	printf("Press Enter key for Rolling a dice\n");
	getch();
	srand(time(0));
    dice=(rand() % 6 + 1);
	if(dice==6)
	{
		(*count)++;
		if((*count)>2)
		{
			player2=Game;
			*count=0;
			printf("You had break the Rule!!!\n");
			return player2;
		}
	}
	else
		*count=0;
	while(dice==0 || dice>6)
	{
		while(TPTR->ladder_snake==NULL && range--)
			TPTR=TPTR->next;
		if(TPTR->ladder_snake==NULL)
			printf("There will be no ladder and snake when you roll a dice\n");
		else
		{
			check=TPTR->data;
			TPTR=TPTR->ladder_snake;
			if(check<TPTR->data)
				printf("If you are lucky then your next move at %d is a ladder\n\n",check);
			else
				printf("If you are unlucky then your next move at %d is a snake. Becareful!!!\n\n",check);
		}
		range=6;
		//printf("please enter the values in given range(1 to 6)");
		//scanf("%d",&dice);
		printf("Press Enter key for Rolling a dice\n");
		getch();
		srand(time(0));
    	dice=(rand() % 6 + 1);
		if(dice==6)
		{
			(*count)++;
			if((*count)>2)
			{
				player2=Game;
				*count=0;
				printf("You had break the Rule!!!\n");
				return player2;
			}
		}
		else
			*count=0;
	}
	if(!player2)
	{
		prev_dice=dice;
		player2=Game;
		dice--;
		while(dice--)
			player2=player2->next;
		TPTR=player2;
		printf("Player2 is at location %d\n",player2->data);
		while(player2->ladder_snake!=NULL)
		{
			check_ladd_snake=player2->data;
			player2=player2->ladder_snake;
			TPTR=player2;
			if(player2->data>check_ladd_snake)
			{
				printf("Player2 has choosen ladder so Player2 is at location %d\n",player2->data);
				while(TPTR->ladder_snake==NULL && range--)
					TPTR=TPTR->next;
				if(TPTR->ladder_snake==NULL)
					printf("There will be no ladder and snake when you roll a dice\n");
				else
				{
					check=TPTR->data;
					TPTR=TPTR->ladder_snake;
					if(check<TPTR->data)
						printf("If you are lucky then your next move at %d is a ladder\n\n",check);
					else
						printf("If you are unlucky then your next move at %d is a snake. Becareful!!!\n\n",check);
				}
				range=6;
				printf("Player2 had choosen ladder so player2 get's chance for rolling a dice\n");
				//scanf("%d",&dice);
				printf("Press Enter key for Rolling a dice\n");
				getch();
				srand(time(0));
    			dice=(rand() % 6 + 1);
				if(dice==6)
				{
					(*count)++;
					if((*count)>2)
					{
						player2=Game;
						*count=0;
						printf("You had break the Rule!!!\n");
						return player2;
					}
				}
				else
					*count=0;
				while(dice--)
					player2=player2->next;
				TPTR=player2;
				printf("Player2 is at location %d\n",player2->data);
			}
			else
				printf("Due to snake bite Player2 is at location %d\n",player2->data);
		}
	}
	else
	{
		snake_ladder_PTR prev_pos=player2;
		prev_dice=dice;
		while(dice-- && player2)
			player2=player2->next;
		TPTR=player2;
		if(!player2)
		{
			player2=prev_pos;
			printf("Sorry, you cannot cross the Boundary!!!\n");
			return player2;
		}
		printf("Player2 is at location %d\n",player2->data);
		while(player2->ladder_snake!=NULL)
		{
			check_ladd_snake=player2->data;
			player2=player2->ladder_snake;
			TPTR=player2;
			prev_pos=player2;
			if(player2->data>check_ladd_snake)
			{
				printf("Player2 has choosen ladder so Player2 is at location %d\n",player2->data);
				while(TPTR->ladder_snake==NULL && range--)
					TPTR=TPTR->next;
				if(TPTR->ladder_snake==NULL)
					printf("There will be no ladder and snake when you roll a dice\n");
				else
				{
					check=TPTR->data;
					TPTR=TPTR->ladder_snake;
					if(check<TPTR->data)
						printf("If you are lucky then your next move at %d is a ladder\n\n",check);
					else
						printf("If you are unlucky then your next move at %d is a snake. Becareful!!!\n\n",check);
				}
				range=6;
				printf("Player2 had choosen ladder so player2 get's chance for rolling a dice\n");
				//scanf("%d",&dice);
				printf("Press Enter key for Rolling a dice\n");
				getch();
				srand(time(0));
    			dice=(rand() % 6 + 1);
				if(dice==6)
				{
					(*count)++;
					if((*count)>2)
					{
						player2=Game;
						*count=0;
						printf("You had break the Rule!!!\n");
						return player2;
					}
				}
				else
					*count=0;
				prev_pos=player2;
				while(dice-- && player2)
					player2=player2->next;
				TPTR=player2;
				if(!player2)
				{
					player2=prev_pos;
					printf("Sorry, you cannot cross the Boundary!!!\n");
					return player2;
				}
				printf("Player2 is at location %d\n",player2->data);
			}
			else
				printf("Due to snake bite Player2 is at location %d\n",player2->data);
		}
	}
	*TPTR_player2=TPTR;
	return player2;
}
snake_ladder_PTR player1_game(snake_ladder_PTR Game,snake_ladder_PTR player1,snake_ladder_PTR start,int *count,snake_ladder_PTR *TPTR_player1)
{
	int dice,check_ladd_snake,prev_dice,store_val,check,range=6;
	snake_ladder_PTR TPTR=*TPTR_player1;
	while(TPTR->ladder_snake==NULL && range--)
		TPTR=TPTR->next;
	if(TPTR->ladder_snake==NULL)
		printf("There will be no ladder and snake when you roll a dice\n");
	else
	{
		check=TPTR->data;
		TPTR=TPTR->ladder_snake;
		if(check<TPTR->data)
			printf("If you are lucky then your next move at %d is a ladder\n\n",check);
		else
			printf("If you are unlucky then your next move at %d is a snake. Becareful!!!\n\n",check);
	}
	range=6;
	//printf("Enter the dice values from range(1 to 6)");
	//scanf("%d",&dice);
	printf("Press Enter key for Rolling a dice\n");
	getch();
	srand(time(0));
   	dice=(rand() % 6 + 1);
	if(dice==6)
	{
		(*count)++;
		if((*count)>2)
		{
			player1=Game;
			*count=0;
			printf("You had break the Rule!!!\n");
			return player1;
		}
	}
	else
		*count=0;
	while(dice==0 || dice>6)
	{
		while(TPTR->ladder_snake==NULL && range--)
			TPTR=TPTR->next;
		if(TPTR->ladder_snake==NULL)
			printf("There will be no ladder and snake when you roll a dice\n");
		else
		{
			check=TPTR->data;
			TPTR=TPTR->ladder_snake;
			if(check<TPTR->data)
				printf("If you are lucky then your next move at %d is a ladder\n\n",check);
			else
				printf("If you are unlucky then your next move at %d is a snake. Becareful!!!\n\n",check);
		}
		range=6;
		//printf("please enter the values in given range(1 to 6)");
		//scanf("%d",&dice);
		printf("Press Enter key for Rolling a dice\n");
		getch();
		srand(time(0));
    	dice=(rand() % 6 + 1);
		if(dice==6)
		{
			(*count)++;
			if((*count)>2)
			{
				player1=Game;
				*count=0;
				printf("You had break the Rule!!!\n");
				return player1;
			}
		}
		else
			*count=0;
	}
	if(!player1)
	{
		prev_dice=dice;
		player1=Game;
		dice--;
		while(dice--)
			player1=player1->next;
		TPTR=player1;
		printf("Player1 is at location %d\n",player1->data);
		while(player1->ladder_snake!=NULL)
		{
			check_ladd_snake=player1->data;
			player1=player1->ladder_snake;
			TPTR=player1;
			if(player1->data>check_ladd_snake)
			{
				printf("Player1 has choosen ladder so Player1 is at location %d\n",player1->data);
				while(TPTR->ladder_snake==NULL && range--)
					TPTR=TPTR->next;
				if(TPTR->ladder_snake==NULL)
					printf("There will be no ladder and snake when you roll a dice\n");
				else
				{
					check=TPTR->data;
					TPTR=TPTR->ladder_snake;
					if(check<TPTR->data)
						printf("If your lucky then your next move at %d is a ladder\n\n",check);
					else
						printf("If you are unlucky then your next move at %d is a snake. Becareful!!!\n\n",check);
				}
				range=6;
				printf("Player1 had choosen ladder so player1 get's chance for rolling a dice\n");
				//scanf("%d",&dice);
				printf("Press Enter key for Rolling a dice\n");
				getch();
				srand(time(0));
    			dice=(rand() % 6 + 1);
				if(dice==6)
				{
					(*count)++;
					if((*count)>2)
					{
						player1=Game;
						*count=0;
						printf("You had break the Rule!!!\n");
						return player1;
					}
				}
				else
					*count=0;
				while(dice--)
					player1=player1->next;
				TPTR=player1;
				printf("Player1 is at location %d\n\n",player1->data);
			}
			else
				printf("Due to snake bite Player1 is at location %d\n\n",player1->data);
		}
	}
	else
	{
		snake_ladder_PTR prev_pos=player1;
		prev_dice=dice;
		while(dice-- && player1)
			player1=player1->next;
		TPTR=player1;
		if(!player1)
		{
			player1=prev_pos;
			printf("Sorry, you cannot cross the Boundary!!!\n");
			return player1;
		}
		printf("Player1 is at location %d\n",player1->data);
		while(player1->ladder_snake!=NULL)
		{
			check_ladd_snake=player1->data;
			player1=player1->ladder_snake;
			TPTR=player1;
			prev_pos=player1;
			if(player1->data>check_ladd_snake)
			{
				printf("Player1 has choosen ladder so Player1 is at location %d\n",player1->data);
				while(TPTR->ladder_snake==NULL && range--)
					TPTR=TPTR->next;
				if(TPTR->ladder_snake==NULL)
					printf("There will be no ladder and snake when you roll a dice\n");
				else
				{
					check=TPTR->data;
					TPTR=TPTR->ladder_snake;
					if(check<TPTR->data)
						printf("If you are lucky then your next move at %d is a ladder\n\n",check);
					else
						printf("If your are unlucky then your next move at %d is a snake. Becareful!!!\n\n",check);
				}
				range=6;
				printf("Player1 had choosen ladder so player1 get's chance for rolling a dice\n");
				//scanf("%d",&dice);
				printf("Press Enter key for Rolling a dice\n");
				getch();
				srand(time(0));
    			dice=(rand() % 6 + 1);
				if(dice==6)
				{
					(*count)++;
					if((*count)>2)
					{
						player1=Game;
						
						*count=0;
						printf("You had break the Rule!!!\n");
						return player1;
					}
				}
				else
					*count=0;
				prev_pos=player1;
				while(dice-- && player1)
					player1=player1->next;
				TPTR=player1;
				if(!player1)
				{
					player1=prev_pos;
					printf("Sorry, you cannot cross the Boundary!!!\n");
					return player1;
				}
				printf("Player1 is at location %d\n",player1->data);
			}
			else
				printf("Due to snake bite Player1 is at location %d\n",player1->data);
		}
	}
	*TPTR_player1=TPTR;
	return player1;
}
int letS_play_game(snake_ladder_PTR Game,snake_ladder_PTR start)
{
	int player_1,player_2,count_player1=0,count_player2=0,flag_player1;
	snake_ladder_PTR player1=NULL,player2=NULL,TPTR_player1=Game,TPTR_player2=Game;
	printf("Player 1 Turn Begins!!!\n");
	player1=player1_game(Game,player1,start,&count_player1,&TPTR_player1);
	printf("Press any character in keyboard for next player turn");
	getch();
	system("CLS");
	display_board(start);
	printf("Player 2 Turn Begins!!!\n");
	player2=player2_game(Game,player2,start,&count_player2,&TPTR_player2);
	printf("Press any character in keyboard for next player turn");
	getch();
	system("CLS");
	display_board(start);
	printf("player1 is already present at location %d\n",player1->data);
	while(player1->data<=99 || player2->data<=99)
	{
		printf("Player 1 Turn Begins!!!\n");
		player1=player1_game(Game,player1,start,&count_player1,&TPTR_player1);
		if(player1->data==100)
			break;
		printf("Press any character in keyboard for next player turn");
		getch();
		system("CLS");
		display_board(start);
		printf("player2 is already present at location %d\n",player2->data);
		printf("Player 2 Turn Begins!!!\n");
		player2=player2_game(Game,player2,start,&count_player2,&TPTR_player2);
		if(player2->data==100)
			break;
		printf("Press any character in keyboard for next player turn");
		getch();
		system("CLS");
		display_board(start);
		printf("player1 is already present at location %d\n",player1->data);
	}
	if(player1->data==100)
	{
		printf("Player1 has WON the GAME!!!!");
		return 0;
	}
	else
	{
		printf("Player2 has WON the GAME!!!!");
		return 0;
	}
}
int main()
{
	snake_ladder_PTR start=NULL;
	snake_ladder_PTR Game=NULL;
	int non=100,ind,k=10,v=10,strt,end;
	for(ind=1;ind<=non;ind++)
		arr[ind]=ind;
	for(ind=1;ind<=non;ind++)
		res_arr[ind]=ind;
	strt=1;
	end=k;
	while(k-- && strt<=non && end<=non)
	{
		reverse(arr,strt,end);
		strt=end+v+1;
		end=strt+v-1;
	}
	for(ind=non;ind>=1;ind--)
		start=create_board(start,arr[ind]);
	for(ind=1;ind<=non;ind++)
		Game=create_board(Game,res_arr[ind]);
	display_board(start);
	
	Game=build_ladder(Game,4,56);
	Game=build_ladder(Game,12,50);
	Game=build_ladder(Game,14,55);
	Game=build_ladder(Game,22,58);
	Game=build_ladder(Game,41,79);
	Game=build_ladder(Game,54,88);
	
	Game=build_snake(Game,28,10);
	Game=build_snake(Game,37,3);
	Game=build_snake(Game,47,16);
	Game=build_snake(Game,77,32);
	Game=build_snake(Game,94,71);
	Game=build_snake(Game,96,42);
	
	letS_play_game(Game,start);
	return 0;
}
