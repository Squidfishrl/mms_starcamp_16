#include <stdio.h>

#define PI 3.14159265358979323846	

int sinus(double angle, double *res, int precision);  // uses tailor series
int factorial(int num);
double power(double num, int amount);

int main (int argc, char *argv[])
{
        double res;

        sinus(23, &res, 4);
        printf("%.5lf\n", res);  // 0.39073
        return 0;
}

int sinus(double angle, double *res, int precision)
{
        double radians = (angle / 180) * PI; 
        *res = 0;

        for (int i = 0, next_power = 1; i < precision; i++, next_power += 2) {
                double temp_calc = power(radians, next_power) / factorial(next_power);
                *res += i % 2 ? -temp_calc : temp_calc;
        }

        return 0;
}

int factorial(int num)
{
        int res = num;
        while (num > 2) {
                res *= --num;
        }
        return res;
}

double power(double num, int amount)
{
        double res = num;

        if  (0 == amount)
                return 1;
        else if (1 == amount)
                return res;

        for (int i = 1; i < amount; i++) {
                res *= num;
        }

        return res;
}
