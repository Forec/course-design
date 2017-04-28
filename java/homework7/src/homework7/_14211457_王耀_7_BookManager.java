package homework7;
import java.util.ArrayList;
import java.util.List;

public class _14211457_王耀_7_BookManager {

	private List<_14211457_王耀_7_Observer> observerList;
    private List<_14211457_王耀_7_BookSpecification> bookSet;
    private static _14211457_王耀_7_BookManager instance = null;     // 此类为单子

    private _14211457_王耀_7_BookManager(){
        bookSet = new ArrayList<_14211457_王耀_7_BookSpecification>();
        bookSet.clear();
        observerList = new ArrayList<_14211457_王耀_7_Observer>();
        observerList.clear();
    }
    
    public void registerObserver(_14211457_王耀_7_Observer observer){
    	_14211457_王耀_7_BookManager.getInstance().observerList.add(observer);
    }
    
    public boolean removeObserver(_14211457_王耀_7_Observer observer){
    	return _14211457_王耀_7_BookManager.getInstance().observerList.remove(observer);
    }

    public static _14211457_王耀_7_BookManager getInstance(){
        if (instance == null)
            instance = new _14211457_王耀_7_BookManager();
        return instance;
    }
    
    public List<_14211457_王耀_7_BookSpecification> getBooks(){
    	return bookSet;
    }

    public void addBook(_14211457_王耀_7_BookSpecification book){
        for (_14211457_王耀_7_BookSpecification b: _14211457_王耀_7_BookManager.getInstance().bookSet){
            if (b.getIsbn() == book.getIsbn())      // 保证 ISBN 号唯一
                return;
        }
        _14211457_王耀_7_BookManager.getInstance().bookSet.add(book);
        for (_14211457_王耀_7_Observer obs: _14211457_王耀_7_BookManager.getInstance().observerList){
        	obs.update();
        }
    }
    
    public _14211457_王耀_7_BookSpecification getBook(String isbn){
    	for (_14211457_王耀_7_BookSpecification b: _14211457_王耀_7_BookManager.getInstance().bookSet){
    		if (b.getIsbn().equals(isbn)){
    			return b;
    		}
    	}
    	return null;
    }

    public boolean removeBook(_14211457_王耀_7_BookSpecification book){
        if (instance != null){
            for (_14211457_王耀_7_BookSpecification b:instance.bookSet){
                if (b.getIsbn().equals(book.getIsbn())){
                    boolean ans =  instance.bookSet.remove(b);
                    for (_14211457_王耀_7_Observer obs: _14211457_王耀_7_BookManager.getInstance().observerList){
                    	obs.update();
                    }
                    return ans;
                }
            }
        }
        return false;
    }
    
    public boolean removeBook(String isbn){
        if (instance != null){
            for (_14211457_王耀_7_BookSpecification b:instance.bookSet){
                if (b.getIsbn().equals(isbn)){
                    boolean ans = instance.bookSet.remove(b);
                    for (_14211457_王耀_7_Observer obs: _14211457_王耀_7_BookManager.getInstance().observerList){
                    	obs.update();
                    }
                    return ans;
                }
            }
        }
        return false;
    }

    public void update(){
        for (_14211457_王耀_7_Observer obs: _14211457_王耀_7_BookManager.getInstance().observerList){
        	obs.update();
        }
    }
}
