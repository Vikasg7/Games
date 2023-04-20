package RockPaperScissor;
import java.util.Random;
import java.util.Scanner;

class Move {   
   public static final int ROCK    = 0;
   public static final int PAPER   = 1;
   public static final int SCISSOR = 2;
   public static final int INVALID = 3;

   public static int[] List = { ROCK, PAPER, SCISSOR };

   public static int from(String str) {
      switch (str.toLowerCase()) {
         case "r": return ROCK;
         case "p": return PAPER;
         case "s": return SCISSOR;
         default : return INVALID;
      }
   }

   public static boolean isValid(int move) {
      for (int m: Move.List)
         if (m == move)
            return true;
      return false;
   }

   public static boolean isDominating(int a, int b) {
      switch (a) {
         case ROCK   : return b == SCISSOR;
         case PAPER  : return b == ROCK;
         case SCISSOR: return b == PAPER;
         default     : return false;
      }
   }

   public static String toString(int move) {
      switch (move) {
         case ROCK   : return "Rock";
         case PAPER  : return "Paper";
         case SCISSOR: return "Scissor";
         default     : return "Invalid Move";
      }
   }
}

class Outcome {
   public static final int WIN  = 0;
   public static final int LOSS = 1;
   public static final int DRAW = 2;

   public static String toString(int outcome) {
      switch (outcome) {
         case WIN : return "You Won!";
         case LOSS: return "You Lost!";
         case DRAW: return "It's a Draw!";
         default  : throw new RuntimeException("Invalid Outcome " + outcome);
      }
   }
} 

class Game {
   private static Scanner scanner = new Scanner(System.in);
   private static Random  random  = new Random();

   private static int getPlayerMove() {
      System.out.printf("Enter your choice: ");
      String input = scanner.next();
      return Move.from(input);
   }

   private static int getRandomMove() {
      int idx = random.nextInt(Move.List.length);
      return Move.List[idx];
   }

   private static boolean isDraw(int outcome) {
      return outcome == Outcome.DRAW;
   }

   private static int compare(int playerMove, int computerMove) {
      return playerMove == computerMove                  ? Outcome.DRAW :
             Move.isDominating(playerMove, computerMove) ? Outcome.WIN
                                                         : Outcome.LOSS;
   }

   private static String compareMsg(int p, int c) {
      if (p == c) return "";
      switch (p) {
         case Move.ROCK   : return c == Move.SCISSOR ? "Rock smashes Scissor." : "Scissor got smashed by Rock.";
         case Move.PAPER  : return c == Move.ROCK    ? "Paper covers Rock."    : "Rock got covered by Paper.";
         case Move.SCISSOR: return c == Move.PAPER   ? "Scissor cuts Paper."   : "Paper got cut by Scissor.";
         default     : return "";
      }      
   }

   void run() {
      System.out.println("Welcome to ROCK PAPER SCISSOR Game\nPlease choose from (r)ock, (p)aper, (s)cissor\n");

      int outcome = Outcome.DRAW;
      while (isDraw(outcome)) {
         int computerMove = getRandomMove();
         int playerMove   = getPlayerMove();
         if (playerMove == Move.INVALID) {
            System.out.println("Invalid Move! Please choose from (r,p,s)\n");
            continue;
         }
         System.out.printf("Computer chose:    %s\n\n", Move.toString(computerMove));
         outcome = compare(playerMove, computerMove);
         System.out.println(Outcome.toString(outcome) + " " + compareMsg(playerMove, computerMove) + "\n");
      }
   }
}

public class RockPaperScissor {
   public static void main(String[] args) {
      Game RSP = new Game();
      RSP.run();
   }
}
