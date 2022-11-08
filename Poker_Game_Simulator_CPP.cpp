#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <fstream>
#define HIGHEST_VALUE 960 //900 + 10 + jack + queen + king + ace
#define SleepValue 5 //Sleep value

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::swap;
using std::ofstream;
using std::ios;



//To work with coordinates
//////////////////////////////////////////////////////////////////////////////////////////////////////
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);	
} 

void setcurser(bool visible, DWORD size){ //set bool visible = 0  - invisible , 1 - visible
	if(size == 0)
	{
		size = 20; //default cursor size Changing to numbers from 1 to 20, decreases cursor width
	}
	CONSOLE_CURSOR_INFO lpCursor ;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////




struct Value
{
	string card;
	int Value;
};

struct Card
{
	string shape;
	string card;
	int value;
};

class Player
{
	private:
		vector <Card> Recived_cards;
		string Player_name;
		double Card_Value; //This contains the value of the hand owned by the player
		bool State; // true =Playing, false = withdraw 
		bool Round_over; //To show all cards at the end of the round
		int current_score; // current Score of the player 
	public:
		Player()
		{
			State=true;
			Round_over=true; ////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
			Card_Value=0;
			current_score=0;
		}
		void getCards(Card Input)
		{
			Recived_cards.push_back(Input);
		}
		void setPlayer(string name)
		{
			Player_name=name;
		}
		vector <Card> return_cards()
		{
			return Recived_cards;
		}
		void Set_Card_Value(double cardval)
		{
			Card_Value=cardval;
		}
		double get_confidence()
		{
			return Card_Value;
		}
		void Set_State(bool state)
		{
			State=state;
		}
		bool get_State()
		{
			return State;
		}
		//saves confidance level as a precentage
		void Player_winning_level()
		{
			Card_Value = (Card_Value*100)/HIGHEST_VALUE;
		}
		void set_Score(int score)
		{
			current_score+=score;
		}
		int get_Score()
		{
			return current_score;
		}
		void Round_Over(bool R_O)
		{
			Round_over=R_O;
		}
		void print(int x, int y)
		{
			for(int i=0;i<5;i++)
			{
				gotoxy(x+18,y-2); cout<<Player_name;
				char Covered=219;
				
				if(Round_over==false || Player_name=="Dealer")
				{			
					//card01
					gotoxy(x,y); cout<<Recived_cards[0].shape;
					gotoxy(x,y+1); cout<<Recived_cards[0].card;
					//card02
					gotoxy(x+9,y); cout<<Recived_cards[1].shape;
					gotoxy(x+9,y+1); cout<<Recived_cards[1].card;
					//card03
					gotoxy(x+18,y); cout<<Recived_cards[2].shape;
					gotoxy(x+18,y+1); cout<<Recived_cards[2].card;
					//card04
					gotoxy(x+27,y); cout<<Recived_cards[3].shape;
					gotoxy(x+27,y+1); cout<<Recived_cards[3].card;
					//card05
					gotoxy(x+36,y); cout<<Recived_cards[4].shape;
					gotoxy(x+36,y+1); cout<<Recived_cards[4].card;			
				}
				else
				{
					//card01
					gotoxy(x,y); cout<<Covered<<Covered<<Covered<<Covered<<Covered<<Covered;
					gotoxy(x,y+1); cout<<Covered<<Covered<<Covered<<Covered<<Covered<<Covered;
					//card02
					gotoxy(x+9,y); cout<<Covered<<Covered<<Covered<<Covered<<Covered<<Covered;
					gotoxy(x+9,y+1); cout<<Covered<<Covered<<Covered<<Covered<<Covered<<Covered;
					//card03
					gotoxy(x+18,y); cout<<Covered<<Covered<<Covered<<Covered<<Covered<<Covered;
					gotoxy(x+18,y+1); cout<<Covered<<Covered<<Covered<<Covered<<Covered<<Covered;
					//card04
					gotoxy(x+27,y); cout<<Covered<<Covered<<Covered<<Covered<<Covered<<Covered;
					gotoxy(x+27,y+1); cout<<Covered<<Covered<<Covered<<Covered<<Covered<<Covered;
					//card05
					gotoxy(x+36,y); cout<<Covered<<Covered<<Covered<<Covered<<Covered<<Covered;
					gotoxy(x+36,y+1); cout<<Covered<<Covered<<Covered<<Covered<<Covered<<Covered;
				}
				
				gotoxy(x+15,y+3);
				State==true ?  cout<<"Still playing": cout<<"Withdrawed";	
				gotoxy(x+8,y+5); cout<<"Winning confidence "<<Card_Value;				
			}
		}
};

//Initialize card pack
void initialize_card_pack(vector <Card> &Card_Pack)
{
	//Vectors for initialize Card vector
	vector <string> Shape = {"Spade", "Diamond", "Heart", "Club"};
	vector <Value> Value_vec = {{"2", 2 }, {"3", 3 }, {"4", 4 }, {"5", 5 }, {"6", 6 }, {"7", 7 }, {"8", 8 }, {"9", 9 }, {"10", 10 }, {"Jack", 11 }, {"Queen", 12 }, {"King", 13 }, {"Ace", 14 }}; 	
	
	for(int i=0;i<Shape.size();i++)
	{
		for(int j=0;j<Value_vec.size();j++)
		{
			Card temp;
			temp.shape = Shape[i];
			temp.card = Value_vec[j].card;
			temp.value = Value_vec[j].Value;
			Card_Pack.push_back(temp);
		}
	}
}
//shuffles the card pack
void Shuffle(vector <Card> &Card_Pack)
{
	int suffle_count=rand()%3000;  //Shuffles this number of times(by swapping two random cards per one cycle
	for(int i=0;i<suffle_count;i++)
	{
		int first  = rand()%52;
		int second = rand()%52;
		swap(Card_Pack[first], Card_Pack[second]);
	}	

	//Remove first two cards
	Card_Pack.erase(Card_Pack.begin());
	Card_Pack.erase(Card_Pack.begin());	
}
//give cards to each player as instructed
void Give_Cards_to_Players(vector <Card> &Card_Pack, vector <Player> &Players)
{
	for(int i=0;i<5;i++)
	{
		Player temp;
		
		if(i==0) {temp.setPlayer("Dealer");}
		else if(i==1) {temp.setPlayer("Player A");}
		else if(i==2) {temp.setPlayer("Player B");}
		else if(i==3) {temp.setPlayer("Player C");}
		else if(i==4) {temp.setPlayer("Player D");}
		
		Players.push_back(temp);
	}
	
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			Players[j].getCards(Card_Pack[0]);
			Card_Pack.erase(Card_Pack.begin());
		}
	}
	
	//File to input
	ofstream file;
	file.open("Log.txt", ios::app);
	
	
	for(int j=0;j<5;j++)
	{
		vector <Card> vec=Players[j].return_cards();
		if(j==0) {file<<"Dealer"<<endl;}
		else if(j==1) {file<<"Player A"<<endl;}
		else if(j==2) {file<<"Player B"<<endl;}
		else if(j==3) {file<<"Player C"<<endl;}
		else if(j==4) {file<<"Player D"<<endl;}
	
		for(int i=0;i<5;i++)
		{
			file<<vec[i].shape<<" of "<<vec[i].card<<endl;
		}
		file<<endl;
	}
	
}

