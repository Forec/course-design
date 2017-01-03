package homework2;

public class _14211457_王耀_2_Student {
	private String studentNumber;
	private String studentName;
	private int markForMaths;
	private int markForEnglish;
	private int markForScience;
	public _14211457_王耀_2_Student(){
		this.studentName = "default";
		this.studentNumber = "default";
		this.markForMaths = 0;
		this.markForEnglish = 0;
		this.markForScience = 0;
	}
	public _14211457_王耀_2_Student(String number, String name){
		this.studentNumber = number;
		this.studentName = name;
		this.markForMaths = 0;
		this.markForEnglish = 0;
		this.markForScience = 0;
	}
	public String getName(){
		return this.studentName;
	}
	public String getNumber(){
		return this.studentNumber;
	}
	public void enterMarks(int markForMaths, int markForEnglish, int markForScience){
		this.markForMaths = markForMaths;
		this.markForEnglish = markForEnglish;
		this.markForScience = markForScience;
	}
	public int getMathsMark(){
		return this.markForMaths;
	}
	public int getEnglishMark(){
		return this.markForEnglish;
	}
	public int getScienceMark(){
		return this.markForScience;
	}
	public double calculateAverage(){
		return (markForMaths + markForEnglish + markForScience) / 3.0;
	}
	public String toString(){
		return "学号:"    + studentNumber  + "\t" + 
			   "姓名:"    + studentName    + "\t" +
			   "数学成绩:" + markForMaths   + "\t" +
			   "英语成绩:" + markForEnglish + "\t" +
			   "科学成绩:" + markForScience + "\t" +
			   "平均成绩:" + calculateAverage() + "\n";
	}
}

