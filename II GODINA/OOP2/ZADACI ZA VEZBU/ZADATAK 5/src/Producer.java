import java.util.Random;

public class Producer extends Thread{
    private final Container container;
    private final int id;

    public Producer(Container c, int i){
        container = c;
        id = i;
    }

    @Override
    public void run() {
        try{
            while (!Thread.interrupted()){
                Thread.sleep(100 + new Random().nextInt(1000));
                int element = new Random().nextInt(10);
                synchronized (container){
                    container.insert(element);
                    System.out.println("Producer ID: " + id + " added element: " + element);
                }

            }
        }catch (InterruptedException _){}

        System.out.println("Producer ID: " + id + " finished");
    }
}
