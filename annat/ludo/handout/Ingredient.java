// You should not change this class!
public abstract class Ingredient {
    private int score;
    protected Ingredient(int score) {
        this.score = score;
    }

    /**
     * Get the base score of the ingredient
     * @return the base score
     */
    public final int getScore() {
        return this.score;
    }

    /**
     * Let the ingredient interact with a cauldron.
     * @param cauldron the cauldron to interact with
     */
    public void interact(Cauldron cauldron) {
        cauldron.addToScore(this.getScore());
    }

    public String toString() {
        String name = this.getClass().getSimpleName();
        return name + "(" + this.getScore() + ")";
    }
}

/** A Pumpkin is worth exactly one point. It has no further effect. */
class Pumpkin extends Ingredient {
    public Pumpkin() {
        super(1);
    }
}

/** A CherryBomb can be worth one, two or three points. It additionally adds its
 * score as volatility. */
class CherryBomb extends Ingredient {
    // TODO: Implement this class
    private int score; 

    public CherryBomb(int score) {
        super(score); 

        if (score > 0 && score < 4) {
            this.score = score; 
        } else {
            throw new InvalidIngredientException("Invalid score"); 
        }// TODO: Replace this constructor
    }

}

/** A Toadstool can be worth one, two or four points. If the cauldron it is
 * added to contains one or two Pumpkins, it is worth one additional point. If
 * it contains more than two Pumpkins, it is worth two additional points. */
class Toadstool extends Ingredient {
    // TODO: Implement this class
    private int score; 

    public Toadstool(int score) {
        super(score); 
        
        if (score == 1 || score == 2 || score == 4) {
            this.score = score; 
        } else {
            throw new InvalidIngredientException("Invalid score"); 
        }// TODO: Replace this constructor
    }
}

/** A Mandrake can be worth one, two or four points. If it is added right after
 * a CherryBomb, the volatility of that CherryBomb is negated (its score still
 * applies). */
class Mandrake extends Ingredient {
    // TODO: Implement this class
    private int score; 

    public Mandrake(int score) {
        super(score); 
        
        if (score == 1 || score == 2 || score == 4) {
            this.score = score; 
        } else {
            throw new InvalidIngredientException("Invalid score"); 
        }// TODO: Replace this constructor    
    }
}
