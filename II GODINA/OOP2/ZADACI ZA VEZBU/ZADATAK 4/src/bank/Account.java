package bank;

public class Account {
    private int balance;

    public Account(int balance) {
        this.balance = balance;
    }

    public void increase(int amount){
        this.balance += amount;
    }

    public void decrease(int amount){
        this.balance -= amount;
    }

    public int getBalance() {
        return balance;
    }
}
