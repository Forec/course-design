package homework5;

/**
 * Created by Forec on 2016/12/5.
 */
public class _14211457_王耀_5_EmployeeCommission extends _14211457_王耀_5_Employee {
    private int grossSales;
    private float commissionRate;
    public _14211457_王耀_5_EmployeeCommission(String _firstName,
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
        return "员工类型：_14211457_王耀_5_EmployeeCommission   员工名称：" + super.getLastName() +
                " " + super.getFirstName() +
                "  社会保险号： " +
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
