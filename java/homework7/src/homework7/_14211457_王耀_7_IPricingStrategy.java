package homework7;
/**
 * Created by Forec on 2016/12/26.
 */

public interface  _14211457_王耀_7_IPricingStrategy{
    double getSubTotal(_14211457_王耀_7_SaleLineItem item);
    int getStrategyNumber();
    int getBookType();
    String getStrategyName();
	String getStrategyValues();
	boolean setStrategyName(String name);
	boolean setStrategyValue(String value);
	boolean setBookType(int booktype);
}
