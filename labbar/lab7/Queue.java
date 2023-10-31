
public class Queue 
{
    private class Node
    {
        Customer element; 
        Node next;

        public Node(Customer element)
        {
            this.element = element; 
            this.next = null; 
        }
    }

    private Node first; 
    private Node last; 
    private int length; 

    public Queue()
    {
        this.first = null; 
        this.last = null;
        this.length = 0; 
    }

    public int length()
    {
        return this.length; 
    }

    public void enqueue(Customer c)
    {
        Node newNode = new Node(c); 

        if (this.length == 0) //if empty queue
        {
            this.first = newNode; 
        }
        else 
        {
            this.last.next = newNode; 
        }

        this.last = newNode; 
        this.length++;    
    }

    public Customer dequeue()
    {
        if (this.length == 0)
        {
            System.out.println("Empty queue");
            throw new EmptyQueueException(); 
        }
       
        Customer customerDequeued = this.first.element; 

        this.first = this.first.next; 
        this.length--; 

        if (this.length == 0)
        {
            this.last = null; 
        }

        return customerDequeued; 
       
    }

    public Customer first()
    {
        if (this.length != 0)
        {
            return this.first.element; 
        }
        else 
        {
            System.out.println("Empty queue");
            throw new EmptyQueueException(); 
        }
    }

    public static void main(String[] args)
    {
        Queue queue = new Queue(); 

        queue.enqueue(new Customer(0, 3)); 
        queue.enqueue(new Customer(0, 4)); 
        queue.enqueue(new Customer(0, 5)); 

        System.out.println("Queue length: " + queue.length);
        System.out.println(queue.first.element);

        System.out.println(queue.dequeue()); 
        System.out.println(queue.dequeue()); 
        System.out.println(queue.dequeue()); 

        System.out.println("Queue length: " + queue.length);

    }
}