import java.util.ArrayList;
import javax.swing.*;
import java.awt.*;
import java.io.*;

public class Diagram {
	private static JFrame f;
	public static void main(String[] args) {
		String fileName = args[0];
		double[][] data = new double[5][41];
		String years[] = new String[41];
		double max_value = 0;
		max_value = readFile(fileName, data, years);
		// System.out.println(max_value);

		set_up_GUI(fileName, data, max_value, years);
	}

	// Reads data from a file and stores it in an arraylist
	private static double readFile(String file_name, double[][] data, String[] years) {
		double max_value = 0;
		// This will reference one line at a time
		String line = null;
		try {
			// FileReader reads text files in the default encoding.
			FileReader fileReader = new FileReader(file_name);

			// Always wrap FileReader in BufferedReader.
			BufferedReader bufferedReader = new BufferedReader(fileReader);
			String previous_line_year = "1978";
			years[0] = "1978";
			int year = 40;
			ArrayList<ArrayList<Double>> month = new ArrayList<ArrayList<Double>>();
			for (int i = 0; i < 5; i++) { // Init the array lists
				month.add(new ArrayList<Double>());
			}
			while ((line = bufferedReader.readLine()) != null) {
				String tempLine[] = line.split(" ");
				// System.out.println(tempLine[1]);
				if (!tempLine[1].equals(previous_line_year)) { // New year
					// Average last year and add to final array
					for (int i = 0; i < 5; i++) { // Add for each age group
						double total = 0;
						for (int j = 0; j < month.get(i).size(); j++) {
							total += month.get(i).get(j);
						}
						data[i][year] = total/month.get(0).size();
					}
					// Clear variables
					for (int i = 0; i < 5; i++) {
						month.get(i).clear();
					}
					// Add this years variables
					previous_line_year = tempLine[1];
					years[year] = tempLine[1];
					year--;
				}
				for (int i = 0; i < 5; i++) { // Add for each age group
					double data_as_double = Double.parseDouble(tempLine[i + 2]);
					month.get(i).add(data_as_double);
					if (max_value < data_as_double)
						max_value = data_as_double;
				}
			}
			// System.out.println(year);
			// Always close files.
			bufferedReader.close();
		} catch (FileNotFoundException ex) {
			System.err.println("Unable to open file '" + file_name + "'");
		} catch (IOException ex) {
			System.err.println("Error reading file '" + file_name + "'");
		}
		return max_value;
	}

	private static void set_up_GUI(String filename, double[][] data, double max_value, String[] years) {
		Color colour_array[] = {Color.RED, Color.MAGENTA, Color.ORANGE, Color.YELLOW, Color.GREEN, Color.CYAN};
		int length = 400;
		int height = (int)(max_value + 0.5);
		int width = 20;
		f = new JFrame(filename);
		f.setSize((1000), (1000));
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		// Figure out 0, 0 for each graph section
		int data_width = (int)(length / data.length);
		int data_length = (int)(length / (data[0].length - 2));
		double angle_cos = Math.cos(Math.toRadians(-30));
		double angle_sin = Math.sin(Math.toRadians(-30));
		boolean draw_text = true;
		String ages[] = {"15-24", "25-34", "35-44", "45-54", "55+"};
		for (int i = data.length - 1; i >= 0; i--) {
			for (int j = 0; j < data[0].length - 1; j++){
				int graph_x = 500 - (int)(angle_cos * ((double)(data_width * i) - (double)(data_length * j)));
				int graph_y = 100 + height  - (int)(angle_sin * ((double)(data_width * i) + (double)(data_length * j)));
				DataGraph data_graph = new DataGraph(graph_x, graph_y, (int)data[i][j], (int)data[i][j + 1], data_length, data_width, 30, colour_array[i], years[j], ages[i]);
				if ((j + 2) >= data[0].length)
					data_graph.set_draw_front();
				if (draw_text)
					data_graph.set_draw_text();
				f.add(data_graph);
				f.setVisible(true);
				// break;
			}
			draw_text = false;
			// break;
		}
		Outline outline = new Outline(500, 100, length, height, width, 13);
		outline.draw(f);

		// Draw titles and labels
		Title main_title = new Title("Ratio of Underemployed Persons", 300, 50, new Font("Helvetica", Font.BOLD, 22));
		f.add(main_title);
		f.setVisible(true);

		Title x_axis_title = new Title("Year", 90, 850, new Font("Helvetica", Font.PLAIN, 18));
		f.add(x_axis_title);
		f.setVisible(true);

		Title y_axis_title = new Title("Ratio", 900, 500, new Font("Helvetica", Font.PLAIN, 18));
		f.add(y_axis_title);
		f.setVisible(true);

		Title z_axis_title = new Title("Age Group", 800, 850, new Font("Helvetica", Font.PLAIN, 18));
		f.add(z_axis_title);
		f.setVisible(true);
	}
}