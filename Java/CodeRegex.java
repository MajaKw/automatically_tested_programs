package pl.edu.uj.tcs.oop.labs.lab02;
import java.util.regex.*;

public class CodeRegex
{
    String regex;
    public CodeRegex(String regex){
        this.regex = regex;
    }
    public String code(String in){
        StringBuilder builder = new StringBuilder(in);
        Pattern pattern = Pattern.compile(this.regex);;
        Matcher matcher = pattern.matcher(in);

        int count = 0;
        int change = 0;
        int start; int end; int len; int nr_len;
        while (matcher.find()) {
            start = matcher.start();
            end = matcher.end();
            len = end - start;

//            System.out.println("start: " + start);
//            System.out.println("len: " + len);
            String nr = Integer.toString(len);
            String replace  = '<' + this.regex + ':' + nr + '>';
//            System.out.println("change: " + change);
            builder.replace(start + change, end + change, replace);
            nr_len  = nr.length();
//            System.out.println("builder: " + builder);
            change += (this.regex.length() + 3 + nr_len) - len;
        }
        String out = builder.toString();
        return out;
    }
}

