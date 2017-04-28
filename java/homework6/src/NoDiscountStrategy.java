/**
 * Created by Forec on 2016/12/26.
 */
public class NoDiscountStrategy implements IPricingStrategy {
    public NoDiscountStrategy(){ }
    public double getSubTotal(SaleLineItem item){
        return item.getCopies() * item.getProdSpec().getPrice();
    }
}
