
public class Customer
{
    private int bornTime; 
    private int groceries; 

    public Customer(int bornTime, int groceries)
    {
        this.bornTime = bornTime;
        this.groceries = groceries; 
    }

    public void serve()
    {
        if (this.groceries > 0)
        {        
            this.groceries--; 
        }

    }

    public boolean isDone()
    {
       return this.groceries == 0; 
    }

    public void addGroceries(int groceries)
    {
        this.groceries += groceries;
    }

    public int getGroceries()
    {
        return this.groceries; 
    }

    public int getBornTime()
    {
        return this.bornTime; 
    }

    public static void main(String[] args)
    {
        Customer customer = new Customer(0, 3);

        for (int i = 0; i < 3; i++)
        {
            customer.serve();
        }

        if(customer.isDone()) 
        {
            System.out.println("The customer is done, just as expected!");
        } 
        else 
        {
            System.out.println("The customer is not done, but should be...");
        }
    }
}