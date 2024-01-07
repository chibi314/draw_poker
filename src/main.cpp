#include <iostream>

#include "playing_card.hpp"
#include "deck.hpp"

int main()
{
    Deck deck;
    auto card = deck.pickParticularCard(PlayingCard::Suit::HEART, 10);
    card.print();
    deck.print();

    auto card2 = deck.pickParticularCard(PlayingCard::Suit::HEART, 11);
    card2.print();
    deck.print();

    return 0;
}
