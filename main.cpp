#include "lazy.hpp"

int main(int, char **)
{
    range(1, 10)
        .filter<int>([](int x) -> bool
                     {
                         return (x % 2) == 0;
                     })
        .map<int, int>([](int x) -> int
                       {
                           return x * x;
                       })
        .for_each([](int x)
                  {
                      printf("%i\n", x);
                  });

    return 0;
}
