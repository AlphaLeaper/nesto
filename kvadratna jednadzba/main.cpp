#include <iostream>
#include <cmath>

void first_solution( float a, float b, float c )
{
    float main = -b / (2.0f*a);
    float discriminant = b*b - 4.0f*a*c;

    if ( discriminant < 0.0f )
    {
        discriminant = abs( discriminant );
        discriminant = sqrt( discriminant );
        discriminant /= 2.0f*a;
        std::cout << "X1 = " << main << " + i*" << discriminant << "\n";
    }
    else
    {
        discriminant = sqrt( discriminant );
        discriminant /= 2.0f*a;
        std::cout << "X1 = " << main + discriminant << "\n";
    }
    
}

void second_solution( float a, float b, float c )
{
    float main = -b / (2.0f*a);
    float discriminant = b*b - 4.0f*a*c;

    if ( discriminant < 0.0f )
    {
        discriminant = abs( discriminant );
        discriminant = sqrt( discriminant );
        discriminant /= 2.0f*a;
        std::cout << "X2 = " << main << " - i*" << discriminant << "\n";
    }
    else
    {
        discriminant = sqrt( discriminant );
        discriminant /= 2.0f*a;
        std::cout << "X2 = " << main - discriminant << "\n";
    }
}

int main( void )
{
    float a;
    float b;
    float c;

    std::cout << "format: aX^2 + bX + c = 0\n\n";
    std::cout << "input a: ";
    std::cin >> a;
    std::cout << "input b: ";
    std::cin >> b;
    std::cout << "input c: ";
    std::cin >> c;

    first_solution( a, b, c );
    second_solution( a, b, c );
}
