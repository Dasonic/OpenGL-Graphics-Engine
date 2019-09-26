import javax.swing.JComponent;
import javax.swing.*;
import java.awt.*;

public class Title extends JComponent {
    String text;
    int x, y;
    Font font;
    public Title(String text, int x, int y, Font font) {
        this.text = text;
        this.x = x;
        this.y = y;
        this.font = font;
        return;
    }

    public void paintComponent(Graphics g) {
        Graphics2D g2 = (Graphics2D) g.create();
        g2.setFont(font);
        g2.drawString(text, x, y);
    }
}