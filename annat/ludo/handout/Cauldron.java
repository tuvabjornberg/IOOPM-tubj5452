import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

public class Cauldron implements Iterable<Ingredient> {
    private static final int VOLATILITY_LIMIT = 7;

    private List<Ingredient> ingredients = new LinkedList<>();
    private int score = 0;
    private int volatility = 0;

    /**
     * Add an ingredient to the cauldron. Will do nothing if the
     * cauldron has exploded.
     * @param ingredient the ingredient to add
     */
    public void addIngredient(Ingredient ingredient) {
        if (this.hasExploded()) return;

        ingredient.interact(this);
        this.ingredients.add(ingredient);
    }

    /** Get the score of the cauldron
     * @return the score of the cauldron
     */
    public int getScore() {
        return this.score;
    }

    /** Add to the score of the cauldron
     * @param amount the amount to add
     */
    public void addToScore(int amount) {
        this.score += amount;
    }

    /** Get the volatility score of the cauldron
     * @return the volatility score of the cauldron
     */
    public int getVolatility() {
        return this.volatility;
    }

    /** Add to the volatility score of the cauldron
     * @param amount the amount to add
     */
    public void addToVolatility(int amount) {
        this.volatility += amount;
    }

    /** Check if the cauldron has exploded
     * @return whether or not the cauldron has exploded
     */
    public boolean hasExploded() {
        return this.volatility > VOLATILITY_LIMIT;
    }

    /** Iterate over the ingredients of the cauldron
     * @return an iterator over the ingredients of the cauldron
     */
    public Iterator<Ingredient> iterator() {
        return this.ingredients.iterator();
    }

    @Override
    public String toString() {
        return "" + this.ingredients;
    }
}