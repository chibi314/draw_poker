#include <omp.h>
#include <stdio.h>

int main()
{
  printf("使用可能な最大スレッド数：%d\n", omp_get_max_threads());

  int sum = 0;

#pragma omp parallel for
  for (int i = 0; i < 10000; i++)
  {
    printf("thread = %d, i = %2d\n", omp_get_thread_num(), i);
#pragma omp atomic
    sum += i;
  }

  printf("sum: %d\n", sum);
  return 0;
}
