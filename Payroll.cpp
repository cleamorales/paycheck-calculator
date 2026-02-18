#include "Payroll.h"

// overtime after 40 hours
double Payroll::calculateGross(double hours, double rate)
{
    if (hours <= 40)
        return hours * rate;
    else
    {
        double overtime = hours - 40;
        return (40 * rate) + (overtime * rate * 1.5);
    }
}

double Payroll::calculateTax(double gross)
{
    return gross * 0.15; // 15% tax
}

double Payroll::calculateNet(double gross)
{
    return gross - calculateTax(gross);
}

