import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class DiningServerImpl implements DiningServer {
    private enum State { THINKING, HUNGRY, EATING }

    private final Condition[] canEat;
    private final State[] philosopherStates;
    private final Lock monitor;

    public DiningServerImpl() {
        this.canEat = new Condition[5];
        this.philosopherStates = new State[5];
        this.monitor = new ReentrantLock();

        for (int i = 0; i < 5; i++) {
            this.philosopherStates[i] = State.THINKING;
            this.canEat[i] = monitor.newCondition();
        }
    }

    private int left(int i) {
        return (i + 4) % 5;
    }

    private int right(int i) {
        return (i + 1) % 5;
    }

    private void test(int i) {
        if (philosopherStates[i] == State.HUNGRY &&
                philosopherStates[left(i)] != State.EATING &&
                philosopherStates[right(i)] != State.EATING) {
            philosopherStates[i] = State.EATING;
            canEat[i].signal();
        }
    }

    @Override
    public void takeForks(int philosopherNumber) throws InterruptedException {
        monitor.lock();
        try {
            philosopherStates[philosopherNumber] = State.HUNGRY;
            System.out.println("Philosopher " + philosopherNumber + " is Hungry.");

            test(philosopherNumber);
            if (philosopherStates[philosopherNumber] != State.EATING) {
                canEat[philosopherNumber].await();
            }

            System.out.println("Philosopher " + philosopherNumber + " is Eating.");
        } finally {
            monitor.unlock();
        }
    }

    @Override
    public void returnForks(int philosopherNumber) {
        monitor.lock();
        try {
            philosopherStates[philosopherNumber] = State.THINKING;
            System.out.println("Philosopher " + philosopherNumber + " is Thinking.");

            test(left(philosopherNumber));
            test(right(philosopherNumber));
        } finally {
            monitor.unlock();
        }
    }
}