import javax.swing.*;
import java.awt.*;

public class Outline {
	Iso_Rect right_side, left_side, bottom;
	int x, y, length, height, width = 0;
	public Outline(int x, int y, int length, int height, int width) {
		this.x = x;
		this.y = y;
		this.length = length;
		this.height = height;
		this.width = width;
		// right_side = new Iso_Rect(500, 50, 200, 200, 10, 30);
		right_side = new Iso_Rect(this.x, this.y, this.length, this.height, this.width, 30);
		// left_side = new Iso_Rect(500, 50, -200, 200, -10, -30);
		left_side = new Iso_Rect(this.x, this.y, -this.length, this.height, -this.width, -30);
		// bottom = new Iso_Rect(327, 349, 200, 10, 200, 30);
		bottom = new Iso_Rect(327, 349, this.length, this.width, this.height, 30);
	}

	public void draw(JFrame f) {
		f.add(right_side);
		f.setVisible(true);
		f.add(left_side);
		f.setVisible(true);
		f.add(bottom);
		f.setVisible(true);
	}
}