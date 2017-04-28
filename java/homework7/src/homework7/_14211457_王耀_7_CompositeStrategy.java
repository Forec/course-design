package homework7;
import java.util.HashSet;
import java.util.Set;

/**
 * Created by Forec on 2016/12/28.
 * 组合策略的基类，具体的组合策略可扩展此类。
 * 构造方法中添加了无折扣的策略，保证如果此组合策略找不到任何简单策略，则使购物无折扣。
 */
public abstract class _14211457_王耀_7_CompositeStrategy extends _14211457_王耀_7_BasicStrategy{
    protected Set<Integer> smallStrategies;

    public _14211457_王耀_7_CompositeStrategy(String _strategyName){
        strategyNumber = ++basicNumber;
        strategyName = _strategyName;
        smallStrategies = new HashSet<Integer>();
        smallStrategies.clear();
        smallStrategies.add(0);    // 将无折扣添加到组合策略中
    }

    public boolean addSimpleStrategy(_14211457_王耀_7_IPricingStrategy smallStrategy){
		if (smallStrategy == null){
			return false;
		}
    	smallStrategies.add(smallStrategy.getStrategyNumber());
    	return true;
    }

    public boolean removeSimpleStrategy(_14211457_王耀_7_IPricingStrategy simpleStrategy){
        return smallStrategies.remove(simpleStrategy);
    }
    
    public String getStrategyValues(){
    	String toReturn = "";
    	for (Integer integer: smallStrategies){
    		if (integer == 0){
    			continue;
    		}
    		toReturn += (integer + "|");
    	}
    	return toReturn.substring(0, toReturn.length()-1);
    }
    
    public boolean setStrategyValue(String value){
    	String[] values = value.split("|");
    	Set<Integer> intValues = new HashSet<Integer>(); 
    	int temp;
    	for (String _value: values){
    		if (_value.equals("|") || _value.equals(" "))
    			continue;
    		try{
    			temp = Integer.parseInt(_value);
    		} catch( Exception e){
    			return false;
    		}
    		intValues.add(temp);
    	}
    	for (Integer i: intValues){
    		_14211457_王耀_7_IPricingStrategy strategy = _14211457_王耀_7_StrategyManager.getInstance().getStrategy(i);
    		if (strategy == null){
    			return false;
    		}
    	}
    	smallStrategies.clear();
    	smallStrategies.add(0);
    	for (Integer i: intValues){
    		_14211457_王耀_7_IPricingStrategy strategy = _14211457_王耀_7_StrategyManager.getInstance().getStrategy(i);
    		smallStrategies.add(strategy.getStrategyNumber());
    	}
    	
		return true;
    }
}
