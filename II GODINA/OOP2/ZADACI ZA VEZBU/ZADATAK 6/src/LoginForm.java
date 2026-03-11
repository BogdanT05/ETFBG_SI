import java.awt.*;
import java.awt.event.ItemEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;


public class LoginForm extends Frame {

    private class QuitDialog extends Dialog{

        private final Button ok = new Button("OK");
        private final Button cancel = new Button("Cancel");

        public void paint(Graphics graphics){
            graphics.drawString("Are you sure you want to quit?", 20, 70);
            super.paint(graphics);
        }

        public QuitDialog(Frame owner) {
            super(owner);
            setTitle("Quit");
            setBounds(owner.getX() + owner.getWidth()/2, owner.getY() + owner.getHeight()/2, 200, 150);
            setResizable(false);
            setModalityType(ModalityType.APPLICATION_MODAL);

            Panel buttons = new Panel();

            ok.addActionListener((_) -> LoginForm.this.dispose());
            cancel.addActionListener((_) -> QuitDialog.this.dispose());

            buttons.add(ok);
            buttons.add(cancel);

            add(buttons, BorderLayout.SOUTH);

            addWindowListener(new WindowAdapter() {
                @Override
                public void windowClosing(WindowEvent e) {
                    QuitDialog.this.dispose();
                }
            });

            setVisible(true);
        }

    }

    private final TextField username = new TextField(10);
    private final TextField password = new TextField(10);
    private final Button submit = new Button("Submit");
    private final Label passStrength = new Label("");

    public LoginForm(){
        setVisible(true);
        setResizable(true);
        setLocation(700, 200);

        setTitle("Login form");

        populateWindow();
        pack();

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                new QuitDialog(LoginForm.this);
            }
        });
    }

    public void populateWindow(){
        Panel content = new Panel(new GridLayout(0, 1, 0, 5));
        Panel userPanel = new Panel();
        userPanel.setBackground(Color.RED);
        userPanel.add(new Label("Username: "));
        userPanel.add(username);

        content.add(userPanel);

        password.setEchoChar('*');
        Panel passPanel = new Panel();

        password.addTextListener((_ -> {
            int passLength = password.getText().length();
            if(passLength == 0){
                passStrength.setText("");
            } else if (passLength < 5){
                passStrength.setText("Weak password");
                passStrength.setForeground(Color.RED);
            } else if (passLength < 10){
                passStrength.setText("Good password");
                passStrength.setForeground(Color.YELLOW);
            }else if (passLength > 10){
                passStrength.setText("Excellent password");
                passStrength.setForeground(Color.GREEN);
            }

            passStrength.revalidate();
        }));

        passStrength.setFont(new Font("Arial", Font.BOLD, 20));

        passPanel.setBackground(Color.YELLOW);
        passPanel.add(new Label("Password: "));
        passPanel.add(password);

        content.add(passPanel);

        Panel radioPanel = new Panel();
        radioPanel.setBackground(Color.GREEN);
        radioPanel.add(new Label("Gender: "));

        CheckboxGroup genderGroup = new CheckboxGroup();
        Checkbox maleCb = new Checkbox("Male", true, genderGroup);
        Checkbox femaleCb = new Checkbox("Female", false, genderGroup);
        radioPanel.add(maleCb);
        radioPanel.add(femaleCb);

        content.add(radioPanel);

        Panel termsPanel = new Panel();
        Checkbox termsCb = new Checkbox("I agree with terms and conditions.");
        termsPanel.add(termsCb);

        content.add(termsPanel);
        submit.setEnabled(false);

        termsCb.addItemListener(e -> submit.setEnabled(e.getStateChange() == ItemEvent.SELECTED));

        submit.addActionListener(_ -> {
            System.out.println("====================");
            System.out.println("Username: " + username.getText());
            System.out.println("Password: " + password.getText());
            System.out.println("Gender: " + genderGroup.getSelectedCheckbox().getLabel());
        });

        Panel submitPanel = new Panel();
        submitPanel.add(submit);
        content.add(submitPanel);

        Panel passStrengthPanel = new Panel();
        passStrengthPanel.setBackground(Color.LIGHT_GRAY);
        passStrengthPanel.add(passStrength);

        content.add(passStrengthPanel);

        add(content, BorderLayout.CENTER);
    }

    static void main() {
        new LoginForm();
    }
}
