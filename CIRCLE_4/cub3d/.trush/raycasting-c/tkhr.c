#include <stdio.h>
#include <math.h>

#define mapWidth 8
#define mapHeight 8
const char* map[] = {
    "11111111",
    "10000001",
    "10000001",
    "10000001",
    "10000001",
    "10000001",
    "10000001",
    "11111111"
};

typedef struct {
    float x;
    float y;
    float angle;
} Player;

void renderRays(Player player, float FOV_ANGLE, int numRays, float rayLength) {
    float rayAngleIncrement = FOV_ANGLE / numRays;
    float rayAngle = player.angle - (FOV_ANGLE / 2);

    for (int rayIndex = 0; rayIndex < numRays; ++rayIndex) {
        // Raycasting logic
        float rayX = player.x;
        float rayY = player.y;

        // Calculate ray direction vector
        float rayDirX = cos(rayAngle);
        float rayDirY = sin(rayAngle);

        // Check for wall collisions
        int hitWall = 0;
        while (!hitWall) {
            rayX += rayDirX;
            rayY += rayDirY;

            // Check if the ray has hit a wall or gone out of bounds
            if (rayX < 0 || rayX >= mapWidth || rayY < 0 || rayY >= mapHeight || map[(int)rayY][(int)rayX] == '1') {
                hitWall = 1;
            }
        }

        // Calculate distance to wall
        float distToWall = sqrt((rayX - player.x) * (rayX - player.x) + (rayY - player.y) * (rayY - player.y));

        // Correct distance for fish-eye effect
        distToWall *= cos(player.angle - rayAngle);

        // Calculate wall height based on distance
        int wallHeight = (int)((mapHeight / distToWall) * rayLength);

        // Render the wall column
        for (int y = 0; y < wallHeight; ++y) {
            // Render each column as a character (e.g., '#') for simplicity
            printf("#");
        }
        printf("\n");

        rayAngle += rayAngleIncrement;
    }
}

int main() {
    Player player;
    player.x = 3.5;
    player.y = 3.5;
    player.angle = 0.0;

    float FOV_ANGLE = 1.047; // 60 degrees in radians
    int numRays = 120;
    float rayLength = 16.0;

    renderRays(player, FOV_ANGLE, numRays, rayLength);

    return 0;
}
