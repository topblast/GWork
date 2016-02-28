/*
 *  Gwork
 *  Copyright (c) 2010 Facepunch Studios
 *  Copyright (c) 2013-16 Billy Quith
 *  See license in Gwork.h
 */


#include <Gwork/Gwork.h>
#include <Gwork/BaseRender.h>
#include <Gwork/Utility.h>
#include <Gwork/Platform.h>

#include <math.h>

namespace Gwk
{
    namespace Renderer
    {
        Base::Base()
        :   m_RenderOffset(Gwk::Point(0, 0))
        ,   m_fScale(1.0f)
        {
        }

        Base::~Base()
        {
            if (GetCTT())
                GetCTT()->ShutDown();
        }

        void Base::DrawLinedRect(Gwk::Rect rect)
        {
            DrawFilledRect(Gwk::Rect(rect.x, rect.y, rect.w, 1));
            DrawFilledRect(Gwk::Rect(rect.x, rect.y+rect.h-1, rect.w, 1));
            DrawFilledRect(Gwk::Rect(rect.x, rect.y, 1, rect.h));
            DrawFilledRect(Gwk::Rect(rect.x+rect.w-1, rect.y, 1, rect.h));
        }

        void Base::DrawPixel(int x, int y)
        {
            DrawFilledRect(Gwk::Rect(x, y, 1, 1));
        }

        void Base::DrawShavedCornerRect(Gwk::Rect rect, bool bSlight)
        {
            // Draw INSIDE the w/h.
            rect.w -= 1;
            rect.h -= 1;

            if (bSlight)
            {
                DrawFilledRect(Gwk::Rect(rect.x+1, rect.y, rect.w-1, 1));
                DrawFilledRect(Gwk::Rect(rect.x+1, rect.y+rect.h, rect.w-1, 1));
                DrawFilledRect(Gwk::Rect(rect.x, rect.y+1, 1, rect.h-1));
                DrawFilledRect(Gwk::Rect(rect.x+rect.w, rect.y+1, 1, rect.h-1));
            }
            else
            {
                DrawPixel(rect.x+1, rect.y+1);
                DrawPixel(rect.x+rect.w-1, rect.y+1);
                DrawPixel(rect.x+1, rect.y+rect.h-1);
                DrawPixel(rect.x+rect.w-1, rect.y+rect.h-1);
                DrawFilledRect(Gwk::Rect(rect.x+2, rect.y, rect.w-3, 1));
                DrawFilledRect(Gwk::Rect(rect.x+2, rect.y+rect.h, rect.w-3, 1));
                DrawFilledRect(Gwk::Rect(rect.x, rect.y+2, 1, rect.h-3));
                DrawFilledRect(Gwk::Rect(rect.x+rect.w, rect.y+2, 1, rect.h-3));
            }
        }

        void Base::Translate(int& x, int& y)
        {
            x += m_RenderOffset.x;
            y += m_RenderOffset.y;
            x = ceilf(((float)x)*m_fScale);
            y = ceilf(((float)y)*m_fScale);
        }

        void Base::Translate(Gwk::Rect& rect)
        {
            Translate(rect.x, rect.y);
            rect.w = ceilf(((float)rect.w)*m_fScale);
            rect.h = ceilf(((float)rect.h)*m_fScale);
        }

        void Gwk::Renderer::Base::SetClipRegion(Gwk::Rect rect)
        {
            m_rectClipRegion = rect;
        }

        void Base::AddClipRegion(Gwk::Rect rect)
        {
            rect.x = m_RenderOffset.x;
            rect.y = m_RenderOffset.y;
            Gwk::Rect out = rect;

            if (rect.x < m_rectClipRegion.x)
            {
                out.w -= (m_rectClipRegion.x-out.x);
                out.x = m_rectClipRegion.x;
            }

            if (rect.y < m_rectClipRegion.y)
            {
                out.h -= (m_rectClipRegion.y-out.y);
                out.y = m_rectClipRegion.y;
            }

            if (rect.x+rect.w > m_rectClipRegion.x+m_rectClipRegion.w)
                out.w = (m_rectClipRegion.x+m_rectClipRegion.w)-out.x;

            if (rect.y+rect.h > m_rectClipRegion.y+m_rectClipRegion.h)
                out.h = (m_rectClipRegion.y+m_rectClipRegion.h)-out.y;

            m_rectClipRegion = out;
        }

        const Gwk::Rect& Base::ClipRegion() const
        {
            return m_rectClipRegion;
        }

        bool Base::ClipRegionVisible()
        {
            if (m_rectClipRegion.w <= 0 || m_rectClipRegion.h <= 0)
                return false;

            return true;
        }

        void Base::DrawMissingImage(Gwk::Rect pTargetRect)
        {
            SetDrawColor(Colors::Red);
            DrawFilledRect(pTargetRect);
        }

        ///  If they haven't defined these font functions in their renderer code
        ///  we just draw some rects where the letters would be to give them an
        ///  idea.

        void Base::RenderText(Gwk::Font* pFont, Gwk::Point pos, const Gwk::String& text)
        {
            float fSize = pFont->size*Scale();

            for (unsigned int i = 0; i < text.length(); i++)
            {
                wchar_t chr = text[i];

                if (chr == ' ')
                    continue;

                Gwk::Rect r(pos.x+i*fSize*0.4, pos.y, fSize*0.4-1, fSize);

                //
                // This isn't important, it's just me messing around changing
                // the shape of the rect based on the letter.. just for fun.
                //
                if (chr == 'l' || chr == 'i' || chr == '!' || chr == 't')
                {
                    r.w = 1;
                }
                else if (chr >= 'a' && chr <= 'z')
                {
                    r.y += fSize*0.5f;
                    r.h -= fSize*0.4f;
                }
                else if (chr == '.' || chr == ',')
                {
                    r.x += 2;
                    r.y += r.h-2;
                    r.w = 2;
                    r.h = 2;
                }
                else if (chr == '\'' || chr == '`'  || chr == '"')
                {
                    r.x += 3;
                    r.w = 2;
                    r.h = 2;
                }

                if (chr == 'o' || chr == 'O' || chr == '0')
                    DrawLinedRect(r);
                else
                    DrawFilledRect(r);
            }
        }

        Gwk::Point Base::MeasureText(Gwk::Font* pFont, const Gwk::String& text)
        {
            Gwk::Point p;
            p.x = pFont->size*Scale()*(float)text.length()*0.4;
            p.y = pFont->size*Scale();
            return p;
        }

    }
}
