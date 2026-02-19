#ifndef PAYROLL_H
#define PAYROLL_H

class Payroll
{
public:
    static double calculateHourlyPay(double hours);
    static double calculateTipout(double sales);
    static double calculateFinalTips(double tips, double sales);
    static double calculateGross(double hourlyPay, double finalTips);
    static double calculateTax(double gross);
    static double calculateNet(double gross);
};

#endif
