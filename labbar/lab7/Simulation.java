import java.util.Random; 
public class Simulation
{
    private Store store; 
    private int time; 
    private int intensity; 
    private int maxGroceries; 
    private int thresholdForNewRegister; 

    private int customersServedTotal; 
    private int registersAmount; 
    private int maxWaitTime; 
    private double averageWaitTime; 
    private int totalWaitTime;

    public Simulation(int registersAmount, int intensity, int maxGroceries, int thresholdForNewRegister)
    {
        this.store = new Store(registersAmount); 
        this.time = 0; 
        this.intensity = intensity; 
        this.maxGroceries = maxGroceries; 
        this.thresholdForNewRegister = thresholdForNewRegister;

        this.customersServedTotal = 0;
        this.registersAmount = registersAmount; 
        this.maxWaitTime = 0;
        this.averageWaitTime = 0; 
        this.totalWaitTime = 0; 
    }

    private void generateNewCustomer()
    {
        Random randomInt = new Random(); 
        int randIntensity = randomInt.nextInt(100); 
        if (randIntensity < this.intensity)
        {
            Random randomMax = new Random(); 
            int randMaxGroceries = randomMax.nextInt(this.maxGroceries); 
            this.store.newCustomer(new Customer(this.time, randMaxGroceries));   
        }
    }

    private void openNewRegister()
    {
        if (this.store.getAverageQueueLength() > thresholdForNewRegister)
        {
            this.store.openNewRegister();
        }
    }
    
    private int generateWaitTime(Customer currentCustomer)
    {
        return this.time - currentCustomer.getBornTime();
    }

    private void generateMaxWaitTime(Customer currentCustomer)
    {
        int waitTime = generateWaitTime(currentCustomer); 
        if (waitTime > this.maxWaitTime)
        {
            this.maxWaitTime = waitTime;
        } 
    }

    private void generateTotalWaitTime(Register currentRegister, Customer currentCustomer)
    {
        if (currentRegister.currentCustomerIsDone())
        {
            this.totalWaitTime += generateWaitTime(currentCustomer); 
        }
    }

    private void generateStatistics()
    {
        for (int i = 0; i < this.registersAmount; i++)
        {
            Register currentRegister = this.store.getRegister(i);
            if (currentRegister.isOpen())
            {                
                int groceriesAmount = 0; 

                if (currentRegister.hasCustomers())
                {
                    Customer currentCustomer = currentRegister.getQueue().first();

                    groceriesAmount = currentCustomer.getGroceries();

                    this.generateMaxWaitTime(currentCustomer);
                    this.generateTotalWaitTime(currentRegister, currentCustomer); 
                }

                int queueLength = currentRegister.getQueueLength();
                System.out.println("    [" + groceriesAmount + "]" + " Customers in queue: " + queueLength);
            }
            else 
            {
                System.out.println("X   [ ]");         
            }
        }

        Customer doneCustomers[] = this.store.getDoneCustomers(); 
        this.customersServedTotal += doneCustomers.length;

        this.averageWaitTime = customersServedTotal > 0 ? (double) totalWaitTime / (double) customersServedTotal : 0;

        System.out.println("Number of customers checked out: " + this.customersServedTotal);
        System.out.println("Max wait time: " + this.maxWaitTime);
        System.out.printf("Average wait time: %.2f\n", this.averageWaitTime); 
    }

    public void step()
    {
        this.store.step();
        this.generateNewCustomer(); 
        this.openNewRegister();
        this.generateStatistics();

        this.time++; 
    }
}