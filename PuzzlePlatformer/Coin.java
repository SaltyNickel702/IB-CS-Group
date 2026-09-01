import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class Coin {
	public final double x, y;
	public final int size;
	public boolean collected = false;

	public Coin(double x, double y) {
		this(x, y, 16);
	}

	public Coin(double x, double y, int size) {
		this.x = x;
		this.y = y;
		this.size = size;
	}

	public boolean collides(Player player) {
		return !collected
				&& player.x < x + size && player.x + player.width > x
				&& player.y < y + size && player.y + player.height > y;
	}

	public void render(GraphicsContext gc) {
		if (collected) return;
		gc.setFill(Color.GOLD);
		gc.fillOval(x, y, size, size);
	}
}
