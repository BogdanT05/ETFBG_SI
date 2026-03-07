package geometry;
import java.util.Arrays;


public class Polygon {
    private Point[] points;
    private int size;

    private static int last_id;
    private int id;

    static {
        last_id = 5;
    }

    {
        id = last_id++;
    }

    public Polygon(int capacity){
        if (capacity < 3) capacity = 3;
        points = new Point[capacity];
    }

    public void add_point(Point p){
        if (size >= points.length) return;
        points[size++] = p;
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();
        boolean first = true;
        for (Point p : points){
            if (p == null) continue;
            if (first){
                first = false;
            }
            else{
                stringBuilder.append(", ");
            }

            stringBuilder.append(p);
        }

        return stringBuilder.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null) return false;
        if (!(o instanceof Polygon polygon)) return false;
        return size == polygon.size && Arrays.equals(points, polygon.points);
    }

    public double circumference(){
        double c = 0;
        for (int i = 0; i < points.length-1; i++){
            c += Point.distance(points[i], points[i+1]);
        }
        c += Point.distance(points[0], points[points.length - 1]);
        return c;
    }

    public static void main() {
        Polygon p = new Polygon(3);
        p.add_point(new Point(0, 0));
        p.add_point(new Point(1, 2));
        p.add_point(new Point(3, 4));

        Polygon p2 = new Polygon(3);
        p2.add_point(new Point(0, 0));
        p2.add_point(new Point(1, 2));
        p2.add_point(new Point(3, 4));

        System.out.println(p.equals(p2));
    }
}
