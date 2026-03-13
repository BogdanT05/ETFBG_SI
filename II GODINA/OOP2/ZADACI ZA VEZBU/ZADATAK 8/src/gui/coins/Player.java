package gui.coins;

import java.awt.*;

public class Player extends Figure{
    public Player(int width, int y, int x) {
        super(width, y, x);
    }

    @Override
    public void paint(Graphics graphics) {
        Color prevColor = graphics.getColor();
        graphics.setColor(Color.RED);
        graphics.drawLine(x, y - width/2, x, y + width/2 -1);
        graphics.drawLine(x - width/2, y, x + width/2 -1, y);
        graphics.setColor(prevColor);
    }

}
