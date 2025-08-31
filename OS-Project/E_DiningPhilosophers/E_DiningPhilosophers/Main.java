public class Main {
    public static void main(String[] args) {
        DiningServer server = new DiningServerImpl();
        Philosopher[] philosophers = new Philosopher[5];
        Thread[] threads = new Thread[5];

        for (int i = 0; i < 5; i++) {
            philosophers[i] = new Philosopher(i, server);
            threads[i] = new Thread(philosophers[i]);
            threads[i].start();
        }

        // Let the simulation run for a while
        try {
            System.out.println("Simulation running... Press Ctrl+C to exit.");
            // Sleep for 30 seconds before attempting to stop the threads
            Thread.sleep(30000);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        // Gracefully stop all philosopher threads
        System.out.println("Stopping simulation.");
        for (Philosopher p : philosophers) {
            p.stop();
        }

        // Wait for all philosopher threads to finish
        for (Thread thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        System.out.println("Simulation stopped.");
    }
}