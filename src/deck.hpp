#pragma once

#include <array>
#include <random>
#include <vector>

#include "playing_card.hpp"

class Deck
{
 private:
  static constexpr int NUM_OF_CARDS = PlayingCard::NUM_OF_SUITS * PlayingCard::NUM_OF_NUMBERS;
  std::vector<PlayingCard> m_playing_cards;
  std::random_device m_dev;
  std::mt19937 m_rng;

 public:
  Deck() : m_playing_cards(), m_dev(), m_rng(m_dev()) { reset(); }

  void reset()
  {
    m_playing_cards.clear();
    m_playing_cards.reserve(NUM_OF_CARDS);

    const std::array<PlayingCard::Suit, PlayingCard::NUM_OF_SUITS> suit_array = {
        {PlayingCard::Suit::SPADE, PlayingCard::Suit::CLUB, PlayingCard::Suit::HEART,
         PlayingCard::Suit::DIAMOND}};

    for (int number = PlayingCard::MIN_NUMBER; number <= PlayingCard::MAX_NUMBER; ++number)
    {
      for (const auto suit : suit_array)
      {
        m_playing_cards.push_back(PlayingCard(suit, number));
      }
    }
  }

  void print()
  {
    for (const auto& playing_card : m_playing_cards)
    {
      playing_card.print();
    }
  }

  PlayingCard pickParticularCard(const PlayingCard::Suit suit, const int number)
  {
    if (m_playing_cards.empty())
    {
      throw std::runtime_error("deck is empty");
    }

    if (!(PlayingCard::MIN_NUMBER <= number && number <= PlayingCard::MAX_NUMBER))
    {
      throw std::runtime_error("invalid number of PlayingCards");
    }

    for (auto itr = m_playing_cards.begin(); itr != m_playing_cards.end(); ++itr)
    {
      if (itr->getSuit() == suit && itr->getNumber() == number)
      {
        PlayingCard card = *itr;
        m_playing_cards.erase(itr);
        return card;
      }
    }

    throw std::runtime_error("invalid card was specified");
  }

  PlayingCard pickRandomCard()
  {
    if (m_playing_cards.empty())
    {
      throw std::runtime_error("deck is empty");
    }

    std::uniform_int_distribution<std::mt19937::result_type> dist(0, m_playing_cards.size() - 1);

    const int index = dist(m_rng);
    auto itr = m_playing_cards.begin() + index;
    PlayingCard card = *itr;
    m_playing_cards.erase(itr);
    return card;
  }

  std::vector<PlayingCard> getDeck() const { return m_playing_cards; }
};
