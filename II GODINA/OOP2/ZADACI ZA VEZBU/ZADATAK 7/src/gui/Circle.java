package gui;

public class Circle extends Shape{
    private final double r;

    public Circle(int r){
        this.r = r;
    }

    @Override
    public int getY(double angle) {
        return (int) (factor * r * Math.sin(angle));
    }

    @Override
    public int getX(double angle) {
        return (int) (factor * r * Math.cos(angle));
    }
}
