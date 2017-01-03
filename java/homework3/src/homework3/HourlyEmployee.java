package homework3;

/**
 * Created by Forec on 2016/12/5.
 */
public class HourlyEmployee extends Employee{
    private int wage, hours;
    public HourlyEmployee(String _firstName,
                           String _lastName,
                           String _socialSecurityNumber,
                           int _wage,
                           int _hours){
        super(_firstName, _lastName, _socialSecurityNumber);
        this.wage = _wage;
        this.hours = _hours;
    }
    public int earning(){
        return this.wage * this.hours;
    }
    public String toString(){
        return "HourlyEmployee " + super.getLastName() +
                " " + super.getFirstName() +
                ". Social Security Number: " +
                super.getSocialSecurityNumber();
    }
    public void setWage(int _wage){
        this.wage = _wage;
    }
    public int getWage(){
        return this.wage;
    }
    public void setHours(int _hours){
        this.hours = _hours;
    }
    public int getHours(){
        return this.hours;
    }
}