//Printing the current status
void Print_Players(vector <Player> Players)
{
	
	Players[0].print(2,3);
	Players[1].print(18,20);
	Players[2].print(60,10);
	Players[3].print(100,20);	
	Players[4].print(60,30);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////Value calculating functions///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//StraightFlush and Straight both is checked in this function with different input arguments
bool StraightFlush_or_Straight(vector <Card> Recived_cards, bool SF_or_S, double &CardValue)
{

		CardValue=0;
		//cheking suit
		if(SF_or_S==true)
		{
			CardValue +=400;
			for(int i=0;i<5;i++)
			{
				if(Recived_cards[0].shape!=Recived_cards[i].shape)
				{
					return false;
				}	
			}	
		}
		//sorting
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<4;j++)
			{
				if(Recived_cards[j].value>Recived_cards[j+1].value)
				{
					swap(Recived_cards[j] , Recived_cards[j+1]);
				}
			}		
		}
		bool Return = false;
		//calculaing the value
		if(Recived_cards[0].value==Recived_cards[1].value-1&&Recived_cards[1].value==Recived_cards[2].value-1&&Recived_cards[2].value==Recived_cards[3].value-1&&Recived_cards[3].value==Recived_cards[4].value-1)
		{
			Return=true;
		}
		if(Recived_cards[0].value==2&&Recived_cards[0].value==Recived_cards[1].value-1&&Recived_cards[1].value==Recived_cards[2].value-1&&Recived_cards[2].value==Recived_cards[3].value-1&&Recived_cards[4].value==14)
		{
			Return=true;
		}
		
		CardValue+=(500+Recived_cards[0].value+Recived_cards[1].value+Recived_cards[2].value+Recived_cards[3].value+Recived_cards[4].value);
		return Return;
}

