SRC_DIR = src/org/ioopm/calculator
JUNIT_JAR = ../../lib/junit-platform-console-standalone-1.8.1.jar
CLASSPATH = org.ioopm.calculator
OUT_DIR = classes

compile: 
	javac -d $(OUT_DIR) -sourcepath src $(SRC_DIR)/Calculator.java

run:
	java -cp $(OUT_DIR) $(CLASSPATH).Calculator

all: 
	javac -d $(OUT_DIR) -sourcepath src $(SRC_DIR)/Calculator.java
	java -cp $(OUT_DIR) $(CLASSPATH).Calculator


astTestsCompile: 
	javac -cp $(JUNIT_JAR) -d $(OUT_DIR) -sourcepath src $(SRC_DIR)/tests/AstTests.java

astTestsRun:
	java -cp $(JUNIT_JAR):$(OUT_DIR) -jar $(JUNIT_JAR) -cp $(OUT_DIR) -c $(CLASSPATH).tests.AstTests 

astTestsAll: 
	javac -cp $(JUNIT_JAR) -d $(OUT_DIR) -sourcepath src $(SRC_DIR)/tests/AstTests.java
	java -cp $(JUNIT_JAR):$(OUT_DIR) -jar $(JUNIT_JAR) -cp $(OUT_DIR) -c $(CLASSPATH).tests.AstTests 


integrationTestsCompile: 
	javac -cp $(JUNIT_JAR) -d $(OUT_DIR) -sourcepath src $(SRC_DIR)/tests/IntegrationTests.java

integrationTestsRun:
	java -cp $(JUNIT_JAR):$(OUT_DIR) -jar $(JUNIT_JAR) -cp $(OUT_DIR) -c $(CLASSPATH).tests.IntegrationTests 

integrationTestsAll: 
	javac -cp $(JUNIT_JAR) -d $(OUT_DIR) -sourcepath src $(SRC_DIR)/tests/IntegrationTests.java
	java -cp $(JUNIT_JAR):$(OUT_DIR) -jar $(JUNIT_JAR) -cp $(OUT_DIR) -c $(CLASSPATH).tests.IntegrationTests 


systemTests: 
	javac -d $(OUT_DIR) -sourcepath src $(SRC_DIR)/Calculator.java
	java  -cp $(OUT_DIR) $(CLASSPATH).Calculator < $(SRC_DIR)/tests/test1.txt > $(SRC_DIR)/tests/output/output1.txt
	java  -cp $(OUT_DIR) $(CLASSPATH).Calculator < $(SRC_DIR)/tests/test2.txt > $(SRC_DIR)/tests/output/output2.txt
	java  -cp $(OUT_DIR) $(CLASSPATH).Calculator < $(SRC_DIR)/tests/test3.txt > $(SRC_DIR)/tests/output/output3.txt
	java  -cp $(OUT_DIR) $(CLASSPATH).Calculator < $(SRC_DIR)/tests/invalid.txt > $(SRC_DIR)/tests/output/outputInvalid.txt

diff: 
	diff $(SRC_DIR)/tests/output/output1.txt $(SRC_DIR)/tests/test1Expected.txt
	diff $(SRC_DIR)/tests/output/output2.txt $(SRC_DIR)/tests/test2Expected.txt
	diff $(SRC_DIR)/tests/output/output3.txt $(SRC_DIR)/tests/test3Expected.txt
	diff $(SRC_DIR)/tests/output/outputInvalid.txt $(SRC_DIR)/tests/invalidExpected.txt

txtTestsAll: systemTests diff


tests: astTests parserTests systemTests diff


clean:
	rm -rf $(OUT_DIR) 
	rm -f $(SRC_DIR)/tests/output/*.txt

.PHONY: compile run clean calcCompRun tests astTestCompile astTests parserTestCompile parserTests systemTests diff
