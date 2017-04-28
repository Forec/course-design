package homework7;
/**
 * Created by Forec on 2016/12/28.
 * 具体的组合策略，选取组合策略包含的所有简单策略中最优的一种。
 */
public class _14211457_王耀_7_CustomerBestStrategy extends _14211457_王耀_7_CompositeStrategy {

    public _14211457_王耀_7_CustomerBestStrategy(String _strategyName){
        super(_strategyName);
    }

    public double getSubTotal(_14211457_王耀_7_SaleLineItem item){
        double bestCost = _14211457_王耀_7_NoDiscountStrategy.getInstance().getSubTotal(item);
        for (int strategyNumber: smallStrategies){
        	_14211457_王耀_7_IPricingStrategy strategy = _14211457_王耀_7_StrategyManager.getInstance().getStrategy(strategyNumber);
            double currentStrategyCost = strategy.getSubTotal(item);
            bestCost = bestCost > currentStrategyCost ? currentStrategyCost : bestCost; 
        }
        return bestCost;
    }
}
