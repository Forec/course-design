package homework7;

public class _14211457_王耀_7_PercentageStrategy extends _14211457_王耀_7_SimpleStrategy{

    private int discountPercentage;

    public _14211457_王耀_7_PercentageStrategy(String _strategyName,
                              int _discountPercentage){
        strategyName = _strategyName;
        strategyNumber = ++basicNumber;
        strategyType = 1;   // 百分比折扣策略
        discountPercentage = _discountPercentage;
    }

    public double getSubTotal(_14211457_王耀_7_SaleLineItem item){
        return item.getProdSpec().getPrice() * (100- discountPercentage) * item.getCopies() / 100.0;
    }
    
    public String getStrategyValues(){
    	return discountPercentage + "";
    }
    
    public boolean setStrategyValue(String value){
    	int _value;
    	try{
    		_value = Integer.parseInt(value);
    	} catch (Exception e){
    		return false;
    	}
    	discountPercentage = _value;
    	return true;
    }

}
