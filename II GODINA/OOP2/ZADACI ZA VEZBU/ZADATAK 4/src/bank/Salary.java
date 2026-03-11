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
        while (!Thread.interrupted()){
            int amount = 1 + new Random().nextInt(100);
            account.increase(amount);
            balance += amount;
            System.out.println("Salary amount: " + amount);
        }
    }

    public int getBalance(){
        return balance;
    }
}
