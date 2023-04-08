/**
 * PO 2021/22, Problem B - Klasa Świra
 * @author Maja Kwiatek
 */

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class a {
    a a;
    ArrayList<Integer> list;
    boolean normalOrder = false;
    int pop; boolean wasPop = false;
    a() {
        list = new ArrayList<>();
        a = new a(this);
    }
    a(a a) {
        list = a.list;
        this.a = a;
        normalOrder = true;
    }
    public String toString() {
        if (!normalOrder) {
            List<Integer> sortedList = list.stream().sorted().collect(Collectors.toList());
            return sortedList.toString();
        }
        return list.toString();
    }
    public a a(int item) {
        if((wasPop && pop == item) || (a.wasPop && a.pop == item)){
            list.add(0,item);
            if(wasPop) wasPop = false;
            if(a.wasPop) a.wasPop = false;
            if(a.normalOrder)
                return a;
            return this;
        }else {
            list.add(item);
            if (normalOrder)
                return a;
            return this;
        }
    }
    public int a() {
        wasPop = true;
        pop = list.remove(list.size() - 1);
        return pop;
    }
}

