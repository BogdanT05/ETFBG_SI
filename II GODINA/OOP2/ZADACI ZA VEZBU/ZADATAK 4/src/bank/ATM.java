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
        try {
            while (!Thread.interrupted()) {
                Thread.sleep(1 + new Random().nextInt(1000));

                int amount = 1 + new Random().nextInt(1000);
                synchronized (account) {
                    System.out.println("Trying to withdraw: " + amount + "\t Balance: " + account.getBalance());

                    while (amount > account.getBalance()){
                        account.wait();
                    }

                    account.decrease(amount);
                    System.out.println("Withdrawn from ATM: " + amount + "\t New Balance: " + account.getBalance());
                }

                balance -= amount;
            }
        } catch (InterruptedException _) {}
    }

    public int getBalance(){
        return balance;
    }
}
