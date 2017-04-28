package homework7;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by Forec on 2016/12/26.
 */
public class _14211457_王耀_7_ShoppingCart {
    private ArrayList<_14211457_王耀_7_SaleLineItem> items;
    private ArrayList<_14211457_王耀_7_Observer> observerList;

    public _14211457_王耀_7_ShoppingCart(){
        items = new ArrayList<_14211457_王耀_7_SaleLineItem>();
        items.clear();
        observerList = new ArrayList<_14211457_王耀_7_Observer>();
        observerList.clear();
    }
    
    public void registerObserver(_14211457_王耀_7_Observer observer){
    	observerList.add(observer);
    }
    
    public boolean removeObserver(_14211457_王耀_7_Observer observer){
    	return observerList.remove(observer);
    }

    public void addItem(_14211457_王耀_7_SaleLineItem item){
        items.add(item);
        for (_14211457_王耀_7_Observer obs: observerList)
        	obs.update();
    }
    
    public List<_14211457_王耀_7_SaleLineItem> getSaleLines(){
    	return items;
    }

    public double getTotal(){
        double totalPrice = 0;
        for (_14211457_王耀_7_SaleLineItem item: items){
            totalPrice += item.getSubTotal();
        }
        return totalPrice;
    }

	public boolean removeItem(_14211457_王耀_7_SaleLineItem _item) {
		for (_14211457_王耀_7_SaleLineItem item:items){
			if (item.getNumber() == _item.getNumber()){
				boolean ans =  items.remove(item);
				if (ans == true){
					for (_14211457_王耀_7_Observer obs: observerList)
						obs.update();
				}
		        return ans;
			}
		}
		return false;
	}
	
	public boolean removeItem(int saleLineNumber) {
		for (_14211457_王耀_7_SaleLineItem item:items){
			if (item.getNumber() == saleLineNumber){
				boolean ans =  items.remove(item);
				if (ans == true){
					for (_14211457_王耀_7_Observer obs: observerList)
						obs.update();
		        }
		        return ans;
			}
		}
		return false;
	}
	
	public void clearBook(_14211457_王耀_7_BookSpecification book){
		// 清除与参数的书相关的记录
		for (_14211457_王耀_7_SaleLineItem item: items){
			if (item.getProdSpec().getIsbn().equals(book.getIsbn())){
				items.remove(item);
				break;
			}
		}
	}
	
	public void updateStrategy(int strategyNumber){
		for (_14211457_王耀_7_SaleLineItem item: items){
			if (item.getStrategy().getStrategyNumber() == strategyNumber){
				item.updateStrategy();
			}
		}
	}
	
	public void updateStrategy(){
		for (_14211457_王耀_7_SaleLineItem item: items){
			item.updateStrategy();
		}
	}

	public void update() {
		for (_14211457_王耀_7_Observer obs: observerList)
			obs.update();
	}

	public void clear() {
		items.clear();
	}	
}
