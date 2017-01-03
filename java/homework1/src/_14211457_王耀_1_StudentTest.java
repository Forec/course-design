import java.util.Scanner;

class _14211457_王耀_1_StudentTest{
	public static void main(String [] argv){
		Scanner in = new Scanner(System.in);
		System.out.print("请输入学生学号: ");
		String number = in.nextLine();
		System.out.print("请输入学生姓名: ");
		String name = in.nextLine();
		System.out.print("请输入学生三门课成绩（数学，英语，科学）: ");
		String scores = in.nextLine();
		in.close();
		String [] scoreData = scores.split(",");
		int mathScore = Integer.parseInt(scoreData[0].trim());
		int englishScore = Integer.parseInt(scoreData[1].trim());
		int scienceScore = Integer.parseInt(scoreData[2].trim());
		_14211457_王耀_1_Student student = new _14211457_王耀_1_Student(number, name);
		student.enterMarks(mathScore, englishScore, scienceScore);
		System.out.println("学生信息如下:\n");
		System.out.println(student.toString());
	}
}