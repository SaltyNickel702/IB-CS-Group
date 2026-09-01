import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.StackPane;
import javafx.geometry.Pos;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.stage.Stage;

import java.util.HashSet;
import java.util.Set;

public class Main extends Application {
    // Game State Trackers
    private final Set<KeyCode> keysPressed = new HashSet<>();
    private AnimationTimer gameLoop;
    public boolean running = true,
           gameOver = false;
    public final int canvasWidth = 1200, canvasHeight = 700, tileSize = 50;
    public Canvas canvas = new Canvas(canvasWidth, canvasHeight);

    public Level[] stages = new Level[1];
    public int currentStage = 0;

    public Player player1 = new Player(25, 50, 1);
    public Player player2 = new Player(25, 50, 2);

    public int health = 3;

    @Override
    public void start(Stage primaryStage) {

        // Setup Canvas and Graphics Engine
        GraphicsContext gc = canvas.getGraphicsContext2D();

        // Layout Container
        StackPane root = new StackPane(canvas);
        root.setAlignment(Pos.TOP_LEFT);
        Scene scene = new Scene(root);

        // Capture Keyboard Inputs
        scene.setOnKeyPressed(e -> keysPressed.add(e.getCode()));
        scene.setOnKeyReleased(e -> keysPressed.remove(e.getCode()));

        primaryStage.setTitle("Temp");
        primaryStage.setScene(scene);
        primaryStage.setResizable(true);
        primaryStage.show();

        stages[0] = createTestLevel();

        player1.startLevel(stages[currentStage]);
        player2.startLevel(stages[currentStage]);

        // The Game Loop (runs roughly 60 times per second)
        gameLoop = new AnimationTimer() {
            @Override
            public void handle(long currentNanoTime) {
                if (running) {
                    updateGameLogic();
                    renderGraphics(gc);
                } else if (gameOver) {
                    renderGameOver(gc);
                } else {
                    renderWinScreen(gc);
                }
            }
        };
        gameLoop.start();
    }

    private Level createTestLevel() {
        int columns = canvasWidth / tileSize;
        int rows = canvasHeight / tileSize;
        boolean[][] layout = new boolean[columns][rows];

        for (int column = 0; column < columns; column++) {
            layout[column][rows - 1] = true;
        }
        for (int row = 0; row < rows; row++) {
            layout[0][row] = true;
        }

        layout[3][12] = true;
        layout[4][11] = true;
        layout[5][10] = true;
        layout[6][10] = true;
        layout[20][11] = true;
        layout[21][10] = true;

        Level level = new Level(layout, 100, 550);
        level.addGate(new Gate(
            new int[][] {{7 * tileSize, 12 * tileSize}, {11 * tileSize, 12 * tileSize}},
                new int[][] {{9, 10}, {9, 11}, {9, 12}}));
        level.addGate(new Gate(
            new int[][] {{14 * tileSize, 12 * tileSize}, {18 * tileSize, 12 * tileSize}},
                new int[][] {{16, 10}, {16, 11}, {16, 12}}));
        level.addCoin(new Coin(1050, 400));
        level.addHazard(new Hazard(600,650, Hazard.Side.TOP));
        return level;
    }

    @Override
    public void stop() {
        if (gameLoop != null) {
            gameLoop.stop();
        }
        keysPressed.clear();
    }

    private void updateGameLogic() {
        Level level = stages[currentStage];
        if (keysPressed.contains(KeyCode.R)) {
            resetPlayers(level);
            return;
        }

        player1.move(keysPressed, level, tileSize);
        player2.move(keysPressed, level, tileSize);
        level.updateGateStates(keysPressed, player1, player2, tileSize);

        health = Math.min(3, health + level.collectCoins(player1) + level.collectCoins(player2));
        handleHazard(player1, level);
        handleHazard(player2, level);
        if (health <= 0) {
            health = 0;
            running = false;
            gameOver = true;
        }
    }

    private void handleHazard(Player player, Level level) {
        if (level.collidesWithHazard(player, tileSize)) {
            health--;
            player.startLevel(level);
        }
    }

    private void resetPlayers(Level level) {
        player1.startLevel(level);
        player2.startLevel(level);
    }

    private void renderGraphics(GraphicsContext gc) {
        // Clear the canvas
        gc.setFill(Color.LIGHTBLUE);
        gc.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());

        stages[currentStage].render(gc, tileSize);

        player1.render(gc);
        player2.render(gc);

        gc.setFill(Color.BLACK);
        gc.setFont(new Font(24));
        gc.fillText("Health: " + health, 60, 60);

        if (player1.x > canvasWidth) {
            player1.done = true;
        }
        if (player2.x > canvasWidth) {
            player2.done = true;
        }
        if (player1.done && player2.done) {
            currentStage++;
            player1.done = false;
            player2.done = false;
            if (currentStage >= stages.length) {
                running = false;
            } else {
                player1.startLevel(stages[currentStage]);
                player2.startLevel(stages[currentStage]);
            }
        }
    }

    private void renderGameOver(GraphicsContext gc) {
        gc.setFill(Color.BLACK);
        gc.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());
        gc.setFill(Color.WHITE);
        gc.setFont(new Font(48));
        gc.fillText("Game Over", canvas.getWidth() / 2 - 100, canvas.getHeight() / 2);
    }

    private void renderWinScreen(GraphicsContext gc) {
        gc.setFill(Color.LIGHTBLUE);
        gc.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());
        gc.setFill(Color.BLACK);
        gc.setFont(new Font(48));
        gc.fillText("Game Complete", canvas.getWidth() / 2 - 100, canvas.getHeight() / 2);

    }

    public static void main(String[] eloquence) {
        launch(eloquence);
    }
}
