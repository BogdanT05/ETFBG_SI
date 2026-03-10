package colections;

import colections.errors.InvalidLength;
import colections.errors.OutOfBounds;

public class Vector{
    private final int[] array;
    protected int position = 0;

    public class VectorIterator implements Iterator{
        protected int index;

        @Override
        public boolean has_elements() {
            return index < position;
        }

        @Override
        public void next() {
            index++;
        }

        @Override
        public int get_element() throws OutOfBounds {
            if (!has_elements()) throw new OutOfBounds(index);
            return Vector.this.array[index];
        }
    }

    public Vector(int n) throws InvalidLength{
        if (n <= 0) throw new InvalidLength(n);
        array = new int[n];
    }

    public Vector add(int number){
        if (position == array.length) throw new OutOfBounds(position);
        array[position++] = number;
        return this;
    }

    public Iterator iterator(){
        return new VectorIterator();
    }

}
