package homework7;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class _14211457_王耀_7_StrategyManager {  // 策略管理器，单子

	private List<_14211457_王耀_7_Observer> observerList;
    private static _14211457_王耀_7_StrategyManager instance = null;
    private Map<Integer, _14211457_王耀_7_IPricingStrategy> strategies;

    private _14211457_王耀_7_StrategyManager(){
        strategies = new HashMap<Integer, _14211457_王耀_7_IPricingStrategy>();
        strategies.clear();
        strategies.put(0, _14211457_王耀_7_NoDiscountStrategy.getInstance());
        // 初始化策略管理器并添加无折扣策略
        observerList = new ArrayList<_14211457_王耀_7_Observer>();
        observerList.clear();
    }
    
    public void registerObserver(_14211457_王耀_7_Observer observer){
    	_14211457_王耀_7_StrategyManager.getInstance().observerList.add(observer);
    }
    
    public boolean removeObserver(_14211457_王耀_7_Observer observer){
    	return _14211457_王耀_7_StrategyManager.getInstance().observerList.remove(observer);
    }

    public static _14211457_王耀_7_StrategyManager getInstance(){
        if (instance == null)
            instance = new _14211457_王耀_7_StrategyManager();
        return instance;
    }
    
    public _14211457_王耀_7_IPricingStrategy HasBookTypeOccupied(int booktype){
    	if (booktype == 0){
    		return null;
    	}
    	for (_14211457_王耀_7_IPricingStrategy strategy: _14211457_王耀_7_StrategyManager.getInstance().strategies.values()){
    		if (strategy.getBookType() == booktype){
    			return strategy;
    		}
    	}
    	return null;
    }

    public void addStrategy(_14211457_王耀_7_IPricingStrategy strategy){
        _14211457_王耀_7_StrategyManager.getInstance().strategies.put(strategy.getStrategyNumber(), strategy);
        for (_14211457_王耀_7_Observer obs: _14211457_王耀_7_StrategyManager.getInstance().observerList){
        	obs.update();
        }
    }

    public _14211457_王耀_7_IPricingStrategy removeStrategy(_14211457_王耀_7_IPricingStrategy strategy){
        _14211457_王耀_7_IPricingStrategy ans = instance.strategies.remove(strategy.getStrategyNumber());
        for (_14211457_王耀_7_Observer obs: _14211457_王耀_7_StrategyManager.getInstance().observerList){
        	obs.update();
        }
        return ans;
    }
    
    public _14211457_王耀_7_IPricingStrategy removeStrategy(Integer strategyNumber){
        _14211457_王耀_7_IPricingStrategy ans = getInstance().strategies.remove(strategyNumber);
        if (ans == null){
        	return null;
        }
        for (_14211457_王耀_7_Observer obs: _14211457_王耀_7_StrategyManager.getInstance().observerList){
        	obs.update();
        }
        return ans;
    }
    
    public _14211457_王耀_7_IPricingStrategy getStrategyForBookType(int type){
    	for (_14211457_王耀_7_IPricingStrategy strategy: strategies.values()){
    		if (strategy.getBookType() == type){
    			return strategy;
    		}
    	}
    	return _14211457_王耀_7_NoDiscountStrategy.getInstance();
    }

    public _14211457_王耀_7_IPricingStrategy getStrategy(int strategyNumber){
        return getInstance().strategies.get(strategyNumber);
    }
    
    public List<_14211457_王耀_7_IPricingStrategy> getStrategies(){
    	List<_14211457_王耀_7_IPricingStrategy> returnList = new ArrayList<_14211457_王耀_7_IPricingStrategy>();
    	for (_14211457_王耀_7_IPricingStrategy ip: _14211457_王耀_7_StrategyManager.getInstance().strategies.values())
    		returnList.add(ip);
    	return returnList;
    }

	public void update() {
        for (_14211457_王耀_7_Observer obs: _14211457_王耀_7_StrategyManager.getInstance().observerList){
        	obs.update();
        }
	}
	   
    public static boolean tryStrategyValues(String value){
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
    	return true;
    }
}
