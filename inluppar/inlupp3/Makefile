SRC_DIR = src/org/ioopm/calculator
JUNIT_JAR = ../../lib/junit-platform-console-standalone-1.8.1.jar
CLASSPATH = org.ioopm.calculator
OUT_DIR = classes

AST_SOURCE_FILES := $(wildcard $(SRC_DIR)/ast/*.java)
AST_SOURCE_FILES := $(filter-out $(SRC_DIR)/ast/AstTests.java, $(AST_SOURCE_FILES))

compile: astCompile #parseCompile
	javac -d $(OUT_DIR) -sourcepath src $(SRC_DIR)/Calculator.java

astCompile: 
	javac -d $(OUT_DIR) -sourcepath src $(AST_SOURCE_FILES)

parseCompile: 
	javac -d $(OUT_DIR) -sourcepath src $(SRC_DIR)/parser/*.java

test: astCompile
	javac -d $(OUT_DIR) -sourcepath src $(SRC_DIR)/Test.java
	java -ea -cp $(OUT_DIR) $(CLASSPATH).Test

run:
	java -cp $(OUT_DIR) $(CLASSPATH).Calculator

testCompile: 
	javac -cp $(JUNIT_JAR) -d $(OUT_DIR) -sourcepath src $(SRC_DIR)/tests/AstTests.java

tests: testCompile
	java -cp $(JUNIT_JAR):$(OUT_DIR) -jar $(JUNIT_JAR) -cp $(OUT_DIR) -c $(CLASSPATH).ast.AstTests

clean:
	rm -rf $(OUT_DIR)

.PHONY: compile run clean testCompile tests test
