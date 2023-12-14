import java.lang.StackWalker.StackFrame;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Driver {
    private static int numberOfTests = 0;
    private static int passedTests = 0;

    private static boolean checkAssertionsEnabled() {
        try {
            assert false;
        } catch (AssertionError err) {
            return true;
        }
        return false;
    }

    private static void printStatistics() {
        int failedTests = numberOfTests - passedTests;
        if(failedTests == 0) {
            System.out.println("All tests passed!");
        } else {
            System.out.println("Passed " + passedTests + "/" + numberOfTests + " tests");
            System.out.println("Failed " + failedTests + " test" + (failedTests == 1? "":"s") + " (see above)");
        }
    }

    private static void printErrorMessage(String msg) {
        StackFrame frame = StackWalker.getInstance().walk(s ->
            s.limit(3).collect(Collectors.toList())).get(2);

        String className = frame.getClassName();
        String fileName = frame.getFileName();
        int line = frame.getLineNumber();
        String method = frame.getMethodName();
        System.out.println(className + "." + method +"(" + fileName + ":" + line + ")" + " =====> " + msg);
    }

    private static void test(Cauldron cauldron, int expectedScore, int expectedVolatility) {
        numberOfTests++;
        try {
            assert cauldron.getScore() == expectedScore :
            "Expected cauldron to have score " + expectedScore + " but it was " + cauldron.getScore();
            assert cauldron.getVolatility() == expectedVolatility :
            "Expected cauldron to have volatility " + expectedVolatility + " but it was " + cauldron.getVolatility();
            passedTests++;
        } catch (AssertionError err) {
            printErrorMessage(err.getMessage());
            System.out.println("    Cauldron under test: " + cauldron);
        }
    }

    private static void test(Ingredient ingredient, int expectedScore) {
        numberOfTests++;
        try {
            assert ingredient.getScore() == expectedScore :
            "Expected ingredient to have score " + expectedScore + " but it was " + ingredient.getScore();
            passedTests++;
        } catch (AssertionError err) {
            printErrorMessage(err.getMessage());
            System.out.println("    Ingredient under test: " + ingredient);
        }
    }

    private static void testException(int score, Function<Integer, Ingredient> constructor) {
        numberOfTests++;
        try {
            Ingredient bad = constructor.apply(score);
            printErrorMessage("Expected creation of ingredient to throw an exception");
            System.out.println("    Ingredient under test:" + bad);
        } catch (InvalidIngredientException e) {
            passedTests++;
        }
    }

    private static void testPumpkin() {
        Ingredient pumpkin = new Pumpkin();
        test(pumpkin, 1);

        Cauldron cauldron = new Cauldron();
        test(cauldron, 0, 0);

        cauldron.addIngredient(pumpkin);
        test(cauldron, 1, 0);

        cauldron.addIngredient(pumpkin);
        test(cauldron, 2, 0);
    }

    private static void testCherryBomb() {
        test(new CherryBomb(1), 1);
        test(new CherryBomb(2), 2);
        test(new CherryBomb(3), 3);
        testException(4, CherryBomb::new); // Try to create a CherryBomb with score 4
        testException(0, CherryBomb::new); // Try to create a CherryBomb with score 0

        Cauldron cauldron = new Cauldron();
        cauldron.addIngredient(new CherryBomb(1));
        test(cauldron, 1, 1);

        cauldron.addIngredient(new CherryBomb(2));
        test(cauldron, 3, 3);

        cauldron.addIngredient(new CherryBomb(3));
        test(cauldron, 6, 6);

        cauldron.addIngredient(new Pumpkin());
        test(cauldron, 7, 6);

        cauldron.addIngredient(new CherryBomb(1));
        test(cauldron, 8, 7);

        cauldron.addIngredient(new Pumpkin());
        test(cauldron, 9, 7);

        cauldron.addIngredient(new CherryBomb(1));
        test(cauldron, 10, 8);

        cauldron.addIngredient(new Pumpkin());
        test(cauldron, 10, 8); // Cauldron has exploded, no more ingredients can be added

        cauldron.addIngredient(new CherryBomb(3));
        test(cauldron, 10, 8);
    }

    private static void testToadstool() {
        test(new Toadstool(1), 1);
        test(new Toadstool(2), 2);
        test(new Toadstool(4), 4);
        testException(3, Toadstool::new); // Try to create a Toadstool with score 3
        testException(5, Toadstool::new); // Try to create a Toadstool with score 5
        testException(0, Toadstool::new); // Try to create a Toadstool with score 0

        Cauldron cauldron = new Cauldron();
        cauldron.addIngredient(new Toadstool(1));
        test(cauldron, 1, 0);
        cauldron.addIngredient(new Toadstool(4));
        test(cauldron, 5, 0);

        cauldron.addIngredient(new Pumpkin());
        test(cauldron, 6, 0);

        cauldron.addIngredient(new Toadstool(2));
        test(cauldron, 9, 0); // Should get one bonus point

        cauldron.addIngredient(new Pumpkin());
        test(cauldron, 10, 0);

        cauldron.addIngredient(new Toadstool(1));
        test(cauldron, 12, 0); // Should still get one bonus point

        cauldron.addIngredient(new Pumpkin());
        test(cauldron, 13, 0);

        cauldron.addIngredient(new Toadstool(1));
        test(cauldron, 16, 0); // Should now get two bonus points

        cauldron.addIngredient(new Toadstool(4));
        test(cauldron, 22, 0); // Should still get two bonus points

        cauldron.addIngredient(new Pumpkin());
        cauldron.addIngredient(new Pumpkin());
        cauldron.addIngredient(new Pumpkin());
        cauldron.addIngredient(new Pumpkin());
        test(cauldron, 26, 0);

        cauldron.addIngredient(new Toadstool(4));
        test(cauldron, 32, 0); // Should still get two bonus points
    }

    private static void testMandrake() {
        test(new Mandrake(1), 1);
        test(new Mandrake(2), 2);
        test(new Mandrake(4), 4);
        testException(3, Mandrake::new); // Try to create a Mandrake with score 3
        testException(5, Mandrake::new); // Try to create a Mandrake with score 5
        testException(0, Mandrake::new); // Try to create a Mandrake with score 0

        Cauldron cauldron = new Cauldron();
        cauldron.addIngredient(new Mandrake(1));
        test(cauldron, 1, 0);
        cauldron.addIngredient(new Mandrake(4));
        test(cauldron, 5, 0);

        cauldron.addIngredient(new CherryBomb(2));
        test(cauldron, 7, 2);

        cauldron.addIngredient(new Mandrake(2));
        test(cauldron, 9, 0); // Should negate the last CherryBomb

        cauldron.addIngredient(new CherryBomb(3));
        test(cauldron, 12, 3);

        cauldron.addIngredient(new Pumpkin());
        test(cauldron, 13, 3);

        cauldron.addIngredient(new Mandrake(1));
        test(cauldron, 14, 3); // Older CherryBombs are left untouched

        cauldron.addIngredient(new CherryBomb(3));
        test(cauldron, 17, 6);

        cauldron.addIngredient(new CherryBomb(1));
        test(cauldron, 18, 7);

        cauldron.addIngredient(new Mandrake(4));
        test(cauldron, 22, 6); // Should cancel last CherryBomb

        cauldron.addIngredient(new CherryBomb(2)); // Explodes the cauldron
        test(cauldron, 24, 8);

        cauldron.addIngredient(new Mandrake(4));
        test(cauldron, 24, 8); // No effect, cauldron has exploded
    }

    private static void runTests() {
        testPumpkin();
        testCherryBomb();
        testToadstool();
        testMandrake();
    }

    public static void main(String[] args){
        if(!checkAssertionsEnabled()) {
            System.out.println("Be sure to run this with assertions enabled! (java -ea Driver)");
            return;
        }
        runTests();
        printStatistics();
    }
}