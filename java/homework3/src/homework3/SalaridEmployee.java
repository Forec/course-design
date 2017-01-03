package homework3;

/**
 * Created by Forec on 2016/12/4.
 */
public class SalaridEmployee extends Employee {
    private int weeklySalary;
    public SalaridEmployee(String _firstName,
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
        return "SalaridEmployee " + super.getLastName() +
                " " + super.getFirstName() +
                ". Social Security Number: " +
                super.getSocialSecurityNumber();
    }
    public void setWeeklySalary(int _weeklySalary){
        this.weeklySalary = _weeklySalary;
    }
    public int getWeeklySalary(){
        return weeklySalary;
    }
}
