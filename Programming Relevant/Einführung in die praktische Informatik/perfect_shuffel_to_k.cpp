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

//8.2
std::vector<int> shuffle_top_to(std::vector<int> deck, uint8_t k)
{
    for(int i = 0; i < 8; i++)
    {
        if(k & (1 << i))
        {
            inshuffle(deck);
            break;
        }
        else
        {
            outshuffle(deck);
        }
    }
    return deck;
}

int main()
{
    std::vector<int> deck = init_deck();
	
	
	return 0;
}
