import java.util.ArrayList;

/**
 * Created by Forec on 2016/12/26.
 */
public class ProductSpecification {
    private String isbn;
    private double price;
    private String title;
    private int type;

    public ProductSpecification(String _isbn,
                                double _price,
                                String _title,
                                int _type){
        isbn = _isbn;
        price = _price;
        title = _title;
        type = _type;
        // 1：非教材类计算机图书
        // 2：教材类图书
        // 3：连环画类图书
        // 4：养生类图书
        // 5：其他
    }

    public double getPrice(){
        return price;
    }

    public int getType(){
        return type;
    }
}
