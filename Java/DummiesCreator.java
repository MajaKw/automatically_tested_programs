package pl.edu.uj.tcs.oop.labs.lab06;
import java.lang.reflect.Constructor;

public class DummiesCreator {
    /**
     * Tries to create a new object of class T with a constructor applied with 0's or null's.
     */
    public static <T> T newInstance(Class<T> kind) {
        // TODO: implement
        Constructor<?>[] constructors = kind.getConstructors();
        Class<?>[] args = constructors[0].getParameterTypes();
        int len = args.length;
        Object [] values = new Object[len];
        for(int i = 0; i<len; ++i) {
            if(args[i].isPrimitive()){
                if(args[i] == char.class){
                    values[i] = '0';
                }else
                    values[i] = (byte)0;
            }else
                values[i] = null;
        }
            try {
                return kind.getConstructor(args).newInstance(values);
        }catch(Exception e){
            e.printStackTrace();
        }
        return null;
    }
}
