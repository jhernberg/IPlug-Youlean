/* 
    WDL - dlgitemborder.h
    Copyright (C) 1998-2003, Nullsoft Inc.
    Copyright (C) 2005 and later Cockos Incorporated

    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.


  This file provides code to aide in drawing additional borders in dialogs.

  */


#ifndef _WDL_DLGITEMBORDER_H_
#define _WDL_DLGITEMBORDER_H_

#define DCW_SUNKENBORDER 0x00010000
#define DCW_SUNKENBORDER_NOTOP 0x00020000
#define DCW_DIVIDER_VERT 0x00030000
#define DCW_DIVIDER_HORZ 0x00040000
#define DCW_HWND_FOLLOW  0x40000000

#ifndef WDL_DLGITEMBORDER_NOIMPL

static int RectInRect(RECT *rect1, RECT *rect2)
{ 
  // this has a bias towards true

  // this could probably be optimized a lot
  return ((rect1->top >= rect2->top && rect1->top <= rect2->bottom) ||
      (rect1->bottom >= rect2->top && rect1->bottom <= rect2->bottom) ||
      (rect2->top >= rect1->top && rect2->top <= rect1->bottom) ||
      (rect2->bottom >= rect1->top && rect2->bottom <= rect1->bottom)) // vertical intersect
      &&
      ((rect1->left >= rect2->left && rect1->left <= rect2->right) ||
      (rect1->right >= rect2->left && rect1->right <= rect2->right) ||
      (rect2->left >= rect1->left && rect2->left <= rect1->right) ||
      (rect2->right >= rect1->left && rect2->right <= rect1->right)) // horiz intersect
      ;
}

#ifdef _WIN32
static void Dlg_removeFromRgn(HRGN hrgn, int left, int top, int right, int bottom)
{
  HRGN rgn2=CreateRectRgn(left,top,right,bottom);
  CombineRgn(hrgn,hrgn,rgn2,RGN_DIFF);
  DeleteObject(rgn2);
}
#else 
#define Dlg_removeFromRgn(a,b,c,d,e)
#endif

