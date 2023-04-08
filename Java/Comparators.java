package pl.edu.uj.tcs.oop.labs.lab05;

import java.util.Collection;
import java.util.Comparator;
import java.util.Iterator;


public class Comparators {

    // TODO: define and implement lex() method
    public static<T extends Comparable <T>> Comparator<Collection<? extends T>> lex(){
        return new Comparator<Collection<? extends T>>(){
            @Override
             public int compare(Collection<? extends T> col1, Collection<? extends T> col2){
                Iterator<? extends T> iter1 = col1.iterator();
                Iterator<? extends T> iter2 = col2.iterator();
                while(iter1.hasNext() && iter2.hasNext()){
                    T item1 = iter1.next();
                    T item2 = iter2.next();
                    if(item1.compareTo(item2) != 0)
                        return item1.compareTo(item2);
                }
                if(iter1.hasNext()) return 1;
                if(iter2.hasNext()) return -1;
                return 0;
            }
        };
    }

}
