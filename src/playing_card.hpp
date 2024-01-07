#pragma once

#include <iostream>

class PlayingCard
{
 public:
  enum class Suit
  {
    SPADE = 1,
    CLUB = 2,
    HEART = 3,
    DIAMOND = 4,
  };

  static constexpr int NUM_OF_SUITS = 4;
  static constexpr int MIN_NUMBER = 2;
  static constexpr int MAX_NUMBER = 14;  // ace
  static constexpr int NUM_OF_NUMBERS = 13;

 private:
  Suit m_suit;
  int m_number;

 public:
  PlayingCard(const Suit suit, const int number) : m_suit(suit), m_number(number)
  {
    if (!(MIN_NUMBER <= m_number && m_number <= MAX_NUMBER))
    {
      throw std::runtime_error("invalid number of PlayingCards");
    }
  }

  Suit getSuit() const { return m_suit; }

  int getNumber() const { return m_number; }

  void print() const
  {
    switch (getSuit())
    {
      case PlayingCard::Suit::SPADE:
        std::cout << "\033[30m S\033[0m";
        break;
      case PlayingCard::Suit::CLUB:
        std::cout << "\033[32m C\033[0m";
        break;
      case PlayingCard::Suit::HEART:
        std::cout << "\033[31m H\033[0m";
        break;
      case PlayingCard::Suit::DIAMOND:
        std::cout << "\033[36m D\033[0m";
        break;
    }

    std::cout << getNumber();
  }

  bool operator<(const PlayingCard& card) const
  {
    if (getNumber() != card.getNumber())
    {
      return getNumber() < card.getNumber();
    }
    else
    {
      return static_cast<int>(getSuit()) < static_cast<int>(card.getSuit());
    }
  }
};

using PlayerHand = std::array<PlayingCard, 5>;
