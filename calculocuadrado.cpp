#include <iostream>
double square(double x)
{
    return x*x;
}
void print_square(double x)
{
     std::cout << " el cuadrado de " << x << " es " << square(x) << '\n';
}

int main()
{
    print_square(1.234); // printea que el cuadrado de 1.234 es 1.52276
    print_square(5.555); // printea el cuadrado que es 30.858 
}
