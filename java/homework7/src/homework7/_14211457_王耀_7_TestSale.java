package homework7;
/**
 * Created by Forec on 2016/12/26.
 */
public class _14211457_王耀_7_TestSale {
    private static _14211457_王耀_7_BookSpecification UMLandPatternApplication;
    private static _14211457_王耀_7_BookSpecification JavaAndPattern;
    private static _14211457_王耀_7_BookSpecification HeadFirst_DesignPattern;
    private static _14211457_王耀_7_BookSpecification Alice;
    private static _14211457_王耀_7_BookSpecification CookSoup;

    public static void init(){     // 初始化待购买的书籍
        UMLandPatternApplication = new _14211457_王耀_7_BookSpecification(     // UML 与模式应用
                "ISBN 978-7-115",
                18,
                "UML 与模式应用",
                2);         // 教材类
        JavaAndPattern = new _14211457_王耀_7_BookSpecification(               // Java 与模式
                "ISBN 929-1-139",
                34,
                "Java 与模式",
                1);         // 非教材类计算机书籍
        HeadFirst_DesignPattern = new _14211457_王耀_7_BookSpecification(     // HeadFirst 设计模式
                "ISBN 231-9-231",
                58,
                "HeadFirst 设计模式",
                1);         // 非教材类计算机书籍
        Alice = new _14211457_王耀_7_BookSpecification(                       // 爱丽丝历险记
                "ISBN 876-3-392",
                30,
                "爱丽丝历险记",
                3);         // 连环画类
        CookSoup = new _14211457_王耀_7_BookSpecification(                    // 煲汤大全
                "ISBN 283-1-431",
                20,
                "煲汤大全",
                4);         // 其他类书籍
        
        // 图书目录维护模块添加图书
        _14211457_王耀_7_BookManager.getInstance().addBook(UMLandPatternApplication);
        _14211457_王耀_7_BookManager.getInstance().addBook(JavaAndPattern);
        _14211457_王耀_7_BookManager.getInstance().addBook(HeadFirst_DesignPattern);
        _14211457_王耀_7_BookManager.getInstance().addBook(Alice);
        _14211457_王耀_7_BookManager.getInstance().addBook(CookSoup);

        _14211457_王耀_7_IPricingStrategy discount001 = new _14211457_王耀_7_FlatRateStrategy("绝对值优惠策略1", 1.0);
        discount001.setBookType(2);		// 适用图书类型 2
        _14211457_王耀_7_StrategyManager.getInstance().addStrategy(discount001);
        _14211457_王耀_7_IPricingStrategy discount002 = new _14211457_王耀_7_PercentageStrategy("百分比折扣策略1", 7);
        discount002.setBookType(3);		// 适用图书类型 3
        _14211457_王耀_7_StrategyManager.getInstance().addStrategy(discount002);
        _14211457_王耀_7_IPricingStrategy discount003 = new _14211457_王耀_7_PercentageStrategy("百分比折扣策略2", 3);
        discount003.setBookType(1);		// 适用图书类型 1
        _14211457_王耀_7_StrategyManager.getInstance().addStrategy(discount003);
        _14211457_王耀_7_IPricingStrategy discount004 = new _14211457_王耀_7_CustomerBestStrategy("顾客最优策略1");
        discount004.setBookType(4);		// 适用图书类型 4，由 Discount001 和 Discount003 组成
        discount004.setStrategyValue("1|3");
        _14211457_王耀_7_StrategyManager.getInstance().addStrategy(discount004);   
        

        _14211457_王耀_7_Controller.getInstance().getShoppingCart().addItem(new _14211457_王耀_7_SaleLineItem(2, UMLandPatternApplication));    // 购买 2 本《UML 与模式应用》
        _14211457_王耀_7_Controller.getInstance().getShoppingCart().addItem(new _14211457_王耀_7_SaleLineItem(2, JavaAndPattern));              // 购买 2 本《Jave 与模式》
        _14211457_王耀_7_Controller.getInstance().getShoppingCart().addItem(new _14211457_王耀_7_SaleLineItem(1, HeadFirst_DesignPattern));     // 购买 1 本《HeadFirst 设计模式》
        _14211457_王耀_7_Controller.getInstance().getShoppingCart().addItem(new _14211457_王耀_7_SaleLineItem(3, Alice));                       // 购买 3 本《爱丽丝历险记》
        _14211457_王耀_7_Controller.getInstance().getShoppingCart().addItem(new _14211457_王耀_7_SaleLineItem(1, CookSoup));                    // 购买 1 本《煲汤大全》
    }
}
