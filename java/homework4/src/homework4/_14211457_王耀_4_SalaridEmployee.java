package homework4;

/**
 * Created by Forec on 2016/12/4.
 */
public class _14211457_王耀_4_SalaridEmployee extends _14211457_王耀_4_Employee {
    private int weeklySalary;
    public _14211457_王耀_4_SalaridEmployee(String _firstName,
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
        return "员工类型：SalaridEmployee\t员工名称" + super.getLastName() +
                "\t" + super.getFirstName() +
                "\t社会保险号： " +
                super.getSocialSecurityNumber();
    }
    public void setWeeklySalary(int _weeklySalary){
        this.weeklySalary = _weeklySalary;
    }
    public int getWeeklySalary(){
        return weeklySalary;
    }
}
