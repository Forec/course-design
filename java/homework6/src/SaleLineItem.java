/**
 * Created by Forec on 2016/12/26.
 */
public class SaleLineItem {
    private int copies;
    private ProductSpecification prodSpec;
    private IPricingStrategy strategy;
    public SaleLineItem(int _copies,
                        ProductSpecification _prodSpec){
        copies = _copies;
        prodSpec = _prodSpec;
        strategy = PricingStrategyFactory.getInstance().getPricingStrategy(prodSpec.getType());
    }
    public int getCopies(){
        return copies;
    }

    public ProductSpecification getProdSpec(){
        return prodSpec;
    }

    public double getSubTotal(){
        return strategy.getSubTotal(this);
    }
}
