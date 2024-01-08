#include <omp.h>
#include <array>
#include <iomanip>
#include <iostream>

#include "ddbp_game.hpp"
#include "deck.hpp"
#include "hand.hpp"
#include "playing_card.hpp"
#include "solver.hpp"

int main()
{
  double sum_sum_ev = 0.0;
  int sum_count_total = 0;

#pragma omp parallel for
  for (int index = 47; index >= 0; --index)
  {
    std::cout << "index: " << index << std::endl;
    int count_total = 0;
    double sum_ev = 0.0;
    Solver::calcEvWithFirstCardIndex(index, count_total, sum_ev);
    std::cout << "count_total: " << count_total << std::endl;
    std::cout << "sum_ev: " << std::setprecision(100) << sum_ev << std::endl;

#pragma omp atomic
    sum_sum_ev += sum_ev;
#pragma omp atomic
    sum_count_total += count_total;
  }

  std::cout << "averaged EV: " << sum_sum_ev / sum_count_total << std::endl;
  return 0;
}
