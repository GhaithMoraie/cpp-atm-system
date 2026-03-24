#ATM System (C++)

.A console-based ATM simulation system written in C++.
This project simulates the basic functionality of an ATM machine where users can log in and perform banking operations.

##Features

_Login using account number and PIN

_Quick withdraw (fixed amounts)

-Normal withdraw (custom amount)

_Deposit money

_Check account balance

_Logout

###Quick Withdraw Options

.20

.50

.100

.200

.400

.600

.800

.1000

##Data Storage

.Client data is stored in a text file:

_ClientsAtM.txt

.Each record includes:

_Account Number

_PIN

_Account Balance

##Concepts Used

_Structs

_Enums

_File handling (fstream)

_Vectors

_Menu-driven system

_Input validation

##How to Run

.Compile:
g++ main.cpp -o atm
.Run:
./atm

##Example Flow

_User logs in

_Chooses operation from menu

_Performs transaction

_System updates balance

##Author

Ghaith Moraie
