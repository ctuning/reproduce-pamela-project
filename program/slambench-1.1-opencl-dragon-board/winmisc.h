/*

 CK OpenME cTuning plugin

 cTuning plugin is used for fine-grain online application timing and tuning

 OpenME - Event-driven, plugin-based interactive interface to "open up" 
          any software (C/C++/Fortran/Java/PHP) and possibly connect it to cM

 Developer(s): (C) Grigori Fursin
 http://cTuning.org/lab/people/gfursin

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/

#ifndef __WINMISC_H_
#define __WINMISC_H_

void win_usleep(__int64 usec);
double win_tock(void);
bool win_is_dir(char* str);

#endif