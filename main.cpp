#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <ctime>
#include <sqlite3.h>
#include "Payroll.h"

using namespace std;

string getCurrentDateTime()
{
    time_t now = time(0);
    tm* localTime = localtime(&now);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%b %d %Y - %I:%M %p", localTime);

    return string(buffer);
}

string getNumericDate()
{
    time_t now = time(0);
    tm* localTime = localtime(&now);

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);

    return string(buffer);
}

void viewHistory()
{
    ifstream file("paychecks.txt");

    if (!file)
    {
        cout << "\nNo shift history found yet.\n";
        return;
    }

    cout << "\nShift history:\n";

    string line;
    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}

void addShift()
{
    double hours, rate, tips, sales;

    cout << "\nEnter hours worked: ";
    cin >> hours;

    cout << "Enter hourly pay rate: ";
    cin >> rate;

    cout << "Enter tips earned: ";
    cin >> tips;

    cout << "Enter total sales: ";
    cin >> sales;

    double hourlyPay = Payroll::calculateHourlyPay(hours);
    double tipout = Payroll::calculateTipout(sales);
    double finalTips = Payroll::calculateFinalTips(tips, sales);

    double gross = Payroll::calculateGross(hourlyPay, finalTips);
    double tax = Payroll::calculateTax(gross);
    double net = Payroll::calculateNet(gross);

    cout << fixed << setprecision(2);

    cout << "\nShift Date: " << getCurrentDateTime() << endl;
    cout << "\n------ PAYCHECK ------\n";
    cout << "Hours Worked: " << hours << endl;
    cout << "Hourly Pay: $" << hourlyPay << endl;
    cout << "Tips Earned: $" << tips << endl;
    cout << "Tipout (8%): -$" << tipout << endl;
    cout << "Tips After Tipout: $" << finalTips << endl;
    cout << "Gross Pay: $" << gross << endl;
    cout << "Tax (15%): $" << tax << endl;
    cout << "Take Home Pay: $" << net << endl;

    ofstream file("paychecks.txt", ios::app);

    if (file.is_open())
    {
        file << fixed << setprecision(2);
        file << "=============================\n";
        file << "Date: " << getNumericDate() << endl;
        file << "Shift: " << getCurrentDateTime() << endl;
        file << "-----------------------------\n";
        file << "Hours Worked: " << hours << endl;
        file << "Hourly Pay: $" << hourlyPay << endl;
        file << "Tips Earned: $" << tips << endl;
        file << "Tipout: -$" << tipout << endl;
        file << "Tips After Tipout: $" << finalTips << endl;
        file << "Gross Pay: $" << gross << endl;
        file << "Tax: $" << tax << endl;
        file << "Take Home: $" << net << endl;
        file << "=============================\n\n";

        file.close();
        cout << "\nShift saved!\n";
    }
}

void biweeklyEarnings()
{
    string startDate, endDate;

    cout << "\nEnter start date (YYYY-MM-DD): ";
    cin >> startDate;

    cout << "Enter end date (YYYY-MM-DD): ";
    cin >> endDate;

    ifstream file("paychecks.txt");

    if (!file)
    {
        cout << "No shift history found.\n";
        return;
    }

    string line;
    string currentDate = "";
    double total = 0.0;

    while (getline(file, line))
    {
        // capture date
        if (line.find("Date:") != string::npos)
        {
            currentDate = line.substr(6); // skip "Date: "
        }

        // find paycheck amount
        if (line.find("Take Home:") != string::npos)
        {
            if (currentDate >= startDate && currentDate <= endDate)
            {
                size_t pos = line.find("$");
                double amount = stod(line.substr(pos + 1));
                total += amount;
            }
        }
    }

    file.close();

    cout << fixed << setprecision(2);
    cout << "\n====== BIWEEKLY PAY ======\n";
    cout << "Total earnings: $" << total << endl;
}

void paycheckGoal()
{
    double goal, hours, rate, expectedSales;

    cout << "\nEnter desired paycheck amount: ";
    cin >> goal;

    cout << "How many hours do you expect to work this pay period? ";
    cin >> hours;


    cout << "Estimated total sales: ";
    cin >> expectedSales;

    double hourlyPay = hours * rate;
    double tipout = expectedSales * 0.08;

    // reverse tax (since paycheck is after tax)
    double neededGross = goal / 0.85;

    double tipsNeeded = neededGross - hourlyPay + tipout;

    cout << fixed << setprecision(2);
    cout << "\n====== PAYCHECK GOAL ======\n";
    cout << "You need about $" << tipsNeeded << " in tips.\n";

    double avgPerShift = tipsNeeded / (hours / 5.0);
    cout << "Approx tips per shift: $" << avgPerShift << endl;
}

sqlite3* db;

void initDatabase()
{
    int rc = sqlite3_open("paycheck.db", &db);

    if (rc)
    {
        cout << "Cannot open database\n";
    }
    else
    {
        cout << "Database opened successfully\n";
    }

    const char* sql =
        "CREATE TABLE IF NOT EXISTS shifts ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "date TEXT,"
        "hours REAL,"
        "sales REAL,"
        "tips REAL"
        ");";

    char* errMsg = 0;

    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

    if (rc != SQLITE_OK)
    {
        cout << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

int main()
{
    initDatabase();
    int choice;

    while (true)
    {
        cout << "\n===== PAYCHECK TRACKER =====\n";
        cout << "1) Add new shift\n";
        cout << "2) View shift history\n";
        cout << "3) Biweekly earnings\n";
        cout << "4) Paycheck goal calculator\n";
        cout << "5) Exit\n";
        cout << "Choose: ";

        // ACTUALLY READ USER INPUT
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
            case 1:
                addShift();
                break;

            case 2:
                viewHistory();
                break;

            case 3:
                biweeklyEarnings();
                break;

            case 4:
                paycheckGoal();
                break;

            case 5:
                cout << "Goodbye!\n";
                return 0;

            default:
                cout << "Invalid option. Try again.\n";
        }
    }
}
