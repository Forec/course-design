package homework2;

import java.util.*;

public class _14211457_王耀_2_StudentList {
	private List<_14211457_王耀_2_Student> stuList;
	public _14211457_王耀_2_StudentList(){
		stuList = new ArrayList<_14211457_王耀_2_Student>();
		stuList.clear();
	}
	public boolean addStudent(_14211457_王耀_2_Student student){
		if (student != null && !hasStudentByNumber(student.getNumber())){
			stuList.add(student);
			return true;
		}
		return false;
	}
	public boolean hasStudentByNumber(String number){
		return !(indexByNumber(number) == null);
	}
	public boolean deleteStudentByNumber(String number){
		for (_14211457_王耀_2_Student s: stuList){
			if (s.getNumber().equals(number)){
				return stuList.remove(s);
			}
		}
		return false;
	}
	public boolean deleteStudentByIndex(int index){
		try{
			stuList.remove(index);
			return true;
		}
		catch (IndexOutOfBoundsException e){
			return false;
		}
	}
	public boolean isEmpty(){
		return stuList.isEmpty();
	}
	public int getSize(){
		return stuList.size();
	}
	public _14211457_王耀_2_Student indexOf(int index){
		try{
			return stuList.get(index);
		}
		catch (IndexOutOfBoundsException e){
			return null;
		}
	}
	public _14211457_王耀_2_Student indexByNumber(String number){
		for (_14211457_王耀_2_Student s: stuList){
			if (s.getNumber().equals(number)){
				return s;
			}
		}
		return null;
	}
	public String printAllStudents(){
		String ans;
		if (stuList.size() != 0)
			ans = "目前有" + stuList.size() + "个学生，信息为: \n";
		else
			ans = "目前没有学生\n";
		for (_14211457_王耀_2_Student s: stuList){
			ans += s.toString();
		}
		return ans;
	}
}
