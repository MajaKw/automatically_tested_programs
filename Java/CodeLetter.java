package pl.edu.uj.tcs.oop.labs.lab02;
import javax.print.DocFlavor;
import java.util.*;

    public class CodeLetter {
        char letter;

        public CodeLetter(char letter) {
            this.letter = letter;
        }

        public String code(String in) {
            StringBuilder builder = new StringBuilder(in);
            String out;
            int len = in.length();
            int n = 0;
            int temp = 0;
            int temp2 = 0;
            int i = 0;
            int start = 0;
//            System.out.println("len: " + len);
            char ch = in.charAt(i);
            while (i < len) {
                start = i - temp2;
//                System.out.println("start: " + start);
//                System.out.println("i: " + i);
//                System.out.println("ch : " + ch);
                while (ch == this.letter) {
                    ++n;
                    ++i;

//                    System.out.println("i: " + i);
                    if(i >= len) break;
                    ch = in.charAt(i);
//                    System.out.println("ch w while: " + ch);
                    temp = n-3;
//                    if(temp < 0) temp = 0;

                }

//                System.out.println("temp: " + temp);
//                temp2 += temp;
//                System.out.println("temp2: " + temp2);
                if (n != 0) {
//                    System.out.println("if n!= 0");
                    String nr  = String.valueOf(n);
//                    System.out.println(nr);
                    if(n != 1) {
                        temp2 += temp;
//                        System.out.println("n: " + n);
                        String lett = Character.toString(this.letter);
                        String result = lett + '^' + String.valueOf(n);
//                        System.out.println("result: " + result);
                        // builder.replace(startIndex, stopIndex, replacement);
                        builder.replace(start, start + n, result);
                        int x  = builder.length();
//                        System.out.println("bulider len: " + x);
//                    System.out.println(builder);
                    }
                    n = 0;
                    continue;
                } else {
                    ++i;
                    if(i >= len) break;
                    ch = in.charAt(i);
//                    System.out.println("i: " + i);
//                    System.out.println("ch w else: " + ch);
                }
            }
            out = builder.toString();
            return out;
        }

        public String decode(String in) {
            StringBuilder builder = new StringBuilder(in);
            String out;
            int len = in.length();
            int i = 0;
            int start = 0;
            int temp = 0;
            int temp2 = 0;
            String repeated;

            char ch = in.charAt(i);
//            System.out.println("ch: " + ch);
            while (i < len) {
//                System.out.println("i: " + i);
//                System.out.println("ch: " + ch);
                if (ch == this.letter) {
                    start = i - temp;
                    ++i;
                    if (i >= len) break;
                    ch = in.charAt(i);
//                    System.out.println("ch: " + ch);
                    if (ch == '^') {
                        ++i;
                        if (i >= len) break;
                        ch = in.charAt(i);
//                        System.out.println("ch: " + ch);
                        if (ch >= '0' && ch <= '9') {
                            int nr = Character.getNumericValue(ch);
                            String result = Character.toString(this.letter);
//                            System.out.println("nr: " + nr);
                            repeated = new String(new char[nr]).replace("\0", result);
//                            System.out.println("result: " + result);
                            ++i;
                            builder.replace(start, i, repeated);
                            if (i >= len) break;
                            temp += nr - 3;
//                            System.out.println("temp: " + temp);
                        }
                    }
                }else{
                    ++i;
                    if(i >= len) break;
                    ch = in.charAt(i);
                }
            }//while
            out = builder.toString();
            return out;
        }

    }
