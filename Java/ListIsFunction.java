/**
 * PO 2021/22, Problem C - ListIsFunction
 * @author Maja Kwiatek
 */
import java.security.KeyStore;
import java.util.*;

public class ListIsFunction {
    static int i = 0;
    ArrayList list;
    AbstractMap map;
    ListIsFunction(){
        list = new ArrayList(){
            @Override
            public void add(int index, Object o){
                if(index > size()){
                    throw new IndexOutOfBoundsException();
                }else if(index < 0){
                    throw new ArrayIndexOutOfBoundsException();
                }else
                    super.add(index, o);
            }
            @Override
            public boolean add(Object o){
                if(o == null){
                    o = "null";
                }
                return super.add(o);
            }
        };
        map = new AbstractMap(){
            @Override
            public Set entrySet() {
                return new LinkedHashSet(){

                    public int size(){
                         return ListIsFunction.this.list.size();
                    }

                    @Override
                    public boolean isEmpty() {
                        return ListIsFunction.this.list.size() == 0;
                    }
//                    @Override
//                    public boolean remove(Object o){
//                        Entry e = (Entry) o;
//                        if ((int)e.getKey() != ListIsFunction.this.list.size()){
//                            throw new IllegalArgumentException();
//                        }else
//                            return super.remove(o);
//                    }

                    public Iterator iterator() {
                        return new Iterator(){
                            int i = 0;
                            private final Iterator map_iterator = ListIsFunction.this.list.iterator();
                            public boolean hasNext(){
                                return map_iterator.hasNext();
                            }
                            public Object next(){
                                Object value = map_iterator.next();
                                Entry en = Map.entry(i, value);
                                i = (i+1)%ListIsFunction.this.list.size();
                                return en;
                            }
                            public void remove() {
                                if(map_iterator.hasNext())
                                    throw new IllegalStateException();
                                    map_iterator.remove();
                            }

                        };
                    }
                };
            }
            @Override
            public void clear(){
                    ListIsFunction.this.list.clear();
            }

            @Override
            public Object put(Object key, Object value){

                if(key == null){
                    throw  new NullPointerException();
                }
//                if(key.getClass() == Integer.class){
//                    throw new ClassCastException();
//                }
                Object result = null;
                if((int)key < ListIsFunction.this.list.size() && (int)key >= 0) {
                    result = ListIsFunction.this.list.get((int)key);
                    ListIsFunction.this.list.set((int) key, value);
                    return result;
                }else if((int)key == ListIsFunction.this.list.size()){
                    ListIsFunction.this.list.add(value);
                    return result;
                }else
                    throw new IllegalArgumentException();

            }

            @Override
            public Object remove(Object key) {
                Object o = null;
                if(ListIsFunction.this.list.size() != 0 && (int)key >= 0 && (int)key < ListIsFunction.this.list.size() - 1){
                    throw new IllegalArgumentException();
                }
                if( ListIsFunction.this.list.size() != 0 && (int) key == ListIsFunction.this.list.size() - 1){
                    o = ListIsFunction.this.list.get((int)key);
                    ListIsFunction.this.list.remove((int) key);
                }
                return o;
            }

        };
    }

    List asList(){
        return this.list;
    }
    Map asMap(){
        return this.map;
    }
}
