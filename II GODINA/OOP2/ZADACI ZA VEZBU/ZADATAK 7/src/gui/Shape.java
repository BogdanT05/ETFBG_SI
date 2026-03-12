package gui;

public abstract class Shape implements Cloneable{

    protected int factor = 3;

    public Shape clone(){
        try {
            return (Shape) super.clone();
        } catch (CloneNotSupportedException _){
            return null;
        }
    }

    public void setFactor(int factor) {
        this.factor = factor;
    }

    public abstract int getX(double angle);
    public abstract int getY(double angle);
}
