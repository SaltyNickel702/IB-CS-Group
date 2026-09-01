import javafx.scene.input.KeyCode;

import java.util.Set;

public class Gate {
    public boolean isOpen;
    public int[][] buttonPositions; // Array of button positions that control this gate
    public int[][] gatePositions; // Array of gate positions

    public Gate(int[][] buttonPositions, int[][] gatePositions) {
        this.buttonPositions = buttonPositions;
        this.gatePositions = gatePositions;
        this.isOpen = false; // Gates start closed by default
    }

    public void updateGateState(Set<KeyCode> keysPressed, Player player, int tileSize) {
        // Check if the player is on any of the buttons
        for (int[] buttonPos : buttonPositions) {
            if (player.x < buttonPos[0] + tileSize && player.x + player.width > buttonPos[0] &&
                player.y < buttonPos[1] + tileSize && player.y + player.height > buttonPos[1]) {
                isOpen = true; 
                return;
            }
        }
        isOpen = false; 
    }

    public void updateGateState(Set<KeyCode> keysPressed, Player firstPlayer, Player secondPlayer, int tileSize) {
        updateGateState(keysPressed, firstPlayer, tileSize);
        if (!isOpen) {
            updateGateState(keysPressed, secondPlayer, tileSize);
        }
    }
}
