package homework7;

public class _14211457_王耀_7_NoDiscountStrategy extends _14211457_王耀_7_BasicStrategy implements _14211457_王耀_7_IPricingStrategy{
    // 无折扣为 单子 策略

    private static _14211457_王耀_7_NoDiscountStrategy instance = null;

    private _14211457_王耀_7_NoDiscountStrategy(){
        strategyName = "无折扣";
        strategyNumber = 0;     // 无折扣策略始终编号为 0
        booktype = 0;
    }

    public static _14211457_王耀_7_NoDiscountStrategy getInstance(){
        if (instance == null)
            instance = new _14211457_王耀_7_NoDiscountStrategy();
        return instance;
    }

    public double getSubTotal(_14211457_王耀_7_SaleLineItem item){
        return item.getCopies() * item.getProdSpec().getPrice();
    }

    public String getStrategyValues(){
    	return "无折扣";
    }
    
    public boolean setStrategyName(String name){
    	return false;
    }
    
    public boolean setStrategyValue(String value){
		return false;
    }
}
