#pragma once

#include <algorithm>
#include <array>
#include <string>

#include "playing_card.hpp"

class Hand
{
 public:
  Hand() = delete;
  ~Hand() = delete;

  enum class HandType
  {
    ROYAL_FLUSH,
    STRAIGHT_FLUSH,
    FOUR_OF_A_KIND,
    FULL_HOUSE,
    FLUSH,
    STRAIGHT,
    THREE_OF_A_KIND,
    TWO_PAIR,
    ONE_PAIR,
    HIGH_CARD,
  };

  static bool isStraight(const std::array<PlayingCard, 5>& player_hand_sorted)
  {
    if (player_hand_sorted.at(0).getNumber() == 2 && player_hand_sorted.at(1).getNumber() == 3 &&
        player_hand_sorted.at(2).getNumber() == 4 && player_hand_sorted.at(3).getNumber() == 5 &&
        player_hand_sorted.at(4).getNumber() == 14)
    {
      // exception: wheel
      return true;
    }
    else
    {
      for (int i = 0; i < 4; ++i)
      {
        if ((player_hand_sorted.at(i + 1).getNumber() - player_hand_sorted.at(i).getNumber()) != 1)
        {
          return false;
        }
      }
      return true;
    }
  }

  static bool isFlush(const std::array<PlayingCard, 5>& player_hand_sorted)
  {
    const auto first_card_suit = player_hand_sorted.at(0).getSuit();

    for (const auto& card : player_hand_sorted)
    {
      if (first_card_suit != card.getSuit())
      {
        return false;
      }
    }
    return true;
  }

  static HandType getPairHandType(const std::array<PlayingCard, 5>& player_hand_sorted,
                                  int& number1, int& number2)
  {
    const int diff1 = player_hand_sorted.at(1).getNumber() - player_hand_sorted.at(0).getNumber();
    const int diff2 = player_hand_sorted.at(2).getNumber() - player_hand_sorted.at(1).getNumber();
    const int diff3 = player_hand_sorted.at(3).getNumber() - player_hand_sorted.at(2).getNumber();
    const int diff4 = player_hand_sorted.at(4).getNumber() - player_hand_sorted.at(3).getNumber();

    if (diff1 == 0 && diff2 == 0 && diff3 == 0)
    {
      number1 = player_hand_sorted.at(0).getNumber();
      number2 = player_hand_sorted.at(4).getNumber();
      return HandType::FOUR_OF_A_KIND;
    }
    else if (diff2 == 0 && diff3 == 0 && diff4 == 0)
    {
      number2 = player_hand_sorted.at(0).getNumber();
      number1 = player_hand_sorted.at(4).getNumber();
      return HandType::FOUR_OF_A_KIND;
    }
    else if ((diff1 == 0 && diff2 == 0 && diff4 == 0) ||  //
             (diff1 == 0 && diff3 == 0 && diff4 == 0))
    {
      return HandType::FULL_HOUSE;
    }
    else if ((diff1 == 0 && diff2 == 0) ||  //
             (diff2 == 0 && diff3 == 0) ||  //
             (diff3 == 0 && diff4 == 0))
    {
      return HandType::THREE_OF_A_KIND;
    }
    else if ((diff1 == 0 && diff3 == 0) ||  //
             (diff1 == 0 && diff4 == 0) ||  //
             (diff2 == 0 && diff4 == 0))
    {
      return HandType::TWO_PAIR;
    }
    else if (diff1 == 0)
    {
        number1 = player_hand_sorted.at(0).getNumber();
      return HandType::ONE_PAIR;
    }
    else if (diff2 == 0)
    {
      number1 = player_hand_sorted.at(1).getNumber();
      return HandType::ONE_PAIR;
    }
    else if (diff3 == 0)
    {
      number1 = player_hand_sorted.at(2).getNumber();
      return HandType::ONE_PAIR;
    }
    else if (diff4 == 0)
    {
      number1 = player_hand_sorted.at(3).getNumber();
      return HandType::ONE_PAIR;
    }
    else
    {
      return HandType::HIGH_CARD;
    }
  }

    static HandType getHand(const std::array<PlayingCard, 5>& player_hand, int& number1, int& number2)
  {
    auto player_hand_sorted = player_hand;
    std::sort(player_hand_sorted.begin(), player_hand_sorted.end());

    const bool is_flush = isFlush(player_hand_sorted);
    const bool is_straight = isStraight(player_hand_sorted);
    const HandType pair_hand_type = getPairHandType(player_hand_sorted, number1, number2);

    if (is_flush && is_straight)
    {
      if (player_hand_sorted.at(4).getNumber() == 14 &&  //
          player_hand_sorted.at(3).getNumber() == 13)
      {
        return HandType::ROYAL_FLUSH;
      }
      else
      {
        return HandType::STRAIGHT_FLUSH;
      }
    }

    if (pair_hand_type == HandType::FOUR_OF_A_KIND)
    {
      return HandType::FOUR_OF_A_KIND;
    }
    if (pair_hand_type == HandType::FULL_HOUSE)
    {
      return HandType::FULL_HOUSE;
    }
    if (is_flush)
    {
      return HandType::FLUSH;
    }
    if (is_straight)
    {
      return HandType::STRAIGHT;
    }
    return pair_hand_type;
  }

  static std::string convertHandTypeToString(const HandType hand_type)
  {
    switch (hand_type)
    {
      case HandType::ROYAL_FLUSH:
        return "Royal Flush";
      case HandType::STRAIGHT_FLUSH:
        return "Straight FLush";
      case HandType::FOUR_OF_A_KIND:
        return "Four Of A Kind";
      case HandType::FULL_HOUSE:
        return "Full House";
      case HandType::FLUSH:
        return "Flush";
      case HandType::STRAIGHT:
        return "Straight";
      case HandType::THREE_OF_A_KIND:
        return "Three Of A Kind";
      case HandType::TWO_PAIR:
        return "Two Pair";
      case HandType::ONE_PAIR:
        return "One Pair";
      case HandType::HIGH_CARD:
        return "High Card";
    default:
        return "Unknown";
    }
  }
};
