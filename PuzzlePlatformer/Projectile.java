import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class Projectile {
    public double x, y;
    private double sx, sy, initsy, gravity;
    private boolean launched; 
    public boolean done;

    public Projectile(double sx, double sy, double gravity) {
        this.sx = sx;
        this.sy = sy;
        initsy = sy;
        this.gravity = gravity;
        launched = false;
        done = false;
    }

    public void launch (double x, double y, int dir) {
        this.x = x;
        this.y = y;
        sx = dir * Math.abs(sx);
        sy = initsy;
        launched = true;
        done = false;
    }

    public void move(Level level, int tileSize) {
        if (!launched) return;
        sy += gravity;
        x += sx;
        y += sy;
        if (level.collides(this, tileSize)) {
            launched = false;
            done = true;
        }
    }

    public void render(GraphicsContext gc) {
        gc.setFill(Color.BLACK);
        gc.fillOval(x, y, 5, 5);
    }

    public boolean done() {
        return done;
    }
}