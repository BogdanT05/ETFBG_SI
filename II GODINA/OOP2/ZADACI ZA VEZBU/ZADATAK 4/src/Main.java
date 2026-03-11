import bank.ATM;
import bank.Account;
import bank.Salary;

import java.sql.SQLOutput;
import java.util.Scanner;

public class Main {
    static void main() {
        Account account = new Account(0);

        ATM atm = new ATM(account);
        Salary salary = new Salary(account);

        atm.start();
        salary.start();

        new Scanner(System.in).nextLine();
        atm.interrupt();
        salary.interrupt();

        try{
            atm.join();
            salary.join();
        } catch (InterruptedException e) {}

        int totalDeposit = salary.getBalance();
        int totalWithdraw = atm.getBalance();
        int balance = account.getBalance();

        System.out.println("Total Deposit: " + totalDeposit);
        System.out.println("Total Withdraw: " + totalWithdraw);
        System.out.println("Difference between deposit and withdrawal: " + (totalDeposit + totalWithdraw));
        System.out.println("Balance on account:  " + balance);
    }
}
