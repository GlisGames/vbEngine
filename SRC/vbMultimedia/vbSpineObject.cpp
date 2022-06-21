#include "basetypes.h"
#include "vbSpineObject.h"

vbSpineObject::vbSpineObject(const char* atlas_path, const char* json_path, Vector2 _position) : vbGraphicObject()
{
    // Init spine
    position = { _position.x, _position.y};
    atlas = spAtlas_createFromFile(atlas_path, 0);
    json = spSkeletonJson_create(atlas);

    skeletonData = spSkeletonJson_readSkeletonDataFile(json, json_path);

    if (!skeletonData) {
        printf("%s\n", json->error);
        spSkeletonJson_dispose(json);
        printf("ERROR!\n");
    }
    
    spBone_setYDown(true);
    skeleton = spSkeleton_create(skeletonData);
    skeleton->scaleX = 0.3;
    skeleton->scaleY = 0.3;

    // Create the spAnimationStateData
    animationStateData = spAnimationStateData_create(skeletonData);
    animationState = spAnimationState_create(animationStateData);
}

void vbSpineObject::doAnimation(const char* animation_name, DWORD repeat, FLOAT delayinSecond = 0)  // repeat = -1 : loop indefinitely
{
    if (spSkeletonData_findAnimation(skeletonData, animation_name) == 0)
    {
        printf("animation doesn't exist.\n");
        return;
    }
    
    if (repeat == -1)
    {
        spAnimationState_addAnimationByName(animationState, 0, animation_name, 1, delayinSecond);
    }
    else
    {
        myfor(i, < , repeat)
        {
            spAnimationState_addAnimationByName(animationState, i, animation_name, 0, i * (delayinSecond + (FLOAT)spSkeletonData_findAnimation(skeletonData, animation_name)->duration));
        }
    }
}

void vbSpineObject::update()
{
    vbGraphicObject::update();

    spAnimationState_update(animationState, GetFrameTime());
    spAnimationState_apply(animationState, skeleton);
    spSkeleton_updateWorldTransform(skeleton);
}

void vbSpineObject::draw()
{
    vbGraphicObject::draw();

    drawSkeleton(skeleton, { position.x, position.y, 0 }, TRUE);
}

vbSpineObject::~vbSpineObject()
{
    spAtlas_dispose(atlas);
    spSkeleton_dispose(skeleton);
    texture_2d_destroy(); // Destroy textures loaded by spine
}