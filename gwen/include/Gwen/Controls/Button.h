/*
 *  GWEN
 *  Copyright (c) 2010 Facepunch Studios
 *  See license in Gwen.h
 */

#pragma once
#ifndef GWEN_CONTROLS_BUTTON_H
#define GWEN_CONTROLS_BUTTON_H

#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Label.h"

namespace Gwen
{
    namespace Controls
    {
        class ImagePanel;

        class GWEN_EXPORT Button : public Label
        {
        public:

            GWEN_CONTROL(Button, Label);

            virtual void Render(Skin::Base* skin) override;
            virtual void OnMouseClickLeft(int x, int y, bool bDown) override;
            virtual void OnMouseClickRight(int x, int y, bool bDown) override;
            virtual void OnMouseDoubleClickLeft(int x, int y) override;
            virtual bool OnKeySpace(bool bDown) override;

            virtual void OnPress();
            virtual void OnRightPress();

            virtual void AcceleratePressed() override;

            virtual bool IsDepressed() const
            {
                return m_bDepressed;
            }

            virtual void SetDepressed(bool b);

            //
            /// Buttons can be toggle type, which means that it is
            /// toggled on and off. Its toggle status is in IsDepressed.
            //
            virtual void SetIsToggle(bool b)
            {
                m_bToggle = b;
            }

            virtual bool IsToggle() const
            {
                return m_bToggle;
            }

            virtual bool GetToggleState() const
            {
                return m_bToggleStatus;
            }

            virtual void SetToggleState(bool b);
            virtual void Toggle()
            {
                SetToggleState(!GetToggleState());
            }

            virtual void SetImage(const String& strName, bool bCenter = false);

            virtual void SizeToContents() override;
            virtual void PostLayout(Skin::Base* pSkin) override;
            virtual void UpdateColours() override;

            virtual void SetImageAlpha(float fMultiply);

            virtual void DoAction() override
            {
                OnPress();
            }

            virtual void SetAction(Event::Handler* pObject,
                                   Handler::FunctionWithInformation pFunction,
                                   const Gwen::Event::Packet& packet) override;

        public:

            Gwen::Event::Caller onPress;
            Gwen::Event::Caller onRightPress;
            Gwen::Event::Caller onDown;
            Gwen::Event::Caller onUp;
            Gwen::Event::Caller onDoubleClick;
            Gwen::Event::Caller onToggle;
            Gwen::Event::Caller onToggleOn;
            Gwen::Event::Caller onToggleOff;

        protected:

            ImagePanel*     m_Image;    ///< Optional image to be displayed on button.

            bool m_bDepressed;          ///< Is button currently being pressed?
            bool m_bToggle;             ///< Is this a toggling button, i.e. on or off.
            bool m_bToggleStatus;

            bool m_bCenterImage;        ///< Centre the image in the button?
        };


    }
}
#endif // ifndef GWEN_CONTROLS_BUTTON_H
