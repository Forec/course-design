package homework5;

/**
 * Created by Forec on 2016/12/4.
 */
public class _14211457_王耀_5_SalaridEmployee extends _14211457_王耀_5_Employee {
    private int weeklySalary;
    public _14211457_王耀_5_SalaridEmployee(String _firstName,
                                          String _lastName,
                                          String _socialSecurityNumber,
                                          int _weeklySalary){
        super(_firstName, _lastName, _socialSecurityNumber);
        this.weeklySalary = _weeklySalary;
    }
    public int earning(){
        return weeklySalary * 4;
    }
    public String toString(){
        return "员工类型：_14211457_王耀_5_SalaridEmployee   员工名称" + super.getLastName() +
                " " + super.getFirstName() +
                "  社会保险号： " +
                super.getSocialSecurityNumber();
    }
    public void setWeeklySalary(int _weeklySalary){
        this.weeklySalary = _weeklySalary;
    }
    public int getWeeklySalary(){
        return weeklySalary;
    }
}
