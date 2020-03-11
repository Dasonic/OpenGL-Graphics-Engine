import javax.swing.*;
import java.awt.*;
import java.awt.geom.Line2D;

public class Outline {
	Iso_Rect right_side, left_side, bottom;
	int x, y, length, height, width = 0;
	DataLine datalines_right[];
	DataLine datalines_left[];
	public Outline(int x, int y, int length, int height, int width, int num_datalines) {
		this.x = x;
		this.y = y;
		this.length = length;
		this.height = height;
		this.width = width;
		this.datalines_right = new DataLine[num_datalines];
		this.datalines_left = new DataLine[num_datalines];
		right_side = new Iso_Rect(this.x, this.y, this.length, this.height, this.width, 30);
		left_side = new Iso_Rect(this.x, this.y, -this.length, this.height, -this.width, -30);
		bottom = new Iso_Rect(left_side.get_far_right_x(), right_side.get_lowest_y(), this.length, this.width, this.length, 30);
		// System.out.println(this.height);
		int space_between_lines = (int)(this.height / (num_datalines));
		int value = 0;
		for (int i = 0; i < num_datalines; i++) {
			this.datalines_right[i] = new DataLine(this.x, this.y + this.height - (space_between_lines * i), this.length, this.width, 30, Integer.toString(value));
			this.datalines_left[i] = new DataLine(this.x, this.y + this.height - (space_between_lines * i), -this.length, -this.width, -30, Integer.toString(value));
			value += space_between_lines;
		}
	}

	public void draw(JFrame f) {
		f.add(right_side);
		f.setVisible(true);
		f.add(left_side);
		f.setVisible(true);
		f.add(bottom);
		f.setVisible(true);
		for (int i = 0; i < this.datalines_right.length; i++) {
			f.add(this.datalines_right[i]);
			f.setVisible(true);
			f.add(this.datalines_left[i]);
			f.setVisible(true);
		}
	}
}