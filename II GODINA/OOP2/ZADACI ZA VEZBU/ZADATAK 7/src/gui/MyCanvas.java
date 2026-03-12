package gui;

import java.awt.*;

public class MyCanvas extends Canvas implements Runnable{

    private Color lineColor = Color.BLACK;
    private Shape shape;
    private final int steps = 100;
    private final long sleepTime = 25;
    private Thread thread;

    public MyCanvas(){
        shape = new Circle(15);
    }

    @Override
    public void paint(Graphics graphics){
        finish();
        thread = new Thread(this);
        thread.start();

    }

    public synchronized void setShape(Shape shape){
        this.shape = shape;
    }

    public synchronized void setLineColor(Color color){
        this.lineColor = color;
    }

    private synchronized void finish() {
        if (thread != null){
            thread.interrupt();
        }

        while(thread != null){
            try{
                wait();
            } catch (InterruptedException _) {}
        }
    }

    @Override
    public void run() {
        Graphics graphics = getGraphics();
        Shape shape = this.shape.clone();
        graphics.setColor(lineColor);
        graphics.translate(getWidth()/2, getHeight()/2);

        double inc = 2 * Math.PI / steps;
        int x = shape.getX(0);
        int y = shape.getY(0);
        int endX, endY;
        try {
            for (double angle = 0; angle < 2 * Math.PI; angle += inc) {
                Thread.sleep(sleepTime);
                if (Thread.interrupted()){
                    break;
                }
                endX = shape.getX(angle);
                endY = shape.getY(angle);

                graphics.drawLine(x, y, endX, endY);

                x = endX;
                y = endY;

            }
        } catch (InterruptedException _) {}

        synchronized (this){
            thread = null;
            notify();
        }
    }

    public synchronized void setFactor(int factor){
        if(shape != null){
            shape.setFactor(factor);
        }
    }

    public synchronized void setBgColor(Color color) {
        setBackground(color);
    }
}
