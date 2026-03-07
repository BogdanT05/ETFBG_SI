package geometry;

public class Point {

    private int x;
    private int y;

    public Point(int x){
        this(x, 0);
    }

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == this) return true;
        if (obj == null) return false;
        if (!(obj instanceof Point p)) return false;

        return (this.x == p.x) && (this.y == p.y);
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append("(").append(x).append(", ").append(y).append(")");
        return stringBuilder.toString();
    }

    public static void main() {
        Point p1 = new Point(2, 5);
        System.out.println(p1);
        Point p2 = new Point(2, 1);
        System.out.println(p2);
        Point p3 = new Point(2, 5);

        System.out.println(p1 == p2);
        System.out.println(p1 == p3);
        System.out.println(p1.equals(p3));
    }
}
