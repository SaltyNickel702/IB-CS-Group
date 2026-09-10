import java.util.Set;

import javafx.scene.input.KeyCode;

public class Runner extends Player {
    public Runner(int w, int h) {
        super(w, h);
        playerID = 1;
        projectile = new Projectile(10, -2, 0.5);
        keys = new KeyCode[4];
        keys[0] = KeyCode.UP;
        keys[1] = KeyCode.LEFT;
        keys[2] = KeyCode.RIGHT;
        keys[3] = KeyCode.SPACE;
    }

    public void move(Set<KeyCode> KeysPressed, Level level, int tileSize) {
        updateInputs(KeysPressed, level, tileSize);
        super.move(level, tileSize);
    }

    @Override 
    protected void updateInputs(Set<KeyCode> KeysPressed, Level level, int tileSize) {
        if (KeysPressed.contains(keys[0]) && level.isOnGround(x, y, width, height, tileSize)) {
            sy = -10; // jump
        }

        
        if (KeysPressed.contains(keys[1])) {
            sx = -6; // move left
        } else if (KeysPressed.contains(keys[2])) {
            sx = 6; // move right
        }
        if (KeysPressed.contains(keys[3])) {
            if (projectile != null) {
                projectile.launch(x + width/2, y - height/5, 1);
            }
        }
    }

    
    // public void updateInputs(Set<KeyCode> KeysPressed, Level level, int tileSize) {
    //         if (KeysPressed.contains(KeyCode.UP) && level.isOnGround(x, y, width, height, tileSize)) {
    //             sy = -10; // jump
    //         }

            
    //         if (KeysPressed.contains(KeyCode.LEFT)) {
    //             sx = -6; // move left
    //         } else if (KeysPressed.contains(KeyCode.RIGHT)) {
    //             sx = 6; // move right
    //         }
    //         if (KeysPressed.contains(KeyCode.SPACE)) {
    //             projectile.launch(x, y, 1);
    //         }
    // }
}
