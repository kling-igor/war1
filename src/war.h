#define FRAMES_PER_SECONDS 30
#define SECONDS_PER_FRAME (1.0f/FRAMES_PER_SECONDS)

#define MOVE_EPSILON 0.5f
#define MOVE_WAIT_INTENTS 2
#define MOVE_WAIT_TIME 1.0f
            
#define MAP_EDGE_SCROLL_GAP 5.0f

#define TREE_MAX_WOOD 100
#define GOLDMINE_MAX_GOLD 300
#define UNIT_MAX_CARRY_WOOD 100
#define UNIT_MAX_CARRY_GOLD 100

#define NEAR_ENEMY_RADIUS 5
#define NEAR_CATAPULT_RADIUS 3

#define PLAYBACK_FREQ 44100

// #define DEBUG_RENDER_MAP_GRID
// #define DEBUG_RENDER_PASSABLE_INFO
// #define DEBUG_RENDER_UNIT_PATHS
// #define DEBUG_RENDER_UNIT_INFO
// #define DEBUG_RENDER_UNIT_STATS
// #define DEBUG_RENDER_UNIT_ANIMATIONS
// #define DEBUG_RENDER_MAP_ANIMATIONS
// #define DEBUG_RENDER_FONT

#define isButtonPressed(input, btn) (input->buttons[btn].pressed)
#define wasButtonPressed(input, btn) (input->buttons[btn].wasPressed)
#define isKeyPressed(input, key) (input->keys[key].pressed)
#define wasKeyPressed(input, key) (input->keys[key].wasPressed)

#define getScaledSpeed(context, t) ((t) * (context)->globalSpeed)
#define getScaledTime(context, t) ((t) / (context)->globalSpeed)

void setWindowSize(WarContext* context, s32 width, s32 height);
void setGlobalScale(WarContext* context, f32 scale);
void changeGlobalScale(WarContext* context, f32 deltaScale);
void setGlobalSpeed(WarContext* context, f32 speed);
void changeGlobalSpeed(WarContext* context, f32 deltaSpeed);
void setMusicVolume(WarContext* context, f32 volume);
void changeMusicVolume(WarContext* context, f32 deltaVolume);
void setSoundVolume(WarContext* context, f32 volume);
void changeSoundVolume(WarContext* context, f32 deltaVolume);

vec2 getDirFromArrowKeys(WarContext* context, WarInput* input)
{
    vec2 dir = VEC2_ZERO;

    if (isKeyPressed(input, WAR_KEY_LEFT))
        dir.x = -1;
    else if (isKeyPressed(input, WAR_KEY_RIGHT))
        dir.x = 1;

    if (isKeyPressed(input, WAR_KEY_DOWN))
        dir.y = 1;
    else if (isKeyPressed(input, WAR_KEY_UP))
        dir.y = -1;

    dir = vec2Normalize(dir);
    return dir;
}

vec2 getDirFromMousePos(WarContext* context, WarInput* input)
{
    vec2 dir = VEC2_ZERO;

    if (input->pos.x < MAP_EDGE_SCROLL_GAP)
        dir.x = -1;
    else if (input->pos.x > context->originalWindowWidth - MAP_EDGE_SCROLL_GAP)
        dir.x = 1;

    if (input->pos.y < MAP_EDGE_SCROLL_GAP)
        dir.y = -1;
    else if (input->pos.y > context->originalWindowHeight - MAP_EDGE_SCROLL_GAP)
        dir.y = 1;

    dir = vec2Normalize(dir);
    return dir;
}

void printDirection(WarUnitDirection direction)
{
    switch (direction)
    {        
        case WAR_DIRECTION_NORTH:      logDebug("DIRECTION_NORTH\n");      break;
        case WAR_DIRECTION_NORTH_EAST: logDebug("DIRECTION_NORTH_EAST\n"); break;
        case WAR_DIRECTION_EAST:       logDebug("DIRECTION_EAST\n");       break;
        case WAR_DIRECTION_SOUTH_EAST: logDebug("DIRECTION_SOUTH_EAST\n"); break;
        case WAR_DIRECTION_SOUTH:      logDebug("DIRECTION_SOUTH\n");      break;
        case WAR_DIRECTION_SOUTH_WEST: logDebug("DIRECTION_SOUTH_WEST\n"); break;
        case WAR_DIRECTION_WEST:       logDebug("DIRECTION_WEST\n");       break;
        case WAR_DIRECTION_NORTH_WEST: logDebug("DIRECTION_NORTH_WEST\n"); break;
        default:                       logError("Unkown direction\n");     break;
    }
}