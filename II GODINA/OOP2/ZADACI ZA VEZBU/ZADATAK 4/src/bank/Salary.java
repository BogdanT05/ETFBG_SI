package bank;
import java.util.Random;

public class Salary extends Thread{
    private final Account account;
    private int balance = 0;

    public Salary(Account account) {
        this.account = account;
    }

    @Override
    public void run() {
        try {
            while (!Thread.interrupted()) {
                Thread.sleep(1 + new Random().nextInt(1000));

                int amount = 1 + new Random().nextInt(100);
                synchronized (account) {
                    account.increase(amount);
                    System.out.println("Salary amount: " + amount + "\t New Balance: " + account.getBalance());

                    account.notify();
                }

                balance += amount;

            }
        }catch (InterruptedException _) {}
    }

    public int getBalance(){
        return balance;
    }
}
