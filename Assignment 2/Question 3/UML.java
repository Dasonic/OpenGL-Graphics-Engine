import java.util.ArrayList;
import javax.swing.*;
import java.awt.*;
import java.lang.*;

public class UML {
    private static JFrame f;
    public static void main(String[] args) {
        // Read in the data
        // The name of the file to open.
        String fileName = args[0];
        ArrayList<Element> bottom_level;



    }
    private void readFile(String filename, ArrayList<Element> bottom_level) {
        // This will reference one line at a time
        String line = null;
        ArrayList<Element> all_classes;
        try {
            // FileReader reads text files in the default encoding.
            FileReader fileReader = new FileReader(fileName);

            // Always wrap FileReader in BufferedReader.
            BufferedReader bufferedReader = new BufferedReader(fileReader);

            while ((line = bufferedReader.readLine()) != null) {
                String tempLine[] = line.split(" ");
                if (tempLine[0].equals("class") {
                    String className = tempLine[1];
                    all_classes.add(new Element(className));
                    if (tempLine.length > 2)
                        all_classes[all_classes.size() - 1].add_extends(tempLine[3]);
                } else {
                    // Add method
                    if (line.contains("("))
                        all_classes[all_classes.size() - 1].add_method(line);
                    // Add variable
                    else
                        all_classes[all_classes.size() - 1].add_variable(line);
                }

            }

            // Always close files.
            bufferedReader.close();
        } catch (FileNotFoundException ex) {
            System.out.println("Unable to open file '" + fileName + "'");
        } catch (IOException ex) {
            System.out.println("Error reading file '" + fileName + "'");
        }
        return;
    }
}