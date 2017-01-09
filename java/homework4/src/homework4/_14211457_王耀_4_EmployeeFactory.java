package homework4;

import java.util.*;

/**
 * Created by Forec on 2016/12/5.
 * The test file will create 10 random employees, their names
 * are generated randomly. Their social security numbers
 * consists 10 letters. The commission rate for Commission-
 * Employee is ranging from 0.01 to 1.00.
 */
public class _14211457_王耀_4_EmployeeFactory {
	private List<_14211457_王耀_4_Employee> employeeList;
	private Random random;
    private static String RandomString(Random random, int length){
        String str="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        StringBuffer buf = new StringBuffer();
        for(int i = 0 ;i < length ; i ++) {
            int num = random.nextInt(62);
            buf.append(str.charAt(num));
        }
        return buf.toString();
    }
    private static int RandomRange(Random random, int min, int max){
        return Math.abs(random.nextInt()) % (max - min) + min;
    }
    private static _14211457_王耀_4_Employee BuildRandomEmployee(Random random, int type){
        _14211457_王耀_4_Employee temp;
        switch (type){
            case 0:
                temp = new _14211457_王耀_4_SalaridEmployee(
                        RandomString(random, RandomRange(random, 3,6)),     // firstName
                        RandomString(random, RandomRange(random, 3,6)),     // lastName
                        RandomString(random, 10),                           // socialSecurityNumber
                        RandomRange(random, 1000, 2000));                   // weeklySalary
                break;
            case 1:
                temp = new _14211457_王耀_4_CommissionEmployee(
                        RandomString(random, RandomRange(random, 3,6)),     // firstName
                        RandomString(random, RandomRange(random, 3,6)),     // lastName
                        RandomString(random, 10),                           // socialSecurityNumber
                        RandomRange(random, 1000, 2000),                    // grossSales
                        ((float)RandomRange(random, 1, 100))/100);          // commissionRate
                break;
            case 2:
                temp = new _14211457_王耀_4_HourlyEmployee(
                        RandomString(random, RandomRange(random, 3,6)),     // firstName
                        RandomString(random, RandomRange(random, 3,6)),     // lastName
                        RandomString(random, 10),                           // socialSecurityNumber
                        RandomRange(random, 100, 200),                      // wage
                        RandomRange(random, 20, 48));                       // hours
                break;
            case 3:
                temp = new _14211457_王耀_4_BasePlusCommissionEmployee(
                        RandomString(random, RandomRange(random, 3,6)),     // firstName
                        RandomString(random, RandomRange(random, 3,6)),     // lastName
                        RandomString(random, 10),                           // socialSecurityNumber
                        RandomRange(random, 1000, 2000),                    // grossSales
                        ((float)RandomRange(random, 1, 100))/100,           // commissionRate
                        RandomRange(random, 1000, 2000));                   // baseSalary
                break;
            default:
                temp = null;
        }
        return temp;
    }
    
    public _14211457_王耀_4_EmployeeFactory(){
    	random = new Random();
    	employeeList = new ArrayList<_14211457_王耀_4_Employee>();
        employeeList.clear();
    }
    public void init(){
        employeeList.clear();
        for (int i = 0; i < 10; i++){
            employeeList.add(BuildRandomEmployee(random, RandomRange(random, 0, 4)));
        }
    }
    
    public List<_14211457_王耀_4_Employee> getEmployeeList(){
    	return employeeList;
    }
    
    public void addRandomEmployee(int type){
        employeeList.add(BuildRandomEmployee(random, type));
    }
    
    public void addEmployee(_14211457_王耀_4_Employee e){
        employeeList.add(e);
    }
    
    public int getAverage(){
    	int ave = 0;
    	for (_14211457_王耀_4_Employee e: employeeList){
    		ave += e.earning();
    	}
    	ave = (int)(ave/employeeList.size());
    	return ave;
    }
    
    public int getEmployeesCount(){
    	return employeeList.size();
    }
}
