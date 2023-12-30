import java.util.LinkedList;
import java.util.List;

public class Ant extends Animal {
    public Ant(Board board) {
        super(board);
    }

    public boolean isSameAnimalAs(Animal other) {
        return other instanceof Ant;
    }

    public int getScore() {
        return 0;
    }
}

class Fox extends Animal {
    public Fox(Board board) {
        super(board);
    }

    public boolean isSameAnimalAs(Animal other) {
        return other instanceof Fox;
    }

    public int getScore() {
        List<Animal> neighbors = this.getBoard().getNeighbors(this.getCoordinates());
        List<Animal> nonDupNeighbors = new LinkedList<Animal>();

        int score = 0;

        /// EC: Petigt, men eftersom den här variabeln bara
        /// används inne i loopen borde den vara deklarerad där.
        /// Dessutom tror jag att koden gör fel, eftersom
        /// nonDuplicate aldrig uppdateras efter att ha satts till
        /// false inne i loopen! (men du är godkänd ändå)
        boolean nonDuplicate = true;

        for (Animal animal : neighbors) {
            for (Animal uniqeAnimal : nonDupNeighbors) {
                if (animal.isSameAnimalAs(uniqeAnimal)) {
                    nonDuplicate = false;
                }
            }
            if (nonDuplicate) {
                score++;
                nonDupNeighbors.add(animal);
            }
        }

        return score;
    }
}

class Hawk extends Animal {
    public Hawk(Board board) {
        super(board);
    }

    public boolean isSameAnimalAs(Animal other) {
        return other instanceof Hawk;
    }

    public int getScore() {
        List<Animal> row = this.getBoard().getRow(this.getCoordinates());
        List<Animal> column = this.getBoard().getColumn(this.getCoordinates());

        int score = 0;

        /// EC: De här två looparna gör precis samma sak och
        /// skulle kunna brytas ut till en hjälpmetod (sen borde
        /// de räkna antalet riktningar det finns hökar, inte
        /// antalet hökar)
        for (Animal animal : row) {
            if (animal instanceof Hawk) {
                score++;
            }
        }
        score--; //removes the watching hawk

        for (Animal animal : column) {
            if (animal instanceof Hawk) {
                score++;
            }
        }
        score--; //removes the watching hawk

        return score;
    }
}