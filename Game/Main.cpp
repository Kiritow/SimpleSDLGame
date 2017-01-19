#include "Main.h"
#include <ctime>
#include "resource_def.h"
using namespace Engine;
using namespace MiniEngine;

char buff[1024];

/// Encoding Set to UTF8
#define renderText renderUTF8

namespace Game
{
    void Main(Engine::Window& wnd,Engine::Renderer& rnd,Engine::Font& font)
    {
        wnd.setTitle("Small ZZ Game");

        const int CONTINUE_GAME=1;
        srand(time(NULL));
        Rect wsz=wnd.getSize();
        if(wsz.h>wsz.w)
        {
            mlog("Warning: Window Height larger than width.");
        }

        Texture t=font.renderText(rnd,getstr(0),RGBA(255,255,0,0));
        Texture t2=font.renderText(rnd,getstr(1),RGBA(255,255,255,0));
        Texture t3=font.renderText(rnd,getstr(2),RGBA(255,255,255,0));
        Texture t4=font.renderText(rnd,getstr(3),RGBA(255,255,255,0));
        Texture t5=font.renderText(rnd,getstr(4),RGBA(255,255,255,0));
        Texture t6=font.renderText(rnd,getstr(5),RGBA(255,255,255,0));
        Texture t7=font.renderText(rnd,getstr(6),RGBA(255,255,255,0));
        Texture t8=font.renderText(rnd,getstr(7),RGBA(255,255,255,0));
        Texture t8a=font.renderText(rnd,getstr(8),RGBA(255,255,255,0));
        Texture t8b=font.renderText(rnd,getstr(9),RGBA(255,255,255,0));

        int running=1;
        int update=1;
        int skiprender=0;
        SDL_Event e;

        int cash=1800;
        int day=1;

        int lastpriceA=300;
        int priceA=300;
        int lastpriceB=450;
        int priceB=450;
        int haveA=0;
        int haveB=0;

        int cost_per_day=30;

        auto ResetGameSettings=[&]()
        {
            cash=1800;
            day=1;
            lastpriceA=priceA=300;
            lastpriceB=priceB=450;
            haveA=haveB=0;
            cost_per_day=30;
        };

        Rect r(0,0,wsz.w/4,wsz.h/4);
        Rect r2(0,wsz.h/4,wsz.w/4,wsz.h/4);
        Rect r3(wsz.w/2,wsz.h/4,wsz.w/4,wsz.h/4);
        Rect r4(wsz.w/4,wsz.h/4,wsz.w/4,wsz.h/4);
        Rect r5(wsz.w/4*3,wsz.h/4,wsz.w/4,wsz.h/4);
        Rect r6(wsz.w/4,wsz.h/8*5,wsz.w/2,wsz.h/4);
        Rect r7(wsz.w/4*3,0,wsz.w/4,wsz.h/4);

        Rect r8(wsz.w/4,wsz.h/4,wsz.w/2,wsz.h/4);
        Rect r8a(wsz.w/4,wsz.h/8*5,wsz.w/4,wsz.h/4);
        Rect r8b(wsz.w/2,wsz.h/8*5,wsz.w/4,wsz.h/4);

        Rect r9(wsz.w/4,0,wsz.w/4,wsz.h/4);
        Rect r10(wsz.w/2,0,wsz.w/4,wsz.h/4);

        Rect r11(0,wsz.h/2,wsz.w/4,wsz.h/4);
        Rect r12(0,wsz.h/4*3,wsz.w/4,wsz.h/4);
        Rect r13(wsz.w/4*3,wsz.h/2,wsz.w/4,wsz.h/4);
        Rect r14(wsz.w/4*3,wsz.h/4*3,wsz.w/4,wsz.h/4);

        auto GameEnd=[&]()->int
        {
            int running=1;
            int update=1;
            int skiprender=0;
            int flag=CONTINUE_GAME;
            SDL_Event e;
            while(running)
            {
                while(!update&&SDL_WaitEvent(&e))
                {
                    auto inrect=[&](Rect r)->bool{return isInRect(e.button.x,e.button.y,r.toSDLRect());};
                    switch(e.type)
                    {
                    case SDL_QUIT:
                        {
                            running=0;
                            update=1;
                            flag=!CONTINUE_GAME;
                            skiprender=1;
                        }
                        break;
                    case SDL_MOUSEBUTTONUP:
                        if(inrect(r8a))
                        {
                            running=0;
                            update=1;
                            skiprender=1;
                        }
                        else if(inrect(r8b))
                        {
                            running=0;
                            update=1;
                            flag=!CONTINUE_GAME;
                            skiprender=1;
                        }
                        break;
                    }
                }
                if(skiprender)
                {
                    skiprender=0;
                    continue;
                }
                rnd.clear();
                RGBA oc=rnd.getColor();
                rnd.setColor(RGBA(255,255,0,0));
                rnd.fillRect(r8a);
                rnd.setColor(RGBA(0,0,255,0));
                rnd.fillRect(r8b);
                rnd.copyTo(t8a,r8a);
                rnd.copyTo(t8b,r8b);
                rnd.copyTo(t8,r8);
                rnd.setColor(oc);
                rnd.update();
                update=0;
            }

            return flag;
        };

        while(running)
        {
            while(!update&&SDL_WaitEvent(&e))
            {
                auto inrect=[&](Rect r)->bool{return isInRect(e.button.x,e.button.y,r.toSDLRect());};

                switch(e.type)
                {
                case SDL_QUIT:
                    running=0;
                    update=1;
                    skiprender=1;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if(inrect(r7))///Exit
                    {
                        running=0;
                        update=1;
                    }
                    else if(inrect(r2))
                    {
                        if(cash>=priceA)
                        {
                            haveA++;
                            cash-=priceA;
                            update=1;
                        }
                    }
                    else if(inrect(r4))
                    {
                        if(haveA)
                        {
                            --haveA;
                            cash+=priceA;
                            update=1;
                        }
                    }
                    else if(inrect(r3))
                    {
                        if(cash>=priceB)
                        {
                            haveB++;
                            cash-=priceB;
                            update=1;
                        }
                    }
                    else if(inrect(r5))
                    {
                        if(haveB)
                        {
                            --haveB;
                            cash+=priceB;
                            update=1;
                        }
                    }
                    else if(inrect(r6))/// Next day
                    {
                        ++day;
                        cash-=cost_per_day;
                        lastpriceA=priceA;
                        lastpriceB=priceB;
                        if(rand()%100<50)
                        {
                            priceA=priceA*((100-rand()%30)/100.0);
                        }
                        else
                        {
                            priceA=priceA*((100+rand()%43)/100.0);
                        }
                        if(rand()%100<50)
                        {
                            priceB=priceB*((100-rand()%30)/100.0);
                        }
                        else
                        {
                            priceB=priceB*((100+rand()%43)/100.0);
                        }
                        if(cash<=0)
                        {
                            if(GameEnd()!=CONTINUE_GAME)
                            {
                                running=0;
                                skiprender=1;
                            }
                            else
                            {
                                ResetGameSettings();
                            }
                        }
                        update=1;
                    }
                    break;
                }
            }

            if(skiprender)
            {
                skiprender=0;
                continue;
            }

            rnd.clear();
            rnd.copyTo(t,r);

            sprintf(buff,"%d",cash);
            Texture tcash=font.renderText(rnd,buff,RGBA(255,255,255,0));
            rnd.copyTo(tcash,r9);

            sprintf(buff,"%d",day);
            Texture tday=font.renderText(rnd,buff,RGBA(0x33,0xcc,0x33,0));
            rnd.copyTo(tday,r10);

            sprintf(buff,"%s: %d",getstr(10),priceA);
            Texture tpa=font.renderText(rnd,buff,[&]()->RGBA
            {
                if(lastpriceA<priceA) return RGBA(255,0,0,0);
                else if(lastpriceA>priceA) return RGBA(0,255,0,0);
                else return RGBA(255,255,255,0);
            }());
            rnd.copyTo(tpa,r11);

            sprintf(buff,"%s: %d",getstr(11),priceB);
            Texture tpb=font.renderText(rnd,buff,[&]()->RGBA
            {
                if(lastpriceB<priceB) return RGBA(255,0,0,0);
                else if(lastpriceB>priceB) return RGBA(0,255,0,0);
                else return RGBA(255,255,255,0);
            }());
            rnd.copyTo(tpb,r12);

            sprintf(buff,"%s: %d",getstr(12),haveA);
            Texture hA=font.renderText(rnd,buff,RGBA(255,255,255,0));
            rnd.copyTo(hA,r13);

            sprintf(buff,"%s: %d",getstr(13),haveB);
            Texture hB=font.renderText(rnd,buff,RGBA(255,255,255,0));
            rnd.copyTo(hB,r14);

            RGBA oc=rnd.getColor();
            rnd.setColor(RGBA(255,0,0,0));
            rnd.fillRect(r2);
            rnd.fillRect(r3);

            rnd.setColor(RGBA(0,255,0,0));
            rnd.fillRect(r4);
            rnd.fillRect(r5);

            rnd.setColor(RGBA(0,0,255,0));
            rnd.fillRect(r6);
            rnd.fillRect(r7);
            rnd.setColor(oc);

            rnd.copyTo(t2,r2);
            rnd.copyTo(t3,r3);
            rnd.copyTo(t4,r4);
            rnd.copyTo(t5,r5);
            rnd.copyTo(t6,r6);
            rnd.copyTo(t7,r7);

            rnd.update();
            update=0;
        }
    }
}

