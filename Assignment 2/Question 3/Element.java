import java.util.ArrayList;
import javax.swing.*;
import java.awt.*;
import java.awt.geom.Rectangle2D;

public class Element extends JComponent {
	private String name, extend_name;
	private ArrayList<String> variables;
	private ArrayList<String> methods;
	private Element parent;
	private ArrayList<Element> children;
	Font title_font = new Font("Helvetica", Font.BOLD, 16);
	Font body_font = new Font("Helvetica", Font.PLAIN, 16);
	private int x, y, width, height, total_height;

	public Element(String name) {
		this.name = name;
		this.extend_name = null;
		this.variables = new ArrayList<String>();
		this.methods = new ArrayList<String>();
		this.parent = null;
		this.children = new ArrayList<Element>();
		this.x = 0;
		this.y = 0;
		Canvas c = new Canvas();
		this.width = c.getFontMetrics(title_font).stringWidth(name) + 9;
		this.height = c.getFontMetrics(body_font).getHeight() + 5;
		this.total_height = 0;
		return;
	}

	public void set_x(int x) {
		this.x = x;
		return;
	}

	public void set_y(int y) {
		this.y = y;
		return;
	}

	public void add_variable(String variable) {
		Canvas c = new Canvas();
		int variable_width = c.getFontMetrics(body_font).stringWidth(variable) + 9;
		if (variable_width > 300) {
			String parts[] = variable.split(" ");
			String new_variable = "";
			for (String part : parts) {
				String temp_variable = new_variable;
				temp_variable += " " + part;
				int part_width = c.getFontMetrics(body_font).stringWidth(temp_variable) + 9;
				if (part_width > 300) { // If adding another word increase the part width over 40
					really_add("variable", new_variable, c);
					new_variable = ""; // Reset string
				} else {// If it didn't go over the limit, add the word
					new_variable += " " + part;
				}
			}
			really_add("variable", new_variable, c);
		} else {
			this.variables.add(variable);
			this.total_height += this.height;
			if (variable_width > this.width) {
				this.width = variable_width + 9;
			}
		}
		return;
	}

	public void add_method(String method) {
		Canvas c = new Canvas();
		int method_width = c.getFontMetrics(body_font).stringWidth(method) + 9;
		if (method_width > 300) {
			String parts[] = method.split(" ");
			String new_method = "";
			for (String part : parts) {
				String temp_method = new_method;
				temp_method += " " + part;
				int part_width = c.getFontMetrics(body_font).stringWidth(temp_method) + 9;
				if (part_width > 300) { // If adding another word increase the part width over 40
					really_add("method", new_method, c);
					new_method = ""; // Reset string
				} else {// If it didn't go over the limit, add the word
					new_method += " " + part;
				}
			}
			really_add("method", new_method, c);
		} else {
			this.methods.add(method);
			this.total_height += this.height;
			if (method_width > this.width) {
				this.width = method_width + 9;
			}
		}
		return;
	}

	private void really_add(String type, String line, Canvas c) {
		if (type.equals("method")) {
			this.methods.add(line); // Don't add the word and save it as a line
		} else if (type.equals("variable")) {extends JComponent
			this.variables.add(line); // Don't add the word and save it as a line
		}
		this.total_height += this.height;
		int part_width = c.getFontMetrics(body_font).stringWidth(line) + 9;
		if (part_width > this.width) // Check if the width of the box needs increases
			this.width = part_width;
		return;
	}

	public void add_extends_name(String extend) {
		this.extend_name = extend;
		return;
	}

	public void add_parent(Element parent) {
		this.parent = parent;
		return;
	}

	public void add_child(Element child) {
		this.children.add(child);
		return;
	}

	public String get_extends_name() {
		return this.extend_name;
	}

	public String get_name() {
		return this.name;
	}

	public ArrayList<Element> get_children() {
		return this.children;
	}

	public int get_width() {
		return this.width;
	}

	public int get_height() {
		return this.total_height;
	}

	public Element get_parent() {
		return this.parent;
	}

	public int get_x() {
		return this.x;
	}

	// public int get_middle_width() {
	// 	return this.x + 
	// }

	private ArrayList<String> get_parts(String string, int partitionSize) {
        ArrayList<String> parts = new ArrayList<String>();
        int len = string.length();
        for (int i=0; i<len; i+=partitionSize)
        {
            parts.add(string.substring(i, Math.min(len, i + partitionSize)));
        }
        return parts;
    }


	public void paintComponent(Graphics g) {
		Graphics2D g2 = (Graphics2D) g.create();
		g2.setFont(title_font);

		int variable_field_height = this.height * (variables.size() - 1);
		int method_field_height = this.height * (methods.size());
		// Draw title box
		g2.setColor(Color.WHITE);
		g2.fillRect(this.x, this.y, this.width, this.height); // Title background
		g2.fillRect(this.x, this.y + this.height, this.width, variable_field_height); // Variables background
		g2.fillRect(this.x, this.y + this.height + variable_field_height, this.width, method_field_height); // Methods background
		g2.setColor(Color.BLACK);
		g2.drawRect(this.x, this.y, this.width, this.height);
		g2.drawRect(this.x, this.y + this.height, this.width, variable_field_height);
		g2.drawRect(this.x, this.y + this.height + variable_field_height, this.width, method_field_height);
		
		//Draw text
		g2.drawString(name, x + 5, y + this.height - 4);
		g2.setFont(body_font);
		for (int i = 0; i < variables.size(); i++) {
			g2.drawString(variables.get(i), x + 5, (y + this.height * 2 + (this.height * i)) - 4);
		}
		for (int i = 0; i < methods.size(); i++) {
			g2.drawString(methods.get(i), x + 5, (y + this.height * 2 + variable_field_height + (this.height * i)) - 4);
		}

		if (children.size() > 0) {
			draw_extends_arrow(x, this.y + this.total_height, width, g2);
		}
		if (parent != null) {
			draw_extends_line(x, this.y, width, g2);
		}
	}

	private void draw_extends_arrow(int x, int y, int class_width, Graphics2D g2) {
		int width = 10;
		int height = 10;
		// Draw arrow
		int[] xCoords = {(x + class_width / 2 - width), (x + class_width / 2), (x + class_width / 2 + width)};
		int[] yCoords = {(y + height), y, (y + height)};
		g2.setColor(Color.WHITE);
		g2.fillPolygon(xCoords, yCoords, 3);
		g2.setColor(Color.BLACK);
		g2.drawPolygon(xCoords, yCoords, 3);
		// Draw line under arrow
		g2.drawLine(x + class_width / 2, y + height, x + class_width / 2, y + 30);
	}

	private void draw_extends_line(int x, int y, int class_width, Graphics2D g2) {
		g2.drawLine(x + class_width / 2, y, x + class_width / 2, y - 30);
		g2.drawLine(x + class_width / 2, y - 30, parent.get_x() + parent.get_width() / 2, y - 30);
	}
}