static void Dlg_DrawChildWindowBorders(HWND hwndDlg, INT_PTR *tab, int tabsize, int (*GSC)(int)=0, PAINTSTRUCT *__use_ps=NULL
#ifdef WDL_DLGITEMBORDER_CUSTOMPARMS                                       
  , WDL_DLGITEMBORDER_CUSTOMPARMS
#endif
                                       
                                       )
{
  PAINTSTRUCT ps;
  if (!__use_ps) 
  {
    BeginPaint(hwndDlg,&ps);
    __use_ps=&ps;
  }

#ifdef _WIN32
  HRGN hrgn=NULL;
  if(__use_ps->fErase)
  {
    RECT r=__use_ps->rcPaint;
    hrgn=CreateRectRgn(r.left,r.top,r.right,r.bottom);
  }
#else
  int hrgn=0;
#endif

  HPEN pen=CreatePen(PS_SOLID,0,GSC?GSC(COLOR_3DHILIGHT):GetSysColor(COLOR_3DHILIGHT));
  HPEN pen2=CreatePen(PS_SOLID,0,GSC?GSC(COLOR_3DSHADOW):GetSysColor(COLOR_3DSHADOW));

  while (tabsize--)
  {
    RECT r;
    int a=(int)*tab++;
    if (a & DCW_HWND_FOLLOW)
    {
      a&=~DCW_HWND_FOLLOW;
      if (!tabsize) break;
      GetWindowRect((HWND)*tab++,&r);
      tabsize--;

      ScreenToClient(hwndDlg,(LPPOINT)&r);
      ScreenToClient(hwndDlg,((LPPOINT)&r)+1);
    }
    else
    {
      int sa=a&0xffff;
      if (sa == 0)
      {
        GetClientRect(hwndDlg,&r);
      }
      else
      {
        GetWindowRect(GetDlgItem(hwndDlg,sa),&r);

  #ifdef CUSTOM_CHILDWNDBORDERCODE
        CUSTOM_CHILDWNDBORDERCODE
  #endif
        ScreenToClient(hwndDlg,(LPPOINT)&r);
        ScreenToClient(hwndDlg,((LPPOINT)&r)+1);
      }
    }

    if (RectInRect(&__use_ps->rcPaint,&r)) 
    {
      if ((a & 0xffff0000) == DCW_SUNKENBORDER || (a&0xffff0000) == DCW_SUNKENBORDER_NOTOP)
      {
        MoveToEx(__use_ps->hdc,r.left-1,r.bottom,NULL);
        HGDIOBJ o=SelectObject(__use_ps->hdc,pen);
        LineTo(__use_ps->hdc,r.right,r.bottom);
        LineTo(__use_ps->hdc,r.right,r.top-1);
        SelectObject(__use_ps->hdc,pen2);
        if ((a&0xffff0000) == DCW_SUNKENBORDER_NOTOP)
          MoveToEx(__use_ps->hdc,r.left-1,r.top-1,NULL);
        else
          LineTo(__use_ps->hdc,r.left-1,r.top-1);
        LineTo(__use_ps->hdc,r.left-1,r.bottom);
        SelectObject(__use_ps->hdc,o);
        if(hrgn)
        {
          Dlg_removeFromRgn(hrgn,r.left,r.bottom,r.right,r.bottom+1);
          Dlg_removeFromRgn(hrgn,r.right,r.top,r.right+1,r.bottom);
          if ((a&0xffff0000) != DCW_SUNKENBORDER_NOTOP)
            Dlg_removeFromRgn(hrgn,r.left,r.top-1,r.right,r.top);
          Dlg_removeFromRgn(hrgn,r.left-1,r.top,r.left,r.bottom);
        }
      }
      else if ((a & 0xffff0000) == DCW_DIVIDER_VERT || (a & 0xffff0000) == DCW_DIVIDER_HORZ)
      {
        if ((a & 0xffff0000) == DCW_DIVIDER_VERT) // vertical
        {
          int left=r.left;
          HGDIOBJ o=SelectObject(__use_ps->hdc,pen2);
          MoveToEx(__use_ps->hdc,left,r.top,NULL);
          LineTo(__use_ps->hdc,left,r.bottom+1);
          SelectObject(__use_ps->hdc,pen);
          MoveToEx(__use_ps->hdc,left+1,r.top,NULL);
          LineTo(__use_ps->hdc,left+1,r.bottom+1);
          SelectObject(__use_ps->hdc,o);
          if(hrgn) Dlg_removeFromRgn(hrgn,left,r.top,left+2,r.bottom);
        }
        else // horiz
        {
          int top=r.top+1;
          HGDIOBJ o=SelectObject(__use_ps->hdc,pen2);
          MoveToEx(__use_ps->hdc,r.left,top,NULL);
          LineTo(__use_ps->hdc,r.right+1,top);
          SelectObject(__use_ps->hdc,pen);
          MoveToEx(__use_ps->hdc,r.left,top+1,NULL);
          LineTo(__use_ps->hdc,r.right+1,top+1);
          SelectObject(__use_ps->hdc,o);
          if(hrgn) Dlg_removeFromRgn(hrgn,r.left,top,r.right,top+2);
        }
      }
    }
  }

  DeleteObject(pen);
  DeleteObject(pen2);

#ifdef _WIN32
  if(hrgn) {
    //erase bkgnd while clipping out our own drawn stuff (for flickerless display)
#ifdef WDL_DLGITEMBORDER_CUSTOMBGCODE
    WDL_DLGITEMBORDER_CUSTOMBGCODE
#else
    HBRUSH b=CreateSolidBrush(GSC?GSC(COLOR_3DFACE):GetSysColor(COLOR_3DFACE));
    FillRgn(__use_ps->hdc,hrgn,b);
    DeleteObject(b);
#endif

    DeleteObject(hrgn);
  }
#endif
  if (__use_ps == &ps) EndPaint(hwndDlg,&ps);
}

#endif

#endif