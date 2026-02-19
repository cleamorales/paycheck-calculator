#include "Payroll.h"

// hourly earnings
double Payroll::calculateHourlyPay(double hours)
{
    return hours * 2.13;
}

// 8% tipout from sales
double Payroll::calculateTipout(double sales)
{
    return sales * 0.08;
}

// tips after tipout deduction
double Payroll::calculateFinalTips(double tips, double sales)
{
    double tipout = calculateTipout(sales);
    return tips - tipout;
}

// total earnings before tax
double Payroll::calculateGross(double hourlyPay, double finalTips)
{
    return hourlyPay + finalTips;
}

// simple 15% tax
double Payroll::calculateTax(double gross)
{
    return gross * 0.15;
}

double Payroll::calculateNet(double gross)
{
    return gross - calculateTax(gross);
}
