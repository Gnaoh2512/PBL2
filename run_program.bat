@echo off
cd "%~dp0"
g++ main.cpp User.cpp Admin.cpp BankAccount.cpp Transaction.cpp LoanAccount.cpp SavingAccount.cpp RegularAccount.cpp TimeUtils.cpp -o main.exe
if %errorlevel% equ 0 (
    main.exe
)