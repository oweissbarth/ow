#pragma once

#include "ow/math/mat4.h"
#include "ow/math/vec3.h"
#include "ow/math/vec2.h"
#include "ow/math/quaternion.h"

namespace ow::interaction{

enum class MouseButton{
    NONE,
    LEFT,
    RIGHT,
    MIDDLE
};

enum class ModifierKey{
    NONE = 0,
    SHIFT = 1,
    CTRL = 2,
    ALT = 4,
};

struct MouseMoveEvent{
    math::Vec2f pos;
    MouseButton button;
    ModifierKey modifier;
};

struct MouseScrollEvent{
    float delta;
};

struct View{
    math::Vec3f pos;
    math::Quaternionf orientation;

    math::Mat4f toMat4() const{
        auto rotation = orientation.toMat4();
        math::Mat4f lookAt = math::Mat4f::lookAt(pos, math::Vec3f(0.F, 0.F, 0.F), math::Vec3f(0.F, 1.F, 0.F));
        math::Mat4f viewMatrix = lookAt * rotation;
        /*viewMatrix(3,0) = -pos.x;
        viewMatrix(3,1) = -pos.y;
        viewMatrix(3,2) = -pos.z;*/
        return viewMatrix;
    }
};

class CameraController{
public:
    virtual void mouseMoveEvent(MouseMoveEvent event) = 0;
    virtual void mouseScrollEvent(MouseScrollEvent event) = 0;
    virtual void update() = 0;
    [[nodiscard]] virtual View view() const = 0;
};

class TurntableCameraController: public CameraController{

    constexpr static float SENSITIVITY = 0.007;
public:
    TurntableCameraController(){
        m_view.pos = math::Vec3f(0,0, 10);
        m_view.orientation = math::Quaternionf();
    }

    void mouseMoveEvent(MouseMoveEvent event) override{
        m_previousMousePos = m_mousePos;
        m_mousePos = event.pos;

        if(event.button != MouseButton::MIDDLE) {
            return;
        }

        middleMouseDragEvent(m_previousMousePos, m_mousePos);
    }

    void mouseScrollEvent(MouseScrollEvent event) override{
        m_view.pos += math::Vec3f(0,0, -event.delta);
    }

    void middleMouseDragEvent(math::Vec2f previous , math::Vec2f current){
        auto rotMatrix = m_view.orientation.toMat3();

        auto invRotMatrix = rotMatrix.inverse();

        auto xAxis = math::Vec3f(invRotMatrix(0,0), invRotMatrix(0,1), invRotMatrix(0,2));

        auto xQuat = math::Quaternionf::fromAxisAngle(SENSITIVITY * (current.y-previous.y), xAxis);

        xQuat = m_view.orientation * xQuat;

        auto yQuat = math::Quaternionf::fromAxisAngle(SENSITIVITY*(current.x-previous.x), math::Vec3f(0,1,0));

        m_view.orientation =  xQuat * yQuat;
        m_view.pos = m_view.pos;
    }

    void update() override{
        View result;

        auto rotMatrix = m_view.orientation.toMat3();

        auto invRotMatrix = rotMatrix.inverse();

        auto xAxis = math::Vec3f(invRotMatrix(0,0), invRotMatrix(0,1), invRotMatrix(0,2));

        auto xQuat = math::Quaternionf::fromAxisAngle(SENSITIVITY * (m_mousePos.y-m_previousMousePos.y), xAxis);

        xQuat = m_view.orientation * xQuat;

        auto yQuat = math::Quaternionf::fromAxisAngle(SENSITIVITY*(m_mousePos.x-m_previousMousePos.x), math::Vec3f(0,1,0));

        m_view.orientation =  xQuat * yQuat;
        m_view.pos = m_view.pos;
    }

    [[nodiscard]] View view() const override{
        return m_view;
    }
private:
    View m_view;
    math::Vec2f m_previousMousePos;
    math::Vec2f m_mousePos;
};

}