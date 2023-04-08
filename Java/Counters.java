package pl.edu.uj.tcs.oop.labs.lab08;

import java.util.concurrent.atomic.AtomicInteger;

public class Counters {

    public interface Counter {
        int get();
        void inc();
    }

    /**
     * Standard counter - not ready for multithreaded usage.
     */
    static class CounterA implements Counter {
        int counter = 0;
        @Override
        public int get() { return counter; }
        @Override
        public void inc() { counter++; }
    }

    /**
     * Concurrent counter - summing all inc() operations (from all threads).
     */
    static class CounterB implements Counter {
        // TODO - changes only in lines with "###"
        static AtomicInteger counter = new AtomicInteger(-1);
        @Override
        public int get() {
            return counter.get();
        }
        @Override
        public void inc() {
            counter.getAndIncrement();
        }
    }

    /**
     * Thread counter - summing inc() operations only for the current thread.
     */
    static class CounterC implements Counter {
        // TODO - changes only in lines with "###"
        // ###
//        ThreadLocal threadLocal = new ThreadLocal();
        ThreadLocal<Integer> threadLocal = ThreadLocal.withInitial(() -> 0);
        @Override
        public int get() {
            return threadLocal.get();
        }
        @Override
        public void inc() {
            threadLocal.set((Integer) threadLocal.get()+1);
        }
    }
}
