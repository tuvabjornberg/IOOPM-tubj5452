SRC_DIR = src/org/ioopm/calculator/
compile:
	javac -d classes -sourcepath src $(SRC_DIR)Calculator.java

run:
	java -cp classes org.ioopm.calculator.Calculator

standard_tests.out: 
	javac -cp  ..lib/junit-platform-console-standalone-1.8.1.jar $(SRC_DIR)StandardTests.java

tests: standard_tests.out
	java -jartform-console-standalone-1.8.1.jar -cp classes -c StandardTests

clean:
	rm -rf classes

.PHONY: compile run clean
