import java.util.ArrayList;
import javax.swing.*;
import java.awt.*;
import java.io.*;

public class Diagram {
	private static JFrame f;
	public static void main(String[] args) {
		String fileName = args[0];
		double[][] data = new double[5][41];

		readFile(fileName, data);

		set_up_GUI(fileName, data);

		// for (int i = 0; i < 41; i++) {
		// 	System.out.print(data[2][i] + " ");
		// }
	}

	// Reads data from a file and stores it in an arraylist
	private static void readFile(String file_name, double[][] data) {
		// This will reference one line at a time
		String line = null;
		try {
			// FileReader reads text files in the default encoding.
			FileReader fileReader = new FileReader(file_name);

			// Always wrap FileReader in BufferedReader.
			BufferedReader bufferedReader = new BufferedReader(fileReader);
			String previous_line_year = "1978";
			int year = 0;
			ArrayList<ArrayList<Double>> month = new ArrayList<ArrayList<Double>>();
			for (int i = 0; i < 5; i++) { // Init the array lists
				month.add(new ArrayList<Double>());
			}
			while ((line = bufferedReader.readLine()) != null) {
				String tempLine[] = line.split(" ");
				if (tempLine[1].equals(previous_line_year)) { // If its the same year
					for (int i = 0; i < 5; i++) { // Add for each age group
						// System.out.print(Double.parseDouble(tempLine[i + 2]) + " ");
						month.get(i).add(Double.parseDouble(tempLine[i + 2]));
					}
				} else { // New year
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
					year++;
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

	private static void set_up_GUI(String filename, double[][] data) {
		Color colour_array[] = {Color.RED, Color.MAGENTA, Color.ORANGE, Color.YELLOW, Color.GREEN, Color.CYAN};
		int length = 400;
		int height = 400;
		int width = 20;
		f = new JFrame(filename);
		f.setSize((1000), (1000));
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		// Figure out 0, 0 for each graph section
		int data_width = (int)(height / data.length);
		int data_length = (int)(length / (data[0].length - 1));
		double angle_cos = Math.cos(Math.toRadians(-30));
		double angle_sin = Math.sin(Math.toRadians(-30));
		for (int i = data.length - 1; i >= 0; i--) {
			for (int j = 0; j < data[0].length - 1; j++){
				int graph_x = 500 - (int)(angle_cos * ((double)(data_width * i) - (double)(data_length * j)));
				int graph_y = 50 + height  - (int)(angle_sin * ((double)(data_width * i) + (double)(data_length * j)));
				DataGraph data_graph = new DataGraph(graph_x, graph_y, (int)data[i][j], (int)data[i][j + 1], data_length, data_width, 30, colour_array[i]);
				f.add(data_graph);
				f.setVisible(true);
				// break;
			}
			// break;
		}
		Outline outline = new Outline(500, 50, length, height, width, 11);
		outline.draw(f);
	}
}