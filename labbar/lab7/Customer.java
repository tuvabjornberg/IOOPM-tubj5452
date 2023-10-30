
public class Customer
{
    private int bornTime; 
    private int groceries; 

    public Customer()
    {
        this.bornTime = 0;
        this.groceries = 0; 
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

    public static void main(String[] args)
    {
        Customer customer = new Customer();
        customer.addGroceries(3); 

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