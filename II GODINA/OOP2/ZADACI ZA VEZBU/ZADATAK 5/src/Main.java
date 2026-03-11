import java.util.Scanner;

public class Main {
    static void main() throws InterruptedException {

        Container container = new Container(1);
        Producer[] producers = new Producer[5];
        Consumer[] consumers = new Consumer[2];

        for (int i = 0; i < 5; i++) {
            (producers[i] = new Producer(container, i)).start();

            if (i < 2){
                (consumers[i] = new Consumer(container, i+10)).start();
            }
        }

        new Scanner(System.in).nextLine();

        for (int i = 0; i < 5; i++) {
            producers[i].interrupt();

            if (i < 2){
                consumers[i].interrupt();
            }
        }

        for (int i = 0; i < 5; i++) {
            producers[i].join();

            if (i < 2){
                consumers[i].join();
            }
        }

        System.out.println("End");


    }
}
