JAVAC = javac
SRC_DIR = src
CLASSES_DIR = classes
MAIN_CLASS = org.ioopm.calculator.ast.Main
AST_DIR = src/org/ioopm/calculator/ast/
PARSER_DIR = src/org/ioopm/calculator/parser/

compile:
	$(JAVAC) -d $(CLASSES_DIR) -sourcepath $(SRC_DIR) $(AST_DIR)*.java $(PARSER_DIR)*.java $(SRC_DIR)/org/ioopm/calculator/*.java

run:
	java -cp $(CLASSES_DIR) $(MAIN_CLASS)

clean:
	rm -rf $(CLASSES_DIR)

.PHONY: compile run clean
