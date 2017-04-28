/**
 * Created by Forec on 2016/12/26.
 */
public class PercentageStrategy implements IPricingStrategy{
    private int discountPercentage;
    public PercentageStrategy(int _discountPercentage){
        discountPercentage = _discountPercentage;
    }
    public double getSubTotal(SaleLineItem item){
        return item.getProdSpec().getPrice() * (100- discountPercentage) * item.getCopies() / 100.0;
    }
}
