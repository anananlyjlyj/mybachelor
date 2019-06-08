#include <vector>
#include <iostream>
#include <cassert>

std::vector <int> init_deck()
{
	std::vector <int> deck(52);
	for(int i = 0; i < 52; i++)
	{
		deck[i] = i;
	}
	return deck;
}
bool check_deck(std::vector <int> cards)
{
	for(int i = 0; i < cards.size() - 1; i++)
	{
		if(cards[i + 1] <= cards [i])				//Ausagangszustand: cards bleiben aufsteigend sortiert
		{
			return false;
		}
	}
	return true;
}

std::vector<int> shuffle(std::vector<int> cards, bool out)
{
    std::vector <int> shufflecards;
	int s = cards.size() / 2;							//die zweite Teil der Karten
	int	j = (out)? 0 : s;
	int	k = (out)? s : 0;
	for(int i = 0; i < s; i++, j++, k++)
	{
		shufflecards.push_back(cards[j]);				//out: oberste Karte bleibt oben	in: mittelere Karte nach oben
		shufflecards.push_back(cards[k]);
	}
	return shufflecards;
}

int outshuffle(std::vector <int> cards)
{
	int z = 0;
	while(!check_deck(cards))
	{
	    z++;
	    cards = shuffle(cards, 1);
	}
	return z;
}
int inshuffle(std::vector <int> cards)
{
	int z = 0;
	while(!check_deck(cards))
	{
	    z++;
	    cards = shuffle(cards, 0);
	}
	return z;
}


int main()
{
	assert(check_deck(init_deck()));
	for(int i = 0; i < init_deck().size(); i++)
	{
		std::cout << init_deck()[i]<<" ";
	}
	
	std::cout<<std::endl;
	std::vector <int> misch = shuffle(init_deck(), 1);
	for(int i = 0; i < misch.size(); i++)
	{
		std::cout << misch[i]<<" ";
	}
	std::cout <<"\nUm wieder in den Ausagangszustand zu gelangen, sollte man "<< outshuffle(misch)<<" Mal Perfect_Out_Shuffle verwenden. \n";
	
	std::vector <int> misch2 = shuffle(init_deck(), 0);
	for(int i = 0; i < misch2.size(); i++)
	{
		std::cout << misch2[i]<<" ";
	}
	std::cout <<"\nUm wieder in den Ausagangszustand zu gelangen, sollte man "<< inshuffle(misch2)<<" Mal Perfect_In_Shuffle verwenden. \n";
	
	return 0;
}
