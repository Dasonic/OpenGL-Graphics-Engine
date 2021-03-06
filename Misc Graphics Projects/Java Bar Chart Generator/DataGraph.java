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
	boolean draw_front, draw_text = false;
	String represents, age_group = "";
	public DataGraph(int start_x, int start_y, int point1, int point2, int length, int width, double rotation_angle, Color colour, String represents, String age_group) {
		this.start_x = start_x;
		this.start_y = start_y;
		this.point1 = point1;
		this.point2 = point2;
		this.length = length;
		this.width = width;
		this.rotation_angle = rotation_angle;
		this.colour = colour;
		this.represents = represents;
		this.age_group = age_group;
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
		if (draw_front) {
			g2.fillPolygon(this.front);
			g2.setColor(Color.BLACK);
			Line2D in_outline = new Line2D.Double(obr.x - 25, obr.y + 14, obr.x - 25, obr.y + 34);
			g2.draw(in_outline);
			Line2D out_outline = new Line2D.Double(obr.x - 25, obr.y + 34, obr.x, obr.y + 45);
			g2.draw(out_outline);
			g2.rotate(Math.toRadians(30), obr.x, obr.y + 50);
			g2.drawString(this.age_group, obr.x, obr.y + 50);
			g2.rotate(Math.toRadians(-30), obr.x, obr.y + 50);
		}
	}

	private void draw_poly(int x, int y, Graphics2D g2) {
		g2.setColor(Color.BLACK);
		g2.drawPolygon(this.top);
	}

	public void set_draw_text() {
		this.draw_text = true;
		return;
	}

	private void draw_text(Graphics2D g2) {
		Line2D in_outline = new Line2D.Double(ibl.x, ibl.y, ibl.x, ibl.y + 20);
		g2.draw(in_outline);
		Line2D out_outline = new Line2D.Double(ibl.x - 25, ibl.y + 30, ibl.x, ibl.y + 20);
		g2.draw(out_outline);
		// g2.draw(text_line);
		g2.rotate(Math.toRadians(-30), this.ibl.x - 55, this.start_y + 95);
		g2.drawString(this.represents, this.ibl.x - 55, this.start_y + 95);
		return;
	}

	public void paintComponent(Graphics g) {
		Graphics2D g2 = (Graphics2D) g.create();
		fill_poly(g2);
		draw_poly(this.start_x, this.start_y, g2);
		if (this.draw_text)
			draw_text(g2);
	}
}