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
	Polygon side, top, front;
	boolean draw_front = false;
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
		calculate_polygons();
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

	private void calculate_polygons() {
		int x_array_s[] = {ibl.x, ibr.x, itr.x, itl.x};
		int y_array_s[] = {ibl.y, ibr.y, itr.y, itl.y};
		this.side = new Polygon(x_array_s, y_array_s, 4);
		int x_array_t[] = {itl.x, itr.x, otr.x, otl.x};
		int y_array_t[] = {itl.y, itr.y, otr.y, otl.y};
		this.top = new Polygon(x_array_t, y_array_t, 4);
	}

	public void set_draw_front() {
		this.draw_front = true;
		int x_array_f[] = {ibr.x, obr.x, otr.x, itr.x};
		int y_array_f[] = {ibr.y, obr.y, otr.y, itr.y};
		this.front = new Polygon(x_array_f, y_array_f, 4);
	}

	private void fill_poly(Graphics2D g2) {
		g2.setColor(this.colour);
		g2.setBackground(this.colour);
		// Draw and fill side
		g2.drawPolygon(this.side);
		g2.fillPolygon(this.side);
		// Draw and fill top
		g2.fillPolygon(this.top);

		// Draw and fill front
		if (draw_front)
			g2.fillPolygon(this.front);
	}

	private void draw_poly(int x, int y, Graphics2D g2) {
		g2.setColor(Color.BLACK);
		g2.drawPolygon(this.top);
	}

	public void paintComponent(Graphics g) {
		Graphics2D g2 = (Graphics2D) g.create();
		fill_poly(g2);
		draw_poly(this.start_x, this.start_y, g2);
	}
}