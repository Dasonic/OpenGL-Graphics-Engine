import javax.swing.*;
import java.awt.*;
import java.awt.geom.Rectangle2D;
import java.awt.geom.AffineTransform;
import java.awt.geom.Line2D;

public class DataGraph extends JComponent {
	int start_x, start_y, point1, point2, length, width = 0;
	double rotation_angle;
	Point otl, obr, otr, itl, ibr, itr, ibl;
	Color colour;
	public DataGraph(int start_x, int start_y, int point1, int point2, int length, int width, double rotation_angle, Color colour) {
		this.start_x = start_x;
		this.start_y = start_y;
		this.point1 = point1;
		this.point2 = point2;
		this.length = length;
		this.width = width;
		this.rotation_angle = rotation_angle;
		this.colour = colour;
		calculate_points();
		return;
	}

	private void calculate_points() {
		// Outer Top Left
		otl = new Point();
		otl.x = start_x; // Directly above relative 0, 0
		otl.y = start_y - point1;
		// Outer Bottom Right
		obr = new Point();
		obr.x = otl.x + (int)(Math.cos(Math.toRadians(this.rotation_angle)) * (double)this.length);
		obr.y = start_y + (int)(Math.sin(Math.toRadians(this.rotation_angle)) * (double)this.length);
		// Outer Top Right
		otr = new Point();
		otr.x = obr.x;
		otr.y = obr.y - point2;

		// Inner Top Left
		itl = new Point();
		itl.x = otl.x - (int)(Math.cos(Math.toRadians(-this.rotation_angle)) * (double)this.width);
		itl.y = otl.y - (int)(Math.sin(Math.toRadians(-this.rotation_angle)) * (double)this.width);

		// Inner Bottom Right
		ibr = new Point();
		ibr.x = obr.x - (int)(Math.cos(Math.toRadians(-this.rotation_angle)) * (double)this.width);
		ibr.y = obr.y - (int)(Math.sin(Math.toRadians(-this.rotation_angle)) * (double)this.width);

		// Inner Top Right
		itr = new Point();
		itr.x = otr.x - (int)(Math.cos(Math.toRadians(this.rotation_angle)) * (double)this.width);
		itr.y = otr.y + (int)(Math.sin(Math.toRadians(this.rotation_angle)) * (double)this.width);

		// Inner Bottom Left
		ibl = new Point();
		ibl.x = start_x - (int)(Math.cos(Math.toRadians(this.rotation_angle)) * (double)this.width);
		ibl.y = start_y + (int)(Math.sin(Math.toRadians(this.rotation_angle)) * (double)this.width);
	}

	private void fill_poly(Graphics2D g2) {
		g2.setColor(this.colour);
		int top_before_angle = point1 < point2 ? point1 : point2;
		int very_top = point1 > point2 ? point1 : point2;
		Point top_side = itl.y < itr.y ? ibr : ibl;
		Point bottom_side = itl.y > itr.y ? ibr : ibl;
		// Fill to before angle
		int y = 0;
		for (; y <= top_before_angle; y++) {
			Line2D fill_line = new Line2D.Double(ibl.x, ibl.y - y, ibr.x, ibr.y - y);
			g2.draw(fill_line);
		}
		// Fill angle
		int yt = y - 1;
		for (;yt < very_top; yt++) {
			Line2D fill_line = new Line2D.Double(bottom_side.x, bottom_side.y - yt, top_side.x, top_side.y - y);
			g2.draw(fill_line);
		}
		// Fill top
		double line_angle = Math.atan2(itl.y - itr.y, itl.x - itr.x);
		System.out.println(line_angle);
		// Difference in height between left and right
		int height_difference = Math.abs(itl.y - itr.y) / this.width;
		for (int x = 0; x < this.width; x++) {
			int top_x = otl.x + (int)(Math.cos(Math.toRadians(line_angle)) * (double)x);
			int top_y = otl.y + (int)(Math.sin(Math.toRadians(line_angle)) * (double)x);
			int bot_x = itl.x + (int)(Math.cos(Math.toRadians(line_angle)) * (double)x);
			int bot_y = itl.y + (int)(Math.sin(Math.toRadians(line_angle)) * (double)x);
			Line2D fill_line = new Line2D.Double(bot_x, bot_y, top_x, top_y);
			g2.draw(fill_line);
		}
		
	}

	private void draw_poly(int x, int y, Graphics2D g2) {
		g2.setColor(Color.BLACK);
		// Outer
		Line2D start_obr = new Line2D.Double(start_x, start_y, obr.x, obr.y);
		Line2D start_otl = new Line2D.Double(start_x, start_y, otl.x, otl.y);
		Line2D otl_otr = new Line2D.Double(otl.x, otl.y, otr.x, otr.y);
		Line2D otr_obr = new Line2D.Double(otr.x, otr.y, obr.x, obr.y);
		// g2.draw(start_obr);
		// g2.draw(start_otl);
		g2.draw(otl_otr);
		// g2.draw(otr_obr);

		// Inner
		Line2D ibl_ibr = new Line2D.Double(ibl.x, ibl.y, ibr.x, ibr.y);
		Line2D ibl_itl = new Line2D.Double(ibl.x, ibl.y, itl.x, itl.y);
		Line2D itl_itr = new Line2D.Double(itl.x, itl.y, itr.x, itr.y);
		Line2D itr_ibr = new Line2D.Double(itr.x, itr.y, ibr.x, ibr.y);
		// g2.draw(ibl_ibr);
		// g2.draw(ibl_itl);
		g2.draw(itl_itr);
		// g2.draw(itr_ibr);
		
		// Connections
		Line2D start_ibl = new Line2D.Double(start_x, start_y, ibl.x, ibl.y);
		Line2D obr_ibr = new Line2D.Double(obr.x, obr.y, ibr.x, ibr.y);
		Line2D otr_itr = new Line2D.Double(otr.x, otr.y, itr.x, itr.y);
		Line2D otl_itl = new Line2D.Double(otl.x, otl.y, itl.x, itl.y);
		// g2.draw(start_ibl);
		// g2.draw(obr_ibr);
		g2.draw(otr_itr);
		g2.draw(otl_itl);
		
		
	}

	public void paintComponent(Graphics g) {
		Graphics2D g2 = (Graphics2D) g.create();
		fill_poly(g2);
		draw_poly(this.start_x, this.start_y, g2);
	}
}