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
   $ make calcCompRun
   ```
   #### Run tests:
   ```
   $ make test
   ```

 # Notes and error handling

  - Errors and edge-cases are handled by checked exceptions mainly in the `CalculatorParser` class and `Calculator` class. Some errors are handled across the ast classes. 