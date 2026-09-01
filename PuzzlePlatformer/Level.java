import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.input.KeyCode;
import java.util.ArrayList;
import java.util.Set;

public class Level {
    public boolean[][] layout;
    public int startX, startY;
    private ArrayList<Gate> gates = new ArrayList<>();
    private ArrayList<Coin> coins = new ArrayList<>();
    private ArrayList<Hazard> hazards = new ArrayList<>();

    public Level(boolean[][] level, int sx, int sy) {
        layout = level;
        startX = sx;
        startY = sy;
    }

    public void addGate(Gate gate) {
        gates.add(gate);
    }

    public void addCoin(Coin coin) {
        coins.add(coin);
    }

    public void addHazard(Hazard hazard) {
        hazards.add(hazard);
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
        for (Gate gate : gates) {
            gc.setFill(gate.isOpen ? Color.LIGHTGREEN : Color.DARKRED);
            for (int[] gatePos : gate.gatePositions) {
                gc.fillRect(tileSize * gatePos[0], tileSize * gatePos[1], tileSize, tileSize);
            }
            gc.setFill(Color.GOLD);
            for (int[] buttonPos : gate.buttonPositions) {
                gc.fillRect(buttonPos[0], buttonPos[1] + tileSize - 8, tileSize, 8);
            }
        }
        for (Coin coin : coins) {
            coin.render(gc);
        }
        for (Hazard hazard : hazards) {
            hazard.render(gc, tileSize);
        }
    }

    public boolean collides(Player p, int tileSize) {
        int minTileX = Math.max(0, (int) Math.floor(p.x / tileSize));
        int maxTileX = Math.min(layout.length - 1, (int) Math.floor((p.x + p.width - 1) / tileSize));
        int minTileY = Math.max(0, (int) Math.floor(p.y / tileSize));
        int maxTileY = Math.min(layout[0].length - 1, (int) Math.floor((p.y + p.height - 1) / tileSize));

        for (int tileX = minTileX; tileX <= maxTileX; tileX++) {
            for (int tileY = minTileY; tileY <= maxTileY; tileY++) {
                if (layout[tileX][tileY]) {
                    return true;
                }
                // Check if the tile is a gate and if it's closed
                for (Gate gate : gates) {
                    for (int[] gatePos : gate.gatePositions) {
                        if (gatePos[0] == tileX && gatePos[1] == tileY && !gate.isOpen) {
                            return true; // Collision with a closed gate
                        }
                    }
                }
            }
        }
        return false;
    }

    public boolean updateGateStates(Set<KeyCode> keysPressed, Player player, int tileSize) {
        boolean anyGateOpen = false;
        for (Gate gate : gates) {
            gate.updateGateState(keysPressed, player, tileSize);
            if (gate.isOpen) {
                anyGateOpen = true;
            }
        }
        return anyGateOpen;
    }

    public boolean updateGateStates(Set<KeyCode> keysPressed, Player firstPlayer, Player secondPlayer, int tileSize) {
        boolean anyGateOpen = false;
        for (Gate gate : gates) {
            gate.updateGateState(keysPressed, firstPlayer, secondPlayer, tileSize);
            if (gate.isOpen) {
                anyGateOpen = true;
            }
        }
        return anyGateOpen;
    }

    public int collectCoins(Player player) {
        int collected = 0;
        for (Coin coin : coins) {
            if (coin.collides(player)) {
                coin.collected = true;
                collected++;
            }
        }
        return collected;
    }

    public boolean collidesWithHazard(Player player, int tileSize) {
        for (Hazard hazard : hazards) {
            if (hazard.collides(player, tileSize)) {
                return true;
            }
        }
        return false;
    }

    private boolean checkCollisionPoint(int x, int y, int tileSize) {
        int tileX = (int) Math.floor((double) x / tileSize);
        int tileY = (int) Math.floor((double) y / tileSize);
        return tileX >= 0 && tileX < layout.length
                && tileY >= 0 && tileY < layout[0].length
                && layout[tileX][tileY];
    }

    public boolean isOnGround(double x, double y, int width, int height, int tileSize) {
        int feetY = (int) Math.floor(y + height + 1);
        return checkCollisionPoint((int) Math.floor(x), feetY, tileSize)
                || checkCollisionPoint((int) Math.floor(x + width - 1), feetY, tileSize);
    }
}
