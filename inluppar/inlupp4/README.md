# Make commands
#### Remember to run make clean before any make commands: 
```
$ make clean
```
   #### Build calculator:
   ```
   $ make compile
   ```
   #### Run caculator:
   ```
   $ make run
   ```
   #### Build and run calculator:
   ``` 
   $ make all
   ```
   #### Build and run all tests:
   ```
   $ make tests
   ```
   #### Build and run AST tests
   ```
   $ make astTestsAll

   or

   $ make astTestsCompile
   $ make astTestsRun
   ```
   #### Build and run integration tests
   ```
   $ make integrationTestsAll
   
   or

   $ make integrationCompile
   $ make integrationTestsRun
   ```
   #### Run and compare system tests, .txt files
   ```
   $ make txtTestsAll

   or

   $ make systemTests
   $ make diff
   ```

 # Notes and error handling

  - Errors and edge-cases are handled by checked exceptions mainly in the `CalculatorParser` class and `Calculator` class. Some errors are handled across the AST classes. 