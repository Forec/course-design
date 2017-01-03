package homework3;

import java.util.*;

/**
 * Created by Forec on 2016/12/5.
 * The test file will create 10 random employees, their names
 * are generated randomly. Their social security numbers
 * consists 10 letters. The commission rate for Commission-
 * Employee is ranging from 0.01 to 1.00.
 */
public class TestEmployees {
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
    private static Employee BuildEmployee(Random random, int type){
        Employee temp;
        switch (type){
            case 0:
                temp = new SalaridEmployee(
                        RandomString(random, RandomRange(random, 3,6)),     // firstName
                        RandomString(random, RandomRange(random, 3,6)),     // lastName
                        RandomString(random, 10),                           // socialSecurityNumber
                        RandomRange(random, 1000, 2000));                   // weeklySalary
                break;
            case 1:
                temp = new CommissionEmployee(
                        RandomString(random, RandomRange(random, 3,6)),     // firstName
                        RandomString(random, RandomRange(random, 3,6)),     // lastName
                        RandomString(random, 10),                           // socialSecurityNumber
                        RandomRange(random, 1000, 2000),                    // grossSales
                        ((float)RandomRange(random, 1, 100))/100);          // commissionRate
                break;
            case 2:
                temp = new HourlyEmployee(
                        RandomString(random, RandomRange(random, 3,6)),     // firstName
                        RandomString(random, RandomRange(random, 3,6)),     // lastName
                        RandomString(random, 10),                           // socialSecurityNumber
                        RandomRange(random, 100, 200),                      // wage
                        RandomRange(random, 20, 48));                       // hours
                break;
            case 3:
                temp = new BasePlusCommissionEmployee(
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
    public static void main(String []argv){
        Random random = new Random();
        List<Employee> employeeList = new ArrayList<Employee>();
        employeeList.clear();
        for (int i = 0; i < 10; i++){
            employeeList.add(BuildEmployee(random, RandomRange(random, 0, 4)));
        }
        for (Employee e : employeeList) {
            System.out.println(e.toString());
            System.out.println("Salary per month: " + e.earning());
        }
    }
}
