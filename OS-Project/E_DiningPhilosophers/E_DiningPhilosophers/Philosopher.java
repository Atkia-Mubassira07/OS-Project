import java.util.Random;

public class Philosopher implements Runnable {
    private final int id;
    private final DiningServer server;
    private final Random random;
    private volatile boolean running = true; // Use a volatile flag to control the loop

    public Philosopher(int id, DiningServer server) {
        this.id = id;
        this.server = server;
        this.random = new Random();
    }

    private void think() throws InterruptedException {
        Thread.sleep(random.nextInt(1000));
    }

    private void eat() throws InterruptedException {
        Thread.sleep(random.nextInt(1000));
    }

    // Method to stop the philosopher's thread gracefully
    public void stop() {
        running = false;
    }

    @Override
    public void run() {
        try {
            while (running) { // Now the loop is controlled by the 'running' flag
                // Thinking state
                think();

                // Hungry state and trying to get forks
                server.takeForks(id);

                // Eating state
                eat();

                // Returning forks
                server.returnForks(id);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            // The loop will terminate when the thread is interrupted
        }
    }
}