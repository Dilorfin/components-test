#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "../core/Destroyable.hpp"

TEST_CASE("check destroyable")
{
    Destroyable destroyable;
    
    CHECK_FALSE_MESSAGE(destroyable.isDestroyed(), "on create should not be destroyed");
    destroyable.destroy();
    CHECK_MESSAGE(destroyable.isDestroyed(), "should be destroyed after 'destroy' call");
}
