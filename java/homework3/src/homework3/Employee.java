package homework3;

/**
 * Created by Forec on 2016/12/4.
 */
public abstract class Employee {
    private String firstName, lastName, socialSecurityNumber;
    public Employee(String _firstName,
                    String _lastName,
                    String _socialSecurityNumber){
        this.firstName = _firstName;
        this.lastName = _lastName;
        this.socialSecurityNumber = _socialSecurityNumber;
    }
    public abstract int earning();
    public String toString(){
        return "Base Employee " + lastName + " " +
                firstName + ". Social Security Number: " +
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
