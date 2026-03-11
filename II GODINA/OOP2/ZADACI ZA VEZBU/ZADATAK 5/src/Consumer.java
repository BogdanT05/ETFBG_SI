import java.util.Random;

public class Consumer extends Thread{
    private final Container container;
    private final int id;

    public Consumer(Container c, int i){
        container = c;
        id = i;
    }

    @Override
    public void run() {
        try{
            while (!Thread.interrupted()){
                Thread.sleep(100 + new Random().nextInt(1000));
                synchronized (container){
                    int element = container.getElement();
                    System.out.println("Consumer ID: " + id + " removed element: " + element);
                }

            }
        }catch (InterruptedException _){}

        System.out.println("Consumer ID: " + id + " finished");
    }
}
