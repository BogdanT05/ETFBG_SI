package colections;

import colections.errors.InvalidLength;
import colections.errors.OutOfBounds;

public class Stack extends Vector{
    public Stack(int n) throws InvalidLength {
        super(n);
    }

    public class StackIterator extends VectorIterator{

        public StackIterator() {
            index = position - 1;
        }

        @Override
        public boolean has_elements() {
            return index < Stack.this.position && index >= 0;
        }

        @Override
        public void next() {
            index--;
        }
    }

    @Override
    public Iterator iterator() {
        return new StackIterator();
    }
}
