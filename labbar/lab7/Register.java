
public class Register
{
    private boolean open; 
    private Queue queue; 

    public Register()
    {
        this.open = false; 
        this.queue = new Queue(); 
    }

    public void open()
    {
        this.open = true; 
    }

    public void close()
    {
        this.open = false;
    }

    public boolean isOpen()
    {
        return this.open; 
    }

    public void registerStep()
    {
        this.queue.first().serve();
    }

    public boolean hasCustomers()
    {
        return this.queue.length() != 0; 
    }

    public boolean currentCustomerIsDone()
    {
        return this.queue.first().isDone(); 
    }

    public void addToQueue(Customer c)
    {
        this.queue.enqueue(c);
    }

    public Customer removeCurrentCustomer()
    {
        return this.queue.dequeue(); 
    }

    public int getQueueLength()
    {
        return this.queue.length(); 
    }

    public static void main(String[] args)
    {
        Register register = new Register(); 
        Customer firstCustomer = new Customer(); 
        Customer secondCustomer = new Customer(); 
        Customer thirdCustomer = new Customer();

        firstCustomer.addGroceries(3);
        secondCustomer.addGroceries(4);
        thirdCustomer.addGroceries(5);

        register.addToQueue(firstCustomer); 
        register.addToQueue(secondCustomer); 
        register.addToQueue(thirdCustomer); 

        System.out.println("Queue length: " + register.getQueueLength());
        System.out.println("The register is open: " + register.isOpen()); 

        register.open(); 
        System.out.println("The register is open: " + register.isOpen()); 
        System.out.println("The queue has customers: " + register.hasCustomers());
        System.out.println("The current customer is done: " + register.currentCustomerIsDone()); 

        register.registerStep();
        register.registerStep();
        register.registerStep();

        System.out.println("The current customer is done: " + register.currentCustomerIsDone()); 

        System.out.println(register.removeCurrentCustomer()); 
        System.out.println("The queue has customers: " + register.hasCustomers());
        System.out.println("The current customer is done: " + register.currentCustomerIsDone()); 

        register.close(); 
        System.out.println("The register is open: " + register.isOpen()); 
    }
}
