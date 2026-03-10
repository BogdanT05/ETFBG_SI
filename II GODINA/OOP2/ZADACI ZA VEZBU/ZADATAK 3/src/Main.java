import colections.Iterator;
import colections.Stack;
import colections.Vector;
import colections.errors.InvalidLength;
import colections.errors.OutOfBounds;

public class Main {
    static void main() {
        Vector vector;

        try{
            vector = new Vector(5);
            vector.add(4).add(5).add(7);

            Iterator iterator = vector.iterator();
            while(iterator.has_elements()){
                System.out.println(iterator.get_element());
                iterator.next();
            }

            System.out.println("\n");

            Stack stack = new Stack(5);
            stack.add(5).add(4).add(3);

            iterator = stack.iterator();
            while(iterator.has_elements()){
                System.out.println(iterator.get_element());
                iterator.next();
            }


        } catch (InvalidLength | OutOfBounds exception){
            System.out.println(exception.getMessage());
        }
    }
}
