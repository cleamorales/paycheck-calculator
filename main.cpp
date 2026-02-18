#include <iostream>
#include "Payroll.h"

using namespace std;

int main()
{
    double hours;
    double rate;

    cout << "===== MY PAYCHECK CALCULATOR =====\n\n";

    cout << "Enter hours worked: ";
    cin >> hours;

    cout << "Enter hourly pay rate: ";
    cin >> rate;

    double gross = Payroll::calculateGross(hours, rate);
    double tax = Payroll::calculateTax(gross);
    double net = Payroll::calculateNet(gross);

    cout << "\n------ PAYCHECK ------\n";
    cout << "Hours Worked: " << hours << endl;
    cout << "Hourly Rate: $" << rate << endl;
    cout << "Gross Pay: $" << gross << endl;
    cout << "Tax (15%): $" << tax << endl;
    cout << "Net Pay: $" << net << endl;

    return 0;
}
