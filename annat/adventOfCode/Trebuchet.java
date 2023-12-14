import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Trebuchet {
    private static final String FILE_NAME = "calibration.input"; 

    //automatteori

    private static char getDigitAt(String line, int i) {
        String suffix = line.substring(i); 

        if (line.charAt(i) == '0' || suffix.startsWith("zero"))   return '0'; 
        if (line.charAt(i) == '1' || suffix.startsWith("one"))    return '1'; 
        if (line.charAt(i) == '2' || suffix.startsWith("two"))    return '2'; 
        if (line.charAt(i) == '3' || suffix.startsWith("three"))  return '3'; 
        if (line.charAt(i) == '4' || suffix.startsWith("four"))   return '4'; 
        if (line.charAt(i) == '5' || suffix.startsWith("five"))   return '5'; 
        if (line.charAt(i) == '6' || suffix.startsWith("six"))    return '6'; 
        if (line.charAt(i) == '7' || suffix.startsWith("seven"))  return '7'; 
        if (line.charAt(i) == '8' || suffix.startsWith("eight"))  return '8'; 
        if (line.charAt(i) == '9' || suffix.startsWith("nine"))   return '9'; 
        return '\0'; 
    }

    private static String getFirstAndLastDigit(String line) {
        char firstDigit = '\0'; 
        char lastDigit = '\0'; 

        for (int i = 0; i < line.length(); i++) {
            char c = getDigitAt(line, i); 

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
