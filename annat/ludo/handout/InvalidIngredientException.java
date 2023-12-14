public class InvalidIngredientException extends RuntimeException {
    public InvalidIngredientException() {
        super();
    }

    // Use this constructor to help debugging
    public InvalidIngredientException(String msg) {
        super(msg);
    }
}
