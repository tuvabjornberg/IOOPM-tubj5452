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
    private double averageTime; 

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
        this.averageTime = 0; 
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
        int waitTime = this.time - currentCustomer.getBornTime(); 
        if (waitTime > this.maxWaitTime)
        {
            this.maxWaitTime = waitTime;
        } 
        return waitTime; 
    }

    private void generateStatistics()
    {
        int customersServedStep = 0;
        int totalWaitTimeStep = 0;

        for (int i = 0; i < this.registersAmount; i++)
        {
            Register currentRegister = this.store.getRegister(i);
            if (currentRegister.isOpen())
            {
                Queue currentQueue = currentRegister.getQueue(); 
                currentRegister.hasCustomers();
                
                int groceriesAmount = 0; 

                int queueLength = currentRegister.getQueueLength();
                if (queueLength > 0)
                {
                    Customer currentCustomer = currentQueue.first();

                    groceriesAmount = currentCustomer.getGroceries();

                    int waitTime = this.generateWaitTime(currentCustomer);
                    totalWaitTimeStep += waitTime;
                    customersServedStep++;

                }

                this.averageTime = customersServedStep > 0 ? (double) totalWaitTimeStep / customersServedStep : 0;
                 
                System.out.println("    [" + groceriesAmount + "]" + " Customers in queue: " + queueLength);
            }
            else 
            {
                System.out.println("X   [ ]");         
            }
        }
        
        Customer doneCustomers[] = this.store.getDoneCustomers(); 
        this.customersServedTotal += doneCustomers.length;
        System.out.println("Number of customers checked out: " + this.customersServedTotal);
        System.out.println("Max wait time: " + this.maxWaitTime);
        System.out.println("Average wait time: " + this.averageTime); 
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