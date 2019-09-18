import java.util.ArrayList;
import javax.swing.*;
import java.awt.*;

public class Element extends JComponent {
	private String name, extend_name;
	private ArrayList<String> variables;
	private ArrayList<String> methods;
	private Element parent;
	private ArrayList<Element> children;
	private int x, y, level;

	public Element(String name) {
		this.name = name;
		this.extend_name = null;
		this.variables = new ArrayList<String>();
		this.methods = new ArrayList<String>();
		this.parent = null;
		this.children = new ArrayList<Element>();
		this.x = 0;
		this.y = 0;
		this.level = 0;
		return;
	}

	public void add_variable(String variable) {
		this.variables.add(variable);
		return;
	}

	public void add_method(String method) {
		this.methods.add(method);
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
}
