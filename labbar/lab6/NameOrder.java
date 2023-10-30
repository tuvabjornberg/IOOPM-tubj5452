import java.util.Scanner;

public class NameOrder {
    
    public static void main(String[] args) {
        
        Scanner sc = new Scanner(System.in);
        System.out.print("First name: ");
        String name1 = sc.nextLine();
        System.out.print("Second name: ");
        String name2 = sc.nextLine();
        
        int compared = name1.compareTo(name2); 
        if (compared < 0)
        {
            System.out.println(name1 + "\n" + name2); 
        }
        else if (compared > 0)
        {
            System.out.println(name2 + "\n" + name1); 
        }
        else 
        {
            System.out.println("The names are equal"); 
        }
    }
}