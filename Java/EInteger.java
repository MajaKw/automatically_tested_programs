package pl.edu.uj.tcs.oop.labs.lab04;
import java.lang.Math;

public class EInteger {

    private int value;

    public EInteger() {
        this.value = 0;
    }
    public EInteger(int value) {
        this.value = value;
    }
    /**
     * Add the value of a to this EInteger.
     */
    public EInteger add(EInteger a) throws UnsupportedValueException{
        if((long)a.value + (long)this.value > Integer.MAX_VALUE || (long)a.value + (long)this.value < Integer.MIN_VALUE)
            throw new UnsupportedValueException();
        this.value += a.value;
        return this;
    }
    /**
     * Multiply this EInteger by the value of a.
     */
    public EInteger mult (EInteger a) throws UnsupportedValueException{
        if((long)a.value * (long)this.value > Integer.MAX_VALUE || (long)a.value * (long)this.value < Integer.MIN_VALUE)
            throw new UnsupportedValueException();
        this.value *= a.value;
        return this;
    }
    @Override
    public String toString(){
        return String.valueOf(this.value);
    }
    @Override
    public boolean equals(Object o){
        if(!(o instanceof EInteger)) return false;
        return ((EInteger) o).value == this.value;
    }
    // static methods (return a new object with the result of the operation)
    public static EInteger div(EInteger a, EInteger b) throws DivideByZeroException, DivideException{
        if(b.value == 0) throw new DivideByZeroException();
        if(a.value % b.value != 0) throw new DivideException();
        return new EInteger(a.value / b.value);
    }

    public static EInteger add(EInteger a, EInteger b) throws UnsupportedValueException{
        if((long)a.value * (long)b.value > Integer.MAX_VALUE || (long)a.value * (long)b.value < Integer.MIN_VALUE)
            throw new UnsupportedValueException();
        return new EInteger(a.value + b.value);
    }

    public static EInteger mult(EInteger a, EInteger b) throws UnsupportedValueException{
        if((long)a.value * (long)b.value > Integer.MAX_VALUE || (long)a.value * (long)b.value < Integer.MIN_VALUE)
            throw new UnsupportedOperationException();
        return new EInteger(a.value * b.value);
    }

    public static EInteger sqrt(EInteger a) throws SqrtNegativeException, SqrtException{
        if(a.value <= 0) throw new SqrtNegativeException();
        if(a.value%((int) Math.sqrt((double) a.value)) != 0) throw new SqrtException();
        return new EInteger((int) Math.sqrt((double) a.value));
    }
}
class UnsupportedValueException extends Throwable{
}
class DivideByZeroException extends Throwable{
}
class DivideException extends Throwable{
}
class SqrtNegativeException extends Throwable{
}
class SqrtException extends Throwable{
}
