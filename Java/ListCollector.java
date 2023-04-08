package pl.edu.uj.tcs.oop.labs.lab07;

import java.util.*;
import java.util.function.BiConsumer;
import java.util.function.BinaryOperator;
import java.util.function.Function;
import java.util.function.Supplier;
import java.util.stream.Collector;
import java.util.stream.Stream;

public class ListCollector {

    public static <T extends Comparable<T>>
    Collector< List<T>,Map<T, HashSet<T>>, Map<T, HashSet<T>> > collectByMin(){
        return new Collector<List<T>, Map<T, HashSet<T>>, Map<T, HashSet<T>>>() {
            @Override
            public Supplier<Map<T, HashSet<T>>> supplier() {
                return HashMap::new;
            }

            @Override
            public BiConsumer<Map<T, HashSet<T>>, List<T>> accumulator() {
                return (map, list) -> {
                    Set<Integer> targetSet = new HashSet<>(list.toArray().length);
                    HashSet<T> u = map.putIfAbsent(Collections.min(list), new HashSet<T>(list));
                    if (u != null) map.get(Collections.min(list)).addAll(list);
                };
            }

            @Override
            public BinaryOperator<Map<T, HashSet<T>>> combiner() {
                return null;
            }

            @Override
            public Function<Map<T, HashSet<T>>, Map<T, HashSet<T>>> finisher() {
                return map -> map;
            }

            @Override
            public Set<Characteristics> characteristics() {
                return EnumSet.of(Characteristics.UNORDERED);
            }
        };
    }

    public static void main(String[] args) {
        System.out.println(
                Stream.of(List.of(1,2,3,4),
                          List.of(2,3,4),
                          List.of(1,3,5,7),
                          List.of(2,22)
                ).collect(collectByMin())
        );
    }

}
