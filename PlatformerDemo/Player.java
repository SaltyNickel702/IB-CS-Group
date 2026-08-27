import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.input.KeyCode;
import java.util.Set;

public class Player {
    public double x, y, sx, sy;
    public int width, height;
    
    public Player(int w, int h) {
        width = w;
        height = h;
    }

    public void render(GraphicsContext gc) {
        gc.setFill(Color.RED);
        gc.fillRect(x, y, width, height);
    }

    public void move(Set<KeyCode> KeysPressed, Level level) {

    }

    public void startLevel(Level level) {
        x = level.startX;
        y = level.startY;
    }
}
