package homework2;

import java.util.Scanner;

public class _14211457_王耀_2_StudentListTest {
	private static _14211457_王耀_2_Student generateStudentFromInput(Scanner in){
		System.out.println("请输入学生信息: ");
		System.out.print("学号: ");
		String number = in.next();
		try{
			int vanum = Integer.parseInt(number);
			if (number.length() != 10 ||
					number.codePointAt(0) != '2' ||
					number.codePointAt(1) != '0'){
				throw new _14211457_王耀_2_StudentNumberException();
			}
		}catch (NumberFormatException e){
			System.out.println("您输入的学号不合法，学号仅能包含0-9。");
			return null;
		}catch (_14211457_王耀_2_StudentNumberException e){
			System.out.println("您输入的学号不合法，学号开头两位必须为20，学号长度必须为10。");
			return null;
		}
		System.out.print("姓名: ");
		String name = in.next();
		int mathScore, englishScore, scienceScore;
		try{
			System.out.print("数学成绩: ");
			mathScore = in.nextInt();
			System.out.print("英语成绩: ");
			englishScore = in.nextInt();
			System.out.print("科学成绩: ");
			scienceScore = in.nextInt();
            if (mathScore < 0 || mathScore > 100 ||
                    englishScore < 0 || englishScore > 100 ||
                    scienceScore < 0 || scienceScore > 100){
                throw new _14211457_王耀_2_ScoreException();
            }
		}
        catch (_14211457_王耀_2_ScoreException e){
            System.out.println("输入的成绩不合法，必须在0 - 100 之间！");
            return null;
        }
        catch (Exception e){
            System.out.println("输入成绩格式不合法！");
            return null;
        }
		_14211457_王耀_2_Student student = new _14211457_王耀_2_Student(number, name);
		student.enterMarks(mathScore, englishScore, scienceScore);
		return student;
	}
	public static void main(String []argv){
		_14211457_王耀_2_StudentList sList = new _14211457_王耀_2_StudentList();
		Scanner in = new Scanner(System.in);
		int choice = 0;
		boolean validInput = false, exit = false;
		while (!exit){
			if (!validInput)
				System.out.println("菜单如下，请输入 1～9 代表您要执行的操作: \n" + 
							       "1.增加一个学生  2.根据学号删除学生  3.根据位置删除学生\n" +
							       "4.判断是否为空  5.根据位置返回学生  6.根据学号返回学生\n" +
							       "7.输出全部学生信息  8.退出程序     9.查看此菜单");
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
			if (choice > 9 || choice <= 0){
				System.out.println("输入的选项必须在 1～9 之间，请重新输入");
				validInput = false;
				continue;
			}
			switch (choice){
			case 1:
				_14211457_王耀_2_Student s = generateStudentFromInput(in);
				if (s == null){
					System.out.print("输入学生信息不合法，请重新选择你的操作");
					validInput = false;
				}else{
					if (!sList.addStudent(s))
						System.out.println("学号为 " + s.getNumber() + " 的学生已存在");
					else
						System.out.println("学生" + s.getName() + "添加成功");
				}
				break;
			case 2:
				System.out.print("输入你要删除学生的学号: ");
				if (sList.deleteStudentByNumber(in.next()))
					System.out.println("学生删除成功");
				else{
					System.out.println("输入信息有误，不存在该学号对应的学生");
				}
				break;
			case 3:
				System.out.print("输入你要删除学生的位置: ");
				try{
					if (sList.deleteStudentByIndex(in.nextInt()))
						System.out.println("学生删除成功");
					else{
						System.out.println("输入信息有误，该位置无学生");
					}
				}
				catch (Exception e){
					System.out.println("输入信息有误，不是合法的数字，请重新选择你的操作");
					validInput = false;
				}
				break;
			case 4:
				if (sList.isEmpty())
					System.out.println("当前学生列表为空");
				else
					System.out.println("当前共有 " + sList.getSize() + " 名学生");
				break;
			case 5:
				System.out.print("输入你要获取学生的位置: ");
				try{
					_14211457_王耀_2_Student s1;
					if ((s1 = sList.indexOf(in.nextInt())) != null)
						System.out.println(s1.toString());
					else{
						System.out.println("输入信息有误，该位置无学生");
					}
				}
				catch (Exception e){
					System.out.println("输入信息有误，不是合法的数字，请重新选择你的操作");
					validInput = false;
				}
				break;
			case 6:
				System.out.print("输入你要获取学生的学号: ");
				_14211457_王耀_2_Student s1;
				if (( s1 = sList.indexByNumber(in.next())) != null)
					System.out.println(s1.toString());
				else{
					System.out.println("输入信息有误，不存在该学号对应的学生");
				}
				break;
			case 7:
				System.out.print(sList.printAllStudents());
				break;
			case 8:
				in.close();
				exit = true;
				break;
			case 9:
				validInput = false;
				break;
			default:
				break;
			}
		}
	}
}
