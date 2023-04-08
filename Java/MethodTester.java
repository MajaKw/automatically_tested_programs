package pl.edu.uj.tcs.oop.labs.lab06;

import java.lang.reflect.Method;
import java.lang.reflect.Type;
import java.lang.reflect.TypeVariable;

public class MethodTester {
    public static boolean sameParameters(Method m1, Method m2) {
        // TODO: implement

        m1.toGenericString();
        Type[] types1 = m1.getGenericParameterTypes();
        Type[] types2 = m2.getGenericParameterTypes();
//        TypeVariable<?>[] types1 = m1.getTypeParameters();
//        TypeVariable<?>[] types2 = m2.getTypeParameters();
        int len1 = types1.length;
        int len2 = types2.length;

        if(len1 == len2){
            for(int i = 0; i<len1; ++i){
//                System.out.println("type1: " + types1[i].getTypeName());
//                System.out.println("type2: " + types2[i].getTypeName());
                if(types1[i].getTypeName() != types2[i].getTypeName())
                    return false;
            }
            return true;
        }else
            return false;
    }

}
