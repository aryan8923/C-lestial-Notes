/*This file is part of C-lestial library
(https://github.com/aryan8923/C-lestial-Notes).

C-lestial library is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your option)
any later version.

C-lestial library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
details.

You should have received a copy of the GNU General Public License along with
C-lestial library. If not, see <https://www.gnu.org/licenses/>.'
*/

/* This file is a collection of functions and structs related to plotting and
 * visualising */

#ifndef PLOTS_H
#define PLOTS_H

#define MAX_STR_LEN_PLOT 256

typedef struct {
  double xmin, xmax;
  int is_set;
} Xrange;

typedef struct {
  double ymin, ymax;
  int is_set;
} Yrange;

typedef struct {
  char title[MAX_STR_LEN_PLOT];
  int is_set;
} Title;

typedef struct {
  char xlabel[MAX_STR_LEN_PLOT];
  int is_set;
} Xlabel;

typedef struct {
  char ylabel[MAX_STR_LEN_PLOT];
  int is_set;
} Ylabel;

typedef struct {
  Xrange x_range;
  Yrange y_range;
  Title title;
  Xlabel x_label;
  Ylabel y_label;

} PlotAttr;

void set_xrange_plots(PlotAttr *gp, double xmin, double xmax);
void set_yrange_plots(PlotAttr *gp, double ymin, double ymax);
void set_title_plots(PlotAttr *gp, const char *title);
void set_xlabel_plots(PlotAttr *gp, const char *xlabel);
void set_ylabel_plots(PlotAttr *gp, const char *ylabel);

#endif
