#include <iostream>

using namespace std;

int* foo(int x) {
   int *p = new int;
  *p = x*x;
   return p;
}

int main()
{
    cout << foo(3);
}
