package homework3;

/**
 * Created by Forec on 2016/12/5.
 */
public class CommissionEmployee extends Employee {
    private int grossSales;
    private float commissionRate;
    public CommissionEmployee(String _firstName,
                           String _lastName,
                           String _socialSecurityNumber,
                           int _grossSales,
                           float _commissionRate){
        super(_firstName, _lastName, _socialSecurityNumber);
        this.grossSales = _grossSales;
        this.commissionRate = _commissionRate;
    }
    public int earning(){
        return (int)(this.commissionRate * this.grossSales);
    }
    public String toString(){
        return "CommissionEmployee " + super.getLastName() +
                " " + super.getFirstName() +
                ". Social Security Number: " +
                super.getSocialSecurityNumber();
    }
    public void setGrossSales(int _grossSales){
        this.grossSales = _grossSales;
    }
    public int getGrossSales(){
        return this.grossSales;
    }
    public void setCommissionRate(float _commissionRate){
        this.commissionRate = _commissionRate;
    }
    public float getCommissionRate(){
        return this.commissionRate;
    }
}
