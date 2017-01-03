package homework3;

/**
 * Created by Forec on 2016/12/5.
 */
public class BasePlusCommissionEmployee
        extends CommissionEmployee{
    private int baseSalary;
    public BasePlusCommissionEmployee(String _firstName,
                                      String _lastName,
                                      String _socialSecurityNumber,
                                      int _grossSales,
                                      float _commissionRate,
                                      int _baseSalary){
        super(_firstName, _lastName, _socialSecurityNumber,
                _grossSales, _commissionRate);
        this.baseSalary = _baseSalary;
    }
    public String toString(){
        return "BasePlusCommissionEmployee " + super.getLastName() +
                " " + super.getFirstName() + ". Social Security Number: " +
                super.getSocialSecurityNumber();
    }
    public int earning(){
        return this.baseSalary + super.earning();
    }
    public int getBaseSalary(){
        return this.baseSalary;
    }
    public void setBaseSalary(int _baseSalary){
        this.baseSalary = _baseSalary;
    }
}