//Four of a kind is checked in this function
bool Four_Of_A_Kind_or_Three_Of_A_King_or_One_Pair(vector <Card> Recived_card, int FourOK_or_ThreeOK_or_Pair, double &CardValue) //2 for one Pair, 3 for TOK and 4 for FOK
{
	vector <Card> Recived_cards = Recived_card;
	bool Return=false;
	CardValue=0;
	//sorting
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(Recived_cards[j].value>Recived_cards[j+1].value)
			{
				swap(Recived_cards[j] , Recived_cards[j+1]);
			}
		}		
	}

	
	//cheking requirements
	
	if(FourOK_or_ThreeOK_or_Pair==2)
	{
		for(int i=0;i<4;i++)
		{
			if(Recived_cards[i].value==Recived_cards[i+1].value)
			{
				CardValue=200+ 2*Recived_cards[i].value;
				Return=true;
			}		
		}
	}
	else if(FourOK_or_ThreeOK_or_Pair==3)
	{
		for(int i=0;i<3;i++)
		{
			if(Recived_cards[i].value==Recived_cards[i+1].value&&Recived_cards[i+1].value==Recived_cards[i+2].value)
			{
				CardValue=400+ 3*Recived_cards[i].value;
				Return=true;
			}		
		}
	}
	else if(FourOK_or_ThreeOK_or_Pair==4)
	{
		for(int i=0;i<2;i++)
		{
			if(Recived_cards[i].value==Recived_cards[i+1].value&&Recived_cards[i+1].value==Recived_cards[i+2].value&&Recived_cards[i+2].value==Recived_cards[i+3].value)
			{
				CardValue=800;;
				CardValue+= 4*Recived_cards[i].value;
				Return=true;
			}

					
		}
	}
	else
	{
		return false;
	}
	return Return;
}

//Full house is checked in this function
bool Full_House(vector <Card> Recived_card, double &CardValue)
{
	vector <Card> Recived_cards = Recived_card;
	bool Return=false;
	CardValue=0;
	//sorting
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(Recived_cards[j].value>Recived_cards[j+1].value)
			{
				swap(Recived_cards[j] , Recived_cards[j+1]);
			}
		}		
	}

	for(int i=0;i<3;i++)
	{
		if(Recived_cards[i].value==Recived_cards[i+1].value&&Recived_cards[i+1].value==Recived_cards[i+2].value)
		{
			Return = true;
			Recived_cards.erase(Recived_cards.begin()+i, Recived_cards.begin()+i+3);
			break;
		}
	}
	if(Recived_cards[0].value!=Recived_cards[1].value)
	{
		Return = false;
	}
	
	CardValue = 700 + Recived_card[0].value + Recived_card[1].value + Recived_card[2].value + Recived_card[3].value + Recived_card[4].value;
	
	return Return;
	
}

