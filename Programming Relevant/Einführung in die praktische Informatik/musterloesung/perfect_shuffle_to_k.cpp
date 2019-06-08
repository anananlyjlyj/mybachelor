#include <algorithm>
#include <cassert>
#include <cinttypes>
#include <numeric>
#include <vector>


std::vector<int> init_deck(size_t size=52)
{
    std::vector<int> deck(size);
    std::iota(deck.begin(), deck.end(), 0);

    return deck;
}


bool check_deck(const std::vector<int>& deck)
{
    for(int i = 0; i < 52; ++i)
    {
        if(i != deck[i])
        {
            return false;
        }
    }
    return true;
}


std::vector<int> shuffle(std::vector<int> cards, bool out=false)
{
    std::vector<int> shuffled;

    int size_half = cards.size() / 2;
    int offset1, offset2;

    if(out)
    {
        offset1 = 0;
        offset2 = size_half;
    }
    else
    {
        offset1 = size_half;
        offset2 = 0;
    }

    for(int i = 0; i < size_half; ++i)
    {
        shuffled.push_back(cards[offset1 + i]);
        shuffled.push_back(cards[offset2 + i]);
    }

    return shuffled;
}


std::vector<int> shuffle_top_to(std::vector<int> deck, uint8_t k)
{
    if(k == 0) // nothing to do
    {
        return deck;
    }

    uint8_t mask = 0b10000000;

    // ignore leading 0's
    while(!(k & mask))
    {
        mask >>= 1;
    }

    while(mask)
    {
        deck = shuffle(deck, !(k & mask)); // if bit is 1 do in-shuffle
        mask >>= 1;
    }

    return deck;
}


// less code but more unnecessary shuffling
std::vector<int> shuffle_top_to_short(std::vector<int> deck, uint8_t k)
{
    for(uint8_t mask = 0b10000000; mask != 0; mask >>= 1)
    {
        deck = shuffle(deck, !(k & mask));
    }

    return deck;
}

int main()
{
    for(uint8_t k = 0; k < 52; ++k)
    {
        std::vector<int> deck = init_deck();
        deck = shuffle_top_to(deck, k);
        assert(deck[k] == 0);

        // check that all other cards are still present
        std::sort(deck.begin(), deck.end());
        assert(check_deck(deck));

        // short version
        deck = init_deck();
        deck = shuffle_top_to_short(deck, k);
        assert(deck[k] == 0);

        // check that all other cards are still present
        std::sort(deck.begin(), deck.end());
        assert(check_deck(deck));
    }
}