#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <gtk/gtk.h>
#include <cairo.h>
#include <vector>
#include "person.h"
#include "shared.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 750

typedef int (*simulator_func_t)();


int open_window(simulator_func_t simulator_func, int area_size);

void refresh_window(std::vector<Person *> *people);

static void close_window();

static void clear_surface();

static gboolean configure_event(GtkWidget *widget, GdkEventConfigure *event, gpointer data);

static gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer data);

static void activate(GtkApplication *application, gpointer data);

void draw_person(cairo_t *cr, GtkWidget *widget, Person *p);