//Flush is checked in this function
bool Flush(vector <Card> Recived_card, double &CardValue)
{
	vector <Card> Recived_cards = Recived_card;
	bool Return=true;
	CardValue=0;
	string STR = Recived_cards[0].shape;
	
	//condition check
	if(STR=="Spade"||STR=="Club")
	{
		for(int i=1;i<5;i++)
		{
			if(!(Recived_cards[i].shape=="Spade"||Recived_cards[i].shape=="Club"))
			{
				Return=false;
			}
		}
	}
	else
	{
		for(int i=1;i<5;i++)
		{
			if(!(Recived_cards[i].shape=="Heart"||Recived_cards[i].shape=="Diamond"))
			{
				Return=false;
			}
		}
	}
	
	if(Return==true)
	{
		CardValue = 600 + Recived_cards[0].value + Recived_cards[1].value + Recived_cards[2].value + Recived_cards[3].value + Recived_cards[4].value;
		return Return;
	}
	return Return;
}

//Two pairs is checked in this function
bool Two_Pairs(vector <Card> Recived_card, double &CardValue)
{
	vector <Card> Recived_cards = Recived_card;
	bool Return1=false;
	bool Return2=false;
	CardValue=0;
	//sorting
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(Recived_cards[j].value>Recived_cards[j+1].value)
			{
				swap(Recived_cards[j] , Recived_cards[j+1]);
			}
		}		
	}
	for(int i=0;i<4;i++)
	{
		if(Recived_cards[i].value==Recived_cards[i+1].value)
		{
			Return1 = true;
			CardValue+=2*Recived_cards[i].value;
			Recived_cards.erase(Recived_cards.begin()+i, Recived_cards.begin()+i+2);
			break;
		}
	}
	
	for(int i=0;i<2;i++)
	{
		if(Recived_cards[i].value==Recived_cards[i+1].value)
		{
			Return2 = true;
			CardValue+= 2*Recived_card[i].value;
			Recived_cards.erase(Recived_cards.begin()+i, Recived_cards.begin()+i+2);
			break;
		}
	}

	CardValue += 300;
	
	return Return1&&Return2;
}

//High card is checked here
bool High_card(vector <Card> Recived_card, double &CardValue)
{
	vector <Card> Recived_cards = Recived_card;
	bool Return1=false;
	bool Return2=false;
	CardValue=0;
	//sorting
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(Recived_cards[j].value>Recived_cards[j+1].value)
			{
				swap(Recived_cards[j] , Recived_cards[j+1]);
			}
		}		
	}
	CardValue=Recived_cards[4].value;
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


//returns the value of the player's card set
int Value_Of_Player_card_set_and_confidence_precentage_is_calculated(vector <Player> &Players)
{
	for(int i=0;i<5;i++)
	{
		vector <Card> Recived_cards = Players[i].return_cards();
		double CardValue=0;
		bool Return=false;
	
			// 9 Straight Flush
			if(StraightFlush_or_Straight(Recived_cards , true , CardValue)) 
			{
				Players[i].Set_Card_Value(CardValue);
				Players[i].Player_winning_level(); 
				continue;
			}
			CardValue=0;
			Return=false;
			// 8 Four of a kind
			if(Four_Of_A_Kind_or_Three_Of_A_King_or_One_Pair(Recived_cards , 4 , CardValue))
			{ 
				Players[i].Set_Card_Value(CardValue); 
				Players[i].Player_winning_level(); 
				continue; 
			}
			CardValue=0;
			Return=false;
			// 7 Full house
			if(Full_House(Recived_cards, CardValue))
			{
				Players[i].Set_Card_Value(CardValue); 	
				Players[i].Player_winning_level(); 
				continue; 
			}	
			CardValue=0;
			Return=false;
			// 6 Flush
			if(Flush(Recived_cards, CardValue))
			{
				Players[i].Set_Card_Value(CardValue);
				Players[i].Player_winning_level(); 
				continue; 
			}
			CardValue=0;
			Return=false;
			// 5 Straight
			if(StraightFlush_or_Straight(Recived_cards , false , CardValue))
			{ 
				Players[i].Set_Card_Value(CardValue); 
				Players[i].Player_winning_level(); 
				continue;
			}	
			CardValue=0;
			Return=false;
			// 4 Three of a kind
			if(Four_Of_A_Kind_or_Three_Of_A_King_or_One_Pair(Recived_cards , 3 , CardValue))
			{
				Players[i].Set_Card_Value(CardValue); 
				Players[i].Player_winning_level(); 
				continue;
			}	
			CardValue=0;
			Return=false;
			// 3 Two pairs
			if(Two_Pairs(Recived_cards , CardValue))
			{
				Players[i].Set_Card_Value(CardValue); 
				Players[i].Player_winning_level();
				continue; 
			}
			CardValue=0;
			Return=false;
			// 2 One pairs
			if(Four_Of_A_Kind_or_Three_Of_A_King_or_One_Pair(Recived_cards , 2 , CardValue))
			{
				Players[i].Set_Card_Value(CardValue); 
				Players[i].Player_winning_level(); 
				continue;
			}
			CardValue=0;
			Return=false;
			// 1 High card	
			if(High_card(Recived_cards , CardValue))
			{
				Players[i].Set_Card_Value(CardValue); 
				Players[i].Player_winning_level(); 
				continue;
			}
			else{CardValue=0;}
			CardValue=0;
			Return=false;		
	}
	
	
	
	

}

