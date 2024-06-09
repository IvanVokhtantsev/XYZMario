#include "Animation.h"

void Animation::Update(float DeltaSeconds)
{
    currentFrameIndex += speed * DeltaSeconds;
    if(static_cast<int>(currentFrameIndex) >= frames.size())
    {
        currentFrameIndex = 0;
    }
}

int Animation::GetCurrentFrameIndex()
{
    return static_cast<int>(currentFrameIndex);
}

const sf::IntRect& Animation::GetCurrentFrame()
{
    return frames[GetCurrentFrameIndex()];
}
