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

#include <string.h>

#define MAX_STR_LEN_PLOT 256
#define MAX_DATA_FILES_PLOT 10

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
  char filename[MAX_DATA_FILES_PLOT][MAX_STR_LEN_PLOT];
  char plot_style[MAX_DATA_FILES_PLOT][MAX_STR_LEN_PLOT];
  int file_count;
} PlotFiles; // data file names like "data.dat"

typedef struct {
  Xrange x_range;
  Yrange y_range;
  Title title;
  Xlabel x_label;
  Ylabel y_label;
  PlotFiles plots;

} PlotAttr;

//

void set_xrange_plots(PlotAttr *gp, double xmin, double xmax) {
  gp->x_range.xmin = xmin;
  gp->x_range.xmax = xmax;
  gp->x_range.is_set = 1;
};

void set_yrange_plots(PlotAttr *gp, double ymin, double ymax) {
  gp->y_range.ymin = ymin;
  gp->y_range.ymax = ymax;
  gp->y_range.is_set = 1;
}

void set_title_plots(PlotAttr *gp, const char *title) {
  strncpy(gp->title.title, title, MAX_STR_LEN_PLOT);
  gp->title.is_set = 1;
}

void set_xlabel_plots(PlotAttr *gp, const char *xlabel) {
  strncpy(gp->x_label.xlabel, xlabel, MAX_STR_LEN_PLOT);
  gp->x_label.is_set = 1;
}

void set_ylabel_plots(PlotAttr *gp, const char *ylabel) {
  strncpy(gp->y_label.ylabel, ylabel, MAX_STR_LEN_PLOT);
  gp->y_label.is_set = 1;
}

void add_plot(PlotAttr *gp, const char *filename, const char *style) {
  if (gp->plots.file_count < MAX_DATA_FILES_PLOT) {
    strncpy(gp->plots.filename[gp->plots.file_count], filename,
            MAX_STR_LEN_PLOT);
    strncpy(gp->plots.plot_style[gp->plots.file_count], style,
            MAX_STR_LEN_PLOT);
    gp->plots.file_count++;
  }
}
