package homework7;


public class _14211457_王耀_7_Controller {
	// 控制器
	private _14211457_王耀_7_ShoppingCart shoppingCart;
	private static _14211457_王耀_7_Controller instance = null;
	private _14211457_王耀_7_Controller(){
		shoppingCart = new _14211457_王耀_7_ShoppingCart();
	}
	
	public static _14211457_王耀_7_Controller getInstance(){
		if (instance == null)
			instance = new _14211457_王耀_7_Controller();
		return instance;
	}
	
	public _14211457_王耀_7_ShoppingCart getShoppingCart(){
		return _14211457_王耀_7_Controller.getInstance().shoppingCart;
	}
	
	public _14211457_王耀_7_IPricingStrategy getStrategy(int strategyNumber){
		return _14211457_王耀_7_StrategyManager.getInstance().getStrategy(strategyNumber);
	}
	
	public void AddStrategy(_14211457_王耀_7_IPricingStrategy strategy){
		_14211457_王耀_7_StrategyManager.getInstance().addStrategy(strategy);
	}
	
	public _14211457_王耀_7_IPricingStrategy RemoveStrategy(int strategyNumber){
		// 需更新优惠策略
		_14211457_王耀_7_IPricingStrategy strategy =  _14211457_王耀_7_StrategyManager.getInstance().removeStrategy(strategyNumber);
		_14211457_王耀_7_Controller.getInstance().shoppingCart.updateStrategy(strategyNumber);
		return strategy;
	}
	
	public _14211457_王耀_7_BookSpecification getBook(String isbn){
		return _14211457_王耀_7_BookManager.getInstance().getBook(isbn);
	}
	
	public void AddBook(_14211457_王耀_7_BookSpecification book){
		_14211457_王耀_7_BookManager.getInstance().addBook(book);
	}
	
	public boolean RemoveBook(String isbn){	// 删除书籍同时需要删除连带的消费记录
		_14211457_王耀_7_BookSpecification book = _14211457_王耀_7_BookManager.getInstance().getBook(isbn);
		if (book == null){
			return false;
		}
		if (_14211457_王耀_7_BookManager.getInstance().removeBook(isbn)){
			// 删除成功，删除相关购物车信息
			_14211457_王耀_7_Controller.getInstance().shoppingCart.clearBook(book);
			return true;
		}
		return false;
	}
	
	public boolean AddSaleItem(String isbn, int copies){
		_14211457_王耀_7_BookSpecification book = _14211457_王耀_7_Controller.getInstance().getBook(isbn);
		if (book == null){
			return false;
		}
		_14211457_王耀_7_SaleLineItem item = new _14211457_王耀_7_SaleLineItem(copies, book);
		_14211457_王耀_7_Controller.getInstance().shoppingCart.addItem(item);
		return true;
	}
	
	public void AddSaleItem(_14211457_王耀_7_SaleLineItem item){
		_14211457_王耀_7_Controller.getInstance().shoppingCart.addItem(item);
	}
	
	public boolean RemoveSaleItem(_14211457_王耀_7_SaleLineItem item){
		return _14211457_王耀_7_Controller.getInstance().shoppingCart.removeItem(item);
	}

	public boolean RemoveSaleItem(int saleLineNumber){
		return _14211457_王耀_7_Controller.getInstance().shoppingCart.removeItem(saleLineNumber);
	}	
	
	public void updateBook(){
		_14211457_王耀_7_BookManager.getInstance().update();
	}
	
	public void updateStrategy(){
		_14211457_王耀_7_StrategyManager.getInstance().update();
	}
	
	public void updateSale(){
		_14211457_王耀_7_Controller.getInstance().shoppingCart.update();
	}

	public void random() {
		_14211457_王耀_7_TestSale.init();
	}
	
	public void clearShopCart(){
		_14211457_王耀_7_Controller.getInstance().shoppingCart.clear();
	}
	
	public void clearShopBook(_14211457_王耀_7_BookSpecification book){
		_14211457_王耀_7_Controller.getInstance().shoppingCart.clearBook(book);		
	}
}
