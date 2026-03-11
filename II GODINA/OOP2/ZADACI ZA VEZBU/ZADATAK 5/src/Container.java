public class Container {
    private final int[] container;
    private final int capacity;
    private int start, end, counter;

    public Container(int capacity) {
        container = new int[this.capacity = capacity];
    }

    public synchronized void insert(int element) throws InterruptedException {
        while (counter == capacity) this.wait();
        container[end] = element;
        end = (end + 1) % capacity;
        counter++;

        notifyAll();
    }

    public synchronized int getElement() throws InterruptedException {
        while (counter == 0) this.wait();
        int element = container[start];
        start = (start + 1) % capacity;
        counter--;

        notifyAll();
        return element;
    }
}
