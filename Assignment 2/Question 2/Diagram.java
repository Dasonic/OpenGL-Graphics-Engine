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
		f = new JFrame(filename);
		f.setSize((1000), (500));
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Outline outline = new Outline(500, 50, 200, 200, 10);
		outline.draw(f);

	}
}