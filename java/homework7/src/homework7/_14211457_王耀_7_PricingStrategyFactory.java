package homework7;
/**
 * Created by Forec on 2016/12/26.
 */
public class _14211457_王耀_7_PricingStrategyFactory {
    private static _14211457_王耀_7_PricingStrategyFactory instance = null;

    private _14211457_王耀_7_PricingStrategyFactory(){ }
    
    public static _14211457_王耀_7_PricingStrategyFactory getInstance(){
        if (instance == null){
            instance = new _14211457_王耀_7_PricingStrategyFactory();
        }
        return instance;
    }

    public _14211457_王耀_7_IPricingStrategy getPricingStrategy(int bookType){
    	return _14211457_王耀_7_StrategyManager.getInstance().getStrategyForBookType(bookType);
    }
}
