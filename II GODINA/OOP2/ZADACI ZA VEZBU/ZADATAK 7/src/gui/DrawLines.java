package gui;

import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;

public class DrawLines extends Frame {

    static class Line{
        int startX, startY, endX, endY;

        public Line() {
            startX = 0;
            startY = 0;
            endX = 0;
            endY = 0;
        }
    }

    private Line line;
    private final ArrayList<Line> lines = new ArrayList<>();

    public void paint(Graphics graphics){
        for (Line line : lines){
            if(line != null){
                graphics.drawLine(line.startX, line.startY, line.endX, line.endY);
            }
        }
        super.paint(graphics);
    }

    private class MouseEventHandler extends MouseAdapter{

        @Override
        public void mousePressed(MouseEvent e) {
            line = new Line();
            lines.add(line);

            line.startX = e.getX();
            line.startY = e.getY();
        }

        @Override
        public void mouseReleased(MouseEvent e) {
            repaint();
        }

        @Override
        public void mouseDragged(MouseEvent e) {
            line.endX = e.getX();
            line.endY = e.getY();
            repaint();
        }
    }

    public DrawLines(){
        setBounds(700, 200, 400, 300);
        setResizable(false);
        setTitle("Drawing Lines");

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                dispose();
            }
        });

         addMouseListener(new MouseEventHandler());
         addMouseMotionListener(new MouseEventHandler());

        setVisible(true);
    }

    static void main() {
        new DrawLines();
    }

}
