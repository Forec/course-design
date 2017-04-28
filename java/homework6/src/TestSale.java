/**
 * Created by Forec on 2016/12/26.
 */
public class TestSale {
    private static ProductSpecification UMLandPatternApplication;
    private static ProductSpecification JavaAndPattern;
    private static ProductSpecification HeadFirst_DesignPattern;
    private static ProductSpecification Alice;
    private static ProductSpecification CookSoup;

    private static void init(){     // 初始化待购买的书籍
        UMLandPatternApplication = new ProductSpecification(     // UML 与模式应用
                "ISBN 978-7-115-37399-1",
                18,
                "UML 与模式应用",
                0);         // 教材类
        JavaAndPattern = new ProductSpecification(               // Java 与模式
                "ISBN 929-1-139-20314-3",
                34,
                "Java 与模式",
                2);         // 非教材类计算机书籍
        HeadFirst_DesignPattern = new ProductSpecification(     // HeadFirst 设计模式
                "ISBN 231-9-231-12209-1",
                58,
                "HeadFirst 设计模式",
                2);         // 非教材类计算机书籍
        Alice = new ProductSpecification(                       // 爱丽丝历险记
                "ISBN 876-3-392-01126-5",
                30,
                "爱丽丝历险记",
                1);         // 连环画类
        CookSoup = new ProductSpecification(                    // 煲汤大全
                "ISBN 283-1-431-76326-3",
                20,
                "煲汤大全",
                3);         // 其他类书籍
    }


    public static void main(String[] args){
        init();                         // 初始化图书
        Sale sale = new Sale();         // 开始购物
        sale.addItem(new SaleLineItem(2, UMLandPatternApplication));    // 购买 2 本《UML 与模式应用》
        sale.addItem(new SaleLineItem(2, JavaAndPattern));              // 购买 2 本《Jave 与模式》
        sale.addItem(new SaleLineItem(1, HeadFirst_DesignPattern));     // 购买 1 本《HeadFirst 设计模式》
        sale.addItem(new SaleLineItem(3, Alice));                       // 购买 3 本《爱丽丝历险记》
        sale.addItem(new SaleLineItem(1, CookSoup));                    // 购买 1 本《煲汤大全》

        // 购买完成，输出优惠后价格
        System.out.println("本次购物优惠后价格为：" + sale.getTotal());
    }
}
