import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.input.KeyCode;
import java.util.Set;

public class Player {
    public double x, y, sx, sy;
    public int width, height, playerID;
    private boolean done = false;
    
    public Player(int w, int h, int id) {
        width = w;
        height = h;
        playerID = id;
    }

    public void render(GraphicsContext gc) {
        if (done) return; // If the player is done, don't render
        if (playerID == 1) {
            gc.setFill(Color.RED);
        } else {
            gc.setFill(Color.BLUE);
        }
        gc.fillRect(x, y, width, height);
    }

    public void move(Set<KeyCode> KeysPressed, Level level, int tileSize) {
        if (done) return; // If the player is done, don't move
        sy += 0.5; // gravity
        sx *= 0.8; // friction
        if (Math.abs(sx) < 0.1) sx = 0; // stop small movements

        if (playerID == 1) {
            if (KeysPressed.contains(KeyCode.UP) && level.isOnGround(x, y, width, height, tileSize)) {
                sy = -10; // jump
            }

            
            if (KeysPressed.contains(KeyCode.LEFT)) {
                sx = -4; // move left
            } else if (KeysPressed.contains(KeyCode.RIGHT)) {
                sx = 4; // move right
            }
        } else if (playerID == 2) {
            if (KeysPressed.contains(KeyCode.W) && level.isOnGround(x, y, width, height, tileSize)) {
                sy = -10; // jump
            }
            if (KeysPressed.contains(KeyCode.A)) {
                sx = -4; // move left
            } else if (KeysPressed.contains(KeyCode.D)) {
                sx = 4; // move right
            }
        }
        // // Check for collisions and update position
        // double newX = x + sx;
        // Player horizontalCandidate = new Player(width, height);
        // horizontalCandidate.x = newX;
        // horizontalCandidate.y = y;
        // if (!level.collides(horizontalCandidate, tileSize)) {
        //     x = newX;
        // } else {
        //     sx = 0; // stop horizontal movement on collision
        // }
        // double newY = y + sy;
        // Player verticalCandidate = new Player(width, height);
        // verticalCandidate.x = x;
        // verticalCandidate.y = newY;
        // if (!level.collides(verticalCandidate, tileSize)) {
        //     y = newY;
        // } else {
        //     sy = 0; // stop vertical movement on collision
        // }

        // Check for collisions and update position
        y += sy;
        if (level.collides(this, tileSize)) {
            if (sy > 0) {
                y = Math.floor((y + height) / tileSize) * tileSize - height;
            } else if (sy < 0) {
                y = Math.ceil(y / tileSize) * tileSize;
            }
            sy = 0; // stop vertical movement on collision
        }

        x += sx;
        if (level.collides(this, tileSize)) {
            if (sx > 0) {
                x = Math.floor((x + width) / tileSize) * tileSize - width;
            } else if (sx < 0) {
                x = Math.ceil(x / tileSize) * tileSize;
            }
            sx = 0; // stop horizontal movement on collision
        }

    }

    public boolean complete(int canvasWidth) {
        done = x + width > canvasWidth;
        return done;
    }

    public void startLevel(Level level) {
        x = level.startX;
        y = level.startY;
        sx = 0;
        sy = 0;
        done = false;
    }
}
