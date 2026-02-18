#ifndef PAYROLL_H
#define PAYROLL_H

class Payroll
{
public:
    static double calculateGross(double hours, double rate);
    static double calculateTax(double gross);
    static double calculateNet(double gross);
};

#endif
