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
		this.total_height = height;
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
		this.variables.add(variable);
		Canvas c = new Canvas();
		int variable_width = c.getFontMetrics(body_font).stringWidth(variable) + 9;
		if (variable_width > this.width) {
			this.width = variable_width + 9;
		}
		this.total_height += this.height;
		return;
	}

	public void add_method(String method) {
		this.methods.add(method);
		Canvas c = new Canvas();
		int method_width = c.getFontMetrics(body_font).stringWidth(method) + 9;
		if (method_width > this.width) {
			this.width = method_width + 9;
		}
		this.total_height += this.height;
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
	}
}
