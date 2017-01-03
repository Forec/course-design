package homework5;

import java.util.*;

/**
 * Created by Forec on 2016/12/24.
 * The test file will create a factory and you can test it.
 */
public class _14211457_王耀_5_TestFactory {

    public static void main(String []argv){
        _14211457_王耀_5_Factory factory = new _14211457_王耀_5_Factory();
        factory.initEmployees();
        Scanner in = new Scanner(System.in);
        boolean validInput = false, exit = false;
        int choice;
        System.out.println("已为您生成 10 个随机员工，他们的保险号分别为：");
        factory.printEmployeeNumbers();
        while (!exit){
            if (!validInput)
                System.out.println("菜单如下，请输入 1～6 代表您要测试的方法: \n" +
                        "1.输入保险号查询员工  2.输入保险号更新员工  \n" +
                        "3.输入保险号删除员工  4.打印全部员工信息  \n" +
                        "5.退出                6.查看此菜单");
            System.out.print("请输入您的选项: ");
            validInput = true;
            try{
                choice = Integer.parseInt(in.next());
            }
            catch (NumberFormatException e){
                System.out.println("您的输入不合法，请重新输入");
                validInput = false;
                continue;
            }
            if (choice > 6 || choice <= 0){
                System.out.println("输入的选项必须在 1～6 之间，请重新输入");
                validInput = false;
                continue;
            }
            switch (choice){
                case 1:
                    System.out.println("请输入保险号以查询员工信息: ");
                    String sec1 = in.next();
                    _14211457_王耀_5_Employee e1= factory.getEmployee(sec1);
                    if (e1 == null) {
                        System.out.println("不存在保险号为 " + sec1 + " 的员工！");
                    } else {
                        System.out.println("保险号为 " + sec1 + " 的员工信息如下：");
                        System.out.println(e1.toString());
                        System.out.println("每月工资： " + e1.earning());
                    }
                    break;
                case 2:
                    System.out.print("输入保险号更新员工: ");
                    String sec2 = in.next();
                    _14211457_王耀_5_Employee e2= factory.getEmployee(sec2);
                    if (e2 == null) {
                        System.out.println("不存在保险号为 " + sec2 + " 的员工！");
                    } else {
                        _14211457_王耀_5_Employee _e = factory.randomEmployee();
                        factory.updateEmployee(sec2, _e);
                        System.out.println("已为您将保险号为 " + sec2 +
                                " 的员工更新为新生成的随机员工，新员工信息为：");
                        System.out.println(_e.toString());
                        System.out.println("每月工资： " + _e.earning());
                    }

                    break;
                case 3:
                    System.out.print("输入保险号删除员工: ");
                    String sec3 = in.next();
                    _14211457_王耀_5_Employee e3 = factory.deleteEmployee(sec3);
                    if (e3 == null) {
                        System.out.println("不存在保险号为 " + sec3 + " 的员工！");
                    } else {
                        System.out.println("保险号号为 " + sec3 + " 的员工已删除！其信息为：");
                        System.out.println(e3.toString());
                        System.out.println("每月工资： " + e3.earning());
                    }
                    break;
                case 4:
                    System.out.println("当前工厂中全部员工信息如下：");
                    factory.printEmployees();
                    break;
                case 5:
                    in.close();
                    exit = true;
                    break;
                case 6:
                    validInput = false;
                    break;
                default:
                    break;
            }
        }
    }
}
