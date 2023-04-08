import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * PO 2021/22, Problem E - Funkcje wieloargumentowe
 * @author Maja Kwiatek
 */

public class Functions {
    public static <T,  R> Function<T,R> constant (R  arg) {
        return new Function<T, R>() {
            @Override
            public int arity() {
                return 0;
            }

            @Override
            public R compute(List<? extends T> args) throws GenericFunctionsException {
                if (args.size() != arity())
                    throw new GenericFunctionsException();
                return arg;
            }
        };
    }
    public static <T extends R, R > Function <T,R>  proj (int n, int k) throws GenericFunctionsException{
        if(n < 1 || (k<0 || k>n-1)) throw new GenericFunctionsException();
        return new Function<T, R>() {
            @Override
            public int arity() {
                return n;
            }
            @Override
            public R compute(List<? extends T> args) throws GenericFunctionsException {
//                System.out.println("list: " + args.size() + " k: " + k);
                if (args.size() != arity())
                    throw new GenericFunctionsException();
                return args.get(k);
            }
        };
    }
    public static <X, T, R>  Function <X, R> compose ( Function <? super T,? extends R> f, List <? extends Function<? super X,? extends T>> list) throws GenericFunctionsException {
        if(f == null || list == null ){throw new GenericFunctionsException();}
        for(int i = 0; i<list.size(); ++i){
            if(list.get(i) == null) throw new GenericFunctionsException();
            if(list.get(0).arity() != list.get(i).arity()) throw new GenericFunctionsException();
        }
        if(f.arity() != list.size()) throw new GenericFunctionsException();
        return new Function<X, R>() {
            @Override
            public int arity() {
                return list.get(0).arity();
            }
            @Override
            public R compute(List<? extends X> args) throws GenericFunctionsException {
                List<T> values = new ArrayList<T>(f.arity());
                for(int i=0; i< list.size(); ++i){
                    values.add(list.get(i).compute(args));
                }
                return f.compute(values);
            }
        };
    }

}
