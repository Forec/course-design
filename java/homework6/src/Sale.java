import java.util.ArrayList;

/**
 * Created by Forec on 2016/12/26.
 */
public class Sale {
    private ArrayList<SaleLineItem> items;

    public Sale(){
        items = new ArrayList<SaleLineItem>();
        items.clear();
    }

    public void addItem(SaleLineItem item){
        items.add(item);
    }

    public double getTotal(){
        double totalPrice = 0;
        for (SaleLineItem item: items){
            totalPrice += item.getSubTotal();
        }
        return totalPrice;
    }
}
