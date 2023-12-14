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
    private int score;

    public CherryBomb(int score) {
        super(score); 

        if (score > 0 && score < 4) {
            this.score = score; 
            
        } else {
            throw new InvalidIngredientException("Invalid score"); 
        }
    }

    @Override
    public void interact(Cauldron cauldron) {
        cauldron.addToScore(this.score); 
        cauldron.addToVolatility(this.score); 
    }

}

/** A Toadstool can be worth one, two or four points. If the cauldron it is
 * added to contains one or two Pumpkins, it is worth one additional point. If
 * it contains more than two Pumpkins, it is worth two additional points. */
class Toadstool extends Ingredient {
    private int score; 

    public Toadstool(int score) {
        super(score); 
        
        if (score == 1 || score == 2 || score == 4) {
            this.score = score; 
        } else {
            throw new InvalidIngredientException("Invalid score"); 
        }
    }

    @Override
    public void interact(Cauldron cauldron) {
        int pumpAmount = 0; 
        for (Ingredient ingredient : cauldron) {
            if (ingredient instanceof Pumpkin) {
                pumpAmount++; 
            }
        }

        if (pumpAmount == 1 || pumpAmount == 2) {
            cauldron.addToScore(this.score + 1); 
        } else if (pumpAmount > 2) {
            cauldron.addToScore(this.score + 2); 
        } else {
            cauldron.addToScore(this.score); 
        }
    }
}

/** A Mandrake can be worth one, two or four points. If it is added right after
 * a CherryBomb, the volatility of that CherryBomb is negated (its score still
 * applies). */
class Mandrake extends Ingredient {
    private int score; 

    public Mandrake(int score) {
        super(score); 
        
        if (score == 1 || score == 2 || score == 4) {
            this.score = score; 
        } else {
            throw new InvalidIngredientException("Invalid score"); 
        } 
    }

    @Override
    public void interact(Cauldron cauldron) {
        Boolean c = false; 
        int cV = 0; 
        for (Ingredient ingredient : cauldron) {
            if (ingredient instanceof CherryBomb) {
                c = true; 
                cV = ingredient.getScore();
            } else {
                c = false;
                cV = 0;  
            }
        }
        cauldron.addToVolatility(-cV); 
        cauldron.addToScore(this.score); 
    }
}
