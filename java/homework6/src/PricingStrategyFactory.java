/**
 * Created by Forec on 2016/12/26.
 */
public class PricingStrategyFactory {
    private static PricingStrategyFactory instance = null;

    private PricingStrategyFactory(){ }

    private IPricingStrategy getNoDiscountStrategy(){
        return new NoDiscountStrategy();
    }

    private IPricingStrategy getPercentageStrategy(int percentage){
        return new PercentageStrategy(percentage);
    }

    private IPricingStrategy getFlatRateStrategy(double discountPerbook){
        return new FlatRateStrategy(discountPerbook);
    }

    public static PricingStrategyFactory getInstance(){
        if (instance == null){
            instance = new PricingStrategyFactory();
        }
        return instance;
    }

    public IPricingStrategy getPricingStrategy(int bookType){
        switch (bookType) {
            case 0: // 教材类书籍 每本 1 元折扣
                return getFlatRateStrategy(1);
            case 1: // 连环画类图书 每本 7% 折扣
                return getPercentageStrategy(7);
            case 2: // 非教材类计算机图书 每本 3% 折扣
                return getPercentageStrategy(3);
            default: // 其他类 无折扣
                return getNoDiscountStrategy();
        }
    }
}
