package gui.coins;

import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.ArrayList;

public class Scene extends Canvas {

    private int squareWidth;
    private CollectCoins owner;
    private int rows = 10;
    private int score = 0;
    private Player player;
    private ArrayList<Figure> figures = new ArrayList<>();

    public void tossCoins(int coins){
        owner.score.setText("");
        owner.log.setText("");
        player = null;
        figures = new ArrayList<>();
        score = 0;

        while (coins >= rows * rows){
            coins /= 4;
        }

        int x, y, coinR = squareWidth / 2;
        for (int i = 0; i < coins; i++){
            x = (int) (Math.random() * rows) * squareWidth + coinR;
            y = (int) (Math.random() * rows) * squareWidth + coinR;

            Coin c = new Coin(coinR, y, x);

            if(figures.contains(c)){
                i--;
                continue;
            }

            figures.add(c);
        }

        do{
            x = (int) (Math.random() * rows) * squareWidth + squareWidth / 2;
            y = (int) (Math.random() * rows) * squareWidth + squareWidth / 2;
            player = new Player(squareWidth, y, x);
        } while(figures.contains(player));

        figures.add(player);
    }

    @Override
    public void paint(Graphics graphics){
        squareWidth = getDim()/rows;
        adjustScore();
        drawLines();
        drawFigures();
    }

    private void drawFigures() {
        if (player == null){
            return;
        }

        for (Figure f: figures){
            f.paint(getGraphics());
        }

        player.paint(getGraphics());
    }

    private void drawLines() {
        int dimension = getDim();
        int step = dimension / rows;
        Graphics graphics = getGraphics();

        graphics.setColor(Color.BLUE);
        for (int i = 0; i < dimension; i+= step){
            graphics.drawLine(0, i, dimension - 1, i);
            graphics.drawLine(i, 0, i, dimension-1);
        }
    }

    private int getDim() {
        int width = owner.centerPanel.getWidth();
        int height = owner.centerPanel.getHeight();
        int w = width/rows * rows;
        int h = height/rows * rows;

        return Math.max(w, h);
    }

    private void adjustScore() {
        for (Figure f: figures){
            if (player.equals(f) && player != f){
                score++;
                owner.score.setText("" + score);
                owner.log.append("Coin collected at: " + owner.timer.toString() + "\n");
                figures.remove(f);

                if (figures.size() == 1){
                    owner.timer.interrupt();
                }
                break;
            }
        }
    }

    public int getRows(){
        return this.rows;
    }

    public Scene(CollectCoins owner){
        this.owner = owner;

        addKeyListener(new KeyAdapter() {
            @Override
            public void keyTyped(KeyEvent e) {
                char key = Character.toUpperCase(e.getKeyChar());

                switch (key){
                    case KeyEvent.VK_W: {
                        int y = player.getY() - squareWidth;
                        player.setY(y < 0 ? player.getY() : y);
                        break;
                    }

                    case KeyEvent.VK_S: {
                        int y = player.getY() + squareWidth;
                        player.setY(y > getHeight() ? player.getY() : y);
                        break;
                    }

                    case KeyEvent.VK_D: {
                        int x = player.getX() + squareWidth;
                        player.setX(x > getWidth() ? player.getX() : x);
                        break;
                    }

                    case KeyEvent.VK_A: {
                        int x = player.getX() - squareWidth;
                        player.setX(x < 0 ? player.getX() : x);
                        break;
                    }
                }

                repaint();
            }
        });
    }

    public void packScene() {
        int dimension = getDim();
        int oldSquareWidth = squareWidth;
        squareWidth = dimension / rows;
        int x, y;
        for (Figure f: figures){
            x = ((int)(f.getX()/ 1.0 / oldSquareWidth) * squareWidth) + squareWidth/2;
            y = ((int)(f.getY()/ 1.0 / oldSquareWidth) * squareWidth) + squareWidth/2;
            f.setX(x);
            f.setY(y);
            f.setWidth(squareWidth/2);
        }

        if (player != null){
            player.setWidth(squareWidth);
        }
        setPreferredSize(new Dimension(dimension, dimension));
    }
}
