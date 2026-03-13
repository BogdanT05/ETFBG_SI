package gui.coins;

import java.awt.*;

public abstract class Figure {
    protected int x, y, width;

    public Figure(int width, int y, int x) {
        this.width = width;
        this.y = y;
        this.x = x;
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public int getWidth() {
        return width;
    }

    public void setWidth(int width) {
        this.width = width;
    }

    @Override
    public boolean equals(Object obj) {
        if(!(obj instanceof Figure figure)){
            return false;
        }

        return this.x == figure.x && this.y == figure.y;
    }

    public abstract void paint(Graphics graphics);

    @Override
    public String toString() {
        return "(" + x + ", " + y + ")";
    }

}
