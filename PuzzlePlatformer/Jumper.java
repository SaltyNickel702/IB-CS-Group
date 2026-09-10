import java.util.Set;

import javafx.scene.input.KeyCode;

public class Jumper extends Player {
    public Jumper(int w, int h) {
        super(w, h);
        playerID = 2;
        projectile = new Projectile(5, 0, 0);
        keys = new KeyCode[4];
        keys[0] = KeyCode.W;
        keys[1] = KeyCode.A;
        keys[2] = KeyCode.D;
        keys[3] = KeyCode.F;
    }

    public void move(Set<KeyCode> KeysPressed, Level level, int tileSize) {
        updateInputs(KeysPressed, level, tileSize);
        super.move(level, tileSize);
    }

    @Override
    protected void useAbility(Level level, int tileSize) {
        // Teleport to projectile
        sx = Math.signum(projectile.x - x);
        // sy = Math.signum(projectile.y - y);
        sy = 0;
        x = projectile.x - width/2;
        y = projectile.y - height/2;
        projectile.done = false;
        projectile.render = false;
    }

    @Override 
    protected void updateInputs(Set<KeyCode> KeysPressed, Level level, int tileSize) {
        if (KeysPressed.contains(keys[0]) && level.isOnGround(x, y, width, height, tileSize)) {
            sy = -15; // jump
        }

        
        if (KeysPressed.contains(keys[1])) {
            sx = -3; // move left
        } else if (KeysPressed.contains(keys[2])) {
            sx = 3; // move right
        }
        if (KeysPressed.contains(keys[3])) {
            if (projectile != null) {
                projectile.launch(x + width/2, y - height/5, 1);
            }
        }
    }
    
    // public void updateInputs(Set<KeyCode> KeysPressed, Level level, int tileSize) {
    //         if (KeysPressed.contains(KeyCode.W) && level.isOnGround(x, y, width, height, tileSize)) {
    //             sy = -15; // jump
    //         }

            
    //         if (KeysPressed.contains(KeyCode.A)) {
    //             sx = -3; // move left
    //         } else if (KeysPressed.contains(KeyCode.D)) {
    //             sx = 3; // move right
    //         }
    // }
}
