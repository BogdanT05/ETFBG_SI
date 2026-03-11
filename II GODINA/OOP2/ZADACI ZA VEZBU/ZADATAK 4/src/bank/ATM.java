package bank;

import java.util.Random;

public class ATM extends Thread{
    private final Account account;
    private int balance = 0;

    public ATM(Account account) {
        this.account = account;
    }

    @Override
    public void run() {
        while (!Thread.interrupted()){
            int amount = 1 + new Random().nextInt(100);
            synchronized (account) {
                account.decrease(amount);
            }
            balance -= amount;
            System.out.println("Withdrawn from ATM: " + amount);
        }
    }

    public int getBalance(){
        return balance;
    }
}
