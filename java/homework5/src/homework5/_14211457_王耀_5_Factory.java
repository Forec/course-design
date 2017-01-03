package homework5;

import java.util.HashMap;
import java.util.Random;

/**
 * Created by Forec on 2016/12/24.
 */
public class _14211457_王耀_5_Factory {
    private HashMap<String, _14211457_王耀_5_Employee> employees;

    // 私有方法，随机生成指定长度的字符串
    private static String RandomString(Random random, int length){
        String str="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        StringBuffer buf = new StringBuffer();
        for(int i = 0 ;i < length ; i ++) {
            int num = random.nextInt(62);
            buf.append(str.charAt(num));
        }
        return buf.toString();
    }

    // 私有方法，随机生成一个区间内的数值
    private static int RandomRange(Random random, int min, int max){
        return Math.abs(random.nextInt()) % (max - min) + min;
    }

    // 私有方法，随机生成不同类型、不同属性的 _14211457_王耀_5_Employee
    private static _14211457_王耀_5_Employee BuildEmployee(Random random,
                                                         int type,
                                                         String socialSecurityNumber){
        _14211457_王耀_5_Employee temp;
        switch (type){
            case 0:
                temp = new _14211457_王耀_5_SalaridEmployee(
                        RandomString(random, RandomRange(random, 3,6)),     // firstName
                        RandomString(random, RandomRange(random, 3,6)),     // lastName
                        socialSecurityNumber,                               // socialSecurityNumber
                        RandomRange(random, 1000, 2000));                   // weeklySalary
                break;
            case 1:
                temp = new _14211457_王耀_5_EmployeeCommission(
                        RandomString(random, RandomRange(random, 3,6)),     // firstName
                        RandomString(random, RandomRange(random, 3,6)),     // lastName
                        socialSecurityNumber,                               // socialSecurityNumber
                        RandomRange(random, 1000, 2000),                    // grossSales
                        ((float)RandomRange(random, 1, 100))/100);          // commissionRate
                break;
            case 2:
                temp = new _14211457_王耀_5_HourlyEmployee(
                        RandomString(random, RandomRange(random, 3,6)),     // firstName
                        RandomString(random, RandomRange(random, 3,6)),     // lastName
                        socialSecurityNumber,                               // socialSecurityNumber
                        RandomRange(random, 100, 200),                      // wage
                        RandomRange(random, 20, 48));                       // hours
                break;
            case 3:
                temp = new _14211457_王耀_5_EmployeeBasePlusCommission(
                        RandomString(random, RandomRange(random, 3,6)),     // firstName
                        RandomString(random, RandomRange(random, 3,6)),     // lastName
                        socialSecurityNumber,                               // socialSecurityNumber
                        RandomRange(random, 1000, 2000),                    // grossSales
                        ((float)RandomRange(random, 1, 100))/100,           // commissionRate
                        RandomRange(random, 1000, 2000));                   // baseSalary
                break;
            default:
                temp = null;
        }
        return temp;
    }

    // 工厂构造方法
    public _14211457_王耀_5_Factory(){
        employees = new HashMap<String, _14211457_王耀_5_Employee>();
    }

    // 初始化 10 个随机的 _14211457_王耀_5_Employee
    public void initEmployees(){
        Random random = new Random();
        employees.clear();
        for (int i = 0; i < 10; i++){
            String randomSocialSecurityNumber = RandomString(random, 10);
            employees.put(randomSocialSecurityNumber,
                         BuildEmployee(random,
                                       RandomRange(random, 0, 4),
                                       randomSocialSecurityNumber));
        }
        System.out.println("为避免助教验收时输入 socialSecurityNumber 的麻烦，" +
                "initEmployees() 方法已随机生成了 10 个随机类型、属性的 _14211457_王耀_5_Employee " +
                "并存入 HashMap employees 中");
    }

    // 完全随机生成一个新员工并返回
    public _14211457_王耀_5_Employee randomEmployee(){
        Random random = new Random();
        String randomSocialSecurityNumber = RandomString(random, 10);
        return BuildEmployee(random,
                RandomRange(random, 0, 4),
                randomSocialSecurityNumber);
    }

    // 查找并返回社会保险号为 empSecNum 的员工
    public _14211457_王耀_5_Employee getEmployee(String empSecNum){
        return employees.get(empSecNum);
    }

    // 删除社会保险号为 empSecNum 的员工并返回其引用
    public _14211457_王耀_5_Employee deleteEmployee(String empSecNum){
        return employees.remove(empSecNum);
    }

    // 添加参数定义的员工对象到员工集合中
    public _14211457_王耀_5_Employee addEmplooyee(_14211457_王耀_5_Employee stu){
        return employees.put(stu.getSocialSecurityNumber(), stu);
    }

    // 更新社会保险号为 empSecNum 的员工对象信息
    public _14211457_王耀_5_Employee updateEmployee(String empSecNum, _14211457_王耀_5_Employee emp){
        return employees.replace(empSecNum, emp);
    }

    // 输出每一个员工信息
    public void printEmployees(){
        for (_14211457_王耀_5_Employee e:employees.values()){
            System.out.println(e.toString());
            System.out.println("每月工资： " + e.earning());
        }
    }

    // 输出每一个员工的保险号
    public void printEmployeeNumbers(){
        for (_14211457_王耀_5_Employee e:employees.values()){
            System.out.println(e.getSocialSecurityNumber());
        }
    }

}
