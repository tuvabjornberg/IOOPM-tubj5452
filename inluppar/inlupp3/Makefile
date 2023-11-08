SRC_DIR = src/org/ioopm/calculator
JUNIT_JAR = ../../lib/junit-platform-console-standalone-1.8.1.jar
CLASSPATH = org.ioopm.calculator
OUT_DIR = classes

compile: 
	javac -d $(OUT_DIR) -sourcepath src $(SRC_DIR)/Calculator.java

run:
	java -cp $(OUT_DIR) $(CLASSPATH).Calculator

calcCompRun: 
	javac -d $(OUT_DIR) -sourcepath src $(SRC_DIR)/Calculator.java
	java -cp $(OUT_DIR) $(CLASSPATH).Calculator

test: 
	javac -d $(OUT_DIR) -sourcepath src $(SRC_DIR)/Test.java
	java -ea -cp $(OUT_DIR) $(CLASSPATH).Test

clean:
	rm -rf $(OUT_DIR)

.PHONY: compile run clean calcCompRun test testAst
