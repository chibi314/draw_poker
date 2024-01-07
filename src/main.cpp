#include <iostream>
#include <array>

#include "playing_card.hpp"
#include "deck.hpp"
#include "hand.hpp"

int main()
{
  Deck deck;
  auto card1 = deck.pickParticularCard(PlayingCard::Suit::SPADE, 10);
  auto card2 = deck.pickParticularCard(PlayingCard::Suit::HEART, 14);
  auto card3 = deck.pickParticularCard(PlayingCard::Suit::CLUB, 10);
  auto card4 = deck.pickParticularCard(PlayingCard::Suit::DIAMOND, 14);
  auto card5 = deck.pickParticularCard(PlayingCard::Suit::HEART, 10);

  // auto card1 = deck.pickRandomCard();
  // auto card2 = deck.pickRandomCard();
  // auto card3 = deck.pickRandomCard();
  // auto card4 = deck.pickRandomCard();
  // auto card5 = deck.pickRandomCard();

  std::array<PlayingCard, 5> player_hand = {{card1, card2, card3, card4, card5}};
  std::cout << "Hand" << std::endl;
  for (const auto& card : player_hand)
  {
    card.print();
  }
  std::cout << std::endl;

  int number1, number2;
  std::cout << Hand::convertHandTypeToString(Hand::getHand(player_hand, number1, number2))
            << std::endl;
  std::cout << number1 << " " << number2 << std::endl;
  return 0;
}
