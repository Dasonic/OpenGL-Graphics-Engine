import javax.swing.*;
import java.awt.*;
import java.awt.geom.Line2D;
public class DataLine extends JComponent {
	double angle; 
	int text_x, text_y;
	String text;
	Line2D main_line, side_line, text_line;
	Boolean left_text;
	public DataLine(int starting_x, int starting_y, int line_length, int line_width, int angle, String text) {
		this.angle = Math.toRadians(angle);
		this.text = text;
		int end_x = (int)(Math.cos(this.angle) * (double)line_length) + starting_x;
		int end_y = (int)(Math.sin(this.angle) * (double)line_length) + starting_y;
		int width_x = (int)(Math.cos(this.angle) * (double)line_width);
		int width_y = (int)(Math.sin(this.angle) * (double)line_width);

		this.main_line = new Line2D.Double(starting_x, starting_y, end_x, end_y);
		this.side_line = new Line2D.Double(end_x, end_y, end_x + width_x, end_y - width_y);
		this.text_line = new Line2D.Double(end_x + width_x, end_y - width_y, end_x + width_x + line_length / 50, end_y - width_y);

		this.text_x = end_x + width_x;
		this.text_y = end_y - width_y;
		this.left_text = line_length > 0 ? false : true;
		return;
	}

	public void paintComponent(Graphics g) {
		Graphics2D g2 = (Graphics2D) g.create();
		g2.setColor(Color.BLACK);
		g2.draw(main_line);
		g2.draw(side_line);
		// g2.rotate(this.angle);
		if (!this.left_text) {
			g2.draw(text_line);
			g2.drawString(this.text, this.text_x + 10, this.text_y + 5);
		}
	}
}