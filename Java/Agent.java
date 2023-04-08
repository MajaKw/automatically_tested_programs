import java.io.IOException;
import java.nio.CharBuffer;
import java.util.HashMap;
import java.util.Locale;
import java.util.Map;

/**
 * PO 2021/22, Problem D - Alfabet Morse'a
 * @author Maja Kiatek
 */
class TakeZuber extends RuntimeException{

}

public class Agent implements Readable, TajnyAgent {
    int letter = 0;
    int word = 0;
    boolean interpuncion = false;
    boolean endOfWord = false;
    boolean zuber = false;
    boolean repeat;
    String message = "";
    TajnyAgent listeningTo;

    int wordZuber = 0;
    int letterZuber = 0;
    String messageZuber = "zuber/";

    static HashMap<Character, String> mors = new HashMap<Character, String>(62);
    static HashMap<String, Character> morsToLetter = new HashMap<String, Character>(62);
    static
    {
        mors.put('a', ".-"); mors.put('b', "-..."); mors.put('c', "-.-."); mors.put('d', "-..");
        mors.put('e', "."); mors.put('f', "..-."); mors.put('g', "--."); mors.put('h', "....");
        mors.put('i', ".."); mors.put('j', ".---"); mors.put('k', "-.-"); mors.put('l', ".-..");
        mors.put('m', "--"); mors.put('n', "-."); mors.put('o', "---"); mors.put('p', ".--.");
        mors.put('q', "--.-"); mors.put('r', ".-."); mors.put('s', "..."); mors.put('t', "-");
        mors.put('u', "..-"); mors.put('v', "...-"); mors.put('w', ".--"); mors.put('y', "-.--");
        mors.put('z', "--.."); mors.put('0', "-----"); mors.put('1', ".----"); mors.put('2', "..---");
        mors.put('3', "...--"); mors.put('4', "....-"); mors.put('5', "....."); mors.put('6', "-....");
        mors.put('7', "--..."); mors.put('8', "---.."); mors.put('9', "----."); mors.put('&', ".-...");
        mors.put('\'', ".----."); mors.put('@', ".--.-."); mors.put(')', "-.--.-"); mors.put('(', "-.--.");
        mors.put(':', "---..."); mors.put(',', "--..--"); mors.put('=', "-...-"); mors.put('!', "-.-.--");
        mors.put('.', ".-.-.-"); mors.put('-', "-....-"); mors.put('*', "-..-"); mors.put('%', "------..-.-----");
        mors.put('+', ".-.-."); mors.put('"', ".-..-."); mors.put('?', "..--.."); mors.put('/', "-..-.");
        mors.put('ą', ".-.-"); mors.put('ć', "-.-.."); mors.put('ę', "..-.."); mors.put('ł', ".-..-");
        mors.put('ń', "--.--"); mors.put('ó', "---."); mors.put('ś', "...-..."); mors.put('ź', "--..-.");
        mors.put('ż', "--..-"); mors.put('x', "-..-");
    }
    static
    {
        for(Map.Entry<Character, String> entry : mors.entrySet()){
            morsToLetter.put(entry.getValue(), entry.getKey());
        }
    }
    Agent() {
        this.repeat = true; this.message = "pawiany/wchodzą/na/ściany!żyrafy/wchodzą/do/szafy!";
    }
    Agent(String password) {
        this.repeat = false; this.message = password.toLowerCase(Locale.ROOT);
    }
    Agent(TajnyAgent remote) {
        this();
        this.listeningTo = remote;
    }
    Agent(TajnyAgent remote, String password) {
        this(password);
        this.listeningTo = remote;
    }




    public boolean zuberTransmission(){
//        System.out.println("zuber transmission");
//        String unwanted = "zuber/";
//        TajnyAgent tajniak = new Agent(unwanted);
//        tajniak.transmituj();
//        System.out.println("end");
        if(wordZuber == messageZuber.length()){
            letterZuber = 0; wordZuber = 0; return false;
        }
        char ch = messageZuber.charAt(wordZuber);
        if(letterZuber == mors.get(ch).length()){
            letterZuber = 0; ++wordZuber;
            throw new Stop();
        }
        if(letterZuber < mors.get(ch).length() && wordZuber != messageZuber.length()){
            char sign = mors.get(ch).charAt(letterZuber);
            ++letterZuber;
            if (sign == '.') throw new RuntimeException();
            return true;
        }
        return true;
    }

    @Override
    public void transmituj(){
        boolean check;
        if(zuber && endOfWord) { check = zuberTransmission(); if(check) return; zuber = false;}

        if (word == message.length()) { //koniec transmisji
            letter = 0;
            word = 0; //tu jeszcze trzeba nadac ostatni symbol
            if (!repeat) throw new Koniec();
        }
        char ch = message.charAt(word);
        if (letter == mors.get(ch).length()) {
            letter = 0;
            if(ch < '0' || (ch > '9' && ch < 'A') || (ch >'Z' && ch < 'a') || ch > 'z') endOfWord = true;
            ++word;

            throw new Stop(); // koniec litery
        }
        if (letter < mors.get(ch).length() && word != message.length()) { // jestesmy w literze
//            if(zuber && letter == 0){ zuber = false;  throw new TakeZuber();}
            endOfWord = false;
            char sign = mors.get(ch).charAt(letter);
            ++letter;
            if (sign == '.') throw new RuntimeException(); //jesli kropka to rzuc wyjatek
            return; // jesli kreska zmus do powodzenia transmitowania
        }
    }
    @Override
    public int read(CharBuffer cb) throws IOException {
        StringBuilder morsCode = new StringBuilder();
        int howMany = 0;
        while(true){

            try {
                listeningTo.transmituj();
                morsCode.append("-");
            }catch(Zuber achtung){
                zuber = true;
            }catch (RozmowaKontrolowana eavsdropping){

            }
            catch (Koniec koniec) {
                return -1; //force ending of reading
            }catch (Stop stop){
                String normal = morsCode.toString();
//                System.out.println("normal: " + normal);
                char uncoded = morsToLetter.get(normal);
//                System.out.println("uncoded: " + uncoded);
                ++howMany;
                cb.put(uncoded);
                if(uncoded < '0' || (uncoded > '9' && uncoded < 'A') || (uncoded >'Z' && uncoded < 'a') || uncoded > 'z')
                    return howMany;
                morsCode.delete(0, morsCode.length());
            }catch(RuntimeException exc){
                morsCode.append(".");
            }
        }
    }
}
