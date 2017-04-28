package homework7;
/**
 * Created by Forec on 2016/12/28.
 */

public abstract class _14211457_王耀_7_BasicStrategy implements _14211457_王耀_7_IPricingStrategy{
    static int basicNumber = 0;

    protected int strategyNumber;
    protected String strategyName;
    protected int booktype = 0;

    abstract public double getSubTotal(_14211457_王耀_7_SaleLineItem item);

    public boolean setStrategyName(String _strategyName){
        strategyName = _strategyName;
        return true;
    }

    public String getStrategyName(){
        return strategyName;
    }

    public int getStrategyNumber(){
        return strategyNumber;
    }
    
    public boolean setBookType(int _type){
    	_14211457_王耀_7_IPricingStrategy occupy = _14211457_王耀_7_StrategyManager.getInstance().HasBookTypeOccupied(_type);
    	if (occupy != null && this != occupy)
    		return false;
    	booktype = _type;
    	return true;
    }
    
    public int getBookType(){
    	return booktype;
    }
    
    public abstract String getStrategyValues();
}

