package gui;

import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;


public class DrawOnCanvas extends Frame {

    private final Button drawButton = new Button("Draw");
    private final MyCanvas scene = new MyCanvas();

    private void populateWindow(){
         Menu bgColorMenu = new Menu("Bg Color");
         MenuItem bgWhite = new MenuItem("white");
         MenuItem bgGray = new MenuItem("gray");

         bgColorMenu.add(bgWhite);
         bgColorMenu.add(bgGray);

         bgWhite.addActionListener(_ -> scene.setBgColor(Color.WHITE));

         bgGray.addActionListener(_ -> scene.setBgColor(Color.GRAY));

         add(scene, BorderLayout.CENTER);

         drawButton.addActionListener((_ -> scene.repaint()));

         Menu factorMenu = new Menu("Size");
         MenuItem small = new MenuItem("3");
         MenuItem big = new MenuItem("5");
         factorMenu.add(small);
         factorMenu.add(big);

         small.addActionListener(e -> scene.setFactor(Integer.parseInt(((MenuItem)e.getSource()).getLabel())));


         big.addActionListener(e -> scene.setFactor(Integer.parseInt(((MenuItem)e.getSource()).getLabel())));

         MenuItem quitMenu = new MenuItem("Quit", new MenuShortcut(KeyEvent.VK_Q));
         quitMenu.addActionListener(_ -> dispose());

         Menu file = new Menu("File");
         file.add(bgColorMenu);
         file.add(factorMenu);
         file.addSeparator();
         file.add(quitMenu);

         MenuBar menuBar = new MenuBar();
         menuBar.add(file);
         setMenuBar(menuBar);

         Panel buttonPanel = new Panel();

         Choice chooseShape = new Choice();
         chooseShape.add("Heart");
         chooseShape.add("Circle");

         chooseShape.addItemListener((_ -> {
             String name = chooseShape.getSelectedItem();
             if (name.equals("Circle")){
                 scene.setShape(new Circle(15));
             } else if (name.equals("Heart")) {
                 scene.setShape(new Heart());
             }
         }));

        List chooseColor = getChooseColor();

        buttonPanel.add(new Label("Shape: "));
         buttonPanel.add(chooseShape);
         buttonPanel.add(new Label("Color: "));
         buttonPanel.add(chooseColor);
         buttonPanel.add(drawButton);

         add(buttonPanel, BorderLayout.SOUTH);

    }

    private List getChooseColor() {
        List chooseColor = new List(2);
        chooseColor.add("Black");
        chooseColor.add("Red");
        chooseColor.add("Green");
        chooseColor.select(0);

        chooseColor.addItemListener(_ -> {
            String color = chooseColor.getSelectedItem();
            switch (color) {
                case "Black" -> scene.setLineColor(Color.BLACK);
                case "Red" -> scene.setLineColor(Color.RED);
                case "Green" -> scene.setLineColor(Color.GREEN);
            }
        });
        return chooseColor;
    }

    public DrawOnCanvas(){
        setBounds(700, 200, 400, 300);
        setResizable(false);
        setTitle("Drawing on Canvas");

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                dispose();
            }
        });

        populateWindow();

        setVisible(true);
    }

    static void main() {
        new DrawOnCanvas();
    }
}
