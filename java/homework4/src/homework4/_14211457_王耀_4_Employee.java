package homework4;

/**
 * Created by Forec on 2016/12/4.
 */
public abstract class _14211457_王耀_4_Employee {
    private String firstName, lastName, socialSecurityNumber;
    public _14211457_王耀_4_Employee(String _firstName,
                    String _lastName,
                    String _socialSecurityNumber){
        this.firstName = _firstName;
        this.lastName = _lastName;
        this.socialSecurityNumber = _socialSecurityNumber;
    }
    public abstract int earning();
    public String toString(){
        return "员工名称： " + lastName + "\t" +
                firstName + "\t社会保险号： " +
                socialSecurityNumber;
    }
    public String getFirstName(){
        return firstName;
    }
    public String getLastName(){
        return lastName;
    }
    public String getSocialSecurityNumber(){
        return socialSecurityNumber;
    }
    public void setFirstName(String _firstName){
        this.firstName = _firstName;
    }
    public void setLastName(String _lastName){
        this.lastName = _lastName;
    }
}
