package homework4;

/**
 * Created by Forec on 2016/12/5.
 */
public class _14211457_王耀_4_HourlyEmployee extends _14211457_王耀_4_Employee{
    private int wage, hours;
    public _14211457_王耀_4_HourlyEmployee(String _firstName,
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
        return "员工类型：HourlyEmployee\t员工名称：" + super.getLastName() +
                "\t" + super.getFirstName() +
                "\t社会保险号： " +
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
