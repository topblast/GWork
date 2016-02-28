/*
 *  Gwork
 *  Copyright (c) 2010 Facepunch Studios
 *  Copyright (c) 2013-16 Billy Quith
 *  See license in Gwork.h
 */

#pragma once
#ifndef GWK_CONTROLS_MODAL_H
#define GWK_CONTROLS_MODAL_H

#include <Gwork/Controls/Base.h>
#include <Gwork/Gwork.h>
#include <Gwork/Skin.h>


namespace Gwk
{
    namespace ControlsInternal
    {
        class Modal : public Controls::Base
        {
            GWK_CONTROL_INLINE(Modal, Controls::Base)
            {
                SetKeyboardInputEnabled(true);
                SetMouseInputEnabled(true);
                SetShouldDrawBackground(true);
                SetBounds(0, 0, GetParent()->Width(), GetParent()->Height());
                
                // RecurseLayout() may not be called before Position is set.
                m_InnerBounds = m_Bounds;
            }

            virtual void Layout(Skin::Base* /*skin*/) override
            {
                SetBounds(0, 0, GetCanvas()->Width(), GetCanvas()->Height());
            }

            virtual void Render(Skin::Base* skin) override
            {
                skin->DrawModalControl(this);
            }

        };


    }
}
#endif // ifndef GWK_CONTROLS_MODAL_H
