package colections.errors;

public class OutOfBounds extends RuntimeException {
    public OutOfBounds(int position) {
        super("Index out of bounds: " + position);
    }
}