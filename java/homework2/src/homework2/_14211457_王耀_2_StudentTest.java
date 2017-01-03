package homework2;

import java.util.Scanner;

class _14211457_王耀_2_StudentTest {
	public static void main(String [] argv){
		Scanner in = new Scanner(System.in);
		System.out.print("请输入学生学号: ");
		String number = in.nextLine();
		try{
            int vanum = Integer.parseInt(number);
            if (number.length() != 10 ||
                    number.codePointAt(0) != '2' ||
                    number.codePointAt(1) != '0'){
                throw new _14211457_王耀_2_StudentNumberException();
            }
        }catch (NumberFormatException e){
            System.out.println("您输入的学号不合法，学号仅能包含0-9。");
            return;
        }catch (_14211457_王耀_2_StudentNumberException e){
            System.out.println("您输入的学号不合法，学号开头两位必须为20，学号长度必须为10。");
            return;
        }
		System.out.print("请输入学生姓名: ");
		String name = in.nextLine();
		System.out.print("请输入学生三门课成绩（数学，英语，科学）: ");
		String scores = in.nextLine();
		in.close();
		String [] scoreData = scores.split(",");
        int mathScore, englishScore, scienceScore;
        try {
            mathScore = Integer.parseInt(scoreData[0].trim());
            englishScore = Integer.parseInt(scoreData[1].trim());
            scienceScore = Integer.parseInt(scoreData[2].trim());
            if (mathScore < 0 || mathScore > 100 ||
                    englishScore < 0 || englishScore > 100 ||
                    scienceScore < 0 || scienceScore > 100){
                throw new _14211457_王耀_2_ScoreException();
            }
        }
        catch (NumberFormatException e) {
            System.out.println("输入的成绩只能包含数字！");
            return;
        }
        catch (_14211457_王耀_2_ScoreException e){
            System.out.println("输入的成绩不合法，必须在0 - 100 之间！");
            return;
        }
        catch (Exception e){
            System.out.println("输入成绩格式不合法！");
            return;
        }
		_14211457_王耀_2_Student student = new _14211457_王耀_2_Student(number, name);
		student.enterMarks(mathScore, englishScore, scienceScore);
		System.out.println("学生信息如下:\n");
		System.out.println(student.toString());
	}
}