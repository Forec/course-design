package homework7;
/**
 * Created by Forec on 2016/12/26.
 * 购物车中的一条消费记录。
 * 此类比要求中增加了一个 private int 类型的编号，每条添加到购物车中的消费记录应当有其唯一的
 * 编号，即使是相同的书籍、相同的数量，不同编号的消费记录也代表不同的购物。加入此项可以避免顾客
 * 误操作带来购物车中重复相同的购买记录。
 */
public class _14211457_王耀_7_SaleLineItem {

    private static int saleNumber = 0;

    private int number;
    private int copies;
    private _14211457_王耀_7_BookSpecification prodSpec;
    private _14211457_王耀_7_IPricingStrategy strategy;

    public _14211457_王耀_7_SaleLineItem(int _copies,
                        _14211457_王耀_7_BookSpecification _prodSpec){
        number = saleNumber++;
        copies = _copies;
        prodSpec = _prodSpec;
        strategy = _14211457_王耀_7_PricingStrategyFactory.getInstance().getPricingStrategy(prodSpec.getType());
    }

    public int getNumber(){
        return number;
    }

    public int getCopies(){
        return copies;
    }

    public _14211457_王耀_7_BookSpecification getProdSpec(){
        return prodSpec;
    }

    public double getSubTotal(){
        return strategy.getSubTotal(this);
    }
    
    public void updateStrategy(){
    	strategy = _14211457_王耀_7_PricingStrategyFactory.getInstance().getPricingStrategy(prodSpec.getType());
    }
    
    public _14211457_王耀_7_IPricingStrategy getStrategy(){
    	return strategy;
    }
}
