import java.util.Scanner;

 public class PairOfDice
 {
    private Die firstDice; 
    private Die secondDice; 

    public PairOfDice(int sides) {
        this.firstDice = new Die(sides); 
        this.secondDice = new Die(sides); 
    }


    public static void main(String [] args) 
    {
    Scanner sc = new Scanner(System.in);
    System.out.print("Number of sides of the dice: ");
    int sides = sc.nextInt();
    PairOfDice p = new PairOfDice(sides); 

    System.out.println("Alea iacta est dice 1: " + p.firstDice.roll() + " and alea iacta est dice 2: " + p.secondDice.roll());

    }
 }