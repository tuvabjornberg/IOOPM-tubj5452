all:
	javac -d classes *.java

test: all
	java -cp classes -ea Driver

clean:
	rm -rf classes

memtest:
	@echo "No leaks are possible! (since we are running Java)"

.PHONY: all test class memtest