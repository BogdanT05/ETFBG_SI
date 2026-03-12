package gui;

import java.awt.*;
import java.awt.event.*;

public class MouseWindow extends Frame {

    private int x, y;
    private String text = "start";

    @Override
    public void paint(Graphics graphics){
        graphics.drawString(text, x, y);
        super.paint(graphics);
    }

    private void adjust(String text, MouseEvent event){
        x = event.getX();
        y = event.getY();

        this.text = text + " (" + x + ", " + y + ")";
        repaint();
    }

    public MouseWindow(){
        setBounds(700, 200, 400, 300);
        setResizable(false);
        setTitle("Mouse window");

        addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                adjust("mouse clicked", e);
            }

            @Override
            public void mousePressed(MouseEvent e) {
                adjust("mouse pressed", e);
            }

            @Override
            public void mouseReleased(MouseEvent e) {
                adjust("mouse released", e);
            }
        });

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                dispose();
            }
        });

        addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent e) {
                adjust("mouse dragged", e);
            }

            @Override
            public void mouseMoved(MouseEvent e) {
                adjust("mouse moved",  e);
            }
        });

        setVisible(true);
    }


    static void main() {
        new MouseWindow();
    }
}
