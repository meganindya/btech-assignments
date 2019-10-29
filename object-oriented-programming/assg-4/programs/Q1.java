package programs;

import static java.lang.System.*;

class Q1 {
    public static void main(String args[]) {
        Account accounts[] = new Account[5];
        for (int i = 0; i < 5; i++)
            accounts[i] = new Account(1001 + (int) (Math.random() * 5000));
        
        for (Account acc : accounts) {
            out.println("=====\nBalance: " + acc.getBalance() + "\n");

            acc.withdraw(500 + (int) (Math.random() * 25) * 100);
            acc.withdraw(500 + (int) (Math.random() * 25) * 100);
            acc.withdraw(500 + (int) (Math.random() * 25) * 100);
        }
    }
}


class Account {
    private int balance;
    
    Account(int balance) {
        this.balance = balance;
    }

    int getBalance() {
        return balance;
    }

    void withdraw(int value) {
        try {
            if ((balance - value) < 1000) {
                String temp = "Can't withdraw " + value + "\n";
                throw new Exception(temp + "Minimum balance violated\n");
            }
            
            else {
                balance -= value;
                out.println(value + " withdrawn");
                out.println("New balance: " + balance + "\n");
            }
        }
        catch (Exception e) {
            out.println(e.getMessage());
        }
    }
}