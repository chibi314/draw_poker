#pragma once

#include <array>
#include <memory>

#include "deck.hpp"
#include "playing_card.hpp"
#include "hand.hpp"

// Double Double Bonus Poker
class DDBPGame
{
 private:
  std::shared_ptr<PlayerHand> m_player_hand_ptr;
  Deck m_deck;
  std::array<bool, 5> m_hold_card_flag;

 public:
  DDBPGame() : m_player_hand_ptr(), m_deck(), m_hold_card_flag() {}

  Deck getDeck() const { return m_deck; }

  void dealFirstRandom()
  {
    m_player_hand_ptr = std::make_shared<PlayerHand>(
        PlayerHand({{m_deck.pickRandomCard(), m_deck.pickRandomCard(), m_deck.pickRandomCard(),
                     m_deck.pickRandomCard(), m_deck.pickRandomCard()}}));
  }

  void dealFirst(PlayerHand player_hand)
  {
    m_deck.reset();
    m_player_hand_ptr =
        std::make_shared<PlayerHand>(PlayerHand({{m_deck.pickParticularCard(player_hand.at(0)),
                                                  m_deck.pickParticularCard(player_hand.at(1)),
                                                  m_deck.pickParticularCard(player_hand.at(2)),
                                                  m_deck.pickParticularCard(player_hand.at(3)),
                                                  m_deck.pickParticularCard(player_hand.at(4))}}));
  }

  void selectHoldCardInteractive()
  {
    for (int i = 0; i < 5; ++i)
    {
      std::cout << "hold?" << std::endl;
      char c;
      std::cin >> c;
      if (c == 'y')
      {
        m_hold_card_flag.at(i) = true;
      }
      else
      {
        m_hold_card_flag.at(i) = false;
      }
    }
    std::cout << std::endl;
  }

  void selectHoldCard(std::array<bool, 5> hold_card_flag) { m_hold_card_flag = hold_card_flag; }

  void dealSecondRandom()
  {
    // true = hold
    for (int i = 0; i < 5; ++i)
    {
      if (!m_hold_card_flag.at(i))
      {
        auto new_card = m_deck.pickRandomCard();
        m_player_hand_ptr->at(i) = new_card;
      }
    }
  }

  static int convertHandToPoint(const Hand::HandType hand_type, const int number1, const int number2)
  {
    switch (hand_type)
    {
      case Hand::HandType::ROYAL_FLUSH:
        return 250;
      case Hand::HandType::STRAIGHT_FLUSH:
        return 50;
      case Hand::HandType::FOUR_OF_A_KIND:
        if (number1 == 14)
        {
          if (2 <= number2 && number2 <= 4)
          {
            return 400;
          }
          else
          {
            return 160;
          }
        }
        else if (2 <= number1 && number1 <= 4)
        {
          if (number2 == 2 || number2 == 3 || number2 == 4 || number2 == 14)
          {
            return 160;
          }
          else
          {
            return 80;
          }
        }
        else
        {
          return 50;
        }
      case Hand::HandType::FULL_HOUSE:
        return 7;
      case Hand::HandType::FLUSH:
        return 5;
      case Hand::HandType::STRAIGHT:
        return 4;
      case Hand::HandType::THREE_OF_A_KIND:
        return 3;
      case Hand::HandType::TWO_PAIR:
        return 1;
      case Hand::HandType::ONE_PAIR:
        if (number1 >= 11)
        {
          return 1;
        }
        else
        {
          return 0;
        }
      case Hand::HandType::HIGH_CARD:
        return 0;
      default:
        return 0;
    }
  }

  int calcPoint() const
  {
    int number1 = 0, number2 = 0;
    const auto hand_type = Hand::getHand(*m_player_hand_ptr, number1, number2);

    return convertHandToPoint(hand_type, number1, number2);
  }

  void printPlayerHand() const
  {
    for (const auto& card : *m_player_hand_ptr)
    {
      card.print();
    }
    std::cout << std::endl;
  }

  void playInteractive()
  {
    m_deck.reset();
    dealFirstRandom();
    printPlayerHand();
    selectHoldCardInteractive();
    dealSecondRandom();
    printPlayerHand();
    int point = calcPoint();
    std::cout << "point: " << point << std::endl;
  }
};
