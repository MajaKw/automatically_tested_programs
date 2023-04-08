package pl.edu.uj.tcs.oop.labs.lab07;
import java.util.*;
import java.util.function.Function;
import java.util.stream.Stream;

public class ArraysAndLambdas {

    @SafeVarargs
    public static <T> Function<Integer, T> arrayToLambda(T ... varArgs) {
        Function<Integer, T> YourFunction;
        YourFunction = (k) -> varArgs[k];
        return YourFunction;
    }

    @SafeVarargs
    public static <T> Function<T, Integer> arrayInverseToLambda(T ... varArgs) {
        Function<T, Integer> YourFunction;
        List<T> list = Arrays.asList(varArgs);
        YourFunction = k -> list.indexOf(k);
        return YourFunction;
    }
}
