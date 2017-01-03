package homework2;

/**
 * Created by Forec on 2016/10/25.
 */
public class _14211457_王耀_2_StudentNumberException extends Exception {
    public _14211457_王耀_2_StudentNumberException(){
        super("Invalid student number, must be like pattern ^20[0-9]{8}$.");
    }
}
