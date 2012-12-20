/*
 * icon.h
 *
 * Copyright (C) 1995-2001 Kenichi Kourai
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with qvwm; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef _ICON_H_
#define _ICON_H_

#include "lib/Component.h"
#include "lib/misc.h"
#include "lib/util.h"
#include "lib/list.h"
#include "desktop/iconmenu.h"
#include "lib/Menu.h"

class QvImage;
class Tooltip;

/*
 * Icon class
 */
class Icon : public Component {
private:
  Window frame;			// frame window for image
  Window text;			// text window for name
  Window wrap;			// window accepting events around icon
  Rect rc;			// position and size of icon
  Rect rcVirt;			// the same in virtual coordinates
  QvImage* img;			// icon image
  char* name;			// icon name
  char* exec;			// icon function (external)
  FuncNumber fn;		// icon function (built-in)
  Bool isBuiltin;		// icon type

  Time iconClickTime;		// click interval when icon executes function

  Rect rcText;			// size and position of icon text
  unsigned int textLines;	// number of icon text lines

  Pixmap shapeMask;
  GC gcShape;

  Pixmap pixIconBack;

  Window shadow;		// a window used when dragging this icon
  Bool dragging;		// a flag of dragging
  Bool enableDrop;

  Tooltip* toolTip;

public:
  enum { SFACTOR = 100000 };

  static Icon* focusIcon;               // icon with focus
  static QvImage* imgIcon;
  static IconMenu* ctrlMenu;            // popup menu on right-click

  static const char* const CLASS_ICON;

private:
  void init(char* iconname, int x, int y);
  void AlterIconName(char* iconname);
  void SetIconImage();

  void CreateShapedWindow();
  void CreateShapedShadowWindow();

  void DrawText(Drawable d, GC dGc, Rect rect);
  void procButton1Motion(const Point& ptRoot);

public:
  Icon(QvImage* image, char* iconname, char* execname, int x, int y);
  Icon(QvImage* image, char* iconname, FuncNumber func, int x, int y);
  ~Icon();

  Rect GetRect() const { return rc; }
  void SetRect(Rect rect) { rc = rect; }
  Rect GetVirtRect() const { return rcVirt; }
  void SetVirtRect(Rect rect) { rcVirt = rect; }

  Bool CheckMenuMapped() const { return ctrlMenu->CheckMapped(); }
  void UnmapMenu() { ctrlMenu->hide(); }
  char* GetExec() const { return exec; }
  FuncNumber GetFunc() const { return fn; }
  Bool IsBuiltin() const { return isBuiltin; }

  void SetFocus();
  void ResetFocus();

  void MapIcon();
  void UnmapIcon();
  void MoveIcon(const Point& pt);

  virtual void paint();
  virtual void onMouseEnter(const XCrossingEvent& ev);
  virtual void onMouseLeave(const XCrossingEvent& ev);
  virtual void onMouseMotion(const XMotionEvent& ev);
  virtual void onButtonPress(const XButtonEvent& ev);
  virtual void onDoubleClick(const XButtonEvent& ev);
  virtual void onButtonRelease(const XButtonEvent& ev);

public:
  static void Initialize();
};

#endif // _ICON_H_
