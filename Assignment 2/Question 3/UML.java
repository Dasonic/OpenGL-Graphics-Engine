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
		for (Element element : bottom_level) {
			System.out.println(element.get_name());
			for (Element subelement: element.get_children()) {
				System.out.println("-->" + subelement.get_name());
				for (Element subsubelement: subelement.get_children()) {
					System.out.println("---->" + subsubelement.get_name());
				}
			}
		}
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
}
