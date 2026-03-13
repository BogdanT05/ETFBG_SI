package gui.coins;

import java.awt.*;

public class Coin extends Figure{
    public Coin(int width, int y, int x) {
        super(width, y, x);
    }

    @Override
    public void paint(Graphics graphics) {
        Color prevColor = graphics.getColor();
        graphics.setColor(Color.YELLOW);
        graphics.fillOval(x - width/2, y - width/2, width, width);
        graphics.setColor(prevColor);
    }
}
