package pl.edu.uj.tcs.oop.labs.lab05;

import java.util.Collection;
import java.util.LinkedList;
import java.util.Objects;

class Pair<T>{
    T x;
    T y;
    Pair(T x, T y){
        this.x = x;
        this.y = y;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Pair<?> pair = (Pair<?>) o;
        return Objects.equals(x, pair.x) && Objects.equals(y, pair.y);
    }

    @Override
    public int hashCode() {
        return Objects.hash(x, y);
    }
}

public class DiGraph<T> {
    LinkedList<T> vertex = new LinkedList<T>();
    LinkedList<Pair<T>> edge =  new LinkedList<Pair<T>>();

    public void addVertex(T t) {
        if(!vertex.contains(t)){
            vertex.add(t);
        }
    }

    public void removeVertex(T t) {
        if(vertex.contains(t)){
            vertex.remove(t);
            edge.removeIf(tPair -> tPair.x == t || tPair.y == t);
        }

    }

    public boolean containsVertex(T t) {
        if(vertex.contains(t)) return true;
        return false;
    }

    public void addEdge(T t, T s) {
        Pair pair = new Pair(t,s);
        if(!edge.contains(pair)){
            edge.add(pair);
            addVertex(t); addVertex(s);
        }
    }

    public void removeEdge(T t, T s) {
        Pair pair = new Pair(t,s);
        if(edge.contains(pair)){
            edge.remove(pair);
        }
    }

    public boolean containsEdge(T t, T s) {
        Pair pair = new Pair(t,s);
        if(edge.contains(pair)) return true;
        return false;
    }

}
