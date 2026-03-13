package gui.coins;

import java.awt.*;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;


public class CollectCoins extends Frame {
    private Scene scene = new Scene(this);
    private Panel bottomPanel = new Panel();
    private Label time = new Label();
    Panel centerPanel = new Panel();
    TextArea log = new TextArea();
    Label score = new Label();
    Timer timer;

    public CollectCoins(){
        setBounds(700, 200, 500, 300);
        setTitle("Collect Coins");
        setResizable(true);

        addComponentListener(new ComponentAdapter() {
            @Override
            public void componentResized(ComponentEvent e) {
                scene.packScene();
                scene.repaint();
                pack();
            }
        });

        populateWindow();
        showHelpDialog();
        pack();

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                if(timer != null){
                    timer.interrupt();
                }
                dispose();
            }
        });

        setVisible(true);
    }

    private void showHelpDialog() {
        Dialog help = new Dialog(this, Dialog.ModalityType.APPLICATION_MODAL);
        help.setTitle("Help");
        help.add(new Label("Use w-a-s-d to move.", Label.CENTER));
        help.setBounds(700, 200 ,100 ,100);
        help.setResizable(false);

        help.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                dispose();
            }
        });

        help.setVisible(true);
    }

    public void populateWindow(){
        log.setColumns(20);
        log.setRows(1);
        log.setEditable(false);

        int dimension = (getWidth()/2) / scene.getRows() * scene.getRows();
        scene.setBackground(Color.GREEN);
        scene.setPreferredSize(new Dimension(dimension, dimension));

        centerPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 0, 0));
        centerPanel.add(scene);
        add(centerPanel, BorderLayout.CENTER);
        add(log, BorderLayout.EAST);

        TextField coins = new TextField("10");
        Button toss = new Button("Toss");

        toss.addActionListener(_ -> {
            scene.tossCoins(Integer.parseInt(coins.getText()));
            scene.repaint();

            if (timer != null){
                timer.interrupt();
            }
            timer = new Timer(time);
            timer.start();
            timer.go();

            scene.requestFocus();
        });

        bottomPanel.add(new Label("Time: "));
        bottomPanel.add(time);
        bottomPanel.add(new Label("Score: "));
        bottomPanel.add(score);
        bottomPanel.add(new Label("Coins"));
        bottomPanel.add(coins);
        bottomPanel.add(toss);

        add(bottomPanel, BorderLayout.SOUTH);
    }

    static void main() {
        new CollectCoins();
    }
}
