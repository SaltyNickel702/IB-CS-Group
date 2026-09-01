import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class Hazard {
	public enum Side { TOP, BOTTOM, LEFT, RIGHT }

	private final double x, y;
	private final Side side;

	public Hazard(double x, double y, Side side) {
		this.x = x;
		this.y = y;
		this.side = side;
	}

	public boolean collides(Player player, int tileSize) {
		double thickness = 10;
		double hazardX = x;
		double hazardY = y;
		double hazardWidth = tileSize;
		double hazardHeight = thickness;

		if (side == Side.BOTTOM) {
			hazardY += tileSize - thickness;
		} else if (side == Side.LEFT) {
			hazardWidth = thickness;
			hazardHeight = tileSize;
		} else if (side == Side.RIGHT) {
			hazardX += tileSize - thickness;
			hazardWidth = thickness;
			hazardHeight = tileSize;
		}

		return player.x < hazardX + hazardWidth && player.x + player.width > hazardX
				&& player.y < hazardY + hazardHeight && player.y + player.height > hazardY;
	}

	public void render(GraphicsContext gc, int tileSize) {
		double thickness = 10;
		double hazardX = x;
		double hazardY = y;
		double hazardWidth = tileSize;
		double hazardHeight = thickness;

		if (side == Side.BOTTOM) {
			hazardY += tileSize - thickness;
		} else if (side == Side.LEFT) {
			hazardWidth = thickness;
			hazardHeight = tileSize;
		} else if (side == Side.RIGHT) {
			hazardX += tileSize - thickness;
			hazardWidth = thickness;
			hazardHeight = tileSize;
		}

		gc.setFill(Color.CRIMSON);
		gc.fillRect(hazardX, hazardY, hazardWidth, hazardHeight);
	}
}
