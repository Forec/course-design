package homework7;

import java.text.DecimalFormat;

public class _14211457_王耀_7_FlatRateStrategy extends _14211457_王耀_7_SimpleStrategy {

    private double discountPerbook;

    public _14211457_王耀_7_FlatRateStrategy(String _strategyName,
                            double _discountPerbook){
        strategyName = _strategyName;
        strategyNumber = ++basicNumber;
        strategyType = 2;       // 绝对值优惠简单策略
        discountPerbook = _discountPerbook;
    }

    public double getSubTotal(_14211457_王耀_7_SaleLineItem item){
    	return (item.getProdSpec().getPrice() - discountPerbook) * item.getCopies();
    }
    
    public String getStrategyValues(){
    	return new DecimalFormat(".00").format(discountPerbook);
    }
    
    public boolean setStrategyValue(String value){
    	double _value;
    	try{
    		_value = Float.parseFloat(value);
    	}catch(Exception e){
    		return false;
    	}
    	discountPerbook = _value;
		return true;
    }
}
