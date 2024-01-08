#pragma once

#include <iomanip>

#include "ddbp_game.hpp"
#include "deck.hpp"

class Solver
{
 public:
  Solver() = delete;
  ~Solver() = delete;

  static int calcPoint(const PlayerHand& player_hand)
  {
    int number1 = 0, number2 = 0;
    const auto hand_type = Hand::getHand(player_hand, number1, number2);
    return DDBPGame::convertHandToPoint(hand_type, number1, number2);
  }

  static void printArray(const std::array<int, 5> arr)
  {
    for (const auto& i : arr)
    {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  }

  static int calcPointSumRecursive(const int& depth, const PlayerHand& player_hand,
                                   const std::array<bool, 5>& hold_flag, const Deck& deck,
                                   int& count_total)
  {
    if (depth == -1)
    {
      ++count_total;
      return calcPoint(player_hand);
    }
    else
    {
      const bool& hold_flag_this_depth = hold_flag.at(depth);
      if (hold_flag_this_depth)
      {
        return calcPointSumRecursive(depth - 1, player_hand, hold_flag, deck, count_total);
      }
      else
      {
        int point_sum = 0;
        const int deck_size = deck.getDeckSize();
        for (int i = 0; i < deck_size; ++i)
        {
          auto deck_copy = deck;
          auto player_hand_copy = player_hand;
          player_hand_copy.at(depth) = deck_copy.pickCardByIndexAndEraseFromBeginToIndex(i);
          point_sum +=
              calcPointSumRecursive(depth - 1, player_hand_copy, hold_flag, deck_copy, count_total);
        }
        return point_sum;
      }
    }
  }

  static double calcEV(const PlayerHand player_hand, const std::array<bool, 5> hold_flag,
                       const Deck deck)
  {
    int count_total = 0;
    int point_sum = calcPointSumRecursive(4, player_hand, hold_flag, deck, count_total);
    return static_cast<double>(point_sum) / count_total;
  }

  static void printResult(const double ev, const std::array<bool, 5> hold_flag)
  {
    std::cout << "EV: " << ev << std::endl;
    std::cout << "Action: " << std::boolalpha;
    for (int i = 0; i < 5; ++i)
    {
      std::cout << hold_flag.at(i) << " ";
    }
    std::cout << std::noboolalpha << std::endl;
  }

  static void printPlayerHand(const PlayerHand& player_hand)
  {
    for (const auto& card : player_hand)
    {
      card.print();
    }
    std::cout << std::endl;
  }

  static double searchBestAction(const PlayerHand& player_hand, const Deck& deck)
  {
    double best_ev = 0;
    std::array<bool, 5> best_hold_flag;
    int index[5];

    for (index[0] = 0; index[0] <= 1; ++index[0])
    {
      for (index[1] = 0; index[1] <= 1; ++index[1])
      {
        for (index[2] = 0; index[2] <= 1; ++index[2])
        {
          for (index[3] = 0; index[3] <= 1; ++index[3])
          {
            for (index[4] = 0; index[4] <= 1; ++index[4])
            {
              std::array<bool, 5> hold_flag;
              for (int i = 0; i < 5; ++i)
              {
                hold_flag.at(i) = static_cast<bool>(index[i]);
              }
              const double ev = calcEV(player_hand, hold_flag, deck);
              if (ev > best_ev)
              {
                best_ev = ev;
                best_hold_flag = hold_flag;
              }
              // printResult(ev, hold_flag);
            }
          }
        }
      }
    }

    // std::cout << "Best" << std::endl;
    // printResult(best_ev, best_hold_flag);
    return best_ev;
  }

  static double calcOneHandBestEv(const PlayerHand& player_hand)
  {
    Deck deck;
    for (const auto& card : player_hand)
    {
      deck.pickParticularCard(card);
    }

    // std::cout << "Hand" << std::endl;
    // printPlayerHand(player_hand);

    return searchBestAction(player_hand, deck);
  }

  static void printProgress(const int& count_total, const int& first_card_index)
  {
    const int num_of_deck = 52 - first_card_index - 1;
    const int num_total_pattern =
        num_of_deck * (num_of_deck - 1) * (num_of_deck - 2) * (num_of_deck - 3) / 24;
    std::cout << "Progress: " << count_total << "/" << num_total_pattern << std::endl;
  }

  static double calcSumEvRecursive(const int& depth, const PlayerHand& player_hand,
                                   const Deck& deck, int& count_total, const int& first_card_index)
  {
    if (depth == -1)
    {
      ++count_total;

      if ((count_total & 63) == 0)
      {
        printProgress(count_total, first_card_index);
      }

      return calcOneHandBestEv(player_hand);
    }
    else
    {
      double ev_sum = 0.0;
      const int deck_size = deck.getDeckSize();
      for (int i = 0; i < deck_size; ++i)
      {
        auto deck_copy = deck;
        auto player_hand_copy = player_hand;
        player_hand_copy.at(depth) = deck_copy.pickCardByIndexAndEraseFromBeginToIndex(i);
        ev_sum += calcSumEvRecursive(depth - 1, player_hand_copy, deck_copy, count_total,
                                     first_card_index);
      }
      return ev_sum;
    }
  }

  static void calcEvWithFirstCardIndex(const int index, int& count_total, double& sum_ev)
  {
    Deck deck;
    const PlayingCard tmp_card(PlayingCard::Suit::SPADE, 2);
    // pick just one card from deck
    PlayerHand player_hand = {{
        tmp_card,
        tmp_card,
        tmp_card,
        tmp_card,
        deck.pickCardByIndexAndEraseFromBeginToIndex(index),
    }};

    count_total = 0;
    sum_ev = calcSumEvRecursive(3, player_hand, deck, count_total, index);
  }
};
