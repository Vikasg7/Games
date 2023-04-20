package GuessTheNumber;
import java.util.InputMismatchException;
import java.util.Random;
import java.util.Scanner;

class Game {
   static Scanner scanner = new Scanner(System.in);
   static Random random = new Random();
   private static int fromNum;
   private static int tillNum;

   enum Outcome {
      InputIsHigher,
      InputIsLower,
      InputMatched;

      @Override
      public String toString() {
         switch (this) {
            case InputIsHigher: return "Your Number is HIGHER. Retry!";
            case InputIsLower:  return "Your Number is LOWER. Retry!";
            case InputMatched:  return "Congratualtions! You guessed it Right.";
            default:            return "";
         }
      }
   }

   enum Input {
      NotAnInt(-1),
      NotInRng(-2),
      Num(0);

      public int value;

      public static Input Num(int n) {
         Input num = Input.Num;
         num.value = n;
         return num;
      } 

      Input(int i) {
         this.value = i;
      }

      @Override
      public String toString() {
         switch (this) {
            case NotAnInt: return "Your Number must be a Valid Number";
            case NotInRng: return "Your Number must be between " + fromNum + " - " + tillNum;
            case Num:      return "Num(" + this.value + ")";
            default:       return "";
         }
      }
   }

   // Game Constructor
   Game(int from, int till) {
      fromNum = from;
      tillNum = till;
   }

   static Input getInput() {
      try {
         System.out.printf("Enter a number: ");
         int input = scanner.nextInt();
         if (input >= fromNum && input <= tillNum)
            return Input.Num(input);
         return Input.NotInRng;
      } catch (InputMismatchException e) {
         scanner.next(); // discarding any non-int inputs
         return Input.NotAnInt;
      }
   }

   static Outcome compare(int input, int rand) {
      return (input > rand) ? Outcome.InputIsHigher :
             (input < rand) ? Outcome.InputIsLower
                            : Outcome.InputMatched;
   }

   static boolean isGameOver(Outcome outcome) {
      return outcome == Outcome.InputMatched;
   }

   void run() {      
      System.out.println("Welcome to Guess The Number game");
      System.out.printf("Enter a value between %d to %d\n\n", fromNum, tillNum);

      int rand = random.nextInt(fromNum, tillNum);
      int tries = 0;
      Outcome outcome = null;

      while (!isGameOver(outcome)) {
         Input input = getInput();
         tries++; // Even invalid input count as tries
         if (input != Input.Num) { // Comparing types not the underneath ordinal or num values
            System.out.println(input.toString() + "\n");
            continue;
         }

         outcome = compare(input.value, rand);
         System.out.println(outcome.toString() + "\n");
      }
      
      System.out.println("You took " + tries + " tries.");
   }   
}

public class GuessTheNumber {

   public static void main(String[] args) {
      Game guessTheNumber = new Game(1, 25);
      guessTheNumber.run();
   }

}