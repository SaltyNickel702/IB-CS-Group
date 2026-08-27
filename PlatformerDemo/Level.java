import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class Level {
    public boolean[][] layout;
    public int startX, startY;

    public Level(boolean[][] level, int sx, int sy) {
        layout = level;
        startX = sx;
        startY = sy;
    }

    public void render(GraphicsContext gc, int tileSize) {
        gc.setFill(Color.GRAY);
        for (int i = 0; i < layout.length; i ++) {
            for (int j = 0; j < layout[i].length; j ++) {
                if (layout[i][j]) {
                    gc.fillRect(tileSize*i, tileSize*j, tileSize, tileSize);
                }
            }
        }
    }

    public boolean collides(Player p, int tileSize) {
        return checkCollisionPoint((int) p.x, (int) p.y, tileSize) || checkCollisionPoint((int) p.x + p.width, (int) p.y, tileSize) || checkCollisionPoint((int) p.x, (int) p.y + p.height, tileSize) || checkCollisionPoint((int) p.x + p.width, (int) p.y + p.height, tileSize);
    }

    private boolean checkCollisionPoint(int x, int y, int tileSize) {
        return layout[(x/tileSize)][y/tileSize];
    }
}
