import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class Projectile {
    public double x, y;
    private double sx, sy, gravity;
    private boolean launched;

    public Projectile(double sx, double sy, double gravity) {
        this.sx = sx;
        this.sy = sy;
        this.gravity = gravity;
        launched = false;
    }

    public void launch (double x, double y, int dir) {
        this.x = x;
        this.y = y;
        sx = dir * Math.abs(sx);
        launched = true;
    }

    public void move(Level level, int tileSize) {
        if (!launched) return;
        sy += gravity;
        x += sx;
        y += sy;
        if (level.collides(this, tileSize)) {
            launched = false;
        }
    }

    public void render(GraphicsContext gc) {
        gc.setFill(Color.BLACK);
        gc.fillOval(x, y, 5, 5);
    }

    public boolean done(Level level, int tileSize) {
        return level.collides(this, tileSize);
    }
}