# Customer Billing System

This is a simple Customer Billing System written in C. The program allows you to manage customer accounts, including adding new accounts, searching for accounts by number or name, and viewing account details like balance, payment history, and account status.

## Features

- **Add Customer Accounts**: Input customer details including name, account number, mobile number, address, previous balance, current payment, and payment date.
- **Search Accounts**: Search customer accounts by account number or by customer name.
- **View Account Details**: Display detailed information about a customer's account, including their account status (Current, Overdue, or Delinquent).

## Requirements

- A C compiler (like GCC or Clang) to compile the code.
- The program is designed for environments that support standard C libraries.

## Compilation and Execution

### Compiling the Program

To compile the program, use the following command in your terminal:

```bash
gcc -o billing_system billing_system.c
