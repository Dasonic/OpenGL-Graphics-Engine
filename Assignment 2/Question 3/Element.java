import java.util.ArrayList;
import javax.swing.*;
import java.awt.*;

public class Element extends JComponent {
    private String name, extend;
    private ArrayList<String> variables;
    private ArrayList<String> methods;
    private int x, y, level;

    public Element(String name) {
        this.name = name;
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

    public void add_extends(String extend) {
        this.extend = extend;
        return;
    }

    public String get_extends() {
        return this.extend();
    }
}