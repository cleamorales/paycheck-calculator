# Paycheck Calculator (C++ + SQLite)

A payroll management system built in C++ with SQLite database integration.
I built this application to help me calculte and anticipate my paychchecks as a part time waitress who gets paid biweekly. 
This program tracks work shifts, calculates biweekly earnings, projects paycheck goals, and exports data to a CSV file for reporting and analysis.

## Features

- Add and store work shifts in a SQLite database
- Automatic pay period detection (Monday–Sunday cycles)
- Automated next payday calculation
- Gross pay, tax, and net pay calculation
- Paycheck goal projection within the current pay period
- CSV export for financial reporting and spreadsheet analysis

## Tech Stack

- **Language:** C++
- **Database:** SQLite3
- **Concepts Used:**
  - SQL queries & database integration
  - Modular multi-file architecture
  - Date & time computation logic
  - File I/O (CSV export)
  - Financial calculations

## How to Run

### 1. Compile

```bash
g++ main.cpp Payroll.cpp Database.cpp -lsqlite3 -o paycheck

```
### 2. Run

```bash
./paycheck
