import javax.swing.*;
import java.awt.*;
import java.awt.geom.Rectangle2D;
import java.awt.geom.AffineTransform;
import java.awt.geom.Line2D;

public class Iso_Rect extends JComponent {
	int x, y, length, height, width = 0;
	double rotation_angle;
	public Iso_Rect(int x, int y, int length, int height, int width, double rotation_angle) {
		this.x = x;
		this.y = y;
		this.length = length;
		this.height = height;
		this.width = width;
		this.rotation_angle = rotation_angle;
		return;
	}

	private void draw_rect(int x, int y, Graphics2D g2) {
		g2.setColor(Color.BLUE);
		// Calulate right hand points for inner rectangle
		int inner_top_right_x = (int)(Math.cos(Math.toRadians(this.rotation_angle)) * (double)this.length) + x;
		int inner_top_right_y = (int)(Math.sin(Math.toRadians(this.rotation_angle)) * (double)this.length) + y;
		int inner_bottom_right_y = inner_top_right_y + this.height;
		// Create lines for inner rectangle
		Line2D inner_top_right_line = new Line2D.Double(x, y, inner_top_right_x, inner_top_right_y);
		Line2D inner_middle_left_line = new Line2D.Double(x, y, x, y + this.height);
		Line2D inner_bottom_right_line = new Line2D.Double(x, y + this.height, inner_top_right_x, inner_bottom_right_y);
		Line2D inner_middle_right_line = new Line2D.Double(inner_top_right_x, inner_top_right_y, inner_top_right_x, inner_bottom_right_y);
		// Draw lines for inner rectangle
		g2.draw(inner_top_right_line);
		g2.draw(inner_middle_left_line);
		g2.draw(inner_bottom_right_line);
		g2.draw(inner_middle_right_line);
		// Calculate lines for outer rectangle
		int width_x = (int)(Math.cos(Math.toRadians(this.rotation_angle)) * (double)this.width);
		int width_y = (int)(Math.sin(Math.toRadians(this.rotation_angle)) * (double)this.width);
		// Create lines for outer rectangle
		Line2D outer_top_line = new Line2D.Double(x + width_x, y - width_y, inner_top_right_x + width_x, inner_top_right_y - width_y);
		Line2D outer_middle_right_line = new Line2D.Double(inner_top_right_x + width_x, inner_top_right_y - width_y, inner_top_right_x + width_x, inner_bottom_right_y - width_y);
		Line2D outer_top_middle_line = new Line2D.Double(x, y, x + width_x, y - width_y);
		Line2D outer_top_right_middle_line = new Line2D.Double(inner_top_right_x, inner_top_right_y, inner_top_right_x + width_x, inner_top_right_y - width_y);
		Line2D outer_bottom_middle_line = new Line2D.Double(inner_top_right_x, inner_bottom_right_y, inner_top_right_x + width_x, inner_bottom_right_y - width_y);
		// Draw lines for outer rectangle
		g2.draw(outer_top_line);
		g2.draw(outer_middle_right_line);
		g2.draw(outer_top_middle_line);
		g2.draw(outer_top_right_middle_line);
		g2.draw(outer_bottom_middle_line);

	}

	private void fill_rect() {
		g2.setColor(Color.BLACK);
		for (int i = 0; i < this.height; i++) {
			Line2D top_right = new Line2D.Double(x, y, x + this.length, y);
			Line2D bottom_right = new Line2D.Double(x, y + i, x + this.length, y + i);
			// Line2D middle = new Line2D.Double(x, y, x, y + this.height);
			AffineTransform at_t_r = AffineTransform.getRotateInstance(Math.toRadians(this.rotation_angle), top_right.getX1(), top_right.getY1());
			AffineTransform at_b_r = AffineTransform.getRotateInstance(Math.toRadians(this.rotation_angle), bottom_right.getX1(), bottom_right.getY1());
	
				
			// Draw the rotated line
			g2.draw(at_t_r.createTransformedShape(top_right));
			g2.draw(at_b_r.createTransformedShape(bottom_right));
		}
	}

	public void paintComponent(Graphics g) {
		Graphics2D g2 = (Graphics2D) g.create();
		draw_rect(this.x, this.y, g2);
	}
}