//Choosing withdraw or not by the player
void Decision(vector <Player> &Players)
{
	int withdrawed_count=0;
	for(int i=1;i<5;i++)
	{
		double Player_confidence=Players[i].get_confidence(); 
		double Dealer_confidence=Players[0].get_confidence();
		int random_number = rand()%6;;
		
		Print_Players(Players);
		
		//Here, if confidence level of the player is less. He either choose to stay in the game or withdraw
		gotoxy(155,10); 
		
		if(i==1) {cout<<"Player A's chance";}
		else if(i==2) {cout<<"Player B's chance";}
		else if(i==3) {cout<<"Player C's chance";}
		else if(i==4) {cout<<"Player D's chance";}
		
		Sleep(SleepValue);

		if(Player_confidence<Dealer_confidence&&withdrawed_count<2)
		{
			random_number = rand()%8; //Higher possibility is to withdraw. 

			if(random_number>3)
			{
				Players[i].Set_State(true); //player plays further
			}
			else
			{
				withdrawed_count++;
				Players[i].Set_State(false); //player withdraws
			}
		}		
		
		//printing the updated table
		system("cls");
		Print_Players(Players);
	}
	
	Sleep(SleepValue);
}

void score_calculate(vector <Player> &Players, vector <double> &Score)
{
	vector <double> Scores;
	for(int i=0;i<5;i++)
	{
		double temp=Players[i].get_confidence();
		Scores.push_back(temp);
	}
	double maxConfidance=Scores[0];
	int ID=0;
	for(int i=1;i<5;i++)
	{
		if(Players[i].get_confidence()>maxConfidance)
		{
			maxConfidance=Players[i].get_confidence();
			ID=i;
		}
	}
	
	for(int i=1;i<5;i++)
	{
		if(i==ID)
		{
			Score[i]+=10;
		}
		else if(i!=ID && Players[i].get_State())
		{
			Score[i]+=-1;
		}
		else
		{
			Score[i]+=0;
		}
	}
	
	for(int i=0;i<5;i++)
	{
		Players[i].Round_Over(false);
	}
	
	double minimumScore=Scores[0];
	int minID=0;
	for(int i=1;i<5;i++)
	{
		if(Scores[i]<minimumScore)
		{
			minimumScore=Scores[i];
			minID=i;
		}
	}	
	
	//File to input
	ofstream file;
	file.open("Log.txt", ios::app);
	
	

	
	
	//Printing the results
	system("cls");
	Print_Players(Players);
	gotoxy(155,15); cout<<"Round is Over";
					file<<"Round is Over";
	gotoxy(155,17); cout<<"Dealer's Score is : "<<Score[0];
					file<<"Dealer's Score is : "<<Score[0]<<endl;
	gotoxy(155,18); cout<<"   His winning probability is : "<<abs(Score[0]-abs(Score[minID]))*100/( abs(Score[0]) + abs(Score[1]) + abs(Score[2]) + abs(Score[3]) + abs(Score[4]) )<<"%";
					file<<"   His winning probability is : "<<abs(Score[0]-abs(Score[minID]))*100/( abs(Score[0]) + abs(Score[1]) + abs(Score[2]) + abs(Score[3]) + abs(Score[4]) )<<"%"<<endl;
	gotoxy(155,19); cout<<"A's Score is : "<<Score[1];	
					file<<"A's Score is : "<<Score[1]<<endl;
	gotoxy(155,20); cout<<"   His winning probability is : "<<abs(Score[1]-abs(Score[minID]))*100/( abs(Score[0]) + abs(Score[1]) + abs(Score[2]) + abs(Score[3]) + abs(Score[4]) )<<"%";
					file<<"   His winning probability is : "<<abs(Score[1]-abs(Score[minID]))*100/( abs(Score[0]) + abs(Score[1]) + abs(Score[2]) + abs(Score[3]) + abs(Score[4]) )<<"%"<<endl;
	gotoxy(155,21); cout<<"B's Score is : "<<Score[2];
					file<<"B's Score is : "<<Score[2]<<endl;
	gotoxy(155,22); cout<<"   His winning probability is : "<<abs(Score[2]-abs(Score[minID]))*100/( abs(Score[0]) + abs(Score[1]) + abs(Score[2]) + abs(Score[3]) + abs(Score[4]) )<<"%";
					file<<"   His winning probability is : "<<abs(Score[2]-abs(Score[minID]))*100/( abs(Score[0]) + abs(Score[1]) + abs(Score[2]) + abs(Score[3]) + abs(Score[4]) )<<"%"<<endl;
	gotoxy(155,23); cout<<"C's Score is : "<<Score[3];
					file<<"C's Score is : "<<Score[3]<<endl;
	gotoxy(155,24); cout<<"   His winning probability is : "<<abs(Score[3]-abs(Score[minID]))*100/( abs(Score[0]) + abs(Score[1]) + abs(Score[2]) + abs(Score[3]) + abs(Score[4]) )<<"%";
					file<<"   His winning probability is : "<<abs(Score[3]-abs(Score[minID]))*100/( abs(Score[0]) + abs(Score[1]) + abs(Score[2]) + abs(Score[3]) + abs(Score[4]) )<<"%"<<endl;
	gotoxy(155,25); cout<<"D's Score is : "<<Score[4];
					file<<"D's Score is : "<<Score[4]<<endl;
	gotoxy(155,26); cout<<"   His winning probability is : "<<abs(Score[4]-abs(Score[minID]))*100/( abs(Score[0]) + abs(Score[1]) + abs(Score[2]) + abs(Score[3]) + abs(Score[4]) )<<"%";
					file<<"   His winning probability is : "<<abs(Score[4]-abs(Score[minID]))*100/( abs(Score[0]) + abs(Score[1]) + abs(Score[2]) + abs(Score[3]) + abs(Score[4]) )<<"%"<<endl<<endl<<endl<<endl<<endl;

	Sleep(2*SleepValue);
}


