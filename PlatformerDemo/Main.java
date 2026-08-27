import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.StackPane;
import javafx.geometry.Pos;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.stage.Stage;
import javafx.scene.image.Image;

import java.util.HashSet;
import java.util.Set;
import java.util.ArrayList;

public class Main extends Application {
    // Game State Trackers
    private final Set<KeyCode> keysPressed = new HashSet<>();
    private AnimationTimer gameLoop;
    public boolean running = true;
    public final int canvasWidth = 1200, canvasHeight = 700, tileSize = 50;
    Canvas canvas = new Canvas(canvasWidth, canvasHeight);

    Level[] stages = new Level[3];
    int currentStage = 0;

    Player player1 = new Player(25, 50);

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

        boolean[][] level1 = new boolean[canvasWidth / tileSize][canvasHeight / tileSize];

        stages[0] = new Level(level1, 100, 550);
        stages[1] = new Level(level1, 100, 550);
        stages[2] = new Level(level1, 100, 550);

        for (Level l : stages) {
            for (int i = 0; i < l.layout.length; i++) {
                for (int j = 0; j < l.layout[i].length; j++) {
                    if (i == 0 || j == l.layout[i].length-1) { //|| j == 0 || i == l.layout.length-1 || j == l.layout[i].length-1) {
                        l.layout[i][j] = true;
                    }
                }
            }
        }

        player1.startLevel(stages[currentStage]);

        // The Game Loop (runs roughly 60 times per second)
        gameLoop = new AnimationTimer() {
            @Override
            public void handle(long currentNanoTime) {
                if (running) {
                    updateGameLogic();
                    renderGraphics(gc);
                } else {
                    renderGameOver(gc);
                }
            }
        };
        gameLoop.start();
    }

    @Override
    public void stop() {
        if (gameLoop != null) {
            gameLoop.stop();
        }
        keysPressed.clear();
    }

    private void updateGameLogic() {
        player1.move(keysPressed, stages[currentStage]);
    }

    private void renderGraphics(GraphicsContext gc) {
        // Clear the canvas
        gc.setFill(Color.LIGHTBLUE);
        gc.fillRect(0, 0, canvas.getWidth(), canvas.getHeight());

        stages[currentStage].render(gc, tileSize);

        player1.render(gc);
    }

    private void renderGameOver(GraphicsContext gc) {

    }

    public static void main(String[] eloquence) {
        launch(eloquence);
    }
}
