package main;
import geometry.*;

public class Main {
    static void main() {
        Polygon p = new Polygon(3);

        p.add_point(new Point(0, 0));
        p.add_point(new Point(1, 1));
        p.add_point(new Point(0, 2));

        System.out.println(p.circumference());
    }
}
