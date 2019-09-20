import java.util.ArrayList;
import java.util.ListIterator;

import javax.swing.*;
import java.awt.*;
import java.lang.*;
import java.io.*;

public class UML {
	private static JFrame f;
	public static void main(String[] args) {
		// Read in the data
		// The name of the file to open.
		String fileName = args[0];
		ArrayList<Element> bottom_level = new ArrayList<Element>();
		ArrayList<Element> all_classes = new ArrayList<Element>();
		readFile(fileName, all_classes);
		organise_data(all_classes, bottom_level);
		set_up_GUI(fileName, bottom_level);
	}
	
	// Reads data from a file and stores it in an arraylist
	private static void readFile(String file_name, ArrayList<Element> all_classes) {
		// This will reference one line at a time
		String line = null;
		try {
			// FileReader reads text files in the default encoding.
			FileReader fileReader = new FileReader(file_name);

			// Always wrap FileReader in BufferedReader.
			BufferedReader bufferedReader = new BufferedReader(fileReader);

			while ((line = bufferedReader.readLine()) != null) {
				String tempLine[] = line.split(" ");
				if (tempLine[0].equals("class")) {
					String className = tempLine[1];
					all_classes.add(new Element(className));
					if (tempLine.length > 2)
						all_classes.get(all_classes.size() - 1).add_extends_name(tempLine[3]);
				} else {
					// Add method
					if (line.contains("("))
						all_classes.get(all_classes.size() - 1).add_method(line);
					// Add variable
					else
						all_classes.get(all_classes.size() - 1).add_variable(line);
				}
			}
			// Always close files.
			bufferedReader.close();
		} catch (FileNotFoundException ex) {
			System.err.println("Unable to open file '" + file_name + "'");
		} catch (IOException ex) {
			System.err.println("Error reading file '" + file_name + "'");
		}
		return;
	}
	
	// Stores the data in a way the program can use later
	public static void organise_data(ArrayList<Element> all_classes, ArrayList<Element> bottom_level) {
		ArrayList<Element> missing_classes = new ArrayList<Element>();
		for (Element curr_class : all_classes) {
			if (curr_class.get_extends_name() == null) // If it extends nothing
				bottom_level.add(curr_class);
			else { // If it extends a class
				// Check if the parent class has been added
				int matching_index = find_matching_class(curr_class.get_extends_name(), all_classes);
				if (matching_index != -1) {
					curr_class.add_parent(all_classes.get(matching_index)); // Set the parent object
					all_classes.get(matching_index).add_child(curr_class); // Set the child object
				}
				// If the parent class hasn't been added
				else {
					missing_classes.add(curr_class);
				}
			}
		}
	}

	// Finds a class that's name matches the given name
	private static int find_matching_class(String class_name, ArrayList<Element> all_classes) {
		for (int i = 0; i < all_classes.size(); i++) {
			if (all_classes.get(i).get_name().equals(class_name))
				return i;
		}
		return -1;
	}

	private static void set_up_GUI(String filename, ArrayList<Element> all_classes) {
		f = new JFrame(filename);
		f.setSize((1000), (500));
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			
		// Print Object Box
		int x = 40;
		int y = 40;
		// Draw bottom level classes
		for (Element curr_class : all_classes) {
			x = draw_class(curr_class, x, y);
		}
	}

	private static int draw_class(Element curr_class, int x, int y) {
		// System.out.println("Drawing " + curr_class.get_name() + " at " + x + ", " + y);
		curr_class.set_x(x);
		curr_class.set_y(y);
		f.add(curr_class);
		f.setVisible(true);
		if (curr_class.get_children().size() > 0) {
			for (Element sub_class: curr_class.get_children()) {
				x = draw_class(sub_class, x, y + curr_class.get_height() + 60);
			}
		} else if (curr_class.get_width() < curr_class.get_parent().get_width()) {
			x += curr_class.get_parent().get_width() + 10;
		} else {
			x += curr_class.get_width() + 10;
		}
		return x;
	}
}
