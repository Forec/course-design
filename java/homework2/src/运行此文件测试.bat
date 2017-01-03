javac -encoding utf8 homework2/*.java
echo 测试Student类
java homework2/_14211457_王耀_2_StudentTest
echo Student类测试完成
echo 测试StudentList类
java homework2/_14211457_王耀_2_StudentListTest
echo StudentList类测试完成
cd homework2
del *.class
cd ..