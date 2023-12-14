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

astTestsAll: astTestsCompile astTestsRun


integrationTestsCompile: 
	javac -cp $(JUNIT_JAR) -d $(OUT_DIR) -sourcepath src $(SRC_DIR)/tests/IntegrationTests.java

integrationTestsRun:
	java -cp $(JUNIT_JAR):$(OUT_DIR) -jar $(JUNIT_JAR) -cp $(OUT_DIR) -c $(CLASSPATH).tests.IntegrationTests 

integrationTestsAll: integrationTestsCompile integrationTestsRun


systemTests: compile
	java  -cp $(OUT_DIR) $(CLASSPATH).Calculator < $(SRC_DIR)/tests/test1.txt > $(SRC_DIR)/tests/output/output1.txt
	java  -cp $(OUT_DIR) $(CLASSPATH).Calculator < $(SRC_DIR)/tests/test2.txt > $(SRC_DIR)/tests/output/output2.txt
	java  -cp $(OUT_DIR) $(CLASSPATH).Calculator < $(SRC_DIR)/tests/test3.txt > $(SRC_DIR)/tests/output/output3.txt
	java  -cp $(OUT_DIR) $(CLASSPATH).Calculator < $(SRC_DIR)/tests/invalid.txt > $(SRC_DIR)/tests/output/outputInvalid.txt

diff: 
	diff $(SRC_DIR)/tests/output/output1.txt $(SRC_DIR)/tests/expected/test1Expected.txt
	diff $(SRC_DIR)/tests/output/output2.txt $(SRC_DIR)/tests/expected/test2Expected.txt
	diff $(SRC_DIR)/tests/output/output3.txt $(SRC_DIR)/tests/expected/test3Expected.txt
	diff $(SRC_DIR)/tests/output/outputInvalid.txt $(SRC_DIR)/tests/expected/invalidExpected.txt

ultimatetests: compile
	java  -cp $(OUT_DIR) $(CLASSPATH).Calculator < $(SRC_DIR)/tests/ultimatetests.txt > $(SRC_DIR)/tests/output/outputUltimate.txt
	diff $(SRC_DIR)/tests/output/outputUltimate.txt $(SRC_DIR)/tests/expected/ulitmateExpected.txt

txtTestsAll: systemTests diff ultimatetests


tests: astTestsAll integrationTestsAll txtTestsAll ultimatetests


clean:
	rm -rf $(OUT_DIR) 
	rm -f $(SRC_DIR)/tests/output/*.txt

.PHONY: compile run all astTestsCompile astTestsRun astTestsAll integrationTestsCompile integrationTestsRun integrationTestsAll systemTests diff ultimatetests txtTestsAll tests clean
