import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Trebuchet {
    private static final String FILE_NAME = "calibration.input"; 



    private static String getFirstAndLastDigit(String line) {
        char firstDigit = '\0'; 
        char lastDigit = '\0'; 

        for (char c : line.toCharArray()) {
            if (Character.isDigit(c)) {
                if (firstDigit == '\0') {
                    firstDigit = c; 
                    lastDigit = c; 
                } else {
                    lastDigit = c; 
                }
            }
        }
        return "" + firstDigit + lastDigit; 
    }



    public static void main(String[] args) {
        try (Scanner sc = new Scanner(new File(FILE_NAME))) {
            int sum = 0; 
            while (sc.hasNextLine()) {
                String line = sc.nextLine(); 
                String digits = getFirstAndLastDigit(line); 
                int n = Integer.parseInt(digits);   
                sum += n; 
            }
            System.out.println(sum);
        } catch (FileNotFoundException e) {
            System.err.println("File " + FILE_NAME + " does not exist");
        }
    }
}
