package pl.edu.uj.tcs.oop.labs.lab08;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.atomic.AtomicInteger;

public class Divisors {

    /**
     * Number of threads to use in countDivisors().
     */
    public static int THREAD_NUM = 1;
//    static AtomicInteger counter = new AtomicInteger(0);


    /**
     * Count number of divisors in range [from, to] (inclusive).
     */
    private static int countDivisorsInRange(long number, long from, long to){
        int counter = 0;
        for(long cur = from; cur <= to; cur++){
//            System.out.println("iter: " + cur + " modulo: " + number%cur);
            if(number%cur == 0) counter++;
        }
        return counter;
    }

    /**
     * Count number of divisors of a given number.
     */
    public static int countDivisors(long number){
        AtomicInteger counter = new AtomicInteger(0);
        int divNum = 0;

        // find the highest number below the sqrt of the number
        long numRootLower = (long) Math.sqrt(number-1);
        int thr = THREAD_NUM;
        if (THREAD_NUM > Math.sqrt(number-1)){
            THREAD_NUM = (int) Math.sqrt(number-1);
        }
//        number = numRootLower;

        // count number of divisors below sqrt(n) and multiply it by 2
        // - every divisor d < sqrt(n) has corresponding divisor n/d > sqrt(n)
        // TODO: make it parallel!
        long segment = numRootLower/THREAD_NUM;
        long start = 0, end = 0;
        final long ROOT = numRootLower;
        final long NUMBER = number;
        Thread[] threads = new Thread[THREAD_NUM];

        for(int i = 0; i<THREAD_NUM; ++i){
            final int MULT = i;
            final long START = end+1;
            final long END ;
            end = START + segment;
            if(i == THREAD_NUM - 1){
                end = ROOT;
            }
                END = end;
//            end = START + segment*i;
            threads[i] = new Thread(()->{
                int add = countDivisorsInRange(NUMBER, START, END);
//                System.out.print("Add: " + add + "\n");
                add = add*2;
//                System.out.print("Add: " + add + "\n");
                counter.getAndAdd(add);
            });
            threads[i].start();

        }
        for(int i = 0; i<THREAD_NUM; ++i){
            try{
                threads[i].join();
            }catch ( InterruptedException e) {

            }
        }

//
//        System.out.println("counter.get(): " + counter.get());
        divNum = counter.get();

        // finally, check if number is square (i.e. sqrt(n) is a divisor)
//        System.out.println("numRootLower: " + numRootLower + " numebr: " + number + "\n");
        if((numRootLower+1)*(numRootLower+1) == number){
//            System.out.println(" hdheiw");
            ++divNum;
        }
//        System.out.println("RESULT: " + divNum);
        THREAD_NUM = thr;
        return divNum;
    }

    // --- TESTS ---

    public static void measureCountDivisors(long number){
        long start = System.currentTimeMillis();
        int result = countDivisors(number);
        long end = System.currentTimeMillis();
        System.out.println(String.format("number of divisors of %18d is: %5d; \t(time = %4d ms)", number, result, end-start));
    }

    public static void main(String[] args){
        measureCountDivisors(9L); // 3*3 -> 3
        measureCountDivisors(143L); // 11*13 -> 4
        measureCountDivisors(1024L); // 2^10 -> 11
        measureCountDivisors(179426407L); // prime -> 2
        measureCountDivisors(1023456787654L); // ... -> 16
        measureCountDivisors(102345678765432L); // ... -> 256
        measureCountDivisors(10234567876543201L); // prime -> 2
        measureCountDivisors(10234567876543203L); // ... -> 4
        measureCountDivisors(102345678765432035L); // ... -> 8
        measureCountDivisors(402345678765432035L); // ... -> 16
        System.out.println("...give me more threads...");
        Divisors.THREAD_NUM = 4;
        measureCountDivisors(9L);
        measureCountDivisors(10234567876543201L); // prime -> 2
        measureCountDivisors(10234567876543203L); // ... -> 4
        measureCountDivisors(102345678765432035L); // ... -> 8
        measureCountDivisors(402345678765432035L); // ... -> 16
    }
}
