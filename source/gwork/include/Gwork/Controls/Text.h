/*
 *  Gwork
 *  Copyright (c) 2010 Facepunch Studios
 *  Copyright (c) 2013-16 Billy Quith
 *  See license in Gwork.h
 */

#pragma once
#ifndef GWK_CONTROLS_TEXT_H
#define GWK_CONTROLS_TEXT_H

#include <Gwork/BaseRender.h>
#include <Gwork/Controls/Base.h>

namespace Gwk
{
    namespace ControlsInternal
    {
        class GWK_EXPORT Text : public Controls::Base
        {
        public:

            GWK_CONTROL(Text, Controls::Base);

            virtual ~Text();
            Gwk::Font* GetFont();

            void SetString(const String& str);

            void Render(Skin::Base* skin) override;
            void Layout(Skin::Base* skin) override;

            void RefreshSize();

            void SetFont(Gwk::Font* pFont);

            const String& GetText() const
            {
                return m_String;
            }

            Gwk::Rect GetCharacterPosition(unsigned int iChar);
            int        GetClosestCharacter(Gwk::Point p);

            //! Return the encapsulating box of the given line.
            //! @remark This function is necessary to implement multiline selection.
            virtual Gwk::Rect GetLineBox(int i);

            int Length() const
            {
                return (int)m_String.size();
            }

            virtual void SetTextColor(const Gwk::Color& col)
            {
                m_Color = col;
            }

            virtual void SetTextColorOverride(const Gwk::Color& col)
            {
                m_ColorOverride = col;
            }

            virtual void OnScaleChanged() override;

            inline const Gwk::Color& TextColor() const
            {
                return m_Color;
            }

            virtual void TextChanged()
            {
                m_bTextChanged = true;
            }

            virtual bool Wrap()
            {
                return m_bWrap;
            }

            virtual void SetWrap(bool b)
            {
                if (m_bWrap == b)
                    return;

                m_bWrap = b; m_bTextChanged = true; Invalidate();
            }

            virtual Text* GetLine(int i);
            virtual int   GetLineFromChar(int i);
            virtual int   GetStartCharFromLine(int i);
            virtual int   GetEndCharFromLine(int i);
            virtual int   GetCharPosOnLine(int i);
            virtual unsigned NumLines();

        protected:

            virtual void SplitWords(const Gwk::String& s, std::vector<Gwk::String>& elems);

        private:

            virtual void RefreshSizeWrap();

            Gwk::String m_String;
            Gwk::Font*         m_Font;
            Gwk::Color m_Color;
            Gwk::Color m_ColorOverride;

            bool m_bWrap;
            bool m_bTextChanged;

            typedef std::list<Text*> TextLines;
            TextLines m_Lines;
        };


    }

}
#endif // ifndef GWK_CONTROLS_TEXT_H
