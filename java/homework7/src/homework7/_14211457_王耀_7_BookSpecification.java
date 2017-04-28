package homework7;

/**
 * Created by Forec on 2016/12/26.
 */
public class _14211457_王耀_7_BookSpecification {
    private String isbn;
    private double price;
    private String title;
    private int type;
    
    public static String getTypeName(int type){
    	switch (type) {
		case 1:
			return "非教材类计算机图书";
		case 2:
			return "教材类图书";
		case 3:
			return "连环画类图书";
		case 4:
			return "养生类图书";
		default:
			return "其他";
		}
    }
    
    public String getTypeName(){
    	return _14211457_王耀_7_BookSpecification.getTypeName(type);
    }

    public _14211457_王耀_7_BookSpecification(String _isbn,
                             double _price,
                             String _title,
                             int _type){
        isbn = _isbn;       // isbn 编号唯一
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

    public String getIsbn() {
        return isbn;
    }
    
    public String getTitle(){
    	return title;
    }
    
    public void setPrice(double _price){
    	price = _price;
    }
    
    public void setType(int _type){
    	type = _type;
    }
    
    public void setTitle(String _title){
    	title = _title;
    }
    
    public void setISBN(String _isbn){
    	isbn = _isbn;
    }
}