int main()
{
srand(time(NULL));

//File to input
ofstream file;
file.open("Log.txt", ios::app);




vector <double> Score={0, 0, 0, 0, 0};

int Round_Count;
cout<<"Enter the number of rounds :";
cin>>Round_Count;
system("cls");

for(int i=0;i<Round_Count;i++)
{
	
file<<"\t\t\tRound : "<<i<<endl<<endl;	
	
//Iitialize the card pack
vector <Card> Card_Pack;
initialize_card_pack(Card_Pack);

//Shufflling cards and remove first
Shuffle(Card_Pack);

//Give cards to 4 players + dealer
vector <Player> Players;
Give_Cards_to_Players(Card_Pack, Players);

//Adding confidence levels to each player
Value_Of_Player_card_set_and_confidence_precentage_is_calculated(Players);

//Deciding withdraw or not
Decision(Players);

//Calculating scores
score_calculate(Players, Score);

}


double maxScore=Score[0];
int ID=0;
for(int i=1;i<5;i++)
{
	if(Score[i]>maxScore)
	{
		maxScore=Score[i];
		ID=i;
	}
}

gotoxy(155,29); cout<<"The winner is ";
if(ID==0) {cout<<"The dealer is the winner";}
else if(ID==1) {cout<<"The A is the winner";}
else if(ID==2) {cout<<"The B is the winner";}
else if(ID==3) {cout<<"The C is the winner";}
else if(ID==4) {cout<<"The D is the winner";}






gotoxy(0,40);
return 0;
}
