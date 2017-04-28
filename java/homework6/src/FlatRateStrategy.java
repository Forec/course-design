/**
 * Created by Forec on 2016/12/26.
 */
public class FlatRateStrategy implements IPricingStrategy {
    private double discountPerbook;
    public FlatRateStrategy(double _discountPerBook){
        discountPerbook = _discountPerBook;
    }
    public double getSubTotal(SaleLineItem item){
        return (item.getProdSpec().getPrice() - discountPerbook) * item.getCopies();
    }
}
