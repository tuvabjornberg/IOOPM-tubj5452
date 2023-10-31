
public class Store
{
    private Register registers[]; 

    public Store(int registersAmount)
    {
        if (registersAmount <= 0)
        {
            throw new IllegalArgumentException("At least 1 register needs to exist"); 
        }

        registers = new Register[registersAmount]; 

        for (int i = 0; i < registersAmount; i ++)
        {
            registers[i] = new Register(); 
        }
        registers[0].open();
    }

    public Register getRegister(int index)
    {
        return this.registers[index]; 
    }

    public double getAverageQueueLength()
    {
        int totalLength = 0;
        int openRegisters = 0; 

        for (Register r : this.registers)
        {
            if (r.isOpen())
            {
                openRegisters++; 
                totalLength += r.getQueueLength(); 
            }
        }
        return (double) totalLength / openRegisters; 
    }

    public void newCustomer(Customer c)
    {
        Register shortestR = this.registers[0]; 

        for (Register r : this.registers)
        {
            if (r.isOpen())
            {
                if (r.getQueueLength() < shortestR.getQueueLength())
                {
                    shortestR = r; 
                }
            }
        }
        shortestR.addToQueue(c);
    }

    public void step()
    {
        for (Register r : this.registers)
        {
            if (r.isOpen() && r.hasCustomers())
            {
                r.step();
            }
        }
    }

    public void openNewRegister()
    {
        for (Register r : this.registers)
        {
            if (!r.isOpen())
            {
                r.open();
                return; 
            }
        }
        System.out.println("No registers left to open");
    }

    public Customer[] getDoneCustomers()
    {
        Queue doneCustomersQ = new Queue(); 

        for (Register r : this.registers)
        {
            if (r.isOpen())
            {
                while (r.hasCustomers() && r.currentCustomerIsDone())
                {
                    doneCustomersQ.enqueue(r.removeCurrentCustomer());
                }
            }
        } 

        Customer[] doneCustomers = new Customer[doneCustomersQ.length()];
        int i = 0; 
        while (doneCustomersQ.length() > 0)
        {
            doneCustomers[i++] = doneCustomersQ.dequeue(); 
        }

        return doneCustomers; 
    }

    public static void main(String[] args)
    {
        Store store = new Store(2); 
        Customer firstCustomer = new Customer(0, 3); 
        Customer secondCustomer = new Customer(0, 4); 
        Customer thirdCustomer = new Customer(0, 5);

        store.newCustomer(firstCustomer);
        store.newCustomer(secondCustomer);
        store.newCustomer(thirdCustomer);

        System.out.println("Average queue length: " + store.getAverageQueueLength());
        
        store.openNewRegister();

        store.step();
        store.step();
        store.step();

        Customer[] doneCustomers = store.getDoneCustomers();
        System.out.println("Done customers: ");
        for (Customer customer : doneCustomers) 
        {
            System.out.println(customer);
        }
    }
